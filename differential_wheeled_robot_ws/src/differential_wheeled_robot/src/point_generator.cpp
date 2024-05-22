#include <chrono>
#include <cstdlib>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point.hpp"
#include "differential_wheeled_robot/msg/path.hpp"

using namespace std::chrono_literals;

class PointGenerator : public rclcpp::Node {
public:
    PointGenerator() :
        Node{"point_generator"},
        publish_once_{true},
        path_message_{differential_wheeled_robot::msg::Path()},
        point_message_{geometry_msgs::msg::Point()}
    {
        number_of_points_ = this->declare_parameter(
            "number_of_points",
            3
        );
        for (int i = 0; i != number_of_points_; ++i) {
            path_.push_back(
                declare_parameter("point" + std::to_string(i), std::vector<double>{0.0, 0.0, 0.0})
            );
        }
        publisher_ = this->create_publisher<differential_wheeled_robot::msg::Path>(
            "/path",
            10
        );
        timer_ = this->create_wall_timer(
            10ms,
            std::bind(&PointGenerator::point_generator_callback, this)
        );
    }
private:
    void point_generator_callback()
    {
        for (int i = 0; i != number_of_points_; ++i) {
            point_message_.x = path_[i][0];
            point_message_.y = path_[i][1];
            point_message_.z = path_[i][2];
            RCLCPP_INFO(
                this->get_logger(),
                "x: %g, y: %g, z: %g",
                point_message_.x,
                point_message_.y,
                point_message_.z
            );
            path_message_.data.push_back(point_message_);
        }
        if (publish_once_) {
            publisher_->publish(path_message_);
            publish_once_ = false;
        }
    }
    bool publish_once_;
    differential_wheeled_robot::msg::Path path_message_;
    geometry_msgs::msg::Point point_message_;
    int number_of_points_;
    std::vector<std::vector<double>> path_;
    rclcpp::Publisher<differential_wheeled_robot::msg::Path>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PointGenerator>());
    rclcpp::shutdown();
    return EXIT_SUCCESS;
}