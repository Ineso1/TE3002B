#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include <opencv2/opencv.hpp>
#include "lane_processing/lane_params.h"

#define DRAW_TRAPEZOID

cv::Point2f* calculateTrapezoidPoints(
    cv::Mat& frame, 
    const PerspectiveConfig& perspective_config
);

std::pair<cv::Mat, cv::Size> trans_matrix(cv::Mat& frame, 
    const PerspectiveConfig& perspective_config,
	const RealCartesianConfig& cartesian_config
);

cv::Mat perspective_trans(cv::Mat& frame, cv::Mat& matrix, cv::Size size);


#endif // PERSPECTIVE_H