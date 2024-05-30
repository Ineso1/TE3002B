// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from differential_wheeled_robot:msg/DiffError.idl
// generated code does not contain a copyright notice
#include "differential_wheeled_robot/msg/detail/diff_error__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
differential_wheeled_robot__msg__DiffError__init(differential_wheeled_robot__msg__DiffError * msg)
{
  if (!msg) {
    return false;
  }
  // error_ang
  // error_dist
  return true;
}

void
differential_wheeled_robot__msg__DiffError__fini(differential_wheeled_robot__msg__DiffError * msg)
{
  if (!msg) {
    return;
  }
  // error_ang
  // error_dist
}

bool
differential_wheeled_robot__msg__DiffError__are_equal(const differential_wheeled_robot__msg__DiffError * lhs, const differential_wheeled_robot__msg__DiffError * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // error_ang
  if (lhs->error_ang != rhs->error_ang) {
    return false;
  }
  // error_dist
  if (lhs->error_dist != rhs->error_dist) {
    return false;
  }
  return true;
}

bool
differential_wheeled_robot__msg__DiffError__copy(
  const differential_wheeled_robot__msg__DiffError * input,
  differential_wheeled_robot__msg__DiffError * output)
{
  if (!input || !output) {
    return false;
  }
  // error_ang
  output->error_ang = input->error_ang;
  // error_dist
  output->error_dist = input->error_dist;
  return true;
}

differential_wheeled_robot__msg__DiffError *
differential_wheeled_robot__msg__DiffError__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  differential_wheeled_robot__msg__DiffError * msg = (differential_wheeled_robot__msg__DiffError *)allocator.allocate(sizeof(differential_wheeled_robot__msg__DiffError), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(differential_wheeled_robot__msg__DiffError));
  bool success = differential_wheeled_robot__msg__DiffError__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
differential_wheeled_robot__msg__DiffError__destroy(differential_wheeled_robot__msg__DiffError * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    differential_wheeled_robot__msg__DiffError__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
differential_wheeled_robot__msg__DiffError__Sequence__init(differential_wheeled_robot__msg__DiffError__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  differential_wheeled_robot__msg__DiffError * data = NULL;

  if (size) {
    data = (differential_wheeled_robot__msg__DiffError *)allocator.zero_allocate(size, sizeof(differential_wheeled_robot__msg__DiffError), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = differential_wheeled_robot__msg__DiffError__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        differential_wheeled_robot__msg__DiffError__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
differential_wheeled_robot__msg__DiffError__Sequence__fini(differential_wheeled_robot__msg__DiffError__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      differential_wheeled_robot__msg__DiffError__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

differential_wheeled_robot__msg__DiffError__Sequence *
differential_wheeled_robot__msg__DiffError__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  differential_wheeled_robot__msg__DiffError__Sequence * array = (differential_wheeled_robot__msg__DiffError__Sequence *)allocator.allocate(sizeof(differential_wheeled_robot__msg__DiffError__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = differential_wheeled_robot__msg__DiffError__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
differential_wheeled_robot__msg__DiffError__Sequence__destroy(differential_wheeled_robot__msg__DiffError__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    differential_wheeled_robot__msg__DiffError__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
differential_wheeled_robot__msg__DiffError__Sequence__are_equal(const differential_wheeled_robot__msg__DiffError__Sequence * lhs, const differential_wheeled_robot__msg__DiffError__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!differential_wheeled_robot__msg__DiffError__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
differential_wheeled_robot__msg__DiffError__Sequence__copy(
  const differential_wheeled_robot__msg__DiffError__Sequence * input,
  differential_wheeled_robot__msg__DiffError__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(differential_wheeled_robot__msg__DiffError);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    differential_wheeled_robot__msg__DiffError * data =
      (differential_wheeled_robot__msg__DiffError *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!differential_wheeled_robot__msg__DiffError__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          differential_wheeled_robot__msg__DiffError__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!differential_wheeled_robot__msg__DiffError__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
