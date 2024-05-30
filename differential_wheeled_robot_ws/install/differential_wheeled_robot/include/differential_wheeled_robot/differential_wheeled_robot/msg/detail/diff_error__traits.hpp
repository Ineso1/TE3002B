// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from differential_wheeled_robot:msg/DiffError.idl
// generated code does not contain a copyright notice

#ifndef DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__DIFF_ERROR__TRAITS_HPP_
#define DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__DIFF_ERROR__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "differential_wheeled_robot/msg/detail/diff_error__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace differential_wheeled_robot
{

namespace msg
{

inline void to_flow_style_yaml(
  const DiffError & msg,
  std::ostream & out)
{
  out << "{";
  // member: error_ang
  {
    out << "error_ang: ";
    rosidl_generator_traits::value_to_yaml(msg.error_ang, out);
    out << ", ";
  }

  // member: error_dist
  {
    out << "error_dist: ";
    rosidl_generator_traits::value_to_yaml(msg.error_dist, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DiffError & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: error_ang
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "error_ang: ";
    rosidl_generator_traits::value_to_yaml(msg.error_ang, out);
    out << "\n";
  }

  // member: error_dist
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "error_dist: ";
    rosidl_generator_traits::value_to_yaml(msg.error_dist, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DiffError & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace differential_wheeled_robot

namespace rosidl_generator_traits
{

[[deprecated("use differential_wheeled_robot::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const differential_wheeled_robot::msg::DiffError & msg,
  std::ostream & out, size_t indentation = 0)
{
  differential_wheeled_robot::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use differential_wheeled_robot::msg::to_yaml() instead")]]
inline std::string to_yaml(const differential_wheeled_robot::msg::DiffError & msg)
{
  return differential_wheeled_robot::msg::to_yaml(msg);
}

template<>
inline const char * data_type<differential_wheeled_robot::msg::DiffError>()
{
  return "differential_wheeled_robot::msg::DiffError";
}

template<>
inline const char * name<differential_wheeled_robot::msg::DiffError>()
{
  return "differential_wheeled_robot/msg/DiffError";
}

template<>
struct has_fixed_size<differential_wheeled_robot::msg::DiffError>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<differential_wheeled_robot::msg::DiffError>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<differential_wheeled_robot::msg::DiffError>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__DIFF_ERROR__TRAITS_HPP_
