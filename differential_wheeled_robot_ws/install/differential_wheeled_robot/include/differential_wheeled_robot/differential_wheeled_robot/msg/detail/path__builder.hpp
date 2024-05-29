// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from differential_wheeled_robot:msg/Path.idl
// generated code does not contain a copyright notice

#ifndef DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__PATH__BUILDER_HPP_
#define DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__PATH__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "differential_wheeled_robot/msg/detail/path__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace differential_wheeled_robot
{

namespace msg
{

namespace builder
{

class Init_Path_data
{
public:
  Init_Path_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::differential_wheeled_robot::msg::Path data(::differential_wheeled_robot::msg::Path::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::differential_wheeled_robot::msg::Path msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::differential_wheeled_robot::msg::Path>()
{
  return differential_wheeled_robot::msg::builder::Init_Path_data();
}

}  // namespace differential_wheeled_robot

#endif  // DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__PATH__BUILDER_HPP_
