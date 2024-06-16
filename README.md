# ROS 2 Differential Robot Project

## Description
This project integrates ROS 2 with OpenCV (with CUDA) on a Jetson platform to manage a differential robot. It features micro-ROS for handling motor controls by sending linear and angular velocities. The workspace includes two main parts: `puzzle_ws` for robot control and real-time operations, and `fog_ws` for off-hardware classification tasks ensuring topic sharing over the network.

## Prerequisites
- ROS 2 installation
- OpenCV with CUDA support
- micro-ROS setup
- Jetson platform (with proper environment setup for CUDA and ROS 2)
- Serial connection for micro-ROS agent (usually via USB)

## Installation
1. Clone the repository:
```bash
git clone https://github.com/paulramirez19/TE3002B/
cd TE3002B
```

2. Prepare the `puzzle_ws` workspace:
```bash
cd puzzle_ws
# Remove previous build artifacts if they exist
rm -rf build install log
# Build the workspace
colcon build
```

3. Prepare the fog_ws workspace:
```bash
cd ../fog_ws
# Remove previous build artifacts if they exist
rm -rf build install log
# Build the workspace
colcon build
```
## Running the Project

1. Launch the micro-ROS agent:
```bash
ros2 run micro_ros_agent micro_ros_agent serial --dev /dev/ttyUSB0
```
2. Source the setup script and run the launcher file:
```bash
source install/setup.bash
ros2 launch puzzle_pkg launch.py
```
Ensure that if you are working remotely or need the fog_ws for classification, topics are correctly shared across the network.

## Usage
The project is configured to control a differential robot by sending appropriate linear and angular velocities through the micro-ROS setup. Adjustments to velocity and other parameters should be made in accordance with the specific robot's configuration and environmental context.


![image](https://github.com/paulramirez19/TE3002B/assets/84602829/dba108f8-101a-4a03-b390-eb61f4fd98e1)

![image](https://github.com/paulramirez19/TE3002B/assets/84602829/a7a3a640-80bf-43e2-bd86-c4d08876cbd6)

![image](https://github.com/paulramirez19/TE3002B/assets/84602829/30f1bdbe-a98e-4cdc-8ff5-0580b4c853f3)

# Video

[![Watch the Video](https://github.com/paulramirez19/TE3002B/blob/main/imgs/WorkTraffic.png?raw=true)](https://www.youtube.com/watch?v=5agHRD6gWp8 "Watch the Video")



