#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <std_msgs/msg/int16.hpp>
#include <iostream>
 
using namespace std::chrono_literals;
using namespace std;
 
class Publisher : public rclcpp::Node{
public:
    Publisher() : Node("publisher"), count_(0) {
        publisher_ = this ->create_publisher<std_msgs::msg::Int16>("topic", 2);
        timer_ = this ->create_wall_timer(500ms, std::bind(&Publisher::timer_callback, this));
    }
    
private:
    void timer_callback(){
        auto message = std_msgs::msg::Int16();
        message.data = count_++;
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data);
        publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Int16>::SharedPtr publisher_;
    size_t count_;
};
 
int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Publisher>());
    rclcpp::shutdown();
    return 0;
}
