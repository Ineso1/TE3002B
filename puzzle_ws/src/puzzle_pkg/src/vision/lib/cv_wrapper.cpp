#include "puzzle_pkg/cv_wrapper.h"


cv::Mat crop_frame(cv::Mat& frame, int y_start, int height, int width) {
    int frame_width = frame.cols;
    int x_start = std::max(0, frame_width / 2 - width / 2);
    cv::Rect roi(x_start, y_start, width, height);
    return cv::Mat(frame, roi);
}

cv::Mat crop_frame(cv::Mat& frame, CropParams& crop) {
    int frame_height = frame.rows;
    int frame_width = frame.cols;
    int x_start = std::max(0, frame_width / 2 - crop.width / 2);
    int y_start = frame_height - crop.height - crop.y_start;
    y_start = std::max(0, y_start);
    cv::Rect roi(x_start, y_start, crop.width, crop.height);
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

cv::Mat apply_closing(
    cv::Mat& image, 
    cv::Size kernel_size, 
    int iterations
) {
    if (image.empty()) {
        throw std::runtime_error("Input image is empty.");
    }
    if (kernel_size.width <= 0 || kernel_size.height <= 0) {
        throw std::runtime_error("Kernel size must be positive.");
    }
    if (iterations < 0) {
        throw std::runtime_error("Iterations cannot be negative.");
    }

    cv::Mat closed_image;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, kernel_size);
    cv::morphologyEx(image, closed_image, cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), iterations);

    if (closed_image.empty()) {
        throw std::runtime_error("Closed image was not created successfully.");
    }

    return closed_image;
}


std::vector<cv::Vec4i> detect_lines_hough(
    cv::Mat& frame, 
    bool consider_x_axis
) {

    cv::Mat gray;
    if (frame.channels() == 3) {
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    } else {
        gray = frame;
    }

    int rho = 1;
    double theta = CV_PI / 180;  // dont know XD
    int threshold = 40;
    int max_line_length = 25;   // Need to adjust in case of something happen 
    int max_line_gap = 15;

    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(gray, lines, rho, theta, threshold, max_line_length, max_line_gap);

    std::vector<cv::Vec4i> filtered_lines;
    double angle_threshold = CV_PI / 4;  // 45 degrees

    for (const auto& line : lines) {
        int x1 = line[0];
        int y1 = line[1];
        int x2 = line[2];
        int y2 = line[3];

        // Filters based on the slope of each line detected
        // Filter if horizontal or vertical
        double line_angle = std::atan2(static_cast<double>(y2 - y1), static_cast<double>(x2 - x1));

        // Normalize the angle to be within the range [0, PI] as allways
        if (line_angle < 0) line_angle += CV_PI;

        if (consider_x_axis) {
            if (std::abs(line_angle) < angle_threshold || std::abs(line_angle - CV_PI) < angle_threshold) {
                filtered_lines.push_back(line);
            }
        } else {
            if (std::abs(line_angle - CV_PI/2) < angle_threshold) {
                filtered_lines.push_back(line);
            }
        }
    }

    return filtered_lines;
}



std::vector<cv::Vec4i> detect_lines_hough(cv::Mat& frame) {
    cv::Mat gray;
    if (frame.channels() == 3) {
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    } else {
        gray = frame;
    }

    int rho = 1;  
    double theta = CV_PI / 180; 
    int threshold = 40;
    int max_line_length = 25;
    int max_line_gap = 20;

    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(gray, lines, rho, theta, threshold, max_line_length, max_line_gap);
    return lines;
}


cv::Mat draw_hough_lines(cv::Mat& frame_src, const std::vector<cv::Vec<double, 4>>& lines, cv::Scalar color, int thickness) {
    cv::Mat color_frame;
    if (frame_src.channels() == 1) {
        cv::cvtColor(frame_src, color_frame, cv::COLOR_GRAY2BGR);
    } else {
        color_frame = frame_src.clone();
    }

    for (const auto& line : lines) {
        cv::Point p1(cvRound(line[0]), cvRound(line[1]));
        cv::Point p2(cvRound(line[2]), cvRound(line[3]));
        cv::line(color_frame, p1, p2, color, thickness);
    }

    return color_frame;
}


cv::Mat draw_hough_lines(cv::Mat& frame_src, const cv::Vec<double, 4>& line, cv::Scalar color, int thickness) {
    cv::Mat color_frame;
    if (frame_src.channels() == 1) {
        cv::cvtColor(frame_src, color_frame, cv::COLOR_GRAY2BGR);
    } else {
        color_frame = frame_src.clone();
    }

    cv::Point p1(cvRound(line[0]), cvRound(line[1]));
    cv::Point p2(cvRound(line[2]), cvRound(line[3]));
    cv::line(color_frame, p1, p2, color, thickness);

    return color_frame;
}