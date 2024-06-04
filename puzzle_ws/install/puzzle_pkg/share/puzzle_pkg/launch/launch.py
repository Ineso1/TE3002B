import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    controller_config = os.path.join(
        get_package_share_directory('puzzle_pkg'),
        'config',
        'controller_params.yaml'
    )
    odometry_config = os.path.join(
        get_package_share_directory('puzzle_pkg'),
        'config',
        'odometry_params.yaml'
    )
    serial_args = ['serial', '--dev', ' /dev/ttyUSB0']

    return LaunchDescription([
        # Node(
        #     package='micro_ros_agent',
        #     executable='micro_ros_agent',
        #     output='screen',
        #     name='hackerboard',
        #     arguments=serial_args
        # ),
        Node(
            package='puzzle_pkg',
            executable='controller',
            name='controller',
            parameters=[controller_config]
        ),
        Node(
            package='puzzle_pkg',
            executable='odometry',
            name='odometry',
            parameters=[odometry_config]
        ),
        Node(
            package='puzzle_pkg',
            executable='lane_detection',
            name='lane_detection'
        ),
        Node(
            package='puzzle_pkg',
            executable='cam_source',
            name='cam_source'
        )
    ])
