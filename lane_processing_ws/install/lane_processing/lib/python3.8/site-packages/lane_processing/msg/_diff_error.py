# generated from rosidl_generator_py/resource/_idl.py.em
# with input from lane_processing:msg/DiffError.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_DiffError(type):
    """Metaclass of message 'DiffError'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('lane_processing')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'lane_processing.msg.DiffError')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__diff_error
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__diff_error
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__diff_error
            cls._TYPE_SUPPORT = module.type_support_msg__msg__diff_error
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__diff_error

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class DiffError(metaclass=Metaclass_DiffError):
    """Message class 'DiffError'."""

    __slots__ = [
        '_error_ang',
        '_error_dist',
    ]

    _fields_and_field_types = {
        'error_ang': 'double',
        'error_dist': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.error_ang = kwargs.get('error_ang', float())
        self.error_dist = kwargs.get('error_dist', float())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.error_ang != other.error_ang:
            return False
        if self.error_dist != other.error_dist:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def error_ang(self):
        """Message field 'error_ang'."""
        return self._error_ang

    @error_ang.setter
    def error_ang(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'error_ang' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'error_ang' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._error_ang = value

    @builtins.property
    def error_dist(self):
        """Message field 'error_dist'."""
        return self._error_dist

    @error_dist.setter
    def error_dist(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'error_dist' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'error_dist' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._error_dist = value
