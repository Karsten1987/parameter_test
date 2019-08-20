#ifndef PARAMETER_TEST__INNER_NODE_HPP_
#define PARAMETER_TEST__INNER_NODE_HPP_

#include "parameter_test/visibility_control.h"

#include "rclcpp/rclcpp.hpp"

namespace parameter_test
{

class InnerNode
{
public:
  InnerNode(std::shared_ptr<rclcpp::Node> node)
  : node_(node)
  {
    node->declare_parameter<double>("my_double_parameter", 42.0);
    callback_handle_ = node->add_on_set_parameters_callback(std::bind(&InnerNode::param_change_callback, this, std::placeholders::_1));
  }

  virtual ~InnerNode() = default;

  rcl_interfaces::msg::SetParametersResult
  param_change_callback(const std::vector<rclcpp::Parameter> & parameters)
  {
    fprintf(stderr, "setting a new set of inner_node parameters\n");

    auto result = rcl_interfaces::msg::SetParametersResult();
    result.successful = false;

    std::stringstream string_result;
    for (auto parameter : parameters) {
      rclcpp::ParameterType parameter_type = parameter.get_type();

      if (parameter.get_name().compare("my_double_parameter") == 0){
        if (parameter_type == rclcpp::ParameterType::PARAMETER_DOUBLE){
          fprintf(stderr, "correct double parameter found\n");
          result.successful = true;
        } else {
          string_result << "The parameter " << parameter.get_name() << " is of the wrong type, should be a double.\n";
          result.successful = false;
        }
      }
    }

    result.reason = string_result.str();
    return result;
  }

private:
  std::shared_ptr<rclcpp::Node> node_;
  rclcpp::node_interfaces::OnSetParametersCallbackHandle::SharedPtr callback_handle_;
};

}  // namespace parameter_test

#endif  // PARAMETER_TEST__INNER_NODE_HPP_
