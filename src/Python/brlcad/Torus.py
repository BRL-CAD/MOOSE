#                       T O R U S . P Y
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
# @file Torus.py
#
# BRL-CAD core simplified Python interface:
#       Python interface implementation for the Torus.cpp
#

import ctypes
from ._bindings import _lib
from .Object import Object

class Torus(Object):
    """Torus primitive tracking container."""

    def __init__(self, *args, **kwargs):
        handle = None
        owned = kwargs.get('owned', True)

        # 1. Handle Input: Torus(raw_handle)
        if len(args) == 1 and isinstance(args[0], (int, ctypes.c_void_p)):
            handle = args[0]

        # 2. C++ Overload Mimic: Torus(center, normal, tubeCenterLineRadius, tubeRadius)
        elif len(args) == 4:
            center, normal, r_c, r_t = args[0], args[1], args[2], args[3]
            handle = _lib.BrlNewTorusAsTorus(
                float(center[0]), float(center[1]), float(center[2]),
                float(normal[0]), float(normal[1]), float(normal[2]),
                float(r_c), float(r_t)
            )

        # 3. Fallback Default: Torus()
        if handle is None:
            handle = _lib.BrlNewTorus()

        super().__init__(handle=handle, owned=owned)

    def GetCenter(self):
        """Returns the center point wrapper handle address of the torus."""
        return _lib.BrlTorusCenter(self._handle)

    def SetCenter(self, x, y, z):
        """Sets the center point coordinates of the torus."""
        _lib.BrlTorusSetCenter(self._handle, float(x), float(y), float(z))

    def GetNormal(self):
        """Returns the normal vector wrapper handle address of the torus."""
        return _lib.BrlTorusNormal(self._handle)

    def SetNormal(self, x, y, z):
        """Sets the normal vector coordinates of the torus."""
        _lib.BrlTorusSetNormal(self._handle, float(x), float(y), float(z))

    def GetTubeCenterLineRadius(self):
        """Returns the tube center line radius of the torus."""
        return _lib.BrlTorusTubeCenterLineRadius(self._handle)

    def SetTubeCenterLineRadius(self, radius):
        """Sets the tube center line radius of the torus."""
        _lib.BrlTorusSetTubeCenterLineRadius(self._handle, float(radius))

    def GetTubeRadius(self):
        """Returns the tube radius of the torus."""
        return _lib.BrlTorusTubeRadius(self._handle)

    def SetTubeRadius(self, radius):
        """Sets the tube radius of the torus."""
        _lib.BrlTorusSetTubeRadius(self._handle, float(radius))

    def SetTorusProperties(self, center, normal, tubeCenterLineRadius, tubeRadius):
        """Mutates the complete internal object context properties in one pass."""
        _lib.BrlTorusSet(
            self._handle,
            float(center[0]), float(center[1]), float(center[2]),
            float(normal[0]), float(normal[1]), float(normal[2]),
            float(tubeCenterLineRadius), float(tubeRadius)
        )

    def ClassName(self):
        """Returns the static C++ class designator identification string."""
        res = _lib.BrlTorusClassName()
        return res.decode('utf-8') if res else ""
