#ifndef PARAMETER_TEST__OUTER_NODE_HPP_
#define PARAMETER_TEST__OUTER_NODE_HPP_

#include <memory>

#include "parameter_test/visibility_control.h"

#include "parameter_test/inner_node.hpp"

#include "rclcpp/rclcpp.hpp"

namespace parameter_test
{

class OuterNode : public rclcpp::Node
{
public:
  OuterNode()
  : rclcpp::Node("parameter_test_node")
  {}

  virtual ~OuterNode() = default;

  void init()
  {
    this->declare_parameter<int>("my_int_parameter", 42);
    callback_handle_ = this->add_on_set_parameters_callback(std::bind(&OuterNode::param_change_callback, this, std::placeholders::_1));

    inner_node_ = std::make_shared<parameter_test::InnerNode>(shared_from_this());
  }

  rcl_interfaces::msg::SetParametersResult
  param_change_callback(const std::vector<rclcpp::Parameter> & parameters)
  {
    fprintf(stderr, "setting a new set of outer_node parameters\n");

    auto result = rcl_interfaces::msg::SetParametersResult();
    result.successful = false;

    std::stringstream string_result;
    for (auto parameter : parameters) {
      rclcpp::ParameterType parameter_type = parameter.get_type();

      if (parameter.get_name().compare("my_int_parameter") == 0){
        if (parameter_type == rclcpp::ParameterType::PARAMETER_INTEGER){
          fprintf(stderr, "correct double parameter found\n");
          result.successful = true;
        } else {
          string_result << "The parameter " << parameter.get_name() << " is of the wrong type, should be a int.\n";
          result.successful = false;
        }
      }
    }

    result.reason = string_result.str();
    return result;
  }

private:
  rclcpp::node_interfaces::OnSetParametersCallbackHandle::SharedPtr callback_handle_;
  std::shared_ptr<parameter_test::InnerNode> inner_node_;
};

}  // namespace parameter_test

#endif  // PARAMETER_TEST__OUTER_NODE_HPP_
