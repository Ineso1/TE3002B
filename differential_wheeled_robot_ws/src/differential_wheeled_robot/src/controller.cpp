/*****************************
    DEBUG MSGS DEFINITION
******************************/

//#define DEBUG_ERRORS
//#define DEBUG_ODOMETRY
//#define DEBUG_CONTROL


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

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "geometry_msgs/msg/pose2_d.hpp"
#include "differential_wheeled_robot/msg/diff_error.hpp"

using namespace std::chrono_literals;

class Controller : public rclcpp::Node
{
public:
    Controller() :
        Node{"controller"},
        errors_{differential_wheeled_robot::msg::DiffError{}},
        odom_{std::array<double, 3>{}},
        vel_message_{geometry_msgs::msg::Twist()}
    {
        this->declare_parameters<double>(
            "",
            {
                {"error_threshold_dis", 0.1},
                {"error_threshold_ang", 0.1},
                {"angular_vel_max", 0.2},
                {"angular_gain", 0.4},
                {"linear_vel_max", 1.0},
                {"linear_gain", 0.5}
            }
        );
        
        
        subscription_errors_ = this->create_subscription<differential_wheeled_robot::msg::DiffError>(
            "/errors",
            10,
            std::bind(&Controller::errors_callback, this, std::placeholders::_1)
        );
        subscription_odom_ = this->create_subscription<geometry_msgs::msg::Pose2D>(
            "/odom",
            10,
            std::bind(&Controller::odom_callback, this, std::placeholders::_1)
        );
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
        timer_ = this->create_wall_timer(
            10ms,
            std::bind(&Controller::controller_callback, this)
        );
        
        RCLCPP_INFO(
            this->get_logger(),
            "Controller node running"
        );
    }
private:
    
    void errors_callback(const differential_wheeled_robot::msg::DiffError& errors)
    {
        errors_ = errors;
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

    void controller_callback()
    {

        double error_threshold_dis_ = get_parameter("error_threshold_dis").as_double();
        double error_threshold_ang_ = get_parameter("error_threshold_ang").as_double();
        //double angular_vel_max_ = get_parameter("angular_vel_max").as_double();
        //double linear_vel_max_ = get_parameter("linear_vel_max").as_double();
        
        double kp_angle_ = get_parameter("kp_angle").as_double();
        double ki_angle_ = get_parameter("ki_angle").as_double();
        double ke_act_ = get_parameter("ke_act").as_double();
        //double kp_distance_ = get_parameter("kp_distance").as_double();

        error_angle_ = errors_.error_ang;
        error_distance_ = errors_.error_dist;


        if ( error_angle_ < error_threshold_ang_ ){
            angular_vel_ = 0;
        } else {
            angular_vel_ = -kp_angle_ * error_angle_ + ki_angle_ * error_angle_integral_;
            //Trim angular velocity to -angular_vel_max_ to angular_vel_max_
        }
        
        act_ = std::tanh(ke_act_ * std::abs( error_angle_ - M_PI / 45)) -1 ;

        if ( error_distance_ < error_threshold_dis_ ){
            linear_vel_ = 0;
        } else {
            linear_vel_ = 0.03 * act_;
            //linear_vel_ = linear_vel_max_ * std::tanh( kp_distance_ * (error_distance_/linear_vel_max_));
        }

        vel_message_.linear.x = linear_vel_;
        vel_message_.linear.y = 0.0;
        vel_message_.linear.z = 0.0;
        vel_message_.angular.x = 0.0;
        vel_message_.angular.y = 0.0;
        vel_message_.angular.z = angular_vel_;

        #ifdef DEBUG_CONTROL
            RCLCPP_INFO(
                this->get_logger(),
                "linear: %g, angular: %g, error distance %g",
                vel_message_.linear.x,
                vel_message_.angular.z,
                error_distance_
            );
        #endif

        publisher_->publish(vel_message_); 
        
    }
    
    rclcpp::Subscription<geometry_msgs::msg::Pose2D>::SharedPtr subscription_odom_;
    rclcpp::Subscription<differential_wheeled_robot::msg::DiffError>::SharedPtr subscription_errors_;

    differential_wheeled_robot::msg::DiffError errors_;
    std::array<double, 3> odom_;

    // Errors
    double error_angle_;
    double error_angle_integral_;
    double error_distance_;

    // Targets
    double act_;
    double target_angle_;

    // Velocity vars
    double angular_vel_;
    double linear_vel_;

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    geometry_msgs::msg::Twist vel_message_;
    
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Controller>());
    rclcpp::shutdown();
    return EXIT_SUCCESS;
}