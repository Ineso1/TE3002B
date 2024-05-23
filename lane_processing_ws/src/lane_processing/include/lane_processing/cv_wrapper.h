#ifndef CV_WRAPPER_H
#define CV_WRAPPER_H

#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include "lane_processing/lane_params.h"


cv::Mat crop_frame(cv::Mat& frame, int y_start, int height, int width);

cv::Mat crop_frame(cv::Mat& frame, CropParams& crop);

cv::Mat apply_gaussian_blur(cv::Mat& frame);

cv::Mat apply_otsu_threshold(cv::Mat& image);

cv::Mat apply_closing(cv::Mat& image, cv::Size kernel_size, int iterations);

std::vector<cv::Vec4i> detect_lines_hough(cv::Mat& frame);


#endif // CV_WRAPPER_H
