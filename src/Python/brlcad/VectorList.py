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

from ._bindings import _lib, BrlVectorListCallback
from .Handle import Handle


class ElementType:
    PointDraw = 0
    PointSize = 1
    LineMove = 2
    LineDraw = 3
    LineWidth = 4
    TriangleStart = 5
    TriangleMove = 6
    TriangleDraw = 7
    TriangleEnd = 8
    TriangleVertexNormal = 9
    PolygonStart = 10
    PolygonMove = 11
    PolygonDraw = 12
    PolygonEnd = 13
    PolygonVertexNormal = 14
    DisplaySpace = 15
    ModelSpace = 16


def _vector3d_tuple(vec_handle):
    if not vec_handle:
        return None
    x = _lib.BrlVector3DX(vec_handle)
    y = _lib.BrlVector3DY(vec_handle)
    z = _lib.BrlVector3DZ(vec_handle)
    _lib.BrlDeleteHandle(vec_handle)
    return (x, y, z)


class VectorListElement(Handle):
    """Borrowed or owned VectorList element handle."""

    def __init__(self, handle, owned=True):
        super().__init__(handle=handle, owned=owned)

    @property
    def element_type(self):
        if not self._handle:
            return None
        return _lib.BrlVectorListElementType(self._handle)

    def cast(self):
        t = self.element_type
        if t == ElementType.PointDraw:
            new_obj = VectorListPointDraw(handle=self._handle)
        elif t == ElementType.PointSize:
            new_obj = VectorListPointSize(handle=self._handle)
        elif t == ElementType.LineMove:
            new_obj = VectorListLineMove(handle=self._handle)
        elif t == ElementType.LineDraw:
            new_obj = VectorListLineDraw(handle=self._handle)
        elif t == ElementType.LineWidth:
            new_obj = VectorListLineWidth(handle=self._handle)
        elif t == ElementType.TriangleStart:
            new_obj = VectorListTriangleStart(handle=self._handle)
        elif t == ElementType.TriangleMove:
            new_obj = VectorListTriangleMove(handle=self._handle)
        elif t == ElementType.TriangleDraw:
            new_obj = VectorListTriangleDraw(handle=self._handle)
        elif t == ElementType.TriangleEnd:
            new_obj = VectorListTriangleEnd(handle=self._handle)
        elif t == ElementType.TriangleVertexNormal:
            new_obj = VectorListTriangleVertexNormal(handle=self._handle)
        elif t == ElementType.PolygonStart:
            new_obj = VectorListPolygonStart(handle=self._handle)
        elif t == ElementType.PolygonMove:
            new_obj = VectorListPolygonMove(handle=self._handle)
        elif t == ElementType.PolygonDraw:
            new_obj = VectorListPolygonDraw(handle=self._handle)
        elif t == ElementType.PolygonEnd:
            new_obj = VectorListPolygonEnd(handle=self._handle)
        elif t == ElementType.PolygonVertexNormal:
            new_obj = VectorListPolygonVertexNormal(handle=self._handle)
        elif t == ElementType.DisplaySpace:
            new_obj = VectorListDisplaySpace(handle=self._handle)
        elif t == ElementType.ModelSpace:
            new_obj = VectorListModelSpace(handle=self._handle)
        else:
            return self
            
        new_obj._owned = self._owned
        self._owned = False
        return new_obj


class VectorListPointDraw(VectorListElement):
    def __init__(self, point=None, handle=None, owned=True):
        if handle is not None:
            super().__init__(handle=handle, owned=owned)
        elif point is not None:
            x, y, z = point
            super().__init__(handle=_lib.BrlNewVectorListPointDrawAsPoint(x, y, z), owned=True)
        else:
            super().__init__(handle=_lib.BrlNewVectorListPointDraw(), owned=True)

    @property
    def point(self):
        return _vector3d_tuple(_lib.BrlVectorListPointDrawPoint(self._handle))


