#include "rclcpp/rclcpp.hpp"
#include "cv_bridge/cv_bridge.h"
#include "sensor_msgs/msg/image.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/string.hpp"
#include <opencv2/opencv.hpp>
#include <chrono>

#include "lane_processing/cv_wrapper.h"
#include "lane_processing/perspective.h"
#include "lane_processing/lane_params.h"
#include <deque>
#include <utility>
#include <functional>

const PerspectiveConfig PERSPECTIVE_CONFIG = {1086, 270, 200};
const RealCartesianConfig REAL_CARTESIAN_CONFIG = {0.3, 0.3, 0.4};
std::map<std::string, CropParams> CROP_PARAMS = {
    {"lane_detection", {0, 150, 60}},
    {"crossing_line_detection", {0, 150, 280}}
};

using namespace std::chrono_literals;

class LaneProcessingNode : public rclcpp::Node {
public:
    LaneProcessingNode() : 
        Node("lane_processing_node"), 
        last_angle_(0.0), 
        last_distance_(0.0) 
        {

        // Subscribe to camera image topic
        image_subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/camera/image_raw", 
            10, 
            std::bind(&LaneProcessingNode::image_callback, this, std::placeholders::_1)
        );

        // Publishers
        angle_publisher_ = this->create_publisher<std_msgs::msg::Float32>("angle_error", 10);
        distance_publisher_ = this->create_publisher<std_msgs::msg::Float32>("distance", 10);
        processed_image_publisher_ = this->create_publisher<sensor_msgs::msg::Image>("processed_image", 10);

        // Timers
        angle_timer_ = this->create_wall_timer(
            10ms,
            std::bind(&LaneProcessingNode::publish_angle, this)
        );

        distance_timer_ = this->create_wall_timer(
            10ms, 
            std::bind(&LaneProcessingNode::publish_distance, this)
        );

        RCLCPP_INFO(this->get_logger(), "Lane Processing Node has started :)");
    }

private:
    void image_callback(const sensor_msgs::msg::Image::SharedPtr msg) {
        cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        cv::Mat color_frame = cv_ptr->image;
        cv::Mat frame, fliped_frame;
        cv::cvtColor(color_frame, frame, cv::COLOR_BGR2GRAY);
        cv::flip(frame, fliped_frame, 0);

        double angle = process_frame(fliped_frame);
        last_angle_ = angle;

    }

    void publish_angle() {
        std_msgs::msg::Float32 angle_msg;
        angle_msg.data = last_angle_;
        angle_publisher_->publish(angle_msg);
    }

    void publish_distance() {
        std_msgs::msg::Float32 distance_msg;
        distance_msg.data = last_distance_; 
        distance_publisher_->publish(distance_msg);
    }

    void publish_processed_image(const cv::Mat &frame) {
        cv_bridge::CvImage cv_image;
        cv_image.header.stamp = this->now();
        cv_image.header.frame_id = "camera";
        cv_image.encoding = "mono8";
        cv_image.image = frame;

        sensor_msgs::msg::Image::SharedPtr msg = cv_image.toImageMsg();
        processed_image_publisher_->publish(*msg);
    }


    double process_frame(cv::Mat &frame) {
        std::pair<cv::Mat, cv::Size> transform_data = trans_matrix(frame, PERSPECTIVE_CONFIG, REAL_CARTESIAN_CONFIG);
        cv::Mat transformed = perspective_trans(frame, transform_data.first, transform_data.second);
        
        CropParams crop_params = CROP_PARAMS["crossing_line_detection"];
        
        cv::Mat cropped_frame = crop_frame(transformed, crop_params);
        cv::Mat blurred = apply_gaussian_blur(cropped_frame);
        cv::Mat closed = apply_closing(blurred, cv::Size(5, 5), 3);
        cv::Mat thresholded = apply_otsu_threshold(closed);
        publish_processed_image(thresholded);

        return 0.0;  // Dummy return // FERCHOOOO
    }

    double last_angle_;
    double last_distance_;
    std::deque<double> lane_history_;



    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscription_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr angle_publisher_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr distance_publisher_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr processed_image_publisher_;
    rclcpp::TimerBase::SharedPtr angle_timer_;
    rclcpp::TimerBase::SharedPtr distance_timer_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LaneProcessingNode>());
    rclcpp::shutdown();
    return 0;
}