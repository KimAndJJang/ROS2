#ifndef ROS2_RL_VISION_LLM_LLM_INTERFACE_HPP
#define ROS2_RL_VISION_LLM_LLM_INTERFACE_HPP

#include <string>
#include <vector>
#include <memory>

namespace ros2_rl_vision_llm {

struct LLMResponse {
    std::string text;
    double confidence;
    std::vector<std::string> tokens;
};

class LLMInterface {
public:
    LLMInterface();
    ~LLMInterface();

    void initialize();
    LLMResponse generateText(const std::string& prompt);
    LLMResponse processCommand(const std::string& command);
    std::vector<double> getEmbedding(const std::string& text);
    std::string interpretAction(const std::vector<double>& state_features);

private:
    struct LLMImpl;
    std::unique_ptr<LLMImpl> impl_;
};

} // namespace ros2_rl_vision_llm

#endif // ROS2_RL_VISION_LLM_LLM_INTERFACE_HPP
