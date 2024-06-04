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

extern const PerspectiveConfig PERSPECTIVE_CONFIG;
extern const RealCartesianConfig REAL_CARTESIAN_CONFIG;
extern std::map<std::string, CropParams> CROP_PARAMS;

#endif // LANE_PARAMS_H
