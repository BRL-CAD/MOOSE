#                       E L L I P S O I D . P Y
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
# @file Ellipsoid.py
#
# BRL-CAD core simplified Python interface:
#       Python interface implementation for the Ellipsoid.cpp
#

import ctypes
from ._bindings import _lib
from .Object import Object

class Ellipsoid(Object):
    """Ellipsoid primitive tracking container."""

    def __init__(self, *args, **kwargs):
        handle = None
        owned = kwargs.get('owned', True)

        # 1. Handle Input: Ellipsoid(raw_handle)
        if len(args) == 1 and isinstance(args[0], (int, ctypes.c_void_p)):
            handle = args[0]

        # 2. Sphere Layout Overload: Ellipsoid(center, radius)
        elif len(args) == 2 and isinstance(args[1], (int, float)):
            center, radius = args[0], args[1]
            handle = _lib.BrlNewEllipsoidAsSphere(
                float(center[0]), float(center[1]), float(center[2]),
                float(radius)
            )

        # 3. Ellipsoid1 Layout Overload: Ellipsoid(center, semi_axis, radius)
        elif len(args) == 3:
            center, semi_axis, radius = args[0], args[1], args[2]
            handle = _lib.BrlNewEllipsoidAsEllipsoid1(
                float(center[0]), float(center[1]), float(center[2]),
                float(semi_axis[0]), float(semi_axis[1]), float(semi_axis[2]),
                float(radius)
            )

        # 4. General Layout Overload: Ellipsoid(center, axis_a, axis_b, axis_c)
        elif len(args) == 4:
            center, axis_a, axis_b, axis_c = args[0], args[1], args[2], args[3]
            handle = _lib.BrlNewEllipsoidAsGeneralEllipsoid(
                float(center[0]), float(center[1]), float(center[2]),
                float(axis_a[0]), float(axis_a[1]), float(axis_a[2]),
                float(axis_b[0]), float(axis_b[1]), float(axis_b[2]),
                float(axis_c[0]), float(axis_c[1]), float(axis_c[2])
            )

        # 5. Fallback Default: Ellipsoid()
        if handle is None:
            handle = _lib.BrlNewEllipsoid()

        super().__init__(handle=handle, owned=owned)

    def GetCenter(self):
        """Returns the center point wrapper handle of the ellipsoid."""
        return _lib.BrlEllipsoidCenter(self._handle)

    def GetSemiPrincipalAxis(self, index):
        """Returns the specific semi-principal axis vector pointer by index."""
        return _lib.BrlEllipsoidSemiPrincipalAxis(self._handle, int(index))

    def SetCenter(self, x, y, z):
        """Sets the center point coordinates of the ellipsoid."""
        _lib.BrlEllipsoidSetCenter(self._handle, float(x), float(y), float(z))

    def SetSemiPrincipalAxis(self, index, x, y, z):
        """Modifies a single directional vector axis by its index location."""
        _lib.BrlEllipsoidSetSemiPrincipalAxis(self._handle, int(index), float(x), float(y), float(z))

    def SetAsGeneralEllipsoid(self, center, semi_axis_a, semi_axis_b, semi_axis_c):
        """Updates geometry footprint values into a general ellipsoid layout configuration."""
        _lib.BrlEllipsoidSetAsGeneralEllipsoid(
            self._handle,
            float(center[0]), float(center[1]), float(center[2]),
            float(semi_axis_a[0]), float(semi_axis_a[1]), float(semi_axis_a[2]),
            float(semi_axis_b[0]), float(semi_axis_b[1]), float(semi_axis_b[2]),
            float(semi_axis_c[0]), float(semi_axis_c[1]), float(semi_axis_c[2])
        )

    def SetAsEllipsoid1(self, center, semi_axis, radius):
        """Updates geometry footprint values into an Ellipsoid1 subvariant layout."""
        _lib.BrlEllipsoidSetAsEllipsoid1(
            self._handle,
            float(center[0]), float(center[1]), float(center[2]),
            float(semi_axis[0]), float(semi_axis[1]), float(semi_axis[2]),
            float(radius)
        )

    def SetFocals(self, focal_a, focal_b, major_axis_length):
        """Sets the geometry properties via focal parameters and major axis length."""
        _lib.BrlEllipsoidSetFocals(
            self._handle,
            float(focal_a[0]), float(focal_a[1]), float(focal_a[2]),
            float(focal_b[0]), float(focal_b[1]), float(focal_b[2]),
            float(major_axis_length)
        )

    def SetSphere(self, x, y, z, radius):
        """Mutates the internal object memory context to hold uniform spherical properties."""
        _lib.BrlEllipsoidSetSphere(self._handle, float(x), float(y), float(z), float(radius))

    def ClassName(self):
        """Returns the static C++ class designator identification string."""
        res = _lib.BrlEllipsoidClassName()
        return res.decode('utf-8') if res else ""
