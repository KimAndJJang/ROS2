#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <geometry_msgs/msg/twist.hpp>

#include "ros2_rl_vision_llm/reinforcement_learning.hpp"
#include "ros2_rl_vision_llm/vision_ai.hpp"
#include "ros2_rl_vision_llm/llm_interface.hpp"

#include <memory>
#include <vector>

class RLVisionLLMNode : public rclcpp::Node {
public:
    RLVisionLLMNode() : Node("rl_vision_llm_node") {
        // Initialize components
        rl_module_ = std::make_unique<ros2_rl_vision_llm::ReinforcementLearning>();
        vision_module_ = std::make_unique<ros2_rl_vision_llm::VisionAI>();
        llm_module_ = std::make_unique<ros2_rl_vision_llm::LLMInterface>();

        rl_module_->initialize();
        vision_module_->initialize();
        llm_module_->initialize();

        // Create publishers
        cmd_vel_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
        status_pub_ = this->create_publisher<std_msgs::msg::String>("system_status", 10);

        // Create subscriptions
        image_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            "camera/image_raw", 10,
            std::bind(&RLVisionLLMNode::imageCallback, this, std::placeholders::_1));

        command_sub_ = this->create_subscription<std_msgs::msg::String>(
            "voice_command", 10,
            std::bind(&RLVisionLLMNode::commandCallback, this, std::placeholders::_1));

        // Create timer for periodic processing
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100),
            std::bind(&RLVisionLLMNode::processLoop, this));

        RCLCPP_INFO(this->get_logger(), "ROS2 RL-Vision-LLM Node initialized");
    }

private:
    void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg) {
        // Process incoming camera images
        std::vector<unsigned char> image_data(msg->data.begin(), msg->data.end());
        
        // Vision AI: Detect objects
        auto detections = vision_module_->detectObjects(
            image_data, msg->width, msg->height);
        
        // Extract features for RL
        auto features = vision_module_->extractFeatures(
            image_data, msg->width, msg->height);
        
        // Store for RL training
        current_state_ = features;
        
        // Update detection status
        if (!detections.empty()) {
            RCLCPP_DEBUG(this->get_logger(), 
                "Detected %zu objects", detections.size());
        }
    }

    void commandCallback(const std_msgs::msg::String::SharedPtr msg) {
        // Process natural language commands via LLM
        auto response = llm_module_->processCommand(msg->data);
        
        RCLCPP_INFO(this->get_logger(), 
            "Command processed: %s (confidence: %.2f)", 
            response.text.c_str(), response.confidence);
        
        // Execute command based on LLM interpretation
        executeCommand(response.text);
    }

    void processLoop() {
        // Main processing loop integrating RL, Vision, and LLM
        
        if (current_state_.empty()) {
            return;
        }
        
        // RL: Predict action based on current state
        auto action_values = rl_module_->predict(current_state_);
        
        if (action_values.empty()) {
            RCLCPP_WARN(this->get_logger(), "Empty action values from RL module");
            return;
        }
        
        // Find best action
        auto max_it = std::max_element(action_values.begin(), action_values.end());
        int best_action = std::distance(action_values.begin(), max_it);
        
        // LLM: Interpret action
        auto action_interpretation = llm_module_->interpretAction(current_state_);
        
        // Execute action
        executeAction(best_action);
        
        // Calculate reward (simplified)
        double reward = calculateReward();
        
        // RL: Train with experience
        rl_module_->train(current_state_, reward);
        rl_module_->updatePolicy();
        
        // Publish status
        publishStatus(action_interpretation);
    }

    void executeCommand(const std::string& command) {
        geometry_msgs::msg::Twist cmd_vel;
        
        if (command == "MOVE_COMMAND") {
            cmd_vel.linear.x = 0.5;
        } else if (command == "STOP_COMMAND") {
            cmd_vel.linear.x = 0.0;
            cmd_vel.angular.z = 0.0;
        }
        
        cmd_vel_pub_->publish(cmd_vel);
    }

    void executeAction(int action) {
        geometry_msgs::msg::Twist cmd_vel;
        
        switch(action) {
            case 0: // Move forward
                cmd_vel.linear.x = 0.3;
                break;
            case 1: // Move backward
                cmd_vel.linear.x = -0.3;
                break;
            case 2: // Turn left
                cmd_vel.angular.z = 0.5;
                break;
            case 3: // Turn right
                cmd_vel.angular.z = -0.5;
                break;
            default:
                break;
        }
        
        cmd_vel_pub_->publish(cmd_vel);
    }

    double calculateReward() {
        // Simplified reward calculation
        // In real implementation, this would be based on task completion
        return 0.1;
    }

    void publishStatus(const std::string& status) {
        auto msg = std_msgs::msg::String();
        msg.data = "Status: " + status;
        status_pub_->publish(msg);
    }

    // Modules
    std::unique_ptr<ros2_rl_vision_llm::ReinforcementLearning> rl_module_;
    std::unique_ptr<ros2_rl_vision_llm::VisionAI> vision_module_;
    std::unique_ptr<ros2_rl_vision_llm::LLMInterface> llm_module_;

    // ROS2 components
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr status_pub_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr command_sub_;
    rclcpp::TimerBase::SharedPtr timer_;

    // State
    std::vector<double> current_state_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RLVisionLLMNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
