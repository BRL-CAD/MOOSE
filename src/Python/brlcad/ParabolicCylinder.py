#                   P A R A B O L I C C Y L I N D E R . P Y
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
# @file ParabolicCylinder.py
#
# BRL-CAD core simplified Python interface:
#       Python interface implementation for ParabolicCylinder.cpp

import ctypes
from ._bindings import _lib
from .Object import Object

class ParabolicCylinder(Object):
    """
    Object-oriented Python interface for the BRL-CAD Parabolic Cylinder (RPC) primitive.
    """

    def __init__(self, base_point=None, height=None, depth=None, half_width=None, handle=None):
        if handle is not None:
            super().__init__(handle=handle)
            return

        if base_point is not None and height is not None and depth is not None and half_width is not None:
            b_x, b_y, b_z = base_point
            h_x, h_y, h_z = height
            d_x, d_y, d_z = depth
            native_handle = _lib.BrlNewParabolicCylinderAsParabolicCylinder(
                b_x, b_y, b_z,
                h_x, h_y, h_z,
                d_x, d_y, d_z,
                half_width
            )
        else:
            native_handle = _lib.BrlNewParabolicCylinder()
            
        super().__init__(handle=native_handle)

    @property
    def base_point(self):
        """Gets or sets the base point of the parabolic cylinder."""
        if not self._handle:
            return (0.0, 0.0, 0.0)
        vec_handle = _lib.BrlParabolicCylinderBasePoint(self._handle)
        if not vec_handle:
            return (0.0, 0.0, 0.0)
        x = _lib.BrlVector3DX(vec_handle)
        y = _lib.BrlVector3DY(vec_handle)
        z = _lib.BrlVector3DZ(vec_handle)
        _lib.BrlDeleteHandle(vec_handle)
        return (x, y, z)

    @base_point.setter
    def base_point(self, value):
        if not self._handle:
            return
        x, y, z = value
        _lib.BrlParabolicCylinderSetBasePoint(self._handle, x, y, z)

    @property
    def height(self):
        """Gets or sets the height vector of the parabolic cylinder."""
        if not self._handle:
            return (0.0, 0.0, 0.0)
        vec_handle = _lib.BrlParabolicCylinderHeight(self._handle)
        if not vec_handle:
            return (0.0, 0.0, 0.0)
        x = _lib.BrlVector3DX(vec_handle)
        y = _lib.BrlVector3DY(vec_handle)
        z = _lib.BrlVector3DZ(vec_handle)
        _lib.BrlDeleteHandle(vec_handle)
        return (x, y, z)

    @height.setter
    def height(self, value):
        if not self._handle:
            return
        x, y, z = value
        _lib.BrlParabolicCylinderSetHeight(self._handle, x, y, z)

    @property
    def depth(self):
        """Gets or sets the depth vector of the parabolic cylinder."""
        if not self._handle:
            return (0.0, 0.0, 0.0)
        vec_handle = _lib.BrlParabolicCylinderDepth(self._handle)
        if not vec_handle:
            return (0.0, 0.0, 0.0)
        x = _lib.BrlVector3DX(vec_handle)
        y = _lib.BrlVector3DY(vec_handle)
        z = _lib.BrlVector3DZ(vec_handle)
        _lib.BrlDeleteHandle(vec_handle)
        return (x, y, z)

    @depth.setter
    def depth(self, value):
        if not self._handle:
            return
        x, y, z = value
        _lib.BrlParabolicCylinderSetDepth(self._handle, x, y, z)

    @property
    def half_width(self):
        """Gets or sets the half-width of the parabolic cylinder."""
        if not self._handle:
            return 0.0
        return _lib.BrlParabolicCylinderHalfWidth(self._handle)

    @half_width.setter
    def half_width(self, value):
        if not self._handle:
            return
        _lib.BrlParabolicCylinderSetHalfWidth(self._handle, value)

    def set(self, base_point, height, depth, half_width):
        """Sets all properties of the parabolic cylinder at once."""
        if not self._handle:
            return
        b_x, b_y, b_z = base_point
        h_x, h_y, h_z = height
        d_x, d_y, d_z = depth
        _lib.BrlParabolicCylinderSet(self._handle, b_x, b_y, b_z, h_x, h_y, h_z, d_x, d_y, d_z, half_width)

    @classmethod
    def class_name(cls):
        """Returns the internal C++ class name."""
        return _lib.BrlParabolicCylinderClassName().decode('utf-8')
