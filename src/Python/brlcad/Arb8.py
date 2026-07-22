#                       A R B 8 . P Y
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
# @file Arb8.py
#
# BRL-CAD core simplified Python interface:
#       Python interface implementation for the Arb8.cpp

import ctypes 
from ._bindings import _lib
from .Object import Object

class Arb8(Object):
    """8-Vertex Arbitrary Polyhedron primitive tracking container."""
    def __init__(self, *args, **kwargs):
        handle = None
        owned = kwargs.get('owned', True)

        # 1. Handle Input: Arb8(raw_handle)
        if len(args) == 1 and isinstance(args[0], (int, ctypes.c_void_p)):
            handle = args[0]

        # 2. Explicit List/Tuple Layout Overload: Arb8(points_list)
        elif len(args) == 1 and isinstance(args[0], (list, tuple)):
            points_list = args[0]
            if len(points_list) != 8 or any(len(p) != 3 for p in points_list):
                raise ValueError("An explicit Arb8 constructor requires exactly 8 elements of (X, Y, Z) coordinates.")
            flat_coords = [float(coord) for point in points_list for coord in point]
            handle = _lib.BrlNewArb8AsArb8(*flat_coords)

        # 3. Two-Point Forms: RPP bounding box vs Arb4 variant
        elif len(args) == 2:
            p1, p2 = args[0], args[1]
            as_rpp = kwargs.get('is_rpp', True)
            
            if as_rpp:
                handle = _lib.BrlNewArb8AsRectengularParallelPiped(
                    float(p1[0]), float(p1[1]), float(p1[2]),
                    float(p2[0]), float(p2[1]), float(p2[2])
                )
            else:
                # Direct Arb4 fallback form (Requires 4 points in full C++, but routes through basic 2-pt bounds here)
                handle = _lib.BrlNewArb8AsArb4(
                    float(p1[0]), float(p1[1]), float(p1[2]),
                    float(p2[0]), float(p2[1]), float(p2[2]),
                    float(p1[0]), float(p1[1]), float(p1[2]),
                    float(p2[0]), float(p2[1]), float(p2[2])
                )

        # 4. Fallback Default Constructor: Arb8()
        if handle is None:
            handle = _lib.BrlNewArb8()

        super().__init__(handle=handle, owned=owned)

    def GetVertexCount(self):
        """Returns the valid structural vertex count from the backend geometry analysis."""
        return int(_lib.BrlArb8NumberOfVertices(self._handle))

    def GetPoint(self, number):
        """Returns a BrlVector3D tracking handle for logical vertex index 1-8."""
        return _lib.BrlArb8Point(self._handle, int(number))

    def GetRawPoint(self, index):
        """Returns a BrlVector3D tracking handle for hardware array index 0-7."""
        return _lib.BrlArb8RawPoint(self._handle, int(index))

    def SetPoint(self, number, x, y, z):
        """Updates a single logical vertex (1-8) coordinate configuration directly."""
        _lib.BrlArb8SetPoint(self._handle, int(number), float(x), float(y), float(z))

    def SetPointsAsRawPoint(self, index, x, y, z):
        """Updates a single hardware indexing vertex (0-7) coordinate configuration directly."""
        _lib.BrlArb8SetRawPoint(self._handle, int(index), float(x), float(y), float(z))

    def SetPointAsArb2(self, p1, p2):
        """Updates internal geometry via a 2-point bounding box footprint."""
        _lib.BrlArb8SetPointsAsRectengularParallelPiped(
            self._handle,
            float(p1[0]), float(p1[1]), float(p1[2]),
            float(p2[0]), float(p2[1]), float(p2[2])
        )

    def SetPointAsArb4(self, p1, p2, p3, p4):
        """Updates internal geometry configuration using 4 points."""
        _lib.BrlArb8SetPointsAsArb4(
            self._handle,
            float(p1[0]), float(p1[1]), float(p1[2]),
            float(p2[0]), float(p2[1]), float(p2[2]),
            float(p3[0]), float(p3[1]), float(p3[2]),
            float(p4[0]), float(p4[1]), float(p4[2])
        )

    def SetPointAsArb5(self, p1, p2, p3, p4, p5):
        """Updates internal geometry configuration using 5 points."""
        _lib.BrlArb8SetPointsAsArb5(
            self._handle,
            float(p1[0]), float(p1[1]), float(p1[2]),
            float(p2[0]), float(p2[1]), float(p2[2]),
            float(p3[0]), float(p3[1]), float(p3[2]),
            float(p4[0]), float(p4[1]), float(p4[2]),
            float(p5[0]), float(p5[1]), float(p5[2])
        )

    def SetPointAsArb6(self, p1, p2, p3, p4, p5, p6):
        """Updates internal geometry configuration using 6 points."""
        _lib.BrlArb8SetPointsAsArb6(
            self._handle,
            float(p1[0]), float(p1[1]), float(p1[2]),
            float(p2[0]), float(p2[1]), float(p2[2]),
            float(p3[0]), float(p3[1]), float(p3[2]),
            float(p4[0]), float(p4[1]), float(p4[2]),
            float(p5[0]), float(p5[1]), float(p5[2]),
            float(p6[0]), float(p6[1]), float(p6[2])
        )

    def SetPointAsArb7(self, points_list):
        """Updates internal geometry configuration using 7 points."""
        if len(points_list) != 7 or any(len(p) != 3 for p in points_list):
            raise ValueError("This method requires exactly 7 entries of 3D vectors.")
        flat_coords = [float(coord) for point in points_list for coord in point]
        _lib.BrlArb8SetPointsAsArb7(self._handle, *flat_coords)

    def SetPointAsArb8(self, points_list):
        """Updates layout using a batch explicit 8-point matrix coordinate array."""
        if len(points_list) != 8 or any(len(p) != 3 for p in points_list):
            raise ValueError("Updating all points requires exactly 8 entries of 3D vectors.")
        flat_coords = [float(coord) for point in points_list for coord in point]
        _lib.BrlArb8SetPointsAsArb8(self._handle, *flat_coords)
        
    def SetPointsAsRectangularParallelpiped(self, p1, p2):
        """Mutates the frame tracking bounds using two opposite coordinate corners."""
        _lib.BrlArb8SetPointsAsRectengularParallelPiped(
            self._handle,
            float(p1[0]), float(p1[1]), float(p1[2]),
            float(p2[0]), float(p2[1]), float(p2[2])
        )
    
    def ClassName(self):
        """Returns the static C++ class designator identification string."""
        res = _lib.BrlArb8ClassName()
        return res.decode('utf-8') if res else ""
