cmake_minimum_required(VERSION 3.8)
project(ros2_rl_vision_llm)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

# Include directories
include_directories(include)

# Add executables
add_executable(rl_vision_llm_node
  src/main.cpp
  src/reinforcement_learning.cpp
  src/vision_ai.cpp
  src/llm_interface.cpp
)

ament_target_dependencies(rl_vision_llm_node
  rclcpp
  std_msgs
  sensor_msgs
  geometry_msgs
)

# Install targets
install(TARGETS
  rl_vision_llm_node
  DESTINATION lib/${PROJECT_NAME}
)

# Install header files
install(DIRECTORY include/
  DESTINATION include/
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
