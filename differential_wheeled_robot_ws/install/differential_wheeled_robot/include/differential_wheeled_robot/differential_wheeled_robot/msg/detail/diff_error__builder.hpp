// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from differential_wheeled_robot:msg/DiffError.idl
// generated code does not contain a copyright notice

#ifndef DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__DIFF_ERROR__BUILDER_HPP_
#define DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__DIFF_ERROR__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "differential_wheeled_robot/msg/detail/diff_error__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace differential_wheeled_robot
{

namespace msg
{

namespace builder
{

class Init_DiffError_error_dist
{
public:
  explicit Init_DiffError_error_dist(::differential_wheeled_robot::msg::DiffError & msg)
  : msg_(msg)
  {}
  ::differential_wheeled_robot::msg::DiffError error_dist(::differential_wheeled_robot::msg::DiffError::_error_dist_type arg)
  {
    msg_.error_dist = std::move(arg);
    return std::move(msg_);
  }

private:
  ::differential_wheeled_robot::msg::DiffError msg_;
};

class Init_DiffError_error_ang
{
public:
  Init_DiffError_error_ang()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DiffError_error_dist error_ang(::differential_wheeled_robot::msg::DiffError::_error_ang_type arg)
  {
    msg_.error_ang = std::move(arg);
    return Init_DiffError_error_dist(msg_);
  }

private:
  ::differential_wheeled_robot::msg::DiffError msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::differential_wheeled_robot::msg::DiffError>()
{
  return differential_wheeled_robot::msg::builder::Init_DiffError_error_ang();
}

}  // namespace differential_wheeled_robot

#endif  // DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__DIFF_ERROR__BUILDER_HPP_
