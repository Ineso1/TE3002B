// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from lane_processing:msg/DiffError.idl
// generated code does not contain a copyright notice

#ifndef LANE_PROCESSING__MSG__DETAIL__DIFF_ERROR__TRAITS_HPP_
#define LANE_PROCESSING__MSG__DETAIL__DIFF_ERROR__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "lane_processing/msg/detail/diff_error__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace lane_processing
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

}  // namespace lane_processing

namespace rosidl_generator_traits
{

[[deprecated("use lane_processing::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const lane_processing::msg::DiffError & msg,
  std::ostream & out, size_t indentation = 0)
{
  lane_processing::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use lane_processing::msg::to_yaml() instead")]]
inline std::string to_yaml(const lane_processing::msg::DiffError & msg)
{
  return lane_processing::msg::to_yaml(msg);
}

template<>
inline const char * data_type<lane_processing::msg::DiffError>()
{
  return "lane_processing::msg::DiffError";
}

template<>
inline const char * name<lane_processing::msg::DiffError>()
{
  return "lane_processing/msg/DiffError";
}

template<>
struct has_fixed_size<lane_processing::msg::DiffError>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<lane_processing::msg::DiffError>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<lane_processing::msg::DiffError>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // LANE_PROCESSING__MSG__DETAIL__DIFF_ERROR__TRAITS_HPP_
