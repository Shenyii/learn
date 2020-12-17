/** talker.cpp **/

#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <memory>
#include <std_msgs/msg/string.hpp>
#include <iostream>
#include "learn/msg/robot_state.hpp"
 
using namespace std::chrono_literals;
using namespace std;
 
class Publisher : public rclcpp::Node{
public:
    Publisher() : Node("publisher"), count_(0) {
        publisher_ = this ->create_publisher<std_msgs::msg::String>("topic", 2);
        //timer_ = this ->create_wall_timer(500ms, std::bind(&Publisher::timer_callback, this));

        pub_robot_state_ = this ->create_publisher<learn::msg::RobotState>("robotstate", 2);
        timer1_ = this ->create_wall_timer(500ms, std::bind(&Publisher::pubRobotState, this));
    }
    
private:
    void timer_callback(){
        auto message = std_msgs::msg::String();
        message.data = "Hello World! " + std::to_string(count_++);
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        publisher_->publish(message);
    }

    void pubRobotState() {
        auto msg = learn::msg::RobotState();
        msg.id = 0;
        msg.frame_id = "map";
        msg.x = 0;
        msg.y = 0;
        msg.theta = 0;
        msg.v = 0;
        msg.w = 0;
        pub_robot_state_->publish(msg);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer1_;
    rclcpp::Publisher<learn::msg::RobotState>::SharedPtr pub_robot_state_;
    size_t count_;
};
 
int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Publisher>());
    rclcpp::shutdown();
    return 0;
}

