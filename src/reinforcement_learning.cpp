#include "ros2_rl_vision_llm/reinforcement_learning.hpp"
#include <algorithm>
#include <cmath>
#include <random>

namespace ros2_rl_vision_llm {

struct ReinforcementLearning::RLImpl {
    std::vector<std::vector<double>> q_table;
    double learning_rate;
    double discount_factor;
    double exploration_rate;
    std::mt19937 rng;
    
    RLImpl() 
        : learning_rate(0.1),
          discount_factor(0.95),
          exploration_rate(0.1),
          rng(std::random_device{}()) {
        q_table.resize(10, std::vector<double>(4, 0.0));
    }
};

ReinforcementLearning::ReinforcementLearning()
    : impl_(std::make_unique<RLImpl>()) {
}

ReinforcementLearning::~ReinforcementLearning() = default;

void ReinforcementLearning::initialize() {
    // Initialize Q-learning parameters
    impl_->learning_rate = 0.1;
    impl_->discount_factor = 0.95;
    impl_->exploration_rate = 0.1;
}

void ReinforcementLearning::train(const std::vector<double>& state, double reward) {
    if (state.empty()) return;
    
    // Simple Q-learning update
    int state_idx = std::abs(static_cast<int>(state[0])) % impl_->q_table.size();
    int action = (state.size() > 1) ? static_cast<int>(state[1]) % 4 : 0;
    
    double max_future_q = *std::max_element(
        impl_->q_table[state_idx].begin(),
        impl_->q_table[state_idx].end()
    );
    
    double current_q = impl_->q_table[state_idx][action];
    double new_q = current_q + impl_->learning_rate * 
                   (reward + impl_->discount_factor * max_future_q - current_q);
    
    impl_->q_table[state_idx][action] = new_q;
}

std::vector<double> ReinforcementLearning::predict(const std::vector<double>& state) {
    if (state.empty()) {
        return {0.0, 0.0, 0.0, 0.0};
    }
    
    int state_idx = std::abs(static_cast<int>(state[0])) % impl_->q_table.size();
    
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    if (dist(impl_->rng) < impl_->exploration_rate) {
        // Explore: random action
        std::uniform_int_distribution<int> action_dist(0, 3);
        int random_action = action_dist(impl_->rng);
        std::vector<double> result(4, 0.0);
        result[random_action] = 1.0;
        return result;
    }
    
    // Exploit: use Q-table
    return impl_->q_table[state_idx];
}

double ReinforcementLearning::getQValue(const std::vector<double>& state, int action) {
    if (state.empty() || action < 0 || action >= 4) {
        return 0.0;
    }
    
    int state_idx = std::abs(static_cast<int>(state[0])) % impl_->q_table.size();
    return impl_->q_table[state_idx][action];
}

void ReinforcementLearning::updatePolicy() {
    // Decay exploration rate
    impl_->exploration_rate *= 0.99;
    if (impl_->exploration_rate < 0.01) {
        impl_->exploration_rate = 0.01;
    }
}

} // namespace ros2_rl_vision_llm
