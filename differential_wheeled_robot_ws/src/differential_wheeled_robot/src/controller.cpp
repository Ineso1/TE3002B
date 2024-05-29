/*****************************
    DEBUG MSGS DEFINITION
******************************/

//#define DEBUG_PATH_MANAGE
//#define DEBUG_ODOMETRY
#define DEBUG_CONTROL


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

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "geometry_msgs/msg/pose2_d.hpp"
#include "differential_wheeled_robot/msg/path.hpp"

using namespace std::chrono_literals;

class Controller : public rclcpp::Node
{
public:
    Controller() :
        Node{"controller"},
        path_{std::vector<std::array<double, 3>>{{0.0, 0.0, 0.0}}},
        odom_{std::array<double, 3>{}},
        point_counter_{0},
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
        subscription_path_ = this->create_subscription<differential_wheeled_robot::msg::Path>(
            "/path",
            10,
            std::bind(&Controller::path_callback, this, std::placeholders::_1)
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
    void path_callback(const differential_wheeled_robot::msg::Path& path)
    {
        std::array<double, 3> p_placeholder{};
        for (const geometry_msgs::msg::Point& p : path.data) {
            p_placeholder[0] = p.x;
            p_placeholder[1] = p.y;
            p_placeholder[2] = p.z;
            path_.push_back(p_placeholder);

            #ifdef DEBUG_PATH_MANAGE
                RCLCPP_INFO(
                    this->get_logger(),
                    "x: %g, y: %g, z: %g",
                    p_placeholder[0],
                    p_placeholder[1],
                    p_placeholder[2]
                );
            #endif
        }
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

        error_threshold_dis_ = get_parameter("error_threshold_dis").as_double();
        error_threshold_ang_ = get_parameter("error_threshold_ang").as_double();

        //target_point_ = path_[point_counter_];
        target_point_ = {0.0, 1.0, 0.0};

        if (
            (error_distance_ < error_threshold_dis_) &&
            (error_angle_ < error_threshold_ang_)
        ) {
            ++point_counter_;
        }

        target_angle_ = std::atan2(target_point_[1], target_point_[0]);
        if (target_angle_ < 0) {
            target_angle_ = 2*M_PI + target_angle_;
        }
        error_angle_ = odom_[2] - target_angle_;

        error_distance_ = std::sqrt(
            std::pow(odom_[0] - target_point_[0], 2) +
            std::pow(odom_[1] - target_point_[1], 2)
        );

        double angular_vel_max_ = get_parameter("angular_vel_max").as_double();
        double angular_gain_ = get_parameter("angular_gain").as_double();

        angular_vel_ = -angular_vel_max_*std::tanh(angular_gain_*(error_angle_/angular_vel_max_));

        double linear_vel_max_ = get_parameter("linear_vel_max").as_double();
        double linear_gain_ = get_parameter("linear_gain").as_double();

        linear_vel_ = linear_vel_max_*std::tanh(linear_gain_*(error_distance_/linear_vel_max_));

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
    rclcpp::Subscription<differential_wheeled_robot::msg::Path>::SharedPtr subscription_path_;

    std::vector<std::array<double, 3>> path_;
    std::array<double, 3> odom_;
    int point_counter_;
    std::array<double, 3> target_point_;

    double error_threshold_dis_;
    double error_threshold_ang_;

    double target_angle_;
    double error_angle_;
    double error_distance_;
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