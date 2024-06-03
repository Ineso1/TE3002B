// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from lane_processing:msg/DiffError.idl
// generated code does not contain a copyright notice

#ifndef LANE_PROCESSING__MSG__DETAIL__DIFF_ERROR__FUNCTIONS_H_
#define LANE_PROCESSING__MSG__DETAIL__DIFF_ERROR__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "lane_processing/msg/rosidl_generator_c__visibility_control.h"

#include "lane_processing/msg/detail/diff_error__struct.h"

/// Initialize msg/DiffError message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * lane_processing__msg__DiffError
 * )) before or use
 * lane_processing__msg__DiffError__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_lane_processing
bool
lane_processing__msg__DiffError__init(lane_processing__msg__DiffError * msg);

/// Finalize msg/DiffError message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_lane_processing
void
lane_processing__msg__DiffError__fini(lane_processing__msg__DiffError * msg);

/// Create msg/DiffError message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * lane_processing__msg__DiffError__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_lane_processing
lane_processing__msg__DiffError *
lane_processing__msg__DiffError__create();

/// Destroy msg/DiffError message.
/**
 * It calls
 * lane_processing__msg__DiffError__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_lane_processing
void
lane_processing__msg__DiffError__destroy(lane_processing__msg__DiffError * msg);

/// Check for msg/DiffError message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_lane_processing
bool
lane_processing__msg__DiffError__are_equal(const lane_processing__msg__DiffError * lhs, const lane_processing__msg__DiffError * rhs);

/// Copy a msg/DiffError message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_lane_processing
bool
lane_processing__msg__DiffError__copy(
  const lane_processing__msg__DiffError * input,
  lane_processing__msg__DiffError * output);

/// Initialize array of msg/DiffError messages.
/**
 * It allocates the memory for the number of elements and calls
 * lane_processing__msg__DiffError__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_lane_processing
bool
lane_processing__msg__DiffError__Sequence__init(lane_processing__msg__DiffError__Sequence * array, size_t size);

/// Finalize array of msg/DiffError messages.
/**
 * It calls
 * lane_processing__msg__DiffError__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_lane_processing
void
lane_processing__msg__DiffError__Sequence__fini(lane_processing__msg__DiffError__Sequence * array);

/// Create array of msg/DiffError messages.
/**
 * It allocates the memory for the array and calls
 * lane_processing__msg__DiffError__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_lane_processing
lane_processing__msg__DiffError__Sequence *
lane_processing__msg__DiffError__Sequence__create(size_t size);

/// Destroy array of msg/DiffError messages.
/**
 * It calls
 * lane_processing__msg__DiffError__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_lane_processing
void
lane_processing__msg__DiffError__Sequence__destroy(lane_processing__msg__DiffError__Sequence * array);

/// Check for msg/DiffError message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_lane_processing
bool
lane_processing__msg__DiffError__Sequence__are_equal(const lane_processing__msg__DiffError__Sequence * lhs, const lane_processing__msg__DiffError__Sequence * rhs);

/// Copy an array of msg/DiffError messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_lane_processing
bool
lane_processing__msg__DiffError__Sequence__copy(
  const lane_processing__msg__DiffError__Sequence * input,
  lane_processing__msg__DiffError__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // LANE_PROCESSING__MSG__DETAIL__DIFF_ERROR__FUNCTIONS_H_
