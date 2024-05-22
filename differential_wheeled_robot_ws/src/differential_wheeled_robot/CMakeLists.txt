cmake_minimum_required(VERSION 3.8)
project(differential_wheeled_robot)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Path.msg"
  DEPENDENCIES geometry_msgs
)

add_executable(point_generator src/point_generator.cpp)
ament_target_dependencies(
  point_generator
  rclcpp
  geometry_msgs
)

add_executable(controller src/controller.cpp)
ament_target_dependencies(
  controller
  rclcpp
  std_msgs
  geometry_msgs
)

add_executable(odometry src/odometry.cpp)
ament_target_dependencies(
  odometry
  rclcpp
  std_msgs
  geometry_msgs
)

rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} rosidl_typesupport_cpp  
)

target_link_libraries(point_generator "${cpp_typesupport_target}")
target_link_libraries(controller "${cpp_typesupport_target}")

install(TARGETS
  point_generator
  controller
  odometry
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
