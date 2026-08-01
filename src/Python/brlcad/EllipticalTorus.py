#                       E L L I P T I C A L T O R U S . P Y
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
# @file EllipticalTorus.py
#
# BRL-CAD core simplified Python interface:
#       Python interface implementation for the EllipticalTorus.cpp
#

import ctypes
from ._bindings import _lib
from .Object import Object

class EllipticalTorus(Object):
    """EllipticalTorus primitive tracking container."""

    def __init__(self, *args, **kwargs):
        handle = None
        owned = kwargs.get('owned', True)

        # 1. Handle Input: EllipticalTorus(raw_handle)
        if len(args) == 1 and isinstance(args[0], (int, ctypes.c_void_p)):
            handle = args[0]

        # 2. C++ Overload Mimic: EllipticalTorus(center, normal, tubeCenterLineRadius, tubeSemiMajorAxis, tubeSemiMinorAxis)
        elif len(args) == 5:
            center, normal, r_c, s_ma, s_mi = args[0], args[1], args[2], args[3], args[4]
            handle = _lib.BrlNewEllipticalTorusAsEllipticalTorus(
                float(center[0]), float(center[1]), float(center[2]),
                float(normal[0]), float(normal[1]), float(normal[2]),
                float(r_c),
                float(s_ma[0]), float(s_ma[1]), float(s_ma[2]),
                float(s_mi)
            )

        # 3. Fallback Default: EllipticalTorus()
        if handle is None:
            handle = _lib.BrlNewEllipticalTorus()

        super().__init__(handle=handle, owned=owned)

    def GetCenter(self):
        return _lib.BrlEllipticalTorusCenter(self._handle)

    def SetCenter(self, x, y, z):
        _lib.BrlEllipticalTorusSetCenter(self._handle, float(x), float(y), float(z))

    def GetNormal(self):
        return _lib.BrlEllipticalTorusNormal(self._handle)

    def SetNormal(self, x, y, z):
        _lib.BrlEllipticalTorusSetNormal(self._handle, float(x), float(y), float(z))

    def GetTubeCenterLineRadius(self):
        return _lib.BrlEllipticalTorusTubeCenterLineRadius(self._handle)

    def SetTubeCenterLineRadius(self, radius):
        _lib.BrlEllipticalTorusSetTubeCenterLineRadius(self._handle, float(radius))

    def GetTubeSemiMajorAxis(self):
        return _lib.BrlEllipticalTorusTubeSemiMajorAxis(self._handle)

    def SetTubeSemiMajorAxis(self, x, y, z):
        _lib.BrlEllipticalTorusSetTubeSemiMajorAxis(self._handle, float(x), float(y), float(z))

    def GetTubeSemiMinorAxis(self):
        return _lib.BrlEllipticalTorusTubeSemiMinorAxis(self._handle)

    def SetTubeSemiMinorAxis(self, radius):
        _lib.BrlEllipticalTorusSetTubeSemiMinorAxis(self._handle, float(radius))

    def SetEllipticalTorusProperties(self, center, normal, r_c, s_ma, s_mi):
        _lib.BrlEllipticalTorusSet(
            self._handle,
            float(center[0]), float(center[1]), float(center[2]),
            float(normal[0]), float(normal[1]), float(normal[2]),
            float(r_c),
            float(s_ma[0]), float(s_ma[1]), float(s_ma[2]),
            float(s_mi)
        )

    def ClassName(self):
        res = _lib.BrlEllipticalTorusClassName()
        return res.decode('utf-8') if res else ""
