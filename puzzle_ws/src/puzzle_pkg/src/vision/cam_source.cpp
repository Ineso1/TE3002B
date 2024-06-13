#include <chrono>
#include <cstdlib>
#include <functional>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"

#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>

using namespace std::chrono_literals;

class Camera : public rclcpp::Node {
public:
    Camera()
        : Node("camera"),
          filename_{
            "nvarguscamerasrc sensor-id=0 ! "
            "video/x-raw(memory:NVMM), width=(int)854, height=(int)480, framerate=15/1, format=(string)NV12 ! "
            "nvvidconv flip-method=2 ! "
            "video/x-raw, format=(string)BGRx ! "
            "videoconvert ! "
            "video/x-raw, format=(string)BGR ! appsink"
          },
          cap_(cv::VideoCapture(filename_, cv::CAP_GSTREAMER)),
          frame_{}
    {
        image_publisher_ = create_publisher<sensor_msgs::msg::Image>("camera/image_raw", 10);
        compressed_publisher_ = create_publisher<sensor_msgs::msg::CompressedImage>("camera/image_compressed", 10);

        if (!cap_.isOpened()) {
            RCLCPP_ERROR(get_logger(), "Failed to open camera with GStreamer pipeline");
            rclcpp::shutdown();
        } else {
            read_and_publish();
        }
    }

private:
    void read_and_publish() {
        while (rclcpp::ok()) {
            cap_.read(frame_);
            if (!frame_.empty()) {
                // Publish raw image
                auto img_msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", frame_).toImageMsg();
                image_publisher_->publish(*img_msg);

                #ifdef DEBUG_VIDEO
                RCLCPP_INFO(get_logger(), "Published video frame");
                #endif

                // Publish compressed image
                std::vector<uint8_t> buffer;
                cv::imencode(".jpg", frame_, buffer);
                auto compressed_msg = std::make_shared<sensor_msgs::msg::CompressedImage>();
                compressed_msg->format = "jpeg";
                compressed_msg->data = std::move(buffer);
                compressed_publisher_->publish(*compressed_msg);
            } else {
                RCLCPP_ERROR(get_logger(), "Failed to capture frame");
                std::this_thread::sleep_for(100ms);
            }
        }
        RCLCPP_INFO(get_logger(), "Releasing video capture");
        cap_.release();
    }
    
    std::string filename_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_publisher_;
    rclcpp::Publisher<sensor_msgs::msg::CompressedImage>::SharedPtr compressed_publisher_;

    cv::VideoCapture cap_;
    cv::Mat frame_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto camera_node = std::make_shared<Camera>();
    rclcpp::spin(camera_node);
    rclcpp::shutdown();
    return EXIT_SUCCESS;
}