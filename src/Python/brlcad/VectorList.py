#                       V E C T O R L I S T . P Y
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
# @file VectorList.py
#
# BRL-CAD core simplified Python interface:
#       Python interface implementation for VectorList.cpp


from ._bindings import _lib
from .Handle import Handle

class VectorListElement(Handle):
    """
    Base class for VectorList elements.
    """
    def __init__(self, handle):
        super().__init__(handle=handle)

    @property
    def element_type(self):
        if not self._handle:
            return 0
        return _lib.BrlVectorListElementType(self._handle)

class VectorListPointDraw(VectorListElement):
    def __init__(self, point):
        x, y, z = point
        handle = _lib.BrlNewVectorListPointDraw(x, y, z)
        super().__init__(handle=handle)

class VectorListPointSize(VectorListElement):
    def __init__(self, size):
        handle = _lib.BrlNewVectorListPointSize(size)
        super().__init__(handle=handle)

class VectorListLineMove(VectorListElement):
    def __init__(self, point):
        x, y, z = point
        handle = _lib.BrlNewVectorListLineMove(x, y, z)
        super().__init__(handle=handle)

class VectorListLineDraw(VectorListElement):
    def __init__(self, point):
        x, y, z = point
        handle = _lib.BrlNewVectorListLineDraw(x, y, z)
        super().__init__(handle=handle)

class VectorListLineWidth(VectorListElement):
    def __init__(self, width):
        handle = _lib.BrlNewVectorListLineWidth(width)
        super().__init__(handle=handle)

class VectorListTriangleStart(VectorListElement):
    def __init__(self, normal):
        nx, ny, nz = normal
        handle = _lib.BrlNewVectorListTriangleStart(nx, ny, nz)
        super().__init__(handle=handle)

class VectorListTriangleMove(VectorListElement):
    def __init__(self, point):
        x, y, z = point
        handle = _lib.BrlNewVectorListTriangleMove(x, y, z)
        super().__init__(handle=handle)

class VectorListTriangleDraw(VectorListElement):
    def __init__(self, point):
        x, y, z = point
        handle = _lib.BrlNewVectorListTriangleDraw(x, y, z)
        super().__init__(handle=handle)

class VectorListTriangleEnd(VectorListElement):
    def __init__(self, point):
        x, y, z = point
        handle = _lib.BrlNewVectorListTriangleEnd(x, y, z)
        super().__init__(handle=handle)

class VectorListTriangleVertexNormal(VectorListElement):
    def __init__(self, normal):
        nx, ny, nz = normal
        handle = _lib.BrlNewVectorListTriangleVertexNormal(nx, ny, nz)
        super().__init__(handle=handle)

class VectorListPolygonStart(VectorListElement):
    def __init__(self, normal):
        nx, ny, nz = normal
        handle = _lib.BrlNewVectorListPolygonStart(nx, ny, nz)
        super().__init__(handle=handle)

class VectorListPolygonMove(VectorListElement):
    def __init__(self, point):
        x, y, z = point
        handle = _lib.BrlNewVectorListPolygonMove(x, y, z)
        super().__init__(handle=handle)

class VectorListPolygonDraw(VectorListElement):
    def __init__(self, point):
        x, y, z = point
        handle = _lib.BrlNewVectorListPolygonDraw(x, y, z)
        super().__init__(handle=handle)

class VectorListPolygonEnd(VectorListElement):
    def __init__(self, point):
        x, y, z = point
        handle = _lib.BrlNewVectorListPolygonEnd(x, y, z)
        super().__init__(handle=handle)

class VectorListPolygonVertexNormal(VectorListElement):
    def __init__(self, normal):
        nx, ny, nz = normal
        handle = _lib.BrlNewVectorListPolygonVertexNormal(nx, ny, nz)
        super().__init__(handle=handle)

class VectorListDisplaySpace(VectorListElement):
    def __init__(self, point):
        x, y, z = point
        handle = _lib.BrlNewVectorListDisplaySpace(x, y, z)
        super().__init__(handle=handle)

class VectorListModelSpace(VectorListElement):
    def __init__(self):
        handle = _lib.BrlNewVectorListModelSpace()
        super().__init__(handle=handle)


class VectorList(Handle):
    """
    Object-oriented Python interface for the BRL-CAD VectorList point container.
    Used for gathering coordinate arrays during geometric plot computations.
    """

    def __init__(self):
        # Initialize by creating a raw native VectorList handle instance
        native_handle = _lib.BrlNewVectorList()
        if not native_handle:
            native_handle = None
        super().__init__(handle=native_handle)

    def append(self, element):
        """Appends a VectorListElement to the VectorList."""
        if not self._handle or not element._handle:
            return False
        return _lib.BrlVectorListAppend(self._handle, element._handle)

    def clear(self):
        """Clears all points currently stored inside the vector list container."""
        if not self._handle:
            return
        _lib.BrlVectorListClear(self._handle)
