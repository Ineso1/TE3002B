#ifndef CV_WRAPPER_H
#define CV_WRAPPER_H

#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include "lane_processing/lane_params.h"


cv::Mat crop_frame(
    cv::Mat& frame, 
    int y_start, 
    int height, 
    int width
);

cv::Mat crop_frame(
    cv::Mat& frame, 
    CropParams& crop
);

cv::Mat apply_gaussian_blur(cv::Mat& frame);

cv::Mat apply_otsu_threshold(cv::Mat& image);

cv::Mat apply_closing(
    cv::Mat& image, 
    cv::Size kernel_size, 
    int iterations
);

std::vector<cv::Vec4i> detect_lines_hough(
    cv::Mat& frame, 
    bool consider_x_axis
);

std::vector<cv::Vec4i> detect_lines_hough(cv::Mat& frame);

cv::Mat draw_hough_lines(
    cv::Mat& frame_src,
    const std::vector<cv::Vec<double, 4>>& lines,
    cv::Scalar color = cv::Scalar(0, 0, 255), 
    int thickness = 3
);

cv::Mat draw_hough_lines(
    cv::Mat& frame_src, 
    const cv::Vec<double, 4>& line, 
    cv::Scalar color = cv::Scalar(0, 0, 255), 
    int thickness = 3
);



#endif // CV_WRAPPER_H
