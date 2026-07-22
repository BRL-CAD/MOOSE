#                       C O N E . P Y
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
# @file Cone.py
#
# BRL-CAD core simplified Python interface:
#       Python interface implementation for the Cone.cpp
#

import ctypes
from ._bindings import _lib
from .Object import Object

class Cone(Object):
    """Cone primitive tracking container."""

    def __init__(self, *args, **kwargs):
        handle = None
        owned = kwargs.get('owned', True)

        # 1. Handle Input: Cone(raw_handle)
        if len(args) == 1 and isinstance(args[0], (int, ctypes.c_void_p)):
            handle = args[0]

        # 2. Right Circular Cylinder Overload: Cone(base, height, radius)
        elif len(args) == 3:
            base, height, radius = args[0], args[1], args[2]
            handle = _lib.BrlNewConeAsRightCircularCylinder(
                float(base[0]), float(base[1]), float(base[2]),
                float(height[0]), float(height[1]), float(height[2]),
                float(radius)
            )

        elif len(args) == 4:
            # 3. Truncated Right Circular Cone Overload: Cone(base, height, radius_base, radius_top)
            if isinstance(args[2], (int, float)) and isinstance(args[3], (int, float)):
                base, height, radius_base, radius_top = args[0], args[1], args[2], args[3]
                handle = _lib.BrlNewConeAsTruncatedRightCircularCone(
                    float(base[0]), float(base[1]), float(base[2]),
                    float(height[0]), float(height[1]), float(height[2]),
                    float(radius_base), float(radius_top)
                )
            # 4. Right Elliptical Cylinder Overload: Cone(base, height, axis_a, axis_b)
            else:
                base, height, axis_a, axis_b = args[0], args[1], args[2], args[3]
                handle = _lib.BrlNewConeAsRightEllipticalCylinder(
                    float(base[0]), float(base[1]), float(base[2]),
                    float(height[0]), float(height[1]), float(height[2]),
                    float(axis_a[0]), float(axis_a[1]), float(axis_a[2]),
                    float(axis_b[0]), float(axis_b[1]), float(axis_b[2])
                )

        # 5. Truncated Erected Cone Overload: Cone(base, height, axis_a, axis_b, scale)
        elif len(args) == 5:
            base, height, axis_a, axis_b, scale = args[0], args[1], args[2], args[3], args[4]
            handle = _lib.BrlNewConeAsTruncatedErectedCone(
                float(base[0]), float(base[1]), float(base[2]),
                float(height[0]), float(height[1]), float(height[2]),
                float(axis_a[0]), float(axis_a[1]), float(axis_a[2]),
                float(axis_b[0]), float(axis_b[1]), float(axis_b[2]),
                float(scale)
            )

        # 6. Truncated General Cone Overload: Cone(base, height, axis_a, axis_b, ratio_c, ratio_d)
        elif len(args) == 6:
            base, height, axis_a, axis_b, ratio_c, ratio_d = args[0], args[1], args[2], args[3], args[4], args[5]
            handle = _lib.BrlNewConeAsTruncatedGeneralCone(
                float(base[0]), float(base[1]), float(base[2]),
                float(height[0]), float(height[1]), float(height[2]),
                float(axis_a[0]), float(axis_a[1]), float(axis_a[2]),
                float(axis_b[0]), float(axis_b[1]), float(axis_b[2]),
                float(ratio_c), float(ratio_d)
            )

        # 7. Fallback Default: Cone()
        if handle is None:
            handle = _lib.BrlNewCone()

        super().__init__(handle=handle, owned=owned)

    def GetBasePoint(self):
        """Returns the base reference point pointer mapping address."""
        return _lib.BrlConeBasePoint(self._handle)

    def GetHeight(self):
        """Returns the height vector pointer mapping address."""
        return _lib.BrlConeHeight(self._handle)

    def GetSemiPrincipalAxis(self, index):
        """Returns the specific semi-principal axis vector pointer by index."""
        return _lib.BrlConeSemiPrincipalAxis(self._handle, int(index))

    def SetBasePoint(self, x, y, z):
        """Sets the raw base reference location coordinates."""
        _lib.BrlConeSetBasePoint(self._handle, float(x), float(y), float(z))

    def SetHeight(self, x, y, z):
        """Sets the primary vector height coordinates."""
        _lib.BrlConeSetHeight(self._handle, float(x), float(y), float(z))

    def SetSemiPrincipalAxis(self, index, x, y, z):
        """Modifies an orientation axis coordinate trajectory by its index value."""
        _lib.BrlConeSetSemiPrincipalAxis(self._handle, int(index), float(x), float(y), float(z))

    def SetAsTruncatedGeneralCone(self, base, height, semi_axis_a, semi_axis_b, ratio_c, ratio_d):
        """Mutates the primitive structure into a truncated general cone framework."""
        _lib.BrlConeSetAsTruncatedGeneralCone(
            self._handle,
            float(base[0]), float(base[1]), float(base[2]),
            float(height[0]), float(height[1]), float(height[2]),
            float(semi_axis_a[0]), float(semi_axis_a[1]), float(semi_axis_a[2]),
            float(semi_axis_b[0]), float(semi_axis_b[1]), float(semi_axis_b[2]),
            float(ratio_c), float(ratio_d)
        )

    def SetAsTruncatedErectedCone(self, base, height, semi_axis_a, semi_axis_b, scale):
        """Mutates the primitive structure into a truncated erected cone framework."""
        _lib.BrlConeSetAsTruncatedErectedCone(
            self._handle,
            float(base[0]), float(base[1]), float(base[2]),
            float(height[0]), float(height[1]), float(height[2]),
            float(semi_axis_a[0]), float(semi_axis_a[1]), float(semi_axis_a[2]),
            float(semi_axis_b[0]), float(semi_axis_b[1]), float(semi_axis_b[2]),
            float(scale)
        )

    def SetAsRightEllipticalCylinder(self, base, height, semi_axis_a, semi_axis_b):
        """Mutates the primitive structure into a right elliptical cylinder configuration."""
        _lib.BrlConeSetAsRightEllipticalCylinder(
            self._handle,
            float(base[0]), float(base[1]), float(base[2]),
            float(height[0]), float(height[1]), float(height[2]),
            float(semi_axis_a[0]), float(semi_axis_a[1]), float(semi_axis_a[2]),
            float(semi_axis_b[0]), float(semi_axis_b[1]), float(semi_axis_b[2])
        )

    def SetAsTruncatedRightCircularCone(self, base, height, radius_base, radius_top):
        """Mutates the primitive structure into a truncated right circular cone framework."""
        _lib.BrlConeSetAsTruncatedRightCircularCone(
            self._handle,
            float(base[0]), float(base[1]), float(base[2]),
            float(height[0]), float(height[1]), float(height[2]),
            float(radius_base), float(radius_top)
        )

    def SetAsRightCircularCylinder(self, base, height, radius):
        """Mutates the primitive structure into a uniform right circular cylinder framework."""
        _lib.BrlConeSetAsRightCircularCylinder(
            self._handle,
            float(base[0]), float(base[1]), float(base[2]),
            float(height[0]), float(height[1]), float(height[2]),
            float(radius)
        )
    
    def ClassName(self):
        """Returns the static C++ class designator identification string."""
        res = _lib.BrlConeClassName()
        return res.decode('utf-8') if res else ""
