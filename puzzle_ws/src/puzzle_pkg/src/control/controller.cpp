/*****************************
    DEBUG MSGS DEFINITION
******************************/

//#define DEBUG_ERRORS
//#define DEBUG_ODOMETRY
//#define DEBUG_CONTROL
//#define DEBUG_ACT
//#define DEBUG_STATE
//#define DEBUG_POS_ERROR

#define DEBUG_POS_CONTROL


/*****************************
    INCLUDES
******************************/
#include <array>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <memory>
#include <vector>
#include <cmath>

#include <iostream>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "geometry_msgs/msg/pose2_d.hpp"
#include "std_msgs/msg/string.hpp"
#include "puzzle_pkg/msg/diff_error.hpp"
#include "std_msgs/msg/int32.hpp"

using namespace std::chrono_literals;

enum class State {
    Init = 0,
    Idle = 1,
    Stop = 2,
    Slow = 3,
    TurnLeft = 4,
    TurnRight = 5
};

enum class ControlManage {
    Stop,
    Forward,
    Slow,
    TurnLeft,
    TurnRight,
    Idle
};

enum class ControlType {
    Line,
    Position
};

class Controller : public rclcpp::Node
{
public:
    Controller() :
        Node{"controller"},
        odom_({}),
        errors_{},
        current_state_(State::Idle),
        last_processed_state_(State::Init),
        error_angle_(0.0),
        error_angle_integral_(0.0),
        error_distance_(0.0),
        cross_walk_(false),
        target_point_({0.0, 0.0}),
        act_(0.0),
        target_angle_(0.0),
        angular_vel_(0.0),
        linear_vel_(0.0),
        control_manage_(ControlManage::Idle),
        control_type_(ControlType::Line),
        counter_(0),
        busy_(0),
        vel_message_(geometry_msgs::msg::Twist())
    {
        this->declare_parameters<double>(
            "",
            {
                {"error_threshold_dis", 0.1},
                {"error_threshold_ang", 0.3},
                {"angular_vel_max", 0.4},
                {"linear_vel_max", 0.4},
                {"kp_distance", 0.5},
                {"kp_angle", 0.15},
                {"ki_angle", -0.03},
                {"ke_act", 50.0},
                {"angle_sensitivity", 30.0}
            }
        );

        rclcpp::QoS qos_settings(10);  // Adjust buffer size as needed //before 10
        qos_settings.reliability(RMW_QOS_POLICY_RELIABILITY_RELIABLE);
        qos_settings.durability(RMW_QOS_POLICY_DURABILITY_VOLATILE);
        
        subscription_errors_ = this->create_subscription<puzzle_pkg::msg::DiffError>(
            "/errors",
            10,
            std::bind(&Controller::errors_callback, this, std::placeholders::_1)
        );
        
        subscription_odom_ = this->create_subscription<geometry_msgs::msg::Pose2D>(
            "/odom",
            10,
            std::bind(&Controller::odom_callback, this, std::placeholders::_1)
        );
        
        subscription_state_ = this->create_subscription<std_msgs::msg::Int32>(
            "/current_state",
            qos_settings,
            std::bind(&Controller::state_callback, this, std::placeholders::_1)
        );
        
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
        
        timer_ = this->create_wall_timer(
            10ms,
            std::bind(&Controller::controller_callback, this)
        );

        busy_ = false;
        
        RCLCPP_INFO(
            this->get_logger(),
            "Controller node running"
        );
    }
private:
    
    void errors_callback(const puzzle_pkg::msg::DiffError& errors)
    {
        errors_ = errors;

        if(errors_.error_dist > 0){

            cross_walk_ = true;
            counter_ ++;
        }
        else{
            cross_walk_ = false;
        }

        #ifdef DEBUG_ERRORS
            RCLCPP_INFO(
                this->get_logger(),
                "angle_error: %g, distance_error: %g",
                errors_.error_ang,
                errors_.error_dist
            );
        #endif        
    }

    void odom_callback(const geometry_msgs::msg::Pose2D& odom)
    {
        odom_[0] = odom.x;
        odom_[1] = odom.y;
        odom_[2] = odom.theta;

        #ifdef DEBUG_ODOMETRY
            RCLCPP_INFO(
                this->get_logger(),
                "x: %g, y: %g, theta: %g",
                odom_[0],
                odom_[1],
                odom_[2]
            );
        #endif
    }

    void state_callback(const std_msgs::msg::Int32::SharedPtr msg)
    {   
        current_state_ = static_cast<State>(msg->data);
        if(last_processed_state_ != current_state_){
            last_processed_state_ = current_state_;
            RCLCPP_INFO(this->get_logger(), "change");
        }

    }

    void calculate_translation(double x, double y){
        double dx = x * cos(odom_[2]) - y * sin(odom_[2]);
        double dy = x * sin(odom_[2]) + y * cos(odom_[2]);
        target_point_[0] = odom_[0] + dx;
        target_point_[1] = odom_[1] + dy;

        #ifdef DEBUG_POS_CONTROL
            RCLCPP_INFO(this->get_logger(), "cx: %g,\tcy: %g", odom_[0], odom_[1]);
            RCLCPP_INFO(this->get_logger(), "tx: %g,\tty: %g", target_point_[0], target_point_[1]);
        #endif
    }

