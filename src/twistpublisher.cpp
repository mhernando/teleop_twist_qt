#include "twistpublisher.h"

TwistPublisher::TwistPublisher(): Node("teleop_twist_qt")
{
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);

}
void TwistPublisher::publish_message()
{
    auto message = geometry_msgs::msg::Twist();
    message.linear.x = static_cast<double>(1);
    message.angular.z = static_cast<double>(1);
    RCLCPP_INFO(this->get_logger(), "Publicando: '%f'", message.linear.x);
    publisher_->publish(message);
}
