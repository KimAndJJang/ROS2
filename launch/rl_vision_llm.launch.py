from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration


def generate_launch_description():
    # Declare launch arguments
    log_level_arg = DeclareLaunchArgument(
        'log_level',
        default_value='info',
        description='Logging level (debug, info, warn, error, fatal)'
    )

    # Define the node
    rl_vision_llm_node = Node(
        package='ros2_rl_vision_llm',
        executable='rl_vision_llm_node',
        name='rl_vision_llm_node',
        output='screen',
        parameters=[],
        arguments=['--ros-args', '--log-level', LaunchConfiguration('log_level')],
        remappings=[
            # Add any topic remappings here if needed
            # ('old_topic', 'new_topic'),
        ]
    )

    return LaunchDescription([
        log_level_arg,
        rl_vision_llm_node,
    ])
