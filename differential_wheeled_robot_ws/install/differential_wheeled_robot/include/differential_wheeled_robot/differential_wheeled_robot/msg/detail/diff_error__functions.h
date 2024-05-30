// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from differential_wheeled_robot:msg/DiffError.idl
// generated code does not contain a copyright notice

#ifndef DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__DIFF_ERROR__FUNCTIONS_H_
#define DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__DIFF_ERROR__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "differential_wheeled_robot/msg/rosidl_generator_c__visibility_control.h"

#include "differential_wheeled_robot/msg/detail/diff_error__struct.h"

/// Initialize msg/DiffError message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * differential_wheeled_robot__msg__DiffError
 * )) before or use
 * differential_wheeled_robot__msg__DiffError__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_differential_wheeled_robot
bool
differential_wheeled_robot__msg__DiffError__init(differential_wheeled_robot__msg__DiffError * msg);

/// Finalize msg/DiffError message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_differential_wheeled_robot
void
differential_wheeled_robot__msg__DiffError__fini(differential_wheeled_robot__msg__DiffError * msg);

/// Create msg/DiffError message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * differential_wheeled_robot__msg__DiffError__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_differential_wheeled_robot
differential_wheeled_robot__msg__DiffError *
differential_wheeled_robot__msg__DiffError__create();

/// Destroy msg/DiffError message.
/**
 * It calls
 * differential_wheeled_robot__msg__DiffError__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_differential_wheeled_robot
void
differential_wheeled_robot__msg__DiffError__destroy(differential_wheeled_robot__msg__DiffError * msg);

/// Check for msg/DiffError message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_differential_wheeled_robot
bool
differential_wheeled_robot__msg__DiffError__are_equal(const differential_wheeled_robot__msg__DiffError * lhs, const differential_wheeled_robot__msg__DiffError * rhs);

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
ROSIDL_GENERATOR_C_PUBLIC_differential_wheeled_robot
bool
differential_wheeled_robot__msg__DiffError__copy(
  const differential_wheeled_robot__msg__DiffError * input,
  differential_wheeled_robot__msg__DiffError * output);

/// Initialize array of msg/DiffError messages.
/**
 * It allocates the memory for the number of elements and calls
 * differential_wheeled_robot__msg__DiffError__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_differential_wheeled_robot
bool
differential_wheeled_robot__msg__DiffError__Sequence__init(differential_wheeled_robot__msg__DiffError__Sequence * array, size_t size);

/// Finalize array of msg/DiffError messages.
/**
 * It calls
 * differential_wheeled_robot__msg__DiffError__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_differential_wheeled_robot
void
differential_wheeled_robot__msg__DiffError__Sequence__fini(differential_wheeled_robot__msg__DiffError__Sequence * array);

/// Create array of msg/DiffError messages.
/**
 * It allocates the memory for the array and calls
 * differential_wheeled_robot__msg__DiffError__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_differential_wheeled_robot
differential_wheeled_robot__msg__DiffError__Sequence *
differential_wheeled_robot__msg__DiffError__Sequence__create(size_t size);

/// Destroy array of msg/DiffError messages.
/**
 * It calls
 * differential_wheeled_robot__msg__DiffError__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_differential_wheeled_robot
void
differential_wheeled_robot__msg__DiffError__Sequence__destroy(differential_wheeled_robot__msg__DiffError__Sequence * array);

/// Check for msg/DiffError message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_differential_wheeled_robot
bool
differential_wheeled_robot__msg__DiffError__Sequence__are_equal(const differential_wheeled_robot__msg__DiffError__Sequence * lhs, const differential_wheeled_robot__msg__DiffError__Sequence * rhs);

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
ROSIDL_GENERATOR_C_PUBLIC_differential_wheeled_robot
bool
differential_wheeled_robot__msg__DiffError__Sequence__copy(
  const differential_wheeled_robot__msg__DiffError__Sequence * input,
  differential_wheeled_robot__msg__DiffError__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__DIFF_ERROR__FUNCTIONS_H_
