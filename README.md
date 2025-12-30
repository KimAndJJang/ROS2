# ROS2 RL-Vision-LLM Project

A ROS2 project integrating **Reinforcement Learning**, **Vision AI**, and **LLM** (Large Language Models) implemented entirely in **C/C++**.

## Project Overview

This project combines three cutting-edge AI technologies in a ROS2 framework:

- **Reinforcement Learning (RL)**: Q-learning based agent for autonomous decision-making
- **Vision AI**: Computer vision module for object detection, feature extraction, and tracking
- **LLM Interface**: Natural language processing for command interpretation and text generation

## Architecture

### Components

1. **Reinforcement Learning Module** (`reinforcement_learning.cpp`)
   - Q-learning implementation
   - State-action value estimation
   - Policy optimization with exploration-exploitation strategy

2. **Vision AI Module** (`vision_ai.cpp`)
   - Object detection
   - Feature extraction from images
   - Object tracking capabilities

3. **LLM Interface Module** (`llm_interface.cpp`)
   - Natural language command processing
   - Text generation and embeddings
   - Action interpretation from state features

4. **Main Node** (`main.cpp`)
   - Integrates all three modules
   - ROS2 node with publishers and subscribers
   - Real-time processing loop

## Building the Project

### Prerequisites

- ROS2 (Humble, Iron, or Rolling)
- C++17 compatible compiler
- CMake 3.8 or higher

### Build Instructions

```bash
# Source ROS2
source /opt/ros/<ros2-distro>/setup.bash

# Build the package
colcon build --packages-select ros2_rl_vision_llm

# Source the workspace
source install/setup.bash
```

## Running the Node

```bash
# Run the main node
ros2 run ros2_rl_vision_llm rl_vision_llm_node
```

## Topics

### Subscribed Topics

- `/camera/image_raw` (sensor_msgs/Image): Camera input for vision processing
- `/voice_command` (std_msgs/String): Natural language commands

### Published Topics

- `/cmd_vel` (geometry_msgs/Twist): Velocity commands for robot control
- `/system_status` (std_msgs/String): System status updates

## Usage Examples

### Sending Commands

```bash
# Send a voice command
ros2 topic pub /voice_command std_msgs/String "data: 'move forward'"

# Send stop command
ros2 topic pub /voice_command std_msgs/String "data: 'stop'"
```

### Monitoring Status

```bash
# Monitor system status
ros2 topic echo /system_status

# Monitor velocity commands
ros2 topic echo /cmd_vel
```

## Implementation Details

### Reinforcement Learning
- Uses Q-learning algorithm for decision-making
- Maintains Q-table for state-action values
- Implements ε-greedy exploration strategy

### Vision AI
- Processes camera images for object detection
- Extracts high-dimensional features for RL agent
- Provides object tracking capabilities

### LLM Interface
- Processes natural language commands
- Generates text embeddings for semantic understanding
- Interprets robot actions based on state features

## Development

### Code Structure

```
ros2_rl_vision_llm/
├── CMakeLists.txt
├── package.xml
├── include/
│   └── ros2_rl_vision_llm/
│       ├── reinforcement_learning.hpp
│       ├── vision_ai.hpp
│       └── llm_interface.hpp
└── src/
    ├── main.cpp
    ├── reinforcement_learning.cpp
    ├── vision_ai.cpp
    └── llm_interface.cpp
```

## License

Apache License 2.0

## Future Enhancements

- Integration with actual deep learning frameworks (TensorFlow, PyTorch)
- Advanced vision models (YOLO, R-CNN for object detection)
- Transformer-based LLM integration
- Multi-agent reinforcement learning
- Real-world robot platform integration