class VectorListPointSize(VectorListElement):
    def __init__(self, size=None, handle=None, owned=True):
        if handle is not None:
            super().__init__(handle=handle, owned=owned)
        elif size is not None:
            super().__init__(handle=_lib.BrlNewVectorListPointSizeAsSize(size), owned=True)
        else:
            super().__init__(handle=_lib.BrlNewVectorListPointSize(), owned=True)

    @property
    def size(self):
        return _lib.BrlVectorListPointSizeSize(self._handle)


class VectorListLineMove(VectorListElement):
    def __init__(self, point=None, handle=None, owned=True):
        if handle is not None:
            super().__init__(handle=handle, owned=owned)
        elif point is not None:
            x, y, z = point
            super().__init__(handle=_lib.BrlNewVectorListLineMoveAsPoint(x, y, z), owned=True)
        else:
            super().__init__(handle=_lib.BrlNewVectorListLineMove(), owned=True)

    @property
    def point(self):
        return _vector3d_tuple(_lib.BrlVectorListLineMovePoint(self._handle))


class VectorListLineDraw(VectorListElement):
    def __init__(self, point=None, handle=None, owned=True):
        if handle is not None:
            super().__init__(handle=handle, owned=owned)
        elif point is not None:
            x, y, z = point
            super().__init__(handle=_lib.BrlNewVectorListLineDrawAsPoint(x, y, z), owned=True)
        else:
            super().__init__(handle=_lib.BrlNewVectorListLineDraw(), owned=True)

    @property
    def point(self):
        return _vector3d_tuple(_lib.BrlVectorListLineDrawPoint(self._handle))


class VectorListLineWidth(VectorListElement):
    def __init__(self, width=None, handle=None, owned=True):
        if handle is not None:
            super().__init__(handle=handle, owned=owned)
        elif width is not None:
            super().__init__(handle=_lib.BrlNewVectorListLineWidthAsWidth(width), owned=True)
        else:
            super().__init__(handle=_lib.BrlNewVectorListLineWidth(), owned=True)

    @property
    def width(self):
        return _lib.BrlVectorListLineWidthWidth(self._handle)


class VectorListTriangleStart(VectorListElement):
    def __init__(self, normal=None, handle=None, owned=True):
        if handle is not None:
            super().__init__(handle=handle, owned=owned)
        elif normal is not None:
            nx, ny, nz = normal
            super().__init__(handle=_lib.BrlNewVectorListTriangleStartAsNormal(nx, ny, nz), owned=True)
        else:
            super().__init__(handle=_lib.BrlNewVectorListTriangleStart(), owned=True)

    @property
    def normal(self):
        return _vector3d_tuple(_lib.BrlVectorListTriangleStartNormal(self._handle))


class VectorListTriangleMove(VectorListElement):
    def __init__(self, point=None, handle=None, owned=True):
        if handle is not None:
            super().__init__(handle=handle, owned=owned)
        elif point is not None:
            x, y, z = point
            super().__init__(handle=_lib.BrlNewVectorListTriangleMoveAsPoint(x, y, z), owned=True)
        else:
            super().__init__(handle=_lib.BrlNewVectorListTriangleMove(), owned=True)

    @property
    def point(self):
        return _vector3d_tuple(_lib.BrlVectorListTriangleMovePoint(self._handle))


class VectorListTriangleDraw(VectorListElement):
    def __init__(self, point=None, handle=None, owned=True):
        if handle is not None:
            super().__init__(handle=handle, owned=owned)
        elif point is not None:
            x, y, z = point
            super().__init__(handle=_lib.BrlNewVectorListTriangleDrawAsPoint(x, y, z), owned=True)
        else:
            super().__init__(handle=_lib.BrlNewVectorListTriangleDraw(), owned=True)

    @property
    def point(self):
        return _vector3d_tuple(_lib.BrlVectorListTriangleDrawPoint(self._handle))


