#                              P I P E . P Y
#  BRL-CAD
#
# Copyright (c) 2026 United States Government as represented by
# the U.S. Army Research Laboratory.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public License
# version 2.1 as published by the Free Software Foundation.
#
# This library is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this file; see the file named COPYING for more
# information.
#
# @file Pipe.py
#
# BRL-CAD core simplified Python interface:
#       Python interface implementation for Pipe.cpp

import ctypes
from ._bindings import _lib
from .Object import Object
from .Handle import Handle

class PipeControlPoint(Handle):
    """
    Handle for a Pipe control point.
    """
    def __init__(self, handle):
        super().__init__(handle=handle)

    @property
    def point(self):
        if not self._handle:
            return (0.0, 0.0, 0.0)
        vec_handle = _lib.BrlPipeControlPointPoint(self._handle)
        if not vec_handle:
            return (0.0, 0.0, 0.0)
        x = _lib.BrlVector3DX(vec_handle)
        y = _lib.BrlVector3DY(vec_handle)
        z = _lib.BrlVector3DZ(vec_handle)
        _lib.BrlDeleteHandle(vec_handle)
        return (x, y, z)

    @point.setter
    def point(self, value):
        if not self._handle:
            return
        x, y, z = value
        _lib.BrlPipeControlPointSetPoint(self._handle, x, y, z)

    @property
    def inner_diameter(self):
        if not self._handle:
            return 0.0
        return _lib.BrlPipeControlPointInnerDiameter(self._handle)

    @inner_diameter.setter
    def inner_diameter(self, value):
        if not self._handle:
            return
        _lib.BrlPipeControlPointSetInnerDiameter(self._handle, value)

    @property
    def outer_diameter(self):
        if not self._handle:
            return 0.0
        return _lib.BrlPipeControlPointOuterDiameter(self._handle)

    @outer_diameter.setter
    def outer_diameter(self, value):
        if not self._handle:
            return
        _lib.BrlPipeControlPointSetOuterDiameter(self._handle, value)

    @property
    def bend_radius(self):
        if not self._handle:
            return 0.0
        return _lib.BrlPipeControlPointBendRadius(self._handle)

    @bend_radius.setter
    def bend_radius(self, value):
        if not self._handle:
            return
        _lib.BrlPipeControlPointSetBendRadius(self._handle, value)


class Pipe(Object):
    """
    Object-oriented Python interface for the BRL-CAD Pipe primitive.
    """

    def __init__(self, handle=None):
        if handle is not None:
            super().__init__(handle=handle)
            return

        native_handle = _lib.BrlNewPipe()
        super().__init__(handle=native_handle)

    @property
    def number_of_control_points(self):
        if not self._handle:
            return 0
        return _lib.BrlPipeNumberOfControlPoints(self._handle)

    def get_control_point(self, index):
        if not self._handle:
            return None
        cp_handle = _lib.BrlPipeGetControlPoint(self._handle, index)
        if cp_handle:
            return PipeControlPoint(handle=cp_handle)
        return None

    def append_control_point(self, point, inner_diameter, outer_diameter, bend_radius):
        if not self._handle:
            return None
        x, y, z = point
        cp_handle = _lib.BrlPipeAppendControlPoint(self._handle, x, y, z, inner_diameter, outer_diameter, bend_radius)
        if cp_handle:
            return PipeControlPoint(handle=cp_handle)
        return None

    def insert_control_point(self, index, point, inner_diameter, outer_diameter, bend_radius):
        if not self._handle:
            return None
        x, y, z = point
        cp_handle = _lib.BrlPipeInsertControlPoint(self._handle, index, x, y, z, inner_diameter, outer_diameter, bend_radius)
        if cp_handle:
            return PipeControlPoint(handle=cp_handle)
        return None

    def delete_control_point(self, index):
        if not self._handle:
            return
        _lib.BrlPipeDeleteControlPoint(self._handle, index)

    @classmethod
    def class_name(cls):
        """Returns the internal C++ class name."""
        return _lib.BrlPipeClassName().decode('utf-8')