    void select_control() {
        if(!busy_){
            switch (current_state_) {
                case State::Init:
                        RCLCPP_INFO(this->get_logger(), "Idle");
                        control_type_ = ControlType::Line;
                        control_manage_ = ControlManage::Stop;
                    break;
                    
                case State::Idle:
                    if (cross_walk_) {
                        RCLCPP_INFO(this->get_logger(), "Cross walk Idle");
                        // Pasados
                        if(last_processed_state_ == State::Idle){
                            RCLCPP_INFO(this->get_logger(), "Idle xd");
                            control_manage_ = ControlManage::Forward;
                            control_type_ = ControlType::Position;
                            calculate_translation(0.65, 0.0);
                        }
                        else if(last_processed_state_ == State::TurnLeft){
                            RCLCPP_INFO(this->get_logger(), "Turn Left xd");
                            control_manage_ = ControlManage::TurnLeft;
                            control_type_ = ControlType::Position;
                            calculate_translation(0.4, 0.25);
                        }
                        else if(last_processed_state_ == State::TurnRight){
                            RCLCPP_INFO(this->get_logger(), "Turn Right xd");
                            control_manage_ = ControlManage::TurnRight;
                            control_type_ = ControlType::Position;
                            calculate_translation(0.4, -0.25);
                        }
                        else{
                            control_manage_ = ControlManage::Forward;
                            control_type_ = ControlType::Position;
                            RCLCPP_INFO(this->get_logger(), "Idle xd");
                            calculate_translation(0.65, 0.0);
                        }

                    } else {
                        RCLCPP_INFO(this->get_logger(), "Idle");
                        control_type_ = ControlType::Line;
                        control_manage_ = ControlManage::Idle;
                    }
                    break;

                case State::Stop:
                    if (cross_walk_) {
                        RCLCPP_INFO(this->get_logger(), "Cross walk Stop ");
                        control_manage_ = ControlManage::Stop;
                        control_type_ = ControlType::Line;
                    } else {
                        RCLCPP_INFO(this->get_logger(), "Stop ");
                        control_manage_ = ControlManage::Stop;
                        control_type_ = ControlType::Line;
                    }
                    break;

                case State::Slow:

                    RCLCPP_INFO(this->get_logger(), "Slow ");
                    control_manage_ = ControlManage::Slow;
                    control_type_ = ControlType::Line;
                    break;

                case State::TurnLeft:

                    if (cross_walk_) {
                        RCLCPP_INFO(this->get_logger(), "Cross walk TurnLeft ");
                        control_manage_ = ControlManage::TurnLeft;
                        control_type_ = ControlType::Position;
                        calculate_translation(0.4, 0.25);

                    } else {
                        RCLCPP_INFO(this->get_logger(), "TurnLeft ");
                        control_manage_ = ControlManage::TurnLeft;
                        control_type_ = ControlType::Line;
                    }
                    break;

                case State::TurnRight:

                    if (cross_walk_) {
                        RCLCPP_INFO(this->get_logger(), "Cross walk TurnRight ");
                        control_manage_ = ControlManage::TurnRight;
                        control_type_ = ControlType::Position;
                        calculate_translation(0.4, -0.25);
                    } else {
                        RCLCPP_INFO(this->get_logger(), "TurnRight ");
                        control_manage_ = ControlManage::TurnRight;
                        control_type_ = ControlType::Line;
                    }
                    break;

                default:
                    RCLCPP_INFO(this->get_logger(), "Unhandled state");
                    break;
            }
        }

    }

    void line_control() {
        double error_threshold_ang = get_parameter("error_threshold_ang").as_double();
        double angular_vel_max = get_parameter("angular_vel_max").as_double();
        double linear_vel_max = get_parameter("linear_vel_max").as_double();

        double kp_angle = get_parameter("kp_angle").as_double();
        double ki_angle = get_parameter("ki_angle").as_double();
        double ke_act = get_parameter("ke_act").as_double();
        double angle_sensitivity = get_parameter("angle_sensitivity").as_double();

        error_angle_ = errors_.error_ang;
        error_distance_ = errors_.error_dist;

        if (std::abs(error_angle_) < error_threshold_ang) {
            angular_vel_ = 0;
        } else {
            angular_vel_ = -(kp_angle * 0.8) * error_angle_ + ki_angle * error_angle_integral_;
            if (angular_vel_ >= angular_vel_max) {
                angular_vel_ = angular_vel_max;
            } else if (angular_vel_ <= -angular_vel_max) {
                angular_vel_ = -angular_vel_max;
            }
        }

        act_ = - (std::tanh(ke_act * (std::abs(error_angle_) - M_PI / angle_sensitivity)) - 1) / 2;

        #ifdef DEBUG_ACT
        RCLCPP_INFO(this->get_logger(), "act: %g", act_);
        #endif

        linear_vel_ = linear_vel_max * act_;
        if (control_manage_ == ControlManage::Slow) {
            linear_vel_ *= 0.3;
        } else if (control_manage_ == ControlManage::Stop) {
            linear_vel_ = 0.0;
            angular_vel_ = 0.0;
        }

        vel_message_.linear.x = linear_vel_;
        vel_message_.angular.z = -angular_vel_;

        #ifdef DEBUG_CONTROL
            RCLCPP_INFO(this->get_logger(), "Linear vel: %g, Angular vel: %g, Error distance: %g, Error angular: %g", linear_vel_, angular_vel_, error_distance_, error_angle_);
        #endif

        publisher_->publish(vel_message_);
    }