class VectorListTriangleEnd(VectorListElement):
    def __init__(self, point=None, handle=None, owned=True):
        if handle is not None:
            super().__init__(handle=handle, owned=owned)
        elif point is not None:
            x, y, z = point
            super().__init__(handle=_lib.BrlNewVectorListTriangleEndAsPoint(x, y, z), owned=True)
        else:
            super().__init__(handle=_lib.BrlNewVectorListTriangleEnd(), owned=True)

    @property
    def point(self):
        return _vector3d_tuple(_lib.BrlVectorListTriangleEndPoint(self._handle))


class VectorListTriangleVertexNormal(VectorListElement):
    def __init__(self, normal=None, handle=None, owned=True):
        if handle is not None:
            super().__init__(handle=handle, owned=owned)
        elif normal is not None:
            nx, ny, nz = normal
            super().__init__(handle=_lib.BrlNewVectorListTriangleVertexNormalAsNormal(nx, ny, nz), owned=True)
        else:
            super().__init__(handle=_lib.BrlNewVectorListTriangleVertexNormal(), owned=True)

    @property
    def normal(self):
        return _vector3d_tuple(_lib.BrlVectorListTriangleVertexNormalNormal(self._handle))


class VectorListPolygonStart(VectorListElement):
    def __init__(self, normal=None, handle=None, owned=True):
        if handle is not None:
            super().__init__(handle=handle, owned=owned)
        elif normal is not None:
            nx, ny, nz = normal
            super().__init__(handle=_lib.BrlNewVectorListPolygonStartAsNormal(nx, ny, nz), owned=True)
        else:
            super().__init__(handle=_lib.BrlNewVectorListPolygonStart(), owned=True)

    @property
    def normal(self):
        return _vector3d_tuple(_lib.BrlVectorListPolygonStartNormal(self._handle))


class VectorListPolygonMove(VectorListElement):
    def __init__(self, point=None, handle=None, owned=True):
        if handle is not None:
            super().__init__(handle=handle, owned=owned)
        elif point is not None:
            x, y, z = point
            super().__init__(handle=_lib.BrlNewVectorListPolygonMoveAsPoint(x, y, z), owned=True)
        else:
            super().__init__(handle=_lib.BrlNewVectorListPolygonMove(), owned=True)

    @property
    def point(self):
        return _vector3d_tuple(_lib.BrlVectorListPolygonMovePoint(self._handle))


class VectorListPolygonDraw(VectorListElement):
    def __init__(self, point=None, handle=None, owned=True):
        if handle is not None:
            super().__init__(handle=handle, owned=owned)
        elif point is not None:
            x, y, z = point
            super().__init__(handle=_lib.BrlNewVectorListPolygonDrawAsPoint(x, y, z), owned=True)
        else:
            super().__init__(handle=_lib.BrlNewVectorListPolygonDraw(), owned=True)

    @property
    def point(self):
        return _vector3d_tuple(_lib.BrlVectorListPolygonDrawPoint(self._handle))


class VectorListPolygonEnd(VectorListElement):
    def __init__(self, point=None, handle=None, owned=True):
        if handle is not None:
            super().__init__(handle=handle, owned=owned)
        elif point is not None:
            x, y, z = point
            super().__init__(handle=_lib.BrlNewVectorListPolygonEndAsPoint(x, y, z), owned=True)
        else:
            super().__init__(handle=_lib.BrlNewVectorListPolygonEnd(), owned=True)

    @property
    def point(self):
        return _vector3d_tuple(_lib.BrlVectorListPolygonEndPoint(self._handle))


class VectorListPolygonVertexNormal(VectorListElement):
    def __init__(self, normal=None, handle=None, owned=True):
        if handle is not None:
            super().__init__(handle=handle, owned=owned)
        elif normal is not None:
            nx, ny, nz = normal
            super().__init__(handle=_lib.BrlNewVectorListPolygonVertexNormalAsNormal(nx, ny, nz), owned=True)
        else:
            super().__init__(handle=_lib.BrlNewVectorListPolygonVertexNormal(), owned=True)

    @property
    def normal(self):
        return _vector3d_tuple(_lib.BrlVectorListPolygonVertexNormalNormal(self._handle))


