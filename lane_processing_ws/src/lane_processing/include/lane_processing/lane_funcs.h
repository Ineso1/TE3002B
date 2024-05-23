#ifndef LANE_FUNCS_H
#define LANE_FUNCS_H

#include <algorithm>
#include <cmath>
#include <deque>
#include <limits>
#include <vector>

#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/matx.hpp>

#include "lane_processing/lane_params.h"

template<typename Type, std::size_t Index>
Type vector_sum(const std::vector<cv::Vec<Type, 6>>& vec)
{
    Type sum{0.0};
    for (const cv::Vec<Type, 6>& v : vec) {
        sum += v[Index];
    }
    return sum;
}

cv::Mat crop_frame(cv::Mat& frame, int y_start, int height, int width);

std::vector<cv::Vec4i> detect_lines_hough(cv::Mat& cropped_frame);

std::vector<cv::Vec4i> group_similar_lines(
    std::vector<cv::Vec4i>& lines,
    int distance_threshold = 10,
    double angle_threshold = M_PI/16,
    int iterations = 3,
    bool x_axis = true
);

cv::Vec<double, 4> select_relevant_line(
    std::vector<cv::Vec<double, 4>>& lines, cv::Vec<double, 4>& previous_line);

double calculate_angle_error(cv::Vec<double, 4>& line, int frame_width, int frame_height);

cv::Mat draw_hough_lines(
    cv::Mat& frame_src, std::vector<cv::Vec<double, 4>>& lines,
    cv::Scalar color = 255, int thickness = 2);

cv::Vec<double, 4> lane_history;

double detect_lane_center(cv::Mat& frame);

#endif // LANE_FUNCS_H