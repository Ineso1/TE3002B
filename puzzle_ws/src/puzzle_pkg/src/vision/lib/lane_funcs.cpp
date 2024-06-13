#include <cstddef>
#include "puzzle_pkg/lane_funcs.h"
#include "puzzle_pkg/cv_wrapper.h"


double point_distance(const cv::Point2d& p1, const cv::Point2d& p2) {
    return cv::norm(p1 - p2);
}

std::vector<cv::Vec<double, 2>> group_similar_lines(
    const std::vector<cv::Vec4d>& lines, 
    double eps, 
    std::size_t minPts
) {
    std::vector<cv::Point2d> midpoints;
    for (const auto& line : lines) {
        midpoints.emplace_back((line[0] + line[2]) / 2.0, (line[1] + line[3]) / 2.0);
    }

    std::vector<int> labels(midpoints.size(), -1);
    int clusterId = 0;

    for (std::size_t i = 0; i < midpoints.size(); ++i) {
        if (labels[i] != -1) continue;

        std::vector<int> neighbors;
        for (std::size_t j = 0; j < midpoints.size(); ++j) {
            if (point_distance(midpoints[i], midpoints[j]) < eps) {
                neighbors.push_back(j);
            }
        }

        if (neighbors.size() < minPts) {
            labels[i] = -2; // Mark as noise
            continue;
        }

        labels[i] = clusterId;
        std::vector<int> seeds = neighbors;
        std::size_t index = 0;
        while (index < seeds.size()) {
            int currentPoint = seeds[index++];
            if (labels[currentPoint] == -2) labels[currentPoint] = clusterId;
            if (labels[currentPoint] != -1) continue;
            labels[currentPoint] = clusterId;

            neighbors.clear();
            for (std::size_t j = 0; j < midpoints.size(); ++j) {
                if (point_distance(midpoints[currentPoint], midpoints[j]) < eps) {
                    neighbors.push_back(j);
                }
            }

            if (neighbors.size() >= minPts) {
                seeds.insert(seeds.end(), neighbors.begin(), neighbors.end());
            }
        }
        clusterId++;
    }

    // Calculate the average point for each cluster
    std::vector<cv::Vec<double, 2>> cluster_centers(clusterId, cv::Vec<double, 2>(0, 0));
    std::vector<int> cluster_sizes(clusterId, 0);
    for (std::size_t i = 0; i < midpoints.size(); ++i) {
        if (labels[i] >= 0) {
            cluster_centers[labels[i]][0] += midpoints[i].x;
            cluster_centers[labels[i]][1] += midpoints[i].y;
            cluster_sizes[labels[i]]++;
        }
    }

    for (std::size_t i = 0; i < cluster_centers.size(); ++i) {
        cluster_centers[i][0] /= cluster_sizes[i];
        cluster_centers[i][1] /= cluster_sizes[i];
    }

    return cluster_centers;
}


double calculate_angle(const cv::Vec<double, 4>& line) {
    return std::atan2(line[3] - line[1], line[2] - line[0]) * 180.0 / CV_PI;
}

bool is_horizontal(const cv::Vec<double, 4>& line, double angle_threshold) {
    double angle = std::fabs(calculate_angle(line));
    return angle < angle_threshold || angle > 180 - angle_threshold;
}

cv::Vec<double, 4> detect_cross_and_return_mean_line(const std::vector<cv::Vec<double, 4>>& lines, double centerX, double minWidth) {
    std::vector<cv::Vec<double, 4>> cross_lines;
    double angle_threshold = 10; // Ángulo máximo en grados para considerar una línea horizontal XD

    for (const cv::Vec<double, 4>& line : lines) {
        if (is_horizontal(line, angle_threshold)) {
            double min_x = std::min(line[0], line[2]);
            double max_x = std::max(line[0], line[2]);
            if (min_x <= centerX && max_x >= centerX) {  // La línea cruza el centro de lado a lado
                double line_width = max_x - min_x;
                if (line_width >= minWidth) {  // La línea tiene el ancho mínimo, igual habra que ver si jala 
                    cross_lines.push_back(line);
                }
            }
        }
    }

    //Promediazo xd
    double sum_x1 = 0, sum_y1 = 0, sum_x2 = 0, sum_y2 = 0;
    for (const auto& line : cross_lines) {
        sum_x1 += line[0];
        sum_y1 += line[1];
        sum_x2 += line[2];
        sum_y2 += line[3];
    }
    int count = cross_lines.size();
    if (count > 0) {
        return cv::Vec<double, 4>(sum_x1 / count, sum_y1 / count, sum_x2 / count, sum_y2 / count);
    } else {
        // Return an empty como el tanque del march :(
        return cv::Vec<double, 4>(0, 0, 0, 0);
    }
}

