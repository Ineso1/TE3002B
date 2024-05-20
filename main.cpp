#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <string>

#include <opencv2/opencv.hpp>

// Draw a trapezoid
// Suppose grayscale
std::vector<cv::Point> DrawTrapezoid(
	cv::Mat& frame,
	const int height,
	const int b_width,
	const int t_width
) {
	const int rows = frame.rows;
	const int cols = frame.cols;

	cv::Point b_l((cols - b_width)/2, rows - 1);
	cv::Point b_r((cols + b_width)/2, rows - 1);
	cv::Point t_l((cols - t_width)/2, rows - height);
	cv::Point t_r((cols + t_width)/2, rows - height);

	std::vector<cv::Point> points{b_l, b_r, t_l, t_r};

	cv::polylines(frame, points, true, 255, 2);

	return points;
}

struct Config {
	double b_width{0.3};
	double t_width{0.3};
	double height{0.4};
};

std::pair<cv::Mat, cv::Point> trans_matrix(
	cv::Mat& frame,
	const int height,
	const int bottom_width,
	const int top_width,
	const Config& cartesian_config
) {
	std::vector<cv::Point> img_pts = DrawTrapezoid(frame, bottom_width, top_width, height);

	double h = cartesian_config.height;
	double w = cartesian_config.b_width;

	std::vector<cv::Point2d> des_points{
		{0, 0},
		{w*1'000, 0},
		{w*1'000, h*1'000},
		{0, h*1'000}
	};

	cv::Mat matrix = cv::getPerspectiveTransform(frame, des_points);

	return {matrix, {static_cast<int>(w)*1'000, static_cast<int>(h)*1'000}};
}

void perspective_trans(
	cv::Mat& frame,
	cv::Mat& matrix,
	
) {

}

int main(int argc, char* argv[])
{
	return EXIT_SUCCESS;
}
