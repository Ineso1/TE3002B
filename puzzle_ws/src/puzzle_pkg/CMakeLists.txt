# set(OpenCV_VERSION 4.5.5)
cmake_minimum_required(VERSION 3.8)
project(puzzle_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


find_package(ament_cmake REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(image_transport REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(OpenCV REQUIRED)
# find_package(CUDA REQUIRED)


rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/DiffError.msg"
  DEPENDENCIES std_msgs
)

ament_export_dependencies(rosidl_default_runtime)

# Include directories
include_directories(
  include
  ${cv_bridge_INCLUDE_DIRS}
  ${image_transport_INCLUDE_DIRS}
  ${sensor_msgs_INCLUDE_DIRS}
  # ${CUDA_INCLUDE_DIRS}
)

add_executable(
  lane_detection
  src/vision/lane_detection.cpp 
  src/vision/lib/cv_wrapper.cpp 
  src/vision/lib/perspective.cpp
  src/vision/lib/lane_funcs.cpp
)
ament_target_dependencies(
  lane_detection
  rclcpp
  cv_bridge
  image_transport
  sensor_msgs
  std_msgs
  OpenCV
)

add_executable(cam_source src/vision/cam_source.cpp)
ament_target_dependencies(
  cam_source
  rclcpp
  cv_bridge
  image_transport
  sensor_msgs
  std_msgs
  OpenCV
)

add_executable(signal_handle src/vision/signal_handle.cpp)
ament_target_dependencies(
  signal_handle
  rclcpp
  cv_bridge
  image_transport
  sensor_msgs
  std_msgs
  OpenCV
)

add_executable(controller src/control/controller.cpp)
ament_target_dependencies(
  controller
  rclcpp
  std_msgs
  geometry_msgs
)

add_executable(odometry src/control/odometry.cpp)
ament_target_dependencies(
  odometry
  rclcpp
  std_msgs
  geometry_msgs
)



rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} rosidl_typesupport_cpp  
)

target_link_libraries(controller "${cpp_typesupport_target}")
target_link_libraries(lane_detection "${cpp_typesupport_target}")

# target_link_libraries(lane_detection ${CUDA_LIBRARIES})
# target_link_libraries(cam_source ${CUDA_LIBRARIES})
# target_link_libraries(controller ${CUDA_LIBRARIES})

target_include_directories(lane_detection PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_include_directories(controller PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

install(TARGETS
  controller
  odometry
  lane_detection
  cam_source
  signal_handle
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  config
  DESTINATION share/${PROJECT_NAME}/
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
