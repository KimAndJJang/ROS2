#ifndef ROS2_RL_VISION_LLM_REINFORCEMENT_LEARNING_HPP
#define ROS2_RL_VISION_LLM_REINFORCEMENT_LEARNING_HPP

#include <vector>
#include <memory>

namespace ros2_rl_vision_llm {

class ReinforcementLearning {
public:
    ReinforcementLearning();
    ~ReinforcementLearning();

    void initialize();
    void train(const std::vector<double>& state, double reward);
    std::vector<double> predict(const std::vector<double>& state);
    double getQValue(const std::vector<double>& state, int action);
    void updatePolicy();

private:
    struct RLImpl;
    std::unique_ptr<RLImpl> impl_;
};

} // namespace ros2_rl_vision_llm

#endif // ROS2_RL_VISION_LLM_REINFORCEMENT_LEARNING_HPP
