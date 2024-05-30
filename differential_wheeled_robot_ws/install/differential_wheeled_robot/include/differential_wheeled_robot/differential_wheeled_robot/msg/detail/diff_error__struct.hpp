// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from differential_wheeled_robot:msg/DiffError.idl
// generated code does not contain a copyright notice

#ifndef DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__DIFF_ERROR__STRUCT_HPP_
#define DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__DIFF_ERROR__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__differential_wheeled_robot__msg__DiffError __attribute__((deprecated))
#else
# define DEPRECATED__differential_wheeled_robot__msg__DiffError __declspec(deprecated)
#endif

namespace differential_wheeled_robot
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DiffError_
{
  using Type = DiffError_<ContainerAllocator>;

  explicit DiffError_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->error_ang = 0.0;
      this->error_dist = 0.0;
    }
  }

  explicit DiffError_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->error_ang = 0.0;
      this->error_dist = 0.0;
    }
  }

  // field types and members
  using _error_ang_type =
    double;
  _error_ang_type error_ang;
  using _error_dist_type =
    double;
  _error_dist_type error_dist;

  // setters for named parameter idiom
  Type & set__error_ang(
    const double & _arg)
  {
    this->error_ang = _arg;
    return *this;
  }
  Type & set__error_dist(
    const double & _arg)
  {
    this->error_dist = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    differential_wheeled_robot::msg::DiffError_<ContainerAllocator> *;
  using ConstRawPtr =
    const differential_wheeled_robot::msg::DiffError_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<differential_wheeled_robot::msg::DiffError_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<differential_wheeled_robot::msg::DiffError_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      differential_wheeled_robot::msg::DiffError_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<differential_wheeled_robot::msg::DiffError_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      differential_wheeled_robot::msg::DiffError_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<differential_wheeled_robot::msg::DiffError_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<differential_wheeled_robot::msg::DiffError_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<differential_wheeled_robot::msg::DiffError_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__differential_wheeled_robot__msg__DiffError
    std::shared_ptr<differential_wheeled_robot::msg::DiffError_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__differential_wheeled_robot__msg__DiffError
    std::shared_ptr<differential_wheeled_robot::msg::DiffError_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DiffError_ & other) const
  {
    if (this->error_ang != other.error_ang) {
      return false;
    }
    if (this->error_dist != other.error_dist) {
      return false;
    }
    return true;
  }
  bool operator!=(const DiffError_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DiffError_

// alias to use template instance with default allocator
using DiffError =
  differential_wheeled_robot::msg::DiffError_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace differential_wheeled_robot

#endif  // DIFFERENTIAL_WHEELED_ROBOT__MSG__DETAIL__DIFF_ERROR__STRUCT_HPP_
