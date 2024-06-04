//#define DEBUG_VIDEO
#include <chrono>
#include <cstdlib>
#include <functional>
#include <memory>
#include <string>
#include <thread>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"

#include <cv_bridge/cv_bridge.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

using namespace std::chrono_literals;

class Camera : public rclcpp::Node {
public:
    Camera()
        : Node { "camera" }
        , filename_{
            "nvarguscamerasrc sensor-id=0 ! "
            "video/x-raw(memory:NVMM), width=(int)1280, height=(int)720, framerate=30/1, format=(string)NV12 ! "
            "nvvidconv flip-method=2 ! "
            "video/x-raw, format=(string)BGRx ! "
            "videoconvert ! "
            "video/x-raw, format=(string)BGR ! appsink"
        }
        , cap_ {cv::VideoCapture(filename_, cv::CAP_GSTREAMER)}
        , frame_ {}
    {
        publisher_ = create_publisher<sensor_msgs::msg::Image>("camera/image_raw", 10);

        if (!cap_.isOpened()) {
            RCLCPP_ERROR(get_logger(), "Failed to open camera with GStreamer pipeline");
        }

        read_and_publish();
    }

private:
    void read_and_publish()
    {
        while (rclcpp::ok()) {
            cap_.read(frame_);
            if (!frame_.empty()) {
                img_msg_ = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", frame_).toImageMsg();
                publisher_->publish(*img_msg_);
                #ifdef DEBUG_VIDEO
                    RCLCPP_INFO(get_logger(), "Published video frame");
                #endif
            } else {
                RCLCPP_ERROR(get_logger(), "Failed to capture frame");
                std::this_thread::sleep_for(100ms);
            }
        }
        RCLCPP_INFO(get_logger(), "Releasing video capture");
        cap_.release();
    }
    
    std::string filename_;

    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;

    cv_bridge::CvImage bridge_;

    cv::VideoCapture cap_;
    cv::Mat frame_;

    sensor_msgs::msg::Image::SharedPtr img_msg_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Camera>());
    rclcpp::shutdown();
    return EXIT_SUCCESS;
}