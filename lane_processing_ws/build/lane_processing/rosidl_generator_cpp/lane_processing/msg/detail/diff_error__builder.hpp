// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from lane_processing:msg/DiffError.idl
// generated code does not contain a copyright notice

#ifndef LANE_PROCESSING__MSG__DETAIL__DIFF_ERROR__BUILDER_HPP_
#define LANE_PROCESSING__MSG__DETAIL__DIFF_ERROR__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "lane_processing/msg/detail/diff_error__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace lane_processing
{

namespace msg
{

namespace builder
{

class Init_DiffError_error_dist
{
public:
  explicit Init_DiffError_error_dist(::lane_processing::msg::DiffError & msg)
  : msg_(msg)
  {}
  ::lane_processing::msg::DiffError error_dist(::lane_processing::msg::DiffError::_error_dist_type arg)
  {
    msg_.error_dist = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lane_processing::msg::DiffError msg_;
};

class Init_DiffError_error_ang
{
public:
  Init_DiffError_error_ang()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DiffError_error_dist error_ang(::lane_processing::msg::DiffError::_error_ang_type arg)
  {
    msg_.error_ang = std::move(arg);
    return Init_DiffError_error_dist(msg_);
  }

private:
  ::lane_processing::msg::DiffError msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::lane_processing::msg::DiffError>()
{
  return lane_processing::msg::builder::Init_DiffError_error_ang();
}

}  // namespace lane_processing

#endif  // LANE_PROCESSING__MSG__DETAIL__DIFF_ERROR__BUILDER_HPP_
