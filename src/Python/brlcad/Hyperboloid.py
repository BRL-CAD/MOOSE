#                       H Y P E R B O L O I D . P Y
#  BRL-CAD
#
# Copyright (c) 2026 United States Government as represented by
# the U.S. Army Research Laboratory.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public License
# version 2.1 as published by the Free Software Foundation.
#
# @file Hyperboloid.py

import ctypes
from ._bindings import _lib
from .Object import Object

class Hyperboloid(Object):
    """Hyperboloid primitive tracking container."""

    def __init__(self, *args, **kwargs):
        handle = None
        owned = kwargs.get('owned', True)

        if len(args) == 1 and isinstance(args[0], (int, ctypes.c_void_p)):
            handle = args[0]
        elif len(args) == 5:
            bp, h, sma, smal, aad = args[0], args[1], args[2], args[3], args[4]
            handle = _lib.BrlNewHyperboloidAsHyperboloid(
                float(bp[0]), float(bp[1]), float(bp[2]),
                float(h[0]), float(h[1]), float(h[2]),
                float(sma[0]), float(sma[1]), float(sma[2]),
                float(smal), float(aad)
            )
        elif len(args) == 6:
            bp, h, dir, smaxl, smal, aad = args[0], args[1], args[2], args[3], args[4], args[5]
            handle = _lib.BrlNewHyperboloidAsHyperboloidWithLength(
                float(bp[0]), float(bp[1]), float(bp[2]),
                float(h[0]), float(h[1]), float(h[2]),
                float(dir[0]), float(dir[1]), float(dir[2]),
                float(smaxl), float(smal), float(aad)
            )

        if handle is None:
            handle = _lib.BrlNewHyperboloid()

        super().__init__(handle=handle, owned=owned)

    def GetBasePoint(self):
        return _lib.BrlHyperboloidBasePoint(self._handle)

    def SetBasePoint(self, x, y, z):
        _lib.BrlHyperboloidSetBasePoint(self._handle, float(x), float(y), float(z))

    def GetHeight(self):
        return _lib.BrlHyperboloidHeight(self._handle)

    def SetHeight(self, x, y, z):
        _lib.BrlHyperboloidSetHeight(self._handle, float(x), float(y), float(z))

    def GetSemiMajorAxis(self):
        return _lib.BrlHyperboloidSemiMajorAxis(self._handle)

    def SetSemiMajorAxis(self, x, y, z):
        _lib.BrlHyperboloidSetSemiMajorAxis(self._handle, float(x), float(y), float(z))

    def SetSemiMajorAxisWithLength(self, dirx, diry, dirz, length):
        _lib.BrlHyperboloidSetSemiMajorAxisWithLength(self._handle, float(dirx), float(diry), float(dirz), float(length))

    def GetSemiMajorAxisDirection(self):
        return _lib.BrlHyperboloidSemiMajorAxisDirection(self._handle)

    def SetSemiMajorAxisDirection(self, x, y, z):
        _lib.BrlHyperboloidSetSemiMajorAxisDirection(self._handle, float(x), float(y), float(z))

    def GetSemiMajorAxisLength(self):
        return _lib.BrlHyperboloidSemiMajorAxisLength(self._handle)

    def SetSemiMajorAxisLength(self, length):
        _lib.BrlHyperboloidSetSemiMajorAxisLength(self._handle, float(length))

    def GetSemiMinorAxisLength(self):
        return _lib.BrlHyperboloidSemiMinorAxisLength(self._handle)

    def SetSemiMinorAxisLength(self, length):
        _lib.BrlHyperboloidSetSemiMinorAxisLength(self._handle, float(length))

    def GetApexAsymptoteDistance(self):
        return _lib.BrlHyperboloidApexAsymptoteDistance(self._handle)

    def SetApexAsymptoteDistance(self, distance):
        _lib.BrlHyperboloidSetApexAsymptoteDistance(self._handle, float(distance))

    def SetHyperboloidProperties(self, bp, h, sma, smal, aad):
        _lib.BrlHyperboloidSet(
            self._handle,
            float(bp[0]), float(bp[1]), float(bp[2]),
            float(h[0]), float(h[1]), float(h[2]),
            float(sma[0]), float(sma[1]), float(sma[2]),
            float(smal), float(aad)
        )

    def SetHyperboloidPropertiesWithLength(self, bp, h, dir, smaxl, smal, aad):
        _lib.BrlHyperboloidSetWithLength(
            self._handle,
            float(bp[0]), float(bp[1]), float(bp[2]),
            float(h[0]), float(h[1]), float(h[2]),
            float(dir[0]), float(dir[1]), float(dir[2]),
            float(smaxl), float(smal), float(aad)
        )

    def ClassName(self):
        res = _lib.BrlHyperboloidClassName()
        return res.decode('utf-8') if res else ""
