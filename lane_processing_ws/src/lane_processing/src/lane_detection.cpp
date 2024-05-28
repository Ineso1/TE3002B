//#define LANE_VIEW
//#define COORDS_PRINT
//#define ANGLE_VIEW

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
#include "lane_processing/lane_funcs.h"

#include <deque>
#include <utility>
#include <functional>

const PerspectiveConfig PERSPECTIVE_CONFIG = {1086, 270, 200};
const RealCartesianConfig REAL_CARTESIAN_CONFIG = {0.3, 0.3, 0.4};
std::map<std::string, CropParams> CROP_PARAMS = {
    {"lane_detection_back", {0, 160, 35}},
    {"lane_detection_front", {35, 160, 35}},
    {"lane_detection", {0, 160, 70}},
    {"crossing_line_detection", {0, 160, 280}}
};
std::deque<std::pair<cv::Vec<double, 2>, cv::Vec<double, 2>>> lane_history;

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

        // Timers
        angle_timer_ = this->create_wall_timer(
            10ms,
            std::bind(&LaneProcessingNode::publish_angle, this)
        );

        distance_timer_ = this->create_wall_timer(
            10ms, 
            std::bind(&LaneProcessingNode::publish_distance, this)
        );
        
        #ifdef LANE_VIEW
            processed_image_publisher_ = this->create_publisher<sensor_msgs::msg::Image>("processed_image", 10);
        #endif

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

    #ifdef LANE_VIEW
        void publish_processed_image(const cv::Mat &frame) {
            cv_bridge::CvImage cv_image;
            cv_image.header.stamp = this->now();  
            cv_image.header.frame_id = "camera";

            if (frame.channels() == 3) {
                cv_image.encoding = "bgr8";  
            } else if (frame.channels() == 1) {
                cv_image.encoding = "mono8"; 
            } else {
                throw std::runtime_error("Unsupported image format");
            }

            cv_image.image = frame;

            sensor_msgs::msg::Image::SharedPtr msg = cv_image.toImageMsg();
            processed_image_publisher_->publish(*msg);
        }
    #endif

    double detect_lane_center(cv::Mat& frame)
    {
        CropParams crop_params_back = CROP_PARAMS["lane_detection_back"];
        CropParams crop_params_front = CROP_PARAMS["lane_detection_front"];
        CropParams crop_params = CROP_PARAMS["lane_detection"];

        std::vector<cv::Vec<double, 2>> grouped_centers_back;
        std::vector<cv::Vec<double, 2>> grouped_centers_front;

        cv::Mat cropped_back = crop_frame(frame, crop_params_back);
        cv::Mat cropped_front = crop_frame(frame, crop_params_front);
        cv::Mat cropped = crop_frame(frame, crop_params);

        int cropped_width = cropped.cols;
        int cropped_height = cropped.rows;

        grouped_centers_back = frame_relevant_points(cropped_back);
        //std::cout<<"BACK "<<grouped_centers_back.size()<<std::endl;

        grouped_centers_front = frame_relevant_points(cropped_front);
        //std::cout<<"FRONT "<<grouped_centers_front.size()<<std::endl;

        int cropped_back_width = cropped_back.cols;
        int cropped_back_height = cropped_back.rows;
        
        cv::Vec<double, 2> average_center = get_average_center(cropped_back_width, cropped_back_height);
        if (!lane_history.empty() && lane_history.size() >= 3) {
            lane_history.pop_front();
        }

        double min_distance = std::numeric_limits<double>::max();
        int min_index_back = -1;
        int min_index_front = -1;

        for (std::size_t i = 0; i < grouped_centers_back.size(); i++) {
            double distance = point_distance(cv::Point2d(grouped_centers_back[i][0], grouped_centers_back[i][1]), cv::Point2d(average_center[0], average_center[1]));
            if (distance < min_distance) {
                min_distance = distance;
                min_index_back = i;
            }        
        }

        min_distance = std::numeric_limits<double>::max();
        for (std::size_t i = 0; i < grouped_centers_front.size(); i++) {
            double distance = point_distance(cv::Point2d(grouped_centers_front[i][0], grouped_centers_front[i][1]), cv::Point2d(average_center[0], average_center[1]));
            if (distance < min_distance) {
                min_distance = distance;
                min_index_front = i;
            }
        }

        cv::Vec<double, 2> selected_center_back;
        cv::Vec<double, 2> selected_center_front;
        double mean_front_point_x = 0.0, mean_front_point_y = 0.0;
        double mean_back_point_x = 0.0, mean_back_point_y = 0.0;

        if (min_index_back != -1 && min_index_front != -1) {
            selected_center_back = grouped_centers_back[min_index_back];
            selected_center_front = grouped_centers_front[min_index_front];
            selected_center_back[1] +=  crop_params_front.y_start;

            if (!lane_history.empty()) {

                int history_count = lane_history.size();

                for (int i = 0; i < history_count; i++) {
                    mean_back_point_x += lane_history[i].first[0];
                    mean_back_point_y += lane_history[i].first[1];
                    mean_front_point_x += lane_history[i].second[0];
                    mean_front_point_y += lane_history[i].second[1];
                }

                history_count += 1;
                mean_back_point_y = (mean_back_point_y + selected_center_back[1]) / history_count;
                mean_back_point_x = (mean_back_point_x + selected_center_back[0]) / history_count;
                mean_front_point_x = (mean_front_point_x + selected_center_front[0]) / history_count;
                mean_front_point_y = (mean_front_point_y + selected_center_front[1]) / history_count;
                
            }
            else{
                mean_back_point_y = selected_center_back[1];
                mean_back_point_x = selected_center_back[0];
                mean_front_point_x = selected_center_front[0];
                mean_front_point_y = selected_center_front[1];
            }
            
            lane_history.push_back({{mean_back_point_x, mean_back_point_y}, {mean_front_point_x, mean_front_point_y}});
        }
        else if (min_index_back != -1 ) {
            /*Handle*/
        }
        else if(min_index_front != -1) {
            /*Handle*/
        }
        else{
            extrapolate_and_update_lane_history();
        }
        
    
        std::pair<cv::Vec<double, 2>, cv::Vec<double, 2>> last_line = lane_history.back();
        cv::Vec<double, 4> selected_line_frame = {last_line.first[0] , last_line.first[1], last_line.second[0], last_line.second[1]};        

        #ifdef COORDS_PRINT
            std::cout<<"this sht "<< last_line.first[0] << " , " << last_line.first[1] << " , \t" << last_line.second[0] << " , " << last_line.second[1] << std::endl; 
        #endif

        #ifdef LANE_VIEW
            cv::Mat line_frame = draw_hough_lines(cropped, selected_line_frame, cv::Scalar(0, 255, 0), 2);
            cv::Vec<double, 4> angle_line = { cropped_width/2 , cropped_height, last_line.second[0], last_line.second[1]};
            line_frame = draw_hough_lines(line_frame, angle_line, cv::Scalar(0, 255, 0), 2);
            publish_processed_image(line_frame);
        #endif

        double angle_error = calculate_angle_error(selected_line_frame, cropped_width, cropped_height);
        #ifdef ANGLE_VIEW
            std::cout << "Angle " << angle_error << std::endl;
        #endif

        // Bullsht

        return angle_error; // Dumb return as FERCHOOOOOOOOOOOO
    }

    double process_frame(cv::Mat &frame) {
        std::pair<cv::Mat, cv::Size> transform_data = trans_matrix(frame, PERSPECTIVE_CONFIG, REAL_CARTESIAN_CONFIG);
        cv::Mat transformed = perspective_trans(frame, transform_data.first, transform_data.second);
        
        CropParams crop_params = CROP_PARAMS["crossing_line_detection"];
        
        cv::Mat cropped_frame = crop_frame(transformed, crop_params);
        cv::Mat blurred = apply_gaussian_blur(cropped_frame);
        cv::Mat closed = apply_closing(blurred, cv::Size(5, 5), 3);
        cv::Mat thresholded = apply_otsu_threshold(closed);
        double error = detect_lane_center(thresholded);

        return error;  // Dummy return // FERCHOOOO
    }

    double last_angle_;
    double last_distance_;
    std::deque<double> lane_history_;

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscription_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr angle_publisher_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr distance_publisher_;
    rclcpp::TimerBase::SharedPtr angle_timer_;
    rclcpp::TimerBase::SharedPtr distance_timer_;
    #ifdef LANE_VIEW
        rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr processed_image_publisher_;
    #endif
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LaneProcessingNode>());
    rclcpp::shutdown();
    return 0;
}