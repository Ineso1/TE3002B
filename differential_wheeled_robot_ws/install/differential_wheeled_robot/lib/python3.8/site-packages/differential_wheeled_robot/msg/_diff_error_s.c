// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from differential_wheeled_robot:msg/DiffError.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "differential_wheeled_robot/msg/detail/diff_error__struct.h"
#include "differential_wheeled_robot/msg/detail/diff_error__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool differential_wheeled_robot__msg__diff_error__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[53];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("differential_wheeled_robot.msg._diff_error.DiffError", full_classname_dest, 52) == 0);
  }
  differential_wheeled_robot__msg__DiffError * ros_message = _ros_message;
  {  // error_ang
    PyObject * field = PyObject_GetAttrString(_pymsg, "error_ang");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->error_ang = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // error_dist
    PyObject * field = PyObject_GetAttrString(_pymsg, "error_dist");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->error_dist = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * differential_wheeled_robot__msg__diff_error__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of DiffError */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("differential_wheeled_robot.msg._diff_error");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "DiffError");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  differential_wheeled_robot__msg__DiffError * ros_message = (differential_wheeled_robot__msg__DiffError *)raw_ros_message;
  {  // error_ang
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->error_ang);
    {
      int rc = PyObject_SetAttrString(_pymessage, "error_ang", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // error_dist
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->error_dist);
    {
      int rc = PyObject_SetAttrString(_pymessage, "error_dist", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
