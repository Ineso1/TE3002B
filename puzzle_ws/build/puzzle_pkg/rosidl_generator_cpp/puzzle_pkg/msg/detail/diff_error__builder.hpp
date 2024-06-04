// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from puzzle_pkg:msg/DiffError.idl
// generated code does not contain a copyright notice

#ifndef PUZZLE_PKG__MSG__DETAIL__DIFF_ERROR__BUILDER_HPP_
#define PUZZLE_PKG__MSG__DETAIL__DIFF_ERROR__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "puzzle_pkg/msg/detail/diff_error__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace puzzle_pkg
{

namespace msg
{

namespace builder
{

class Init_DiffError_error_dist
{
public:
  explicit Init_DiffError_error_dist(::puzzle_pkg::msg::DiffError & msg)
  : msg_(msg)
  {}
  ::puzzle_pkg::msg::DiffError error_dist(::puzzle_pkg::msg::DiffError::_error_dist_type arg)
  {
    msg_.error_dist = std::move(arg);
    return std::move(msg_);
  }

private:
  ::puzzle_pkg::msg::DiffError msg_;
};

class Init_DiffError_error_ang
{
public:
  Init_DiffError_error_ang()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DiffError_error_dist error_ang(::puzzle_pkg::msg::DiffError::_error_ang_type arg)
  {
    msg_.error_ang = std::move(arg);
    return Init_DiffError_error_dist(msg_);
  }

private:
  ::puzzle_pkg::msg::DiffError msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::puzzle_pkg::msg::DiffError>()
{
  return puzzle_pkg::msg::builder::Init_DiffError_error_ang();
}

}  // namespace puzzle_pkg

#endif  // PUZZLE_PKG__MSG__DETAIL__DIFF_ERROR__BUILDER_HPP_
