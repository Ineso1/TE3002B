#include "lane_processing/lane_funcs.h"

std::vector<cv::Vec4i> detect_lines_hough(cv::Mat& frame)
{
    int rho = 0;
    int theta = M_PI/180;
    int threshold = 40;
    int max_line_length = 25;
    int max_line_gap = 20;

    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(frame, lines, rho, theta, threshold, max_line_length, max_line_gap);
    return lines;
}

std::vector<cv::Vec4i> group_similar_lines(
    std::vector<cv::Vec4i>& lines,
    int distance_threshold = 10,
    double angle_threshold = M_PI/16,
    int iterations = 3,
    bool x_axis = true
) {
    if (lines.empty()) {
        return std::vector<cv::Vec4i>();
    }
    while (iterations--) {
        std::vector<cv::Vec<double, 6>> prepared_lines;
        for (cv::Vec4i& line : lines) {
            int x1 = line[0];
            int y1 = line[1];
            int x2 = line[2];
            int y2 = line[3];
            double angle = std::atan2(y2 - y1, x2 - x1);
            double avg_coordiante = (x_axis) ? ((x2 + x1)/2) : ((y2 + y1)/2);
            prepared_lines.push_back({x1, y1, x2, y2, angle, avg_coordiante});
        }
        std::sort(prepared_lines.begin(), prepared_lines.end(),
            [](cv::Vec<double, 6>& a, cv::Vec<double, 6>& b) -> bool {
                if (a[4] < b[4]) {
                    return true;
                }
                else if (a[4] == b[4]) {
                    return (a[5] < b[5]);
                }
                else {
                    return false;
                }
            }
        );
        std::vector<cv::Vec<double, 4>> grouped_lines;
        std::vector<cv::Vec<double, 6>> current_group{prepared_lines[0]};

        double last_angle = prepared_lines[0][4];
        double last_avg_coordinate = prepared_lines[0][5];

        for (auto it = prepared_lines.begin() + 1; it != prepared_lines.end(); ++it) {
            if (
                (std::abs((*it)[4] - last_angle) <= angle_threshold)
                &&
                (std::abs(avg_coordiante - last_avg_coordinate) <= distance_threshold)
            ) {
                current_group.push_back({x1, y1, x2, y2, angle, avg_coordiante});
            }
            else {
                if (!current_group.empty()) {
                    int avg_x1 = static_cast<int>(vector_sum<double, 0>(current_group)/current_group.size());
                    int avg_y1 = static_cast<int>(vector_sum<double, 1>(current_group)/current_group.size());
                    int avg_x2 = static_cast<int>(vector_sum<double, 2>(current_group)/current_group.size());
                    int avg_y2 = static_cast<int>(vector_sum<double, 3>(current_group)/current_group.size());
                    grouped_lines.push_back({avg_x1, avg_y1, avg_x2, avg_y2});
                    current_group.clear();
                }
                last_angle = angle;
                last_avg_coordinate = avg_coordiante;
            }
        }
        if (!current_group.empty()) {
            int avg_x1 = static_cast<int>(vector_sum<double, 0>(current_group)/current_group.size());
            int avg_y1 = static_cast<int>(vector_sum<double, 1>(current_group)/current_group.size());
            int avg_x2 = static_cast<int>(vector_sum<double, 2>(current_group)/current_group.size());
            int avg_y2 = static_cast<int>(vector_sum<double, 3>(current_group)/current_group.size());
            grouped_lines.push_back({avg_x1, avg_y1, avg_x2, avg_y2});
        }
        lines = grouped_lines;
    }
    return grouped_lines;
}

cv::Vec<double, 4> select_relevant_line(
    std::vector<cv::Vec<double, 4>>& lines, cv::Vec<double, 4>& previous_line)
{
    if (lines.empty()) {
        return previous_line;
    }

    if (previous_line == {0, 0, 0, 0}) {
        return lines[0];
    }
    
    double pre_mid_x = (previous_line[0] + previous_line[2])/2;
    double pre_mid_y = (previous_line[1] + previous_line[3])/2;
    double pre_mid_angle = std::atan2(previous_line[3] - previous_line[1], previous_line[2] - previous_line[0]);

    double min_distance = std::numeric_limits<double>::infinity();
    cv::Vec<double, 4> selected_line = lines[0];

    for (cv::Vec<double, 4>& line : lines) {
        double mid_x = (line[0] + line[2])/2;
        double mid_y = (line[1] + line[3])/2;
        double angle = std::atan2(line[3] - line[1], line[2] - line[0]);

        double distance = std::sqrt(std::pow(prev_mid_x - mid_x, 2) + std::pow(prev_mid_y - mid_y, 2));
        double angle_diff = std::abs(prev_angle - angle);

        if (distance + angle_diff < min_distance) {
            min_distance = distance + angle_diff;
            selected_line = line;
        }
    }
    return selected_line;
}

double calculate_angle_error(cv::Vec<double, 4>& line, int frame_width, int frame_height)
{
    double mid_x = (line[0] + line[2])/2;
    double mid_y = (line[1] + line[3])/2;

    double bottom_center_x = frame_width/2;
    double bottom_center_y = frame_height;

    dx = mid_x - bottom_center_x;
    dy = bottom_center_y - mid_y;

    double angle_radians = 0;
    if (dy == 0) {
        angle_radians = (dx > 0) ? (M_PI/2) : (-M_PI/2);
    }
    else if (dx == 0) {
        angle_radians = 0;
    }
    else {
        angle_radians = std::atan(dx/dy);
    }
    angle_radians *= -1;
    return angle_radians;
}

cv::Mat draw_hough_lines(
    cv::Mat& frame_src, std::vector<std::Vec<double, 4>>& lines,
    cv::Scalar& color = 255, int thickness = 2)
{
    if (lines.empty()) {
        return frame_src;
    }

    for (cv::Vec<double, 4>& line : lines) {
        cv::Point p1(line[0], line[1]);
        cv::Point p2(line[2], line[3]);
        cv::line(frame_src, p1, p2, color, thickness);
    }

    return frame;
}
    

double detect_lane_center(cv::Mat& frame)
{
    CropParams params = CROP_PARAMS["lane_detection"];
    cv::Mat cropped_frame = crop_frame(frame, frame.rows - params.height, params.height, params.width);
    std::vector<Vec4i> lines = detect_lines_hough(cropped_frame);
    lines = group_similar_lines(lines);
    previous_line = lane_history;
    selected_line = select_relevant_line(lines, previous_line);
    if (selected_line != {0, 0, 0, 0}) {
        double angle_error = calculate_angle_error(selected_line, cropped_frame.rows, cropped_frame.cols);
        cv::Mat hough_lines_frame = draw_hough_lines(cropped_frame, selected_line);
        // Publish
        return angle_error;
    }
    else {
        std::cerr << "No valid line detected, using previous line if available.\n";
        return 0; 
    }
}