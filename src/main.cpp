#include <cstdio>

#include "rclcpp/rclcpp.hpp"
#include "parameter_test/outer_node.hpp"

using namespace std::chrono_literals;

int main(int argc, char ** argv)
{
  printf("hello world parameter_test package\n");
  rclcpp::init(argc, argv);

  auto outer_node = std::make_shared<parameter_test::OuterNode>();
  outer_node->init();

  rclcpp::WallRate loop_rate(1s);
  while (rclcpp::ok()) {
    rclcpp::spin_some(outer_node);
    loop_rate.sleep();
  }

  rclcpp::shutdown();
  return 0;
}
