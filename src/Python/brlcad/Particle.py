#                       P A R T I C L E . P Y
#  BRL-CAD
#
# Copyright (c) 2026 United States Government as represented by
# the U.S. Army Research Laboratory.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public License
# version 2.1 as published by the Free Software Foundation.
#
# @file Particle.py

import ctypes
from ._bindings import _lib
from .Object import Object

class Particle(Object):
    """Particle primitive tracking container."""

    def __init__(self, *args, **kwargs):
        handle = None
        owned = kwargs.get('owned', True)

        if len(args) == 1 and isinstance(args[0], (int, ctypes.c_void_p)):
            handle = args[0]
        elif len(args) == 4:
            bp, h, rb, rt = args[0], args[1], args[2], args[3]
            handle = _lib.BrlNewParticleAsParticle(
                float(bp[0]), float(bp[1]), float(bp[2]),
                float(h[0]), float(h[1]), float(h[2]),
                float(rb), float(rt)
            )

        if handle is None:
            handle = _lib.BrlNewParticle()

        super().__init__(handle=handle, owned=owned)

    def GetBasePoint(self):
        return _lib.BrlParticleBasePoint(self._handle)

    def SetBasePoint(self, x, y, z):
        _lib.BrlParticleSetBasePoint(self._handle, float(x), float(y), float(z))

    def GetHeight(self):
        return _lib.BrlParticleHeight(self._handle)

    def SetHeight(self, x, y, z):
        _lib.BrlParticleSetHeight(self._handle, float(x), float(y), float(z))

    def GetBaseRadius(self):
        return _lib.BrlParticleBaseRadius(self._handle)

    def SetBaseRadius(self, radius):
        _lib.BrlParticleSetBaseRadius(self._handle, float(radius))

    def GetTopRadius(self):
        return _lib.BrlParticleTopRadius(self._handle)

    def SetTopRadius(self, radius):
        _lib.BrlParticleSetTopRadius(self._handle, float(radius))

    def SetParticleProperties(self, bp, h, rb, rt):
        _lib.BrlParticleSet(
            self._handle,
            float(bp[0]), float(bp[1]), float(bp[2]),
            float(h[0]), float(h[1]), float(h[2]),
            float(rb), float(rt)
        )

    def ClassName(self):
        res = _lib.BrlParticleClassName()
        return res.decode('utf-8') if res else ""
