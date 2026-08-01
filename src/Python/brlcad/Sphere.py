#                       S P H E R E . P Y
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
# @file Sphere.py
#
# BRL-CAD core simplified Python interface:
#       Python interface implementation for the Sphere.cpp
#

import ctypes
from ._bindings import _lib
from .Object import Object

class Sphere(Object):
    """Sphere primitive tracking container."""

    def __init__(self, *args, **kwargs):
        handle = None
        owned = kwargs.get('owned', True)

        # 1. Handle Input: Sphere(raw_handle)
        if len(args) == 1 and isinstance(args[0], (int, ctypes.c_void_p)):
            handle = args[0]

        # 2. C++ Overload Mimic: Sphere(center, radius)
        elif len(args) == 2:
            center, radius = args[0], args[1]
            handle = _lib.BrlNewSphereAsSphere(
                float(center[0]), float(center[1]), float(center[2]),
                float(radius)
            )

        # 3. Fallback Default: Sphere()
        if handle is None:
            handle = _lib.BrlNewSphere()

        super().__init__(handle=handle, owned=owned)

    def GetCenter(self):
        """Returns the center point wrapper handle address of the sphere."""
        return _lib.BrlSphereCenter(self._handle)

    def GetRadius(self):
        """Returns the radius of the sphere."""
        return _lib.BrlSphereRadius(self._handle)

    def SetCenter(self, x, y, z):
        """Sets the center point coordinates of the sphere."""
        _lib.BrlSphereSetCenter(self._handle, float(x), float(y), float(z))

    def SetRadius(self, radius):
        """Sets the radius of the sphere."""
        _lib.BrlSphereSetRadius(self._handle, float(radius))

    def SetSphereProperties(self, center, radius):
        """Mutates the complete internal object context properties in one pass."""
        _lib.BrlSphereSet(
            self._handle,
            float(center[0]), float(center[1]), float(center[2]),
            float(radius)
        )

    def ClassName(self):
        """Returns the static C++ class designator identification string."""
        res = _lib.BrlSphereClassName()
        return res.decode('utf-8') if res else ""
