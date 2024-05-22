#ifndef LANE_PARAMS_H
#define LANE_PARAMS_H

#include <map>
#include <string>


// Structure for real world dimensions after perspective transformation
struct RealCartesianConfig {
    // Measures on meters
	double b_width;
	double t_width;
	double t_height;
};

// Structure for perspective transformation configuration
struct PerspectiveConfig {
    // Measures on meters
	double b_width;
	double t_width;
	double height;
};

// Structure to hold crop parameters
struct CropParams {
    // Mesure on px
    int y_start;
    int width;
    int height;
};

const PerspectiveConfig PERSPECTIVE_CONFIG = {1046, 200, 300};
const RealCartesianConfig REAL_CARTESIAN_CONFIG = {0.3, 0.3, 0.4};

const std::map<std::string, CropParams> CROP_PARAMS = {
    {"lane_detection", {0, 150, 60}},
    {"crossing_line_detection", {0, 150, 280}}
};

#endif // LANE_PARAMS_H
