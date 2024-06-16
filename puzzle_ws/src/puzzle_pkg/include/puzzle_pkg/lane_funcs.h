#ifndef LANE_FUNCS_H
#define LANE_FUNCS_H

#include <algorithm>
#include <cmath>
#include <deque>
#include <limits>
#include <vector>
#include <unordered_map>
#include <numeric> 


#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/matx.hpp>

#include "puzzle_pkg/lane_params.h"

extern std::deque<std::pair<cv::Vec<double, 2>, cv::Vec<double, 2>>> lane_history;

double point_distance(const cv::Point2d& p1, const cv::Point2d& p2); 

std::vector<cv::Vec<double, 2>> group_similar_lines(
    const std::vector<cv::Vec<double, 4>>& lines, 
    double eps, 
    std::size_t minPts
);

double calculate_angle(const cv::Vec<double, 4>& line);

bool is_horizontal(const cv::Vec<double, 4>& line, double angle_threshold);

cv::Vec<double, 4> detect_cross_and_return_mean_line(const std::vector<cv::Vec<double, 4>>& lines, double centerX, double minWidth);

std::vector<cv::Vec<double, 2>> frame_relevant_points(cv::Mat& frame, cv::Vec<double, 2> average_center, bool& cross_line);
std::vector<cv::Vec<double, 2>> frame_relevant_points(cv::Mat& frame);

cv::Vec<double, 2> get_average_center(int frame_width, int frame_height);

cv::Vec<double, 2> linear_regression(const std::vector<double>& x, const std::vector<double>& y);

void extrapolate_and_update_lane_history();

double calculate_angle_error(
    cv::Vec<double, 4>& line, 
    int frame_width, 
    int frame_height
);

#endif // LANE_FUNCS_H