// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from lane_processing:msg/DiffError.idl
// generated code does not contain a copyright notice

#ifndef LANE_PROCESSING__MSG__DETAIL__DIFF_ERROR__STRUCT_H_
#define LANE_PROCESSING__MSG__DETAIL__DIFF_ERROR__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/DiffError in the package lane_processing.
typedef struct lane_processing__msg__DiffError
{
  double error_ang;
  double error_dist;
} lane_processing__msg__DiffError;

// Struct for a sequence of lane_processing__msg__DiffError.
typedef struct lane_processing__msg__DiffError__Sequence
{
  lane_processing__msg__DiffError * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} lane_processing__msg__DiffError__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // LANE_PROCESSING__MSG__DETAIL__DIFF_ERROR__STRUCT_H_
