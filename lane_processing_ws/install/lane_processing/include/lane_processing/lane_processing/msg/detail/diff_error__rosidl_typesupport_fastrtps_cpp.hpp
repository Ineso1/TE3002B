// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from lane_processing:msg/DiffError.idl
// generated code does not contain a copyright notice

#ifndef LANE_PROCESSING__MSG__DETAIL__DIFF_ERROR__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define LANE_PROCESSING__MSG__DETAIL__DIFF_ERROR__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "lane_processing/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "lane_processing/msg/detail/diff_error__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace lane_processing
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_lane_processing
cdr_serialize(
  const lane_processing::msg::DiffError & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_lane_processing
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  lane_processing::msg::DiffError & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_lane_processing
get_serialized_size(
  const lane_processing::msg::DiffError & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_lane_processing
max_serialized_size_DiffError(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace lane_processing

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_lane_processing
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, lane_processing, msg, DiffError)();

#ifdef __cplusplus
}
#endif

#endif  // LANE_PROCESSING__MSG__DETAIL__DIFF_ERROR__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
