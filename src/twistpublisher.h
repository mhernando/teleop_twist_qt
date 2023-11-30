#ifndef TWISTPUBLISHER_H
#define TWISTPUBLISHER_H

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

class TwistPublisher : public rclcpp::Node
{
public:
    TwistPublisher();
     void publish_message();
private:

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

#endif // TWISTPUBLISHER_H
