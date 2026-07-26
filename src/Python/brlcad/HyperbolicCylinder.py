#                       H Y P E R B O L I C C Y L I N D E R . P Y
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
# @file HyperbolicCylinder.py
#
# BRL-CAD core simplified Python interface:
#       Python interface implementation for the HyperbolicCylinder.cpp
#

import ctypes
from ._bindings import _lib
from .Object import Object

class HyperbolicCylinder(Object):
    """HyperbolicCylinder primitive tracking container."""

    def __init__(self, *args, **kwargs):
        handle = None
        owned = kwargs.get('owned', True)

        # 1. Handle Input: HyperbolicCylinder(raw_handle)
        if len(args) == 1 and isinstance(args[0], (int, ctypes.c_void_p)):
            handle = args[0]

        # 2. C++ Overload Mimic: HyperbolicCylinder(basePoint, height, depth, halfWidth, apexAsymptoteDistance)
        elif len(args) == 5:
            bp, h, d, hw, aad = args[0], args[1], args[2], args[3], args[4]
            handle = _lib.BrlNewHyperbolicCylinderAsHyperbolicCylinder(
                float(bp[0]), float(bp[1]), float(bp[2]),
                float(h[0]), float(h[1]), float(h[2]),
                float(d[0]), float(d[1]), float(d[2]),
                float(hw), float(aad)
            )

        # 3. Fallback Default: HyperbolicCylinder()
        if handle is None:
            handle = _lib.BrlNewHyperbolicCylinder()

        super().__init__(handle=handle, owned=owned)
        
    def GetBasePoint(self):
        return _lib.BrlHyperbolicCylinderBasePoint(self._handle)

    def SetBasePoint(self, x, y, z):
        _lib.BrlHyperbolicCylinderSetBasePoint(self._handle, float(x), float(y), float(z))

    def GetHeight(self):
        return _lib.BrlHyperbolicCylinderHeight(self._handle)

    def SetHeight(self, x, y, z):
        _lib.BrlHyperbolicCylinderSetHeight(self._handle, float(x), float(y), float(z))

    def GetDepth(self):
        return _lib.BrlHyperbolicCylinderDepth(self._handle)

    def SetDepth(self, x, y, z):
        _lib.BrlHyperbolicCylinderSetDepth(self._handle, float(x), float(y), float(z))

    def GetHalfWidth(self):
        return _lib.BrlHyperbolicCylinderHalfWidth(self._handle)

    def SetHalfWidth(self, w):
        _lib.BrlHyperbolicCylinderSetHalfWidth(self._handle, float(w))

    def GetApexAsymptoteDistance(self):
        return _lib.BrlHyperbolicCylinderApexAsymptoteDistance(self._handle)

    def SetApexAsymptoteDistance(self, d):
        _lib.BrlHyperbolicCylinderSetApexAsymptoteDistance(self._handle, float(d))

    def SetHyperbolicCylinderProperties(self, bp, h, d, hw, aad):
        _lib.BrlHyperbolicCylinderSet(
            self._handle,
            float(bp[0]), float(bp[1]), float(bp[2]),
            float(h[0]), float(h[1]), float(h[2]),
            float(d[0]), float(d[1]), float(d[2]),
            float(hw), float(aad)
        )

    def ClassName(self):
        res = _lib.BrlHyperbolicCylinderClassName()
        return res.decode('utf-8') if res else ""
