#                       H A L F S P A C E . P Y
#  BRL-CAD
#
# Copyright (c) 2026 United States Government as represented by
# the U.S. Army Research Laboratory.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public License
# version 2.1 as published by the Free Software Foundation.
#
# @file Halfspace.py

import ctypes
from ._bindings import _lib
from .Object import Object

class Halfspace(Object):
    """Halfspace primitive tracking container."""

    def __init__(self, *args, **kwargs):
        handle = None
        owned = kwargs.get('owned', True)

        if len(args) == 1 and isinstance(args[0], (int, ctypes.c_void_p)):
            handle = args[0]
        elif len(args) == 2:
            n, d = args[0], args[1]
            handle = _lib.BrlNewHalfspaceAsHalfspace(
                float(n[0]), float(n[1]), float(n[2]),
                float(d)
            )

        if handle is None:
            handle = _lib.BrlNewHalfspace()

        super().__init__(handle=handle, owned=owned)

    def GetNormal(self):
        return _lib.BrlHalfspaceNormal(self._handle)

    def SetNormal(self, nx, ny, nz):
        _lib.BrlHalfspaceSetNormal(self._handle, float(nx), float(ny), float(nz))

    def GetDistanceFromOrigin(self):
        return _lib.BrlHalfspaceDistanceFromOrigin(self._handle)

    def SetDistanceFromOrigin(self, distance):
        _lib.BrlHalfspaceSetDistanceFromOrigin(self._handle, float(distance))

    def SetHalfspaceProperties(self, n, d):
        _lib.BrlHalfspaceSet(
            self._handle,
            float(n[0]), float(n[1]), float(n[2]),
            float(d)
        )

    def ClassName(self):
        res = _lib.BrlHalfspaceClassName()
        return res.decode('utf-8') if res else ""
