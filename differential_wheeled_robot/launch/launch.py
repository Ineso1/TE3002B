import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    point_generator_config = os.path.join(
        get_package_share_directory('differential_wheeled_robot'),
        'config',
        'point_generator_params.yaml'
    )
    controller_config = os.path.join(
        get_package_share_directory('differential_wheeled_robot'),
        'config',
        'controller_params.yaml'
    )
    odometry_config = os.path.join(
        get_package_share_directory('differential_wheeled_robot'),
        'config',
        'odometry_params.yaml'
    )
    return LaunchDescription([
        Node(
            package='differential_wheeled_robot',
            executable='controller',
            name='controller',
            parameters=[controller_config]
        ),
        Node(
            package='differential_wheeled_robot',
            executable='odometry',
            name='odometry',
            parameters=[odometry_config]
        ),
        Node(
            package='differential_wheeled_robot',
            executable='point_generator',
            name='point_generator',
            parameters=[point_generator_config]
        )
    ])