#include "rclcpp/rclcpp.hpp"
#include "cv_bridge/cv_bridge.h"
#include "sensor_msgs/msg/image.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/string.hpp"
#include <opencv2/opencv.hpp>
#include <chrono>

#include "lane_detection/cv_wrapper.h"
#include "lane_detection/perspective.h"
#include "lane_detection/lane_params.h"
#include <deque>
#include <utility>

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
            std::chrono::milliseconds(10),
            std::bind(&LaneProcessingNode::publish_angle, this, 0.0)
        );

        distance_timer_ = this->create_wall_timer(
            std::chrono::milliseconds(10), 
            std::bind(&LaneProcessingNode::publish_distance, this, 0.0)
        );

        RCLCPP_INFO(this->get_logger(), "Lane Processing Node has started :)");
    }

private:
    void image_callback(const sensor_msgs::msg::Image::SharedPtr msg) {
        cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        cv::Mat color_frame = cv_ptr->image;
        cv::Mat frame;
        cv::cvtColor(color_frame, frame, cv::COLOR_BGR2GRAY);
        cv::flip(frame, frame, 1);

        double angle = process_frame(frame);
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
        //auto msg = cv_bridge::CvImage(std_msgs::msg::Header(), "mono8", frame).toImageMsg();
        //processed_image_publisher_->publish(msg);
    }


    double process_frame(cv::Mat &frame) {
        //std::pair<cv::Mat, cv::Size> transform_data = trans_matrix(frame, PERSPECTIVE_CONFIG, REAL_CARTESIAN_CONFIG);
        //cv::Mat transformed = perspective_trans(frame, transform_data.first, transform_data.second);
        
        //CropParams crop_params = CROP_PARAMS["lane_detection"];
        //cv::Mat cropped_frame = crop_frame(transformed, crop_params)
        //cv::Mat blurred = apply_gaussian_blur(cropped_frame);
        //cv::Mat thresholded = apply_otsu_threshold(blurred);
        //cv::Mat closed = apply_closing(thresholded, cv::Size(5, 5), 3);
        //publish_processed_image(frame);

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