#include "puzzle_pkg/perspective.h"


cv::Point2f* calculateTrapezoidPoints(cv::Mat& frame, const PerspectiveConfig& perspective_config) {
    static cv::Point2f points[4];
    int rows = frame.rows;
    int cols = frame.cols;

    points[0] = cv::Point2f((float)(cols / 2 - perspective_config.t_width / 2), (float)perspective_config.height);
    points[1] = cv::Point2f((float)(cols / 2 + perspective_config.t_width / 2), (float)perspective_config.height);
    points[2] = cv::Point2f((float)(cols / 2 + perspective_config.b_width / 2), (float)(rows - 1));
    points[3] = cv::Point2f((float)(cols / 2 - perspective_config.b_width / 2), (float)(rows - 1));

    #ifdef DRAW_TRAPEZOID
        std::vector<cv::Point> intPoints;
        for (const auto& p : points) {
            intPoints.push_back(cv::Point(cvRound(p.x), cvRound(p.y)));
        }
        cv::Scalar color = frame.channels() == 1 ? cv::Scalar(255) : cv::Scalar(0, 0, 255);
        cv::polylines(frame, std::vector<std::vector<cv::Point>>{intPoints}, true, color, 2);
    #endif

    return points;
}


std::pair<cv::Mat, cv::Size> trans_matrix(
    cv::Mat& frame,
	const PerspectiveConfig& perspective_config,
	const RealCartesianConfig& cartesian_config
) 
{
    cv::Point2f* img_pts = calculateTrapezoidPoints(frame, perspective_config);
    double h = cartesian_config.t_height;
    double w = cartesian_config.b_width;

    cv::Point2f des_points[4] = {
        cv::Point2f(    0.0     ,    0.0    ),
        cv::Point2f(  w * 1'000 ,    0.0    ),
        cv::Point2f(  w * 1'000 , h * 1'000 ),
        cv::Point2f(    0.0     , h * 1'000 )
    };

    cv::Mat matrix = cv::getPerspectiveTransform(img_pts, des_points);
    return {matrix, cv::Size(static_cast<int>(w * 1000), static_cast<int>(h * 1000))};
}



cv::Mat perspective_trans(
    cv::Mat& frame, 
    cv::Mat& matrix, 
    cv::Size size
) {
    cv::Mat output;
    cv::warpPerspective(frame, output, matrix, size);
    return output;
}