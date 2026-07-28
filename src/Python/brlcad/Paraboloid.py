#                       P A R A B O L O I D . P Y
#  BRL-CAD
#
# Copyright (c) 2026 United States Government as represented by
# the U.S. Army Research Laboratory.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public License
# version 2.1 as published by the Free Software Foundation.
#
# @file Paraboloid.py

import ctypes
from ._bindings import _lib
from .Object import Object

class Paraboloid(Object):
    """Paraboloid primitive tracking container."""

    def __init__(self, *args, **kwargs):
        handle = None
        owned = kwargs.get('owned', True)

        if len(args) == 1 and isinstance(args[0], (int, ctypes.c_void_p)):
            handle = args[0]
        elif len(args) == 4:
            bp, h, sma, smal = args[0], args[1], args[2], args[3]
            handle = _lib.BrlNewParaboloidAsParaboloid(
                float(bp[0]), float(bp[1]), float(bp[2]),
                float(h[0]), float(h[1]), float(h[2]),
                float(sma[0]), float(sma[1]), float(sma[2]),
                float(smal)
            )
        elif len(args) == 5:
            bp, h, dir, smaxl, smal = args[0], args[1], args[2], args[3], args[4]
            handle = _lib.BrlNewParaboloidAsParaboloidWithLength(
                float(bp[0]), float(bp[1]), float(bp[2]),
                float(h[0]), float(h[1]), float(h[2]),
                float(dir[0]), float(dir[1]), float(dir[2]),
                float(smaxl), float(smal)
            )

        if handle is None:
            handle = _lib.BrlNewParaboloid()

        super().__init__(handle=handle, owned=owned)

    def GetBasePoint(self):
        return _lib.BrlParaboloidBasePoint(self._handle)

    def SetBasePoint(self, x, y, z):
        _lib.BrlParaboloidSetBasePoint(self._handle, float(x), float(y), float(z))

    def GetHeight(self):
        return _lib.BrlParaboloidHeight(self._handle)

    def SetHeight(self, x, y, z):
        _lib.BrlParaboloidSetHeight(self._handle, float(x), float(y), float(z))

    def GetSemiMajorAxis(self):
        return _lib.BrlParaboloidSemiMajorAxis(self._handle)

    def SetSemiMajorAxis(self, x, y, z):
        _lib.BrlParaboloidSetSemiMajorAxis(self._handle, float(x), float(y), float(z))

    def SetSemiMajorAxisWithLength(self, dirx, diry, dirz, length):
        _lib.BrlParaboloidSetSemiMajorAxisWithLength(self._handle, float(dirx), float(diry), float(dirz), float(length))

    def GetSemiMajorAxisDirection(self):
        return _lib.BrlParaboloidSemiMajorAxisDirection(self._handle)

    def SetSemiMajorAxisDirection(self, x, y, z):
        _lib.BrlParaboloidSetSemiMajorAxisDirection(self._handle, float(x), float(y), float(z))

    def GetSemiMajorAxisLength(self):
        return _lib.BrlParaboloidSemiMajorAxisLength(self._handle)

    def SetSemiMajorAxisLength(self, length):
        _lib.BrlParaboloidSetSemiMajorAxisLength(self._handle, float(length))

    def GetSemiMinorAxisLength(self):
        return _lib.BrlParaboloidSemiMinorAxisLength(self._handle)

    def SetSemiMinorAxisLength(self, length):
        _lib.BrlParaboloidSetSemiMinorAxisLength(self._handle, float(length))

    def SetParaboloidProperties(self, bp, h, sma, smal):
        _lib.BrlParaboloidSet(
            self._handle,
            float(bp[0]), float(bp[1]), float(bp[2]),
            float(h[0]), float(h[1]), float(h[2]),
            float(sma[0]), float(sma[1]), float(sma[2]),
            float(smal)
        )

    def SetParaboloidPropertiesWithLength(self, bp, h, dir, smaxl, smal):
        _lib.BrlParaboloidSetWithLength(
            self._handle,
            float(bp[0]), float(bp[1]), float(bp[2]),
            float(h[0]), float(h[1]), float(h[2]),
            float(dir[0]), float(dir[1]), float(dir[2]),
            float(smaxl), float(smal)
        )

    def ClassName(self):
        res = _lib.BrlParaboloidClassName()
        return res.decode('utf-8') if res else ""
