// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from differential_wheeled_robot:msg/Path.idl
// generated code does not contain a copyright notice

#ifndef DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__PATH__TRAITS_HPP_
#define DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__PATH__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "differential_wheeled_robot/msg/detail/path__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'data'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace differential_wheeled_robot
{

namespace msg
{

inline void to_flow_style_yaml(
  const Path & msg,
  std::ostream & out)
{
  out << "{";
  // member: data
  {
    if (msg.data.size() == 0) {
      out << "data: []";
    } else {
      out << "data: [";
      size_t pending_items = msg.data.size();
      for (auto item : msg.data) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Path & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.data.size() == 0) {
      out << "data: []\n";
    } else {
      out << "data:\n";
      for (auto item : msg.data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Path & msg, bool use_flow_style = false)
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
  const differential_wheeled_robot::msg::Path & msg,
  std::ostream & out, size_t indentation = 0)
{
  differential_wheeled_robot::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use differential_wheeled_robot::msg::to_yaml() instead")]]
inline std::string to_yaml(const differential_wheeled_robot::msg::Path & msg)
{
  return differential_wheeled_robot::msg::to_yaml(msg);
}

template<>
inline const char * data_type<differential_wheeled_robot::msg::Path>()
{
  return "differential_wheeled_robot::msg::Path";
}

template<>
inline const char * name<differential_wheeled_robot::msg::Path>()
{
  return "differential_wheeled_robot/msg/Path";
}

template<>
struct has_fixed_size<differential_wheeled_robot::msg::Path>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<differential_wheeled_robot::msg::Path>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<differential_wheeled_robot::msg::Path>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__PATH__TRAITS_HPP_
