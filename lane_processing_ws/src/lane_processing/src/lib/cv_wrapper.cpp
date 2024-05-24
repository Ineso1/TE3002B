#include "lane_processing/cv_wrapper.h"


cv::Mat crop_frame(cv::Mat& frame, int y_start, int height, int width) {
    //int frame_height = frame.rows;
    int frame_width = frame.cols;
    int x_start = std::max(0, frame_width / 2 - width / 2);
    cv::Rect roi(x_start, y_start, width, height);
    return cv::Mat(frame, roi);
}

cv::Mat crop_frame(cv::Mat& frame, CropParams& crop) {
    //int frame_height = frame.rows;
    int frame_width = frame.cols;
    int x_start = std::max(0, frame_width / 2 - crop.width / 2);
    cv::Rect roi(x_start, crop.y_start, crop.width, crop.height);
    return cv::Mat(frame, roi);
}

cv::Mat apply_gaussian_blur(cv::Mat& frame) {
    cv::Mat blurred_image;
    cv::GaussianBlur(frame, blurred_image, cv::Size(5, 5), 5);
    return blurred_image;
}

cv::Mat apply_otsu_threshold(cv::Mat& image) {
    cv::Mat gray_image;
    if (image.channels() == 3) {
        cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
    } else {
        gray_image = image.clone();
    }
    cv::Mat otsu_thresh_image;
    cv::threshold(gray_image, otsu_thresh_image, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::Mat inverted_image;
    cv::bitwise_not(otsu_thresh_image, inverted_image);
    return inverted_image;
}

cv::Mat apply_closing(cv::Mat& image, cv::Size kernel_size, int iterations) {
    cv::Mat closed_image;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, kernel_size);
    cv::morphologyEx(image, closed_image, cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), iterations);
    return closed_image;
}

std::vector<cv::Vec4i> detect_lines_hough(cv::Mat& frame)
{
    int rho = 1;
    int theta = CV_PI/180;
    int threshold = 40;
    int max_line_length = 25;
    int max_line_gap = 20;

    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(frame, lines, rho, theta, threshold, max_line_length, max_line_gap);
    return lines;
}
