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

extern cv::Vec<double, 4> lane_history;

struct Line {
    int x1, y1, x2, y2;
    double angle;
    double avgCoordinate;
};

template<typename Type, std::size_t Index>

Type vector_sum(const std::vector<cv::Vec<Type, 6>>& vec)
{
    Type sum{0.0};
    for (const cv::Vec<Type, 6>& v : vec) {
        sum += v[Index];
    }
    return sum;
}

cv::Vec4i average_lines(const std::vector<Line>& lines);

std::vector<cv::Vec4i> group_similar_lines(
    std::vector<cv::Vec4i>& lines,
    int distance_threshold = 10,
    double angle_threshold = M_PI/16,
    int iterations = 3,
    bool x_axis = true
);

cv::Vec4i select_relevant_line(
    std::vector<cv::Vec4i>& lines, 
    cv::Vec4i& previous_line
);

double calculate_angle_error(
    cv::Vec<double, 4>& line, 
    int frame_width, 
    int frame_height
);

cv::Mat draw_hough_lines(
    cv::Mat& frame_src, 
    const std::vector<cv::Vec4i>& lines,
    cv::Scalar color = cv::Scalar(255), 
    int thickness = 2
);


#endif // LANE_FUNCS_H