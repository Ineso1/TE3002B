# generated from
# rosidl_cmake/cmake/template/rosidl_cmake_export_typesupport_targets.cmake.in

set(_exported_typesupport_targets
  "__rosidl_generator_c:differential_wheeled_robot__rosidl_generator_c;__rosidl_typesupport_fastrtps_c:differential_wheeled_robot__rosidl_typesupport_fastrtps_c;__rosidl_generator_cpp:differential_wheeled_robot__rosidl_generator_cpp;__rosidl_typesupport_fastrtps_cpp:differential_wheeled_robot__rosidl_typesupport_fastrtps_cpp;__rosidl_typesupport_introspection_c:differential_wheeled_robot__rosidl_typesupport_introspection_c;__rosidl_typesupport_c:differential_wheeled_robot__rosidl_typesupport_c;__rosidl_typesupport_introspection_cpp:differential_wheeled_robot__rosidl_typesupport_introspection_cpp;__rosidl_typesupport_cpp:differential_wheeled_robot__rosidl_typesupport_cpp;__rosidl_generator_py:differential_wheeled_robot__rosidl_generator_py")

# populate differential_wheeled_robot_TARGETS_<suffix>
if(NOT _exported_typesupport_targets STREQUAL "")
  # loop over typesupport targets
  foreach(_tuple ${_exported_typesupport_targets})
    string(REPLACE ":" ";" _tuple "${_tuple}")
    list(GET _tuple 0 _suffix)
    list(GET _tuple 1 _target)

    set(_target "differential_wheeled_robot::${_target}")
    if(NOT TARGET "${_target}")
      # the exported target must exist
      message(WARNING "Package 'differential_wheeled_robot' exports the typesupport target '${_target}' which doesn't exist")
    else()
      list(APPEND differential_wheeled_robot_TARGETS${_suffix} "${_target}")
    endif()
  endforeach()
endif()
