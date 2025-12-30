#ifndef ROS2_RL_VISION_LLM_VISION_AI_HPP
#define ROS2_RL_VISION_LLM_VISION_AI_HPP

#include <vector>
#include <string>
#include <memory>

namespace ros2_rl_vision_llm {

struct DetectionResult {
    std::string label;
    double confidence;
    int x, y, width, height;
};

class VisionAI {
public:
    VisionAI();
    ~VisionAI();

    void initialize();
    std::vector<DetectionResult> detectObjects(const std::vector<unsigned char>& image_data, 
                                                 int width, int height);
    std::vector<double> extractFeatures(const std::vector<unsigned char>& image_data,
                                         int width, int height);
    bool trackObject(const std::vector<unsigned char>& image_data,
                     int width, int height,
                     const DetectionResult& target);

private:
    struct VisionImpl;
    std::unique_ptr<VisionImpl> impl_;
};

} // namespace ros2_rl_vision_llm

#endif // ROS2_RL_VISION_LLM_VISION_AI_HPP
