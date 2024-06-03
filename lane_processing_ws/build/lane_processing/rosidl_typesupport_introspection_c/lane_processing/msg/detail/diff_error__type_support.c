// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from lane_processing:msg/DiffError.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "lane_processing/msg/detail/diff_error__rosidl_typesupport_introspection_c.h"
#include "lane_processing/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "lane_processing/msg/detail/diff_error__functions.h"
#include "lane_processing/msg/detail/diff_error__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void lane_processing__msg__DiffError__rosidl_typesupport_introspection_c__DiffError_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  lane_processing__msg__DiffError__init(message_memory);
}

void lane_processing__msg__DiffError__rosidl_typesupport_introspection_c__DiffError_fini_function(void * message_memory)
{
  lane_processing__msg__DiffError__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember lane_processing__msg__DiffError__rosidl_typesupport_introspection_c__DiffError_message_member_array[2] = {
  {
    "error_ang",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lane_processing__msg__DiffError, error_ang),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "error_dist",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lane_processing__msg__DiffError, error_dist),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers lane_processing__msg__DiffError__rosidl_typesupport_introspection_c__DiffError_message_members = {
  "lane_processing__msg",  // message namespace
  "DiffError",  // message name
  2,  // number of fields
  sizeof(lane_processing__msg__DiffError),
  lane_processing__msg__DiffError__rosidl_typesupport_introspection_c__DiffError_message_member_array,  // message members
  lane_processing__msg__DiffError__rosidl_typesupport_introspection_c__DiffError_init_function,  // function to initialize message memory (memory has to be allocated)
  lane_processing__msg__DiffError__rosidl_typesupport_introspection_c__DiffError_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t lane_processing__msg__DiffError__rosidl_typesupport_introspection_c__DiffError_message_type_support_handle = {
  0,
  &lane_processing__msg__DiffError__rosidl_typesupport_introspection_c__DiffError_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_lane_processing
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lane_processing, msg, DiffError)() {
  if (!lane_processing__msg__DiffError__rosidl_typesupport_introspection_c__DiffError_message_type_support_handle.typesupport_identifier) {
    lane_processing__msg__DiffError__rosidl_typesupport_introspection_c__DiffError_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &lane_processing__msg__DiffError__rosidl_typesupport_introspection_c__DiffError_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
