// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from differential_wheeled_robot:msg/DiffError.idl
// generated code does not contain a copyright notice

#ifndef DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__DIFF_ERROR__STRUCT_H_
#define DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__DIFF_ERROR__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/DiffError in the package differential_wheeled_robot.
typedef struct differential_wheeled_robot__msg__DiffError
{
  double error_ang;
  double error_dist;
} differential_wheeled_robot__msg__DiffError;

// Struct for a sequence of differential_wheeled_robot__msg__DiffError.
typedef struct differential_wheeled_robot__msg__DiffError__Sequence
{
  differential_wheeled_robot__msg__DiffError * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} differential_wheeled_robot__msg__DiffError__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__DIFF_ERROR__STRUCT_H_