    void pos_control() {
        
        busy_ = true;

        double error_threshold_dis = get_parameter("error_threshold_dis").as_double();
        double error_threshold_ang = get_parameter("error_threshold_ang").as_double();
        double angular_vel_max = get_parameter("angular_vel_max").as_double();
        double linear_vel_max = get_parameter("linear_vel_max").as_double();

        double kp_angle = get_parameter("kp_angle").as_double();
        double ki_angle = get_parameter("ki_angle").as_double();
        double ke_act = get_parameter("ke_act").as_double();
        double kp_distance = get_parameter("kp_distance").as_double();
        double angle_sensitivity = get_parameter("angle_sensitivity").as_double();

        target_angle_ = std::atan2(target_point_[1] - odom_[1], target_point_[0] - odom_[0]);

        //error_angle_ = odom_[2] - target_angle_;
        error_angle_ = target_angle_ - odom_[2];

        if (error_angle_ > M_PI) {
            error_angle_ -= 2 * M_PI;
        } else if (error_angle_ < -M_PI) {
            error_angle_ += 2 * M_PI;
        }

        error_distance_ = std::sqrt(
            std::pow(odom_[0] - target_point_[0], 2) +
            std::pow(odom_[1] - target_point_[1], 2)
        );
        
        if (std::abs(error_angle_) < error_threshold_ang) {
            angular_vel_ = 0.0;
        } else {
            angular_vel_ = kp_angle * error_angle_ + ki_angle * error_angle_integral_;
            if (angular_vel_ >= angular_vel_max) {
                angular_vel_ = angular_vel_max;
            } else if (angular_vel_ <= -angular_vel_max) {
                angular_vel_ = -angular_vel_max;
            }
        }


        #ifdef DEBUG_ACT
        RCLCPP_INFO(this->get_logger(), "act: %g", act_);
        #endif

        if (error_distance_ < error_threshold_dis) {
            linear_vel_ = 0;
            busy_ = false;

            RCLCPP_INFO(this->get_logger(), "pos ok");
            control_manage_ = ControlManage::Idle;
            control_type_ = ControlType::Line;

        } else {
            act_ = (std::tanh(ke_act * (std::abs(error_angle_) - angle_sensitivity)) - 1) / 2;
            linear_vel_ = -act_ * linear_vel_max * std::tanh(kp_distance * (error_distance_ / linear_vel_max));
        }

        vel_message_.linear.x = linear_vel_;
        vel_message_.angular.z = angular_vel_;

        RCLCPP_INFO(this->get_logger(), "e_a: %g,\te_d: %g", error_angle_, error_distance_);


        #if defined(DEBUG_CONTROL)  || defined(DEBUG_POS_ERROR)
        RCLCPP_INFO(this->get_logger(), "Linear vel: %g, Angular vel: %g, Error distance: %g", linear_vel_, angular_vel_, error_distance_);
        RCLCPP_INFO(this->get_logger(), "tx: %g, ty: %g", target_point_[0], target_point_[1]);
        #endif

        publisher_->publish(vel_message_);
        
    }

    void controller_callback() {
        //RCLCPP_INFO(this->get_logger(), "C State: %d, P State: %d", static_cast<int>(current_state_), static_cast<int>(last_processed_state_));
        select_control();
        if (control_type_ == ControlType::Line) {
            //RCLCPP_INFO(this->get_logger(), "LINE");
            line_control();
        } else if (control_type_ == ControlType::Position) {
            //RCLCPP_INFO(this->get_logger(), "POS");
            pos_control();
        }
    }
    
    rclcpp::Subscription<geometry_msgs::msg::Pose2D>::SharedPtr subscription_odom_;
    rclcpp::Subscription<puzzle_pkg::msg::DiffError>::SharedPtr subscription_errors_;
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_state_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

    //make a diferent global variable to handle position errors and other line errors
    puzzle_pkg::msg::DiffError errors_;
    std::array<double, 3> odom_;

    State current_state_;
    State last_processed_state_; 

    // Errors
    double error_angle_;
    double error_angle_integral_;
    double error_distance_;
    bool cross_walk_;
    double target_point_ [2];

    // Targets
    double act_;
    double target_angle_;

    // Velocity vars
    double angular_vel_;
    double linear_vel_;

    int counter_;

    bool busy_;

    ControlManage control_manage_;
    ControlType control_type_;

    geometry_msgs::msg::Twist vel_message_;
    
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Controller>());
    rclcpp::shutdown();
    return EXIT_SUCCESS;
}