//#define DEBUG_PRIORITY

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32_multi_array.hpp"
#include "std_msgs/msg/int32.hpp"
#include <deque>
#include <map>
#include <vector>
#include <queue>

class SignalHandlerNode : public rclcpp::Node
{
public:
    SignalHandlerNode() : Node("signal_handler")
    {
        rclcpp::QoS qos_settings(2);  // Buffer size
        qos_settings.reliability(RMW_QOS_POLICY_RELIABILITY_RELIABLE);
        qos_settings.durability(RMW_QOS_POLICY_DURABILITY_VOLATILE);
        subscriber_ = this->create_subscription<std_msgs::msg::Int32MultiArray>(
            "classification_results",
            qos_settings,
            std::bind(&SignalHandlerNode::handle_signal, this, std::placeholders::_1));

        publisher_ = this->create_publisher<std_msgs::msg::Int32>("current_state", 10);

        history_size = 5; 
        initialize_priorities_and_votes();
    }

private:
    std::deque<std::vector<int>> signal_history;
    std::queue<int> state_queue;
    int history_size;
    std::map<int, int> priority_map;
    std::map<int, int> vote_threshold;
    rclcpp::Subscription<std_msgs::msg::Int32MultiArray>::SharedPtr subscriber_;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;

    void initialize_priorities_and_votes() {
        // Initialize signal priorities and voting thresholds
        priority_map[0] = 2; vote_threshold[0] = 3; // Turn Right
        priority_map[1] = 2; vote_threshold[1] = 3; // Turn Left
        priority_map[2] = 3; vote_threshold[2] = 1; // Semaphore (Yellow)
        priority_map[3] = 3; vote_threshold[3] = 1; // SlowByConstruction
        priority_map[4] = 1; vote_threshold[4] = 1; // Semaphore (Red)
        priority_map[5] = 4; vote_threshold[5] = 4; // Rond
        priority_map[6] = 1; vote_threshold[6] = 1; // Stop
        priority_map[7] = 2; vote_threshold[7] = 1; // Forward
        priority_map[8] = 3; vote_threshold[8] = 2; // SlowByConstruction
        priority_map[9] = 3; vote_threshold[9] = 2; // Semaphore (Green)

    }

    void handle_signal(const std_msgs::msg::Int32MultiArray::SharedPtr msg) {
        if (msg->data.empty()) {
            #ifdef DEBUG_PRIORITY
                RCLCPP_INFO(this->get_logger(), "Received empty results.");
            #endif

            std_msgs::msg::Int32 state_msg;
            state_msg.data = 1;
            publisher_->publish(state_msg);
            return;
        }

        update_history(msg->data);
        std::vector<int> most_frequent_signals = get_most_frequent_signals();
        std::vector<int> prioritized_signals = filter_by_priority(most_frequent_signals);
        update_state_queue(prioritized_signals);
        process_state_queue();
    }

    void update_history(const std::vector<int>& new_data) {
        if (signal_history.size() >= history_size) {
            signal_history.pop_front();
        }
        signal_history.push_back(new_data);
    }

    std::vector<int> get_most_frequent_signals() {
        std::map<int, int> frequency;
        for (const auto& signals : signal_history) {
            for (int signal : signals) {
                if (++frequency[signal] >= vote_threshold[signal]) {
                    frequency[signal] = vote_threshold[signal]; // Cap frequency at threshold to avoid overcount
                }
            }
        }

        std::vector<int> valid_signals;
        for (const auto& pair : frequency) {
            if (pair.second == vote_threshold[pair.first]) {
                valid_signals.push_back(pair.first);
            }
        }

        return valid_signals;
    }

    std::vector<int> filter_by_priority(const std::vector<int>& signals) {
        std::vector<int> prioritized;
        int highest_priority = 4;
        for (int signal : signals) {
            int priority = priority_map[signal];
            if (priority < highest_priority) {
                highest_priority = priority;
                prioritized.clear();
                prioritized.push_back(signal);
            } else if (priority == highest_priority) {
                prioritized.push_back(signal);
            }
        }

        return prioritized;
    }

    void update_state_queue(const std::vector<int>& prioritized_signals) {
        for (int signal : prioritized_signals) {
            int new_state = signal_to_state_code(signal);
            if (state_queue.empty() || state_queue.back() != new_state) {
                state_queue.push(new_state);
            }
        }

        if (state_queue.empty()) {
            state_queue.push(1);  // IDLE represented as 1
        }
    }

    int signal_to_state_code(int signal) {
        switch(signal) {
            case 0: return 5; // Turn Right         // TurnRight
            case 1: return 4; // Turn Left          // TurnLeft
            case 2: return 1; // Semaphore(Yellow)  // Idle
            case 3: return 3; // SlowByConstruction // Slow
            case 4: return 2; // Semaphore (Red)    // Stop
            case 5: return 3; // Rond               // Slow
            case 6: return 2; // Stop               // Stop
            case 7: return 1; // Forward            // Idle
            case 8: return 3; // SlowByConstruction // Slow
            case 9: return 1; // Semaphore (Green)  // Idle
            default: return 1; // None              // Idle      
        }
    }

    void process_state_queue() {
        if (!state_queue.empty()) {
            int current_state = state_queue.front();
            state_queue.pop();
            execute_state_action(current_state);
            publish_current_state(current_state);
        }
    }

    void execute_state_action(int state_code) {
        #ifdef DEBUG_PRIORITY
            RCLCPP_INFO(this->get_logger(), "Executing action for state code: %d", state_code);
        #endif
    }

    void publish_current_state(int state_code) {
        std_msgs::msg::Int32 state_msg;
        state_msg.data = state_code;
        publisher_->publish(state_msg);
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SignalHandlerNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