class VectorListDisplaySpace(VectorListElement):
    def __init__(self, point=None, handle=None, owned=True):
        if handle is not None:
            super().__init__(handle=handle, owned=owned)
        elif point is not None:
            x, y, z = point
            super().__init__(handle=_lib.BrlNewVectorListDisplaySpaceAsReferencePoint(x, y, z), owned=True)
        else:
            super().__init__(handle=_lib.BrlNewVectorListDisplaySpace(), owned=True)

    @property
    def reference_point(self):
        return _vector3d_tuple(_lib.BrlVectorListDisplaySpaceReferencePoint(self._handle))


class VectorListModelSpace(VectorListElement):
    def __init__(self, handle=None, owned=True):
        if handle is not None:
            super().__init__(handle=handle, owned=owned)
        else:
            super().__init__(handle=_lib.BrlNewVectorListModelSpace(), owned=True)


_ELEMENT_CLASSES = {
    ElementType.PointDraw: VectorListPointDraw,
    ElementType.PointSize: VectorListPointSize,
    ElementType.LineMove: VectorListLineMove,
    ElementType.LineDraw: VectorListLineDraw,
    ElementType.LineWidth: VectorListLineWidth,
    ElementType.TriangleStart: VectorListTriangleStart,
    ElementType.TriangleMove: VectorListTriangleMove,
    ElementType.TriangleDraw: VectorListTriangleDraw,
    ElementType.TriangleEnd: VectorListTriangleEnd,
    ElementType.TriangleVertexNormal: VectorListTriangleVertexNormal,
    ElementType.PolygonStart: VectorListPolygonStart,
    ElementType.PolygonMove: VectorListPolygonMove,
    ElementType.PolygonDraw: VectorListPolygonDraw,
    ElementType.PolygonEnd: VectorListPolygonEnd,
    ElementType.PolygonVertexNormal: VectorListPolygonVertexNormal,
    ElementType.DisplaySpace: VectorListDisplaySpace,
    ElementType.ModelSpace: VectorListModelSpace,
}


def _wrap_borrowed_element(handle):
    if not handle:
        return None
    element_type = _lib.BrlVectorListElementType(handle)
    cls = _ELEMENT_CLASSES.get(element_type, VectorListElement)
    return cls(handle=handle, owned=False)


class VectorList(Handle):
    """
    Object-oriented Python interface for the BRL-CAD VectorList.
    Typically filled by Plot, then read via iterate().
    """

    def __init__(self):
        native_handle = _lib.BrlNewVectorList()
        if not native_handle:
            native_handle = None
        super().__init__(handle=native_handle)

    def clear(self):
        if not self._handle:
            return
        _lib.BrlVectorListClear(self._handle)

    def iterate(self, callback):
        """
        Call callback(element) for each element.
        Return False from callback to stop; True/None continues.
        Element handles are borrowed and only valid during the callback.
        """
        if not self._handle:
            return

        @BrlVectorListCallback
        def c_callback(element_handle, userdata):
            element = _wrap_borrowed_element(element_handle)
            result = callback(element)
            if result is False:
                return 0
            return 1

        _lib.BrlVectorListIterate(self._handle, c_callback, None)

    def elements(self):
        """Collect a snapshot of readable element data during iteration."""
        items = []

        def collect(element):
            entry = {'type': element.element_type}
            if hasattr(element, 'point'):
                entry['point'] = element.point
            if hasattr(element, 'normal'):
                entry['normal'] = element.normal
            if hasattr(element, 'size'):
                entry['size'] = element.size
            if hasattr(element, 'width'):
                entry['width'] = element.width
            if hasattr(element, 'reference_point'):
                entry['reference_point'] = element.reference_point
            items.append(entry)
            return True

        self.iterate(collect)
        return items

    def append(self, element):
        """Secondary write helper."""
        if not self._handle or not element._handle:
            return False
        res = _lib.BrlVectorListAppend(self._handle, element._handle) != 0
        if res:
            element._owned = False
        return res
