// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from differential_wheeled_robot:msg/Path.idl
// generated code does not contain a copyright notice

#ifndef DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__PATH__STRUCT_H_
#define DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__PATH__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'data'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/Path in the package differential_wheeled_robot.
typedef struct differential_wheeled_robot__msg__Path
{
  geometry_msgs__msg__Point__Sequence data;
} differential_wheeled_robot__msg__Path;

// Struct for a sequence of differential_wheeled_robot__msg__Path.
typedef struct differential_wheeled_robot__msg__Path__Sequence
{
  differential_wheeled_robot__msg__Path * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} differential_wheeled_robot__msg__Path__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__PATH__STRUCT_H_
