#define DEBUG_POSITION

#include <chrono>
#include <cmath>
#include <cstddef>
#include <memory>
#include <functional>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include "geometry_msgs/msg/pose2_d.hpp"


/*
    Just receibe the angular velocity from each motor and calculates the current position
    OK
*/

using namespace std::chrono_literals;

class Odometry : public rclcpp::Node {
public:
    Odometry() : 
        Node{"odometry"},
        clock_{std::chrono::system_clock::now()},
        dt_{0.0},
        next_position_{geometry_msgs::msg::Pose2D()}
    {
        this->declare_parameters<double>(
            "",
            {
                {"wheel_radius", 0.05},
                {"wheel_length", 0.19},
                {"position_x", 0.0},
                {"position_y", 0.0},
                {"position_theta", 0.0}
            }
        );
        wheel_radius_ = this->get_parameter("wheel_radius").as_double();
        wheel_length_ = this->get_parameter("wheel_length").as_double();
        position_x_ = this->get_parameter("position_x").as_double();
        position_y_ = this->get_parameter("position_y").as_double();
        position_theta_ = this->get_parameter("position_theta").as_double();

        rclcpp::QoS qos_profile(10);
        qos_profile.reliability(RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT);
        qos_profile.history(RMW_QOS_POLICY_HISTORY_KEEP_LAST);
        
        subscription_left_ = this->create_subscription<std_msgs::msg::Float32>(
            "/VelocityEncL",
            qos_profile,
            std::bind(&Odometry::subscription_left_callback, this, std::placeholders::_1)
        );
        subscription_right_ = this->create_subscription<std_msgs::msg::Float32>(
            "/VelocityEncR",
            qos_profile,
            std::bind(&Odometry::subscription_right_callback, this, std::placeholders::_1)
        );
        publisher_position_ = this->create_publisher<geometry_msgs::msg::Pose2D>(
            "/odom",
            10
        );
        timer_ = this->create_wall_timer(
            10ms,
            std::bind(&Odometry::publisher_position_callback, this)
        );
    }
private:
    void subscription_left_callback(const std_msgs::msg::Float32& angular_vel_l)
    {
        angular_vel_left_ = angular_vel_l.data;

        #ifdef DEBUG_TIME_STEP_ENCODERS
            RCLCPP_INFO(
                this->get_logger(),
                "Left Angular Velocity % g",
                angular_vel_l.data
            );
        #endif
    }
    void subscription_right_callback(const std_msgs::msg::Float32& angular_vel_r)
    {
        angular_vel_right_ = angular_vel_r.data;

        #ifdef DEBUG_TIME_STEP_ENCODERS
            RCLCPP_INFO(
                this->get_logger(),
                "Right Angular Velocity % g",
                angular_vel_r.data
            );
        #endif
    }

    void publisher_position_callback()
    {
        next_clock_ = std::chrono::system_clock::now();
        elapsed_ = next_clock_ - clock_;
        clock_ = next_clock_;
        dt_ = elapsed_.count();

        #ifdef DEBUG_TIME_STEP_ENCODERS
            RCLCPP_INFO(
                this->get_logger(),
                "Time Step: %g",
                dt_,
            );
        #endif

        next_position_.x = position_x_
            + (wheel_radius_/2.0)*(angular_vel_right_ + angular_vel_left_)*dt_*std::cos(position_theta_);
        next_position_.y = position_y_
            + (wheel_radius_/2.0)*(angular_vel_right_ + angular_vel_left_)*dt_*std::sin(position_theta_);
        next_position_.theta = position_theta_
            + (wheel_radius_/wheel_length_)*(angular_vel_right_ - angular_vel_left_)*dt_;

        #ifdef DEBUG_POSITION
            RCLCPP_INFO(
                this->get_logger(),
                "x: %g, y: %g, theta: %g",
                next_position_.x,
                next_position_.y,
                next_position_.theta
            );
        #endif

        publisher_position_->publish(next_position_);

        position_x_ = next_position_.x;
        position_y_ = next_position_.y;
        position_theta_ = next_position_.theta;
    }
    // Parameters
    double wheel_radius_;
    double wheel_length_;
    double position_x_;
    double position_y_;
    double position_theta_;

    // Time
    std::chrono::time_point<std::chrono::system_clock> clock_;
    std::chrono::time_point<std::chrono::system_clock> next_clock_;
    std::chrono::duration<double> elapsed_;
    double dt_;

    // Subscription
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr subscription_left_;
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr subscription_right_;
    double angular_vel_left_;
    double angular_vel_right_;

    // Publishing
    rclcpp::Publisher<geometry_msgs::msg::Pose2D>::SharedPtr publisher_position_;
    rclcpp::TimerBase::SharedPtr timer_;
    geometry_msgs::msg::Pose2D next_position_;
};

// Timer and differential time

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Odometry>());
    rclcpp::shutdown();
    return EXIT_SUCCESS;
}