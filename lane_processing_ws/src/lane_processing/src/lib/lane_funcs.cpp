#include "lane_processing/lane_funcs.h"


std::vector<cv::Vec4i> group_similar_lines(
    std::vector<cv::Vec4i>& lines,
    int distance_threshold,
    double angle_threshold,
    int iterations,
    bool x_axis
) {
    if (lines.empty()) {
        return {};
    }

    std::vector<cv::Vec4i> grouped_lines;
    for (int iter = 0; iter < iterations; ++iter) {
        std::vector<Line> prepared_lines;
        for (std::vector<cv::Vec4i>::size_type i = 0; i < lines.size(); ++i) {
            int x1 = lines[i][0], y1 = lines[i][1], x2 = lines[i][2], y2 = lines[i][3];
            double angle = std::atan2(static_cast<double>(y2 - y1), static_cast<double>(x2 - x1));
            double avgCoordinate = x_axis ? (x1 + x2) / 2.0 : (y1 + y2) / 2.0;
            Line line = {x1, y1, x2, y2, angle, avgCoordinate};
            prepared_lines.push_back(line);
        }

        std::vector<Line> current_group;
        double last_angle = prepared_lines[0].angle;
        double last_avg_coordinate = prepared_lines[0].avgCoordinate;
        current_group.push_back(prepared_lines[0]);

        for (std::vector<Line>::size_type i = 1; i < prepared_lines.size(); ++i) {
            Line line = prepared_lines[i];
            if (std::abs(line.angle - last_angle) <= angle_threshold &&
                std::abs(line.avgCoordinate - last_avg_coordinate) <= distance_threshold) {
                current_group.push_back(line);
            } else {
                if (!current_group.empty()) {
                    grouped_lines.push_back(average_lines(current_group));
                    current_group.clear();
                }
                last_angle = line.angle;
                last_avg_coordinate = line.avgCoordinate;
                current_group.push_back(line);
            }
        }

        if (!current_group.empty()) {
            grouped_lines.push_back(average_lines(current_group));
        }

        lines = grouped_lines;
        grouped_lines.clear();
    }

    return lines;
}

cv::Vec4i average_lines(const std::vector<Line>& lines) {
    int total_x1 = 0, total_y1 = 0, total_x2 = 0, total_y2 = 0;
    for (std::vector<Line>::size_type i = 0; i < lines.size(); ++i) {
        total_x1 += lines[i].x1;
        total_y1 += lines[i].y1;
        total_x2 += lines[i].x2;
        total_y2 += lines[i].y2;
    }
    int count = static_cast<int>(lines.size());
    return cv::Vec4i(total_x1 / count, total_y1 / count, total_x2 / count, total_y2 / count);
}

cv::Vec4i select_relevant_line(const std::vector<cv::Vec4i>& lines, const cv::Vec4i& previous_line) {
    if (lines.empty()) {
        return previous_line;
    }

    if (previous_line == cv::Vec4i(0, 0, 0, 0)) {
        return lines[0];
    }

    double prev_mid_x = (previous_line[0] + previous_line[2]) / 2.0;
    double prev_mid_y = (previous_line[1] + previous_line[3]) / 2.0;
    double prev_angle = std::atan2(static_cast<double>(previous_line[3] - previous_line[1]), static_cast<double>(previous_line[2] - previous_line[0]));

    double min_distance = std::numeric_limits<double>::max();
    cv::Vec4i selected_line = lines[0];

    for (std::vector<cv::Vec4i>::size_type i = 0; i < lines.size(); ++i) {
        double mid_x = (lines[i][0] + lines[i][2]) / 2.0;
        double mid_y = (lines[i][1] + lines[i][3]) / 2.0;
        double angle = std::atan2(static_cast<double>(lines[i][3] - lines[i][1]), static_cast<double>(lines[i][2] - lines[i][0]));

        double distance = std::sqrt((prev_mid_x - mid_x) * (prev_mid_x - mid_x) + (prev_mid_y - mid_y) * (prev_mid_y - mid_y));
        double angle_diff = std::abs(prev_angle - angle);

        if (distance + angle_diff < min_distance) {
            min_distance = distance + angle_diff;
            selected_line = lines[i];
        }
    }

    return selected_line;
}


double calculate_angle_error(cv::Vec4i& line, int frame_width, int frame_height) {
    double mid_x = (line[0] + line[2]) / 2.0;
    double mid_y = (line[1] + line[3]) / 2.0;

    double bottom_center_x = frame_width / 2.0;
    double bottom_center_y = frame_height;

    double dx = mid_x - bottom_center_x;
    double dy = bottom_center_y - mid_y;

    double angle_radians;
    if (dy == 0) {
        angle_radians = M_PI / 2.0 * (dx > 0 ? 1 : -1);
    } else if (dx == 0) {
        angle_radians = 0;
    } else {
        angle_radians = std::atan(dx / dy);
    }

    // Convert radians to degrees ass
    angle_radians = angle_radians * (180.0 / M_PI);

    return angle_radians;
}