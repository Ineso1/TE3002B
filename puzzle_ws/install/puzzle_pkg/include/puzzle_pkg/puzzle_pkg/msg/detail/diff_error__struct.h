// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from puzzle_pkg:msg/DiffError.idl
// generated code does not contain a copyright notice

#ifndef PUZZLE_PKG__MSG__DETAIL__DIFF_ERROR__STRUCT_H_
#define PUZZLE_PKG__MSG__DETAIL__DIFF_ERROR__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/DiffError in the package puzzle_pkg.
typedef struct puzzle_pkg__msg__DiffError
{
  double error_ang;
  double error_dist;
} puzzle_pkg__msg__DiffError;

// Struct for a sequence of puzzle_pkg__msg__DiffError.
typedef struct puzzle_pkg__msg__DiffError__Sequence
{
  puzzle_pkg__msg__DiffError * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} puzzle_pkg__msg__DiffError__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PUZZLE_PKG__MSG__DETAIL__DIFF_ERROR__STRUCT_H_
