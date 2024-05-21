#include <opencv2/opencv.hpp>
#include "perspective.h"
#include "lane_params.h"
#include "cv_wrapper.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <VideoPath>\n";
        return -1;
    }

    cv::VideoCapture cap(argv[1]);
    if (!cap.isOpened()) {
        std::cerr << "Error opening video stream or file" << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        auto [matrix, size] = trans_matrix(frame, PERSPECTIVE_CONFIG, REAL_CARTESIAN_CONFIG);
        cv::Mat transformed = perspective_trans(frame, matrix, size);

        cv::Mat blurred = apply_gaussian_blur(transformed);
        cv::Mat thresholded = apply_otsu_threshold(blurred);
        cv::Mat closed = apply_closing(thresholded, cv::Size(5, 5), 3);
        std::vector<cv::Vec4i> lines = detect_lines_hough(closed);

        for (auto& line : lines) {
            cv::line(transformed, cv::Point(line[0], line[1]), cv::Point(line[2], line[3]), cv::Scalar(0, 255, 0), 2);
        }

        cv::imshow("Original", frame);
        cv::imshow("Transformed", transformed);  
        cv::imshow("Thresholded", thresholded); 

        if (cv::waitKey(30) >= 0) break;
    }
    cap.release();
    cv::destroyAllWindows();
    return 0;
}