std::vector<cv::Vec<double, 2>> frame_relevant_points(cv::Mat& frame, cv::Vec<double, 2> average_center, bool& cross_line){
    int minPts = 2;
    double eps = 50.0;
    std::vector<cv::Vec4i> lines;
    cv::Vec<double, 4> selected_line;
    std::vector<cv::Vec<double, 4>> converted_lines;
    std::vector<cv::Vec<double, 2>> grouped_lines;

    lines = detect_lines_hough(frame);
    
    for (const auto& line : lines) {
        converted_lines.push_back(cv::Vec<double, 4>(line[0], line[1], line[2], line[3]));
    }

    cv::Vec<double, 4> cross_lines = detect_cross_and_return_mean_line(converted_lines, average_center[0], 85);

    if (cross_lines[0] && cross_lines[1] && cross_lines[2] && cross_lines[3])
    {
        cross_line = true;
    }
    else{
        cross_line = false;
    }
    
    //std::cout << "Number of lines that form a cross: " << cross_lines[0] << " , " << cross_lines[1] << cross_lines[2] << " , " << cross_lines[3] << std::endl;
    grouped_lines = group_similar_lines(converted_lines, eps, minPts);

    return grouped_lines;
} 

std::vector<cv::Vec<double, 2>> frame_relevant_points(cv::Mat& frame){
    int minPts = 2;
    double eps = 50.0;
    std::vector<cv::Vec4i> lines;
    cv::Vec<double, 4> selected_line;
    std::vector<cv::Vec<double, 4>> converted_lines;
    std::vector<cv::Vec<double, 2>> grouped_lines;

    lines = detect_lines_hough(frame);
    for (const auto& line : lines) {
        converted_lines.push_back(cv::Vec<double, 4>(line[0], line[1], line[2], line[3]));
    }

    grouped_lines = group_similar_lines(converted_lines, eps, minPts);

    return grouped_lines;
} 

cv::Vec<double, 2> get_average_center(int frame_width, int frame_height) {
    cv::Vec<double, 2> center_p(0.0, 0.0);
    int count = lane_history.size();

    if (count > 0) {
        for (auto& history : lane_history) {
            center_p[0] += history.first[0];
            center_p[1] += history.first[1];
        }
        return cv::Vec<double, 2>(center_p[0] / count, center_p[1] / count);
    } else {
        // Return the center of the frame if there is no history
        return cv::Vec<double, 2>(frame_width / 2.0, frame_height / 2.0);
    }
}


cv::Vec<double, 2> linear_regression(const std::vector<double>& x, const std::vector<double>& y) {
    const size_t n = x.size();
    double sum_x = std::accumulate(x.begin(), x.end(), 0.0);
    double sum_y = std::accumulate(y.begin(), y.end(), 0.0);
    double sum_xx = std::inner_product(x.begin(), x.end(), x.begin(), 0.0);
    double sum_xy = std::inner_product(x.begin(), x.end(), y.begin(), 0.0);

    double slope = (n * sum_xy - sum_x * sum_y) / (n * sum_xx - sum_x * sum_x);
    double intercept = (sum_y - slope * sum_x) / n;

    return {slope, intercept};  // slope (m), intercept (b)
}

void extrapolate_and_update_lane_history() {
    if (lane_history.size() < 2) {
        return;
    }

    std::vector<double> x_values, back_y_values, front_y_values;
    for (size_t i = 0; i < lane_history.size(); ++i) {
        x_values.push_back(i);
        back_y_values.push_back(lane_history[i].first[1]);  // Using y-coordinate of back points
        front_y_values.push_back(lane_history[i].second[1]);  // Using y-coordinate of front points
    }

    cv::Vec<double, 2> back_trend = linear_regression(x_values, back_y_values);
    cv::Vec<double, 2> front_trend = linear_regression(x_values, front_y_values);

    // Predict the next point using the trend
    double next_x = x_values.back() + 1;
    double next_back_y = back_trend[0] * next_x + back_trend[1];
    double next_front_y = front_trend[0] * next_x + front_trend[1];

    // Append the extrapolated point to the history
    lane_history.push_back({{next_x, next_back_y}, {next_x, next_front_y}});
}



double calculate_angle_error(cv::Vec<double, 4>& line, int frame_width, int frame_height) {
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

    //angle_radians *= (180.0 / M_PI); // Do not convert radians to degrees ass hole :)

    return angle_radians;
}



