// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from puzzle_pkg:msg/DiffError.idl
// generated code does not contain a copyright notice
#include "puzzle_pkg/msg/detail/diff_error__rosidl_typesupport_fastrtps_cpp.hpp"
#include "puzzle_pkg/msg/detail/diff_error__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace puzzle_pkg
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_puzzle_pkg
cdr_serialize(
  const puzzle_pkg::msg::DiffError & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: error_ang
  cdr << ros_message.error_ang;
  // Member: error_dist
  cdr << ros_message.error_dist;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_puzzle_pkg
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  puzzle_pkg::msg::DiffError & ros_message)
{
  // Member: error_ang
  cdr >> ros_message.error_ang;

  // Member: error_dist
  cdr >> ros_message.error_dist;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_puzzle_pkg
get_serialized_size(
  const puzzle_pkg::msg::DiffError & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: error_ang
  {
    size_t item_size = sizeof(ros_message.error_ang);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: error_dist
  {
    size_t item_size = sizeof(ros_message.error_dist);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_puzzle_pkg
max_serialized_size_DiffError(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: error_ang
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: error_dist
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = puzzle_pkg::msg::DiffError;
    is_plain =
      (
      offsetof(DataType, error_dist) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _DiffError__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const puzzle_pkg::msg::DiffError *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _DiffError__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<puzzle_pkg::msg::DiffError *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _DiffError__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const puzzle_pkg::msg::DiffError *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _DiffError__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_DiffError(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _DiffError__callbacks = {
  "puzzle_pkg::msg",
  "DiffError",
  _DiffError__cdr_serialize,
  _DiffError__cdr_deserialize,
  _DiffError__get_serialized_size,
  _DiffError__max_serialized_size
};

static rosidl_message_type_support_t _DiffError__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_DiffError__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace puzzle_pkg

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_puzzle_pkg
const rosidl_message_type_support_t *
get_message_type_support_handle<puzzle_pkg::msg::DiffError>()
{
  return &puzzle_pkg::msg::typesupport_fastrtps_cpp::_DiffError__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, puzzle_pkg, msg, DiffError)() {
  return &puzzle_pkg::msg::typesupport_fastrtps_cpp::_DiffError__handle;
}

#ifdef __cplusplus
}
#endif
