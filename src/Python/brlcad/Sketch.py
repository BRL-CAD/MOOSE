#                            S K E T C H . P Y
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
# @file Sketch.py
#
# BRL-CAD core simplified Python interface:
#       Python interface implementation for Sketch.cpp

import ctypes
from ._bindings import _lib
from .Object import Object
from .Handle import Handle


class SketchSegment(Handle):
    """
    Base class for Sketch Segments.
    """
    def __init__(self, handle):
        super().__init__(handle=handle)

    @property
    def segment_type(self):
        if not self._handle:
            return 0
        return _lib.BrlSketchSegmentType(self._handle)

    @property
    def start_point(self):
        if not self._handle:
            return (0.0, 0.0)
        vec_handle = _lib.BrlSketchSegmentStartPoint(self._handle)
        if not vec_handle:
            return (0.0, 0.0)
        x = _lib.BrlVector3DX(vec_handle)
        y = _lib.BrlVector3DY(vec_handle)
        _lib.BrlDeleteHandle(vec_handle)
        return (x, y)

    @property
    def end_point(self):
        if not self._handle:
            return (0.0, 0.0)
        vec_handle = _lib.BrlSketchSegmentEndPoint(self._handle)
        if not vec_handle:
            return (0.0, 0.0)
        x = _lib.BrlVector3DX(vec_handle)
        y = _lib.BrlVector3DY(vec_handle)
        _lib.BrlDeleteHandle(vec_handle)
        return (x, y)

    @property
    def reverse(self):
        if not self._handle:
            return False
        return _lib.BrlSketchSegmentReverse(self._handle)

    @reverse.setter
    def reverse(self, value):
        if not self._handle:
            return
        _lib.BrlSketchSegmentSetReverse(self._handle, value)

    def cast(self):
        """Downcasts generic segment to specific segment class."""
        t = self.segment_type
        if t == 1: # Line
            h = _lib.BrlCastToSketchLine(self._handle)
            return SketchLine(handle=h)
        elif t == 2: # CircularArc
            h = _lib.BrlCastToSketchCircularArc(self._handle)
            return SketchCircularArc(handle=h)
        elif t == 3: # Nurb
            h = _lib.BrlCastToSketchNurb(self._handle)
            return SketchNurb(handle=h)
        elif t == 4: # Bezier
            h = _lib.BrlCastToSketchBezier(self._handle)
            return SketchBezier(handle=h)
        return self


class SketchLine(SketchSegment):
    def __init__(self, handle):
        super().__init__(handle=handle)

    @SketchSegment.start_point.setter
    def start_point(self, value):
        if not self._handle:
            return
        x, y = value
        _lib.BrlSketchLineSetStartPoint(self._handle, x, y)

    @SketchSegment.end_point.setter
    def end_point(self, value):
        if not self._handle:
            return
        x, y = value
        _lib.BrlSketchLineSetEndPoint(self._handle, x, y)


class SketchCircularArc(SketchSegment):
    def __init__(self, handle):
        super().__init__(handle=handle)

    @SketchSegment.start_point.setter
    def start_point(self, value):
        if not self._handle:
            return
        x, y = value
        _lib.BrlSketchCircularArcSetStartPoint(self._handle, x, y)

    @SketchSegment.end_point.setter
    def end_point(self, value):
        if not self._handle:
            return
        x, y = value
        _lib.BrlSketchCircularArcSetEndPoint(self._handle, x, y)

    @property
    def center(self):
        if not self._handle:
            return (0.0, 0.0, 0.0)
        vec_handle = _lib.BrlSketchCircularArcCenter(self._handle)
        if not vec_handle:
            return (0.0, 0.0, 0.0)
        x = _lib.BrlVector3DX(vec_handle)
        y = _lib.BrlVector3DY(vec_handle)
        z = _lib.BrlVector3DZ(vec_handle)
        _lib.BrlDeleteHandle(vec_handle)
        return (x, y, z)

    @center.setter
    def center(self, value):
        if not self._handle:
            return
        # Wait, the C API for SetCenter takes x, y (Vector2D). The getter returns Vector3D in C++.
        # Let's check Sketch.h again... yes, SetCenter(Vector2D c).
        x, y = value
        _lib.BrlSketchCircularArcSetCenter(self._handle, x, y)

    @property
    def radius(self):
        if not self._handle:
            return 0.0
        return _lib.BrlSketchCircularArcRadius(self._handle)

    @radius.setter
    def radius(self, value):
        if not self._handle:
            return
        _lib.BrlSketchCircularArcSetRadius(self._handle, value)

    @property
    def center_is_left(self):
        if not self._handle:
            return False
        return _lib.BrlSketchCircularArcCenterIsLeft(self._handle)

    @center_is_left.setter
    def center_is_left(self, value):
        if not self._handle:
            return
        _lib.BrlSketchCircularArcSetCenterIsLeft(self._handle, value)

    @property
    def clockwise_oriented(self):
        if not self._handle:
            return False
        return _lib.BrlSketchCircularArcClockwiseOriented(self._handle)

    @clockwise_oriented.setter
    def clockwise_oriented(self, value):
        if not self._handle:
            return
        _lib.BrlSketchCircularArcSetClockwiseOriented(self._handle, value)


class SketchNurb(SketchSegment):
    def __init__(self, handle):
        super().__init__(handle=handle)

    @SketchSegment.start_point.setter
    def start_point(self, value):
        if not self._handle:
            return
        x, y = value
        _lib.BrlSketchNurbSetStartPoint(self._handle, x, y)

    @SketchSegment.end_point.setter
    def end_point(self, value):
        if not self._handle:
            return
        x, y = value
        _lib.BrlSketchNurbSetEndPoint(self._handle, x, y)

    @property
    def order(self):
        if not self._handle:
            return 0
        return _lib.BrlSketchNurbOrder(self._handle)

    @order.setter
    def order(self, value):
        if not self._handle:
            return
        _lib.BrlSketchNurbSetOrder(self._handle, value)

    @property
    def is_rational(self):
        if not self._handle:
            return False
        return _lib.BrlSketchNurbIsRational(self._handle)

    @property
    def number_of_knots(self):
        if not self._handle:
            return 0
        return _lib.BrlSketchNurbNumberOfKnots(self._handle)

    def knot(self, index):
        if not self._handle:
            return 0.0
        return _lib.BrlSketchNurbKnot(self._handle, index)

    def add_knot(self, value):
        if not self._handle:
            return
        _lib.BrlSketchNurbAddKnot(self._handle, value)

    @property
    def number_of_control_points(self):
        if not self._handle:
            return 0
        return _lib.BrlSketchNurbNumberOfControlPoints(self._handle)

    def control_point(self, index):
        if not self._handle:
            return (0.0, 0.0)
        vec_handle = _lib.BrlSketchNurbControlPoint(self._handle, index)
        if not vec_handle:
            return (0.0, 0.0)
        x = _lib.BrlVector3DX(vec_handle)
        y = _lib.BrlVector3DY(vec_handle)
        _lib.BrlDeleteHandle(vec_handle)
        return (x, y)

    def control_point_weight(self, index):
        if not self._handle:
            return 0.0
        return _lib.BrlSketchNurbControlPointWeight(self._handle, index)

    def add_control_point(self, point, weight=None):
        if not self._handle:
            return
        x, y = point
        if weight is None:
            _lib.BrlSketchNurbAddControlPoint(self._handle, x, y)
        else:
            _lib.BrlSketchNurbAddControlPointWeight(self._handle, x, y, weight)


class SketchBezier(SketchSegment):
    def __init__(self, handle):
        super().__init__(handle=handle)

    @SketchSegment.start_point.setter
    def start_point(self, value):
        if not self._handle:
            return
        x, y = value
        _lib.BrlSketchBezierSetStartPoint(self._handle, x, y)

    @SketchSegment.end_point.setter
    def end_point(self, value):
        if not self._handle:
            return
        x, y = value
        _lib.BrlSketchBezierSetEndPoint(self._handle, x, y)

    @property
    def degree(self):
        if not self._handle:
            return 0
        return _lib.BrlSketchBezierDegree(self._handle)

    def control_point(self, index):
        if not self._handle:
            return (0.0, 0.0)
        vec_handle = _lib.BrlSketchBezierControlPoint(self._handle, index)
        if not vec_handle:
            return (0.0, 0.0)
        x = _lib.BrlVector3DX(vec_handle)
        y = _lib.BrlVector3DY(vec_handle)
        _lib.BrlDeleteHandle(vec_handle)
        return (x, y)

    def add_control_point(self, point):
        if not self._handle:
            return
        x, y = point
        _lib.BrlSketchBezierAddControlPoint(self._handle, x, y)


class Sketch(Object):
    """
    Object-oriented Python interface for the BRL-CAD Sketch primitive.
    """

    def __init__(self, handle=None):
        if handle is not None:
            super().__init__(handle=handle)
            return

        native_handle = _lib.BrlNewSketch()
        super().__init__(handle=native_handle)

    @property
    def embedding_plane_x(self):
        if not self._handle:
            return (0.0, 0.0, 0.0)
        vec_handle = _lib.BrlSketchEmbeddingPlaneX(self._handle)
        if not vec_handle:
            return (0.0, 0.0, 0.0)
        x = _lib.BrlVector3DX(vec_handle)
        y = _lib.BrlVector3DY(vec_handle)
        z = _lib.BrlVector3DZ(vec_handle)
        _lib.BrlDeleteHandle(vec_handle)
        return (x, y, z)

    @embedding_plane_x.setter
    def embedding_plane_x(self, value):
        if not self._handle:
            return
        x, y, z = value
        _lib.BrlSketchSetEmbeddingPlaneX(self._handle, x, y, z)

    @property
    def embedding_plane_y(self):
        if not self._handle:
            return (0.0, 0.0, 0.0)
        vec_handle = _lib.BrlSketchEmbeddingPlaneY(self._handle)
        if not vec_handle:
            return (0.0, 0.0, 0.0)
        x = _lib.BrlVector3DX(vec_handle)
        y = _lib.BrlVector3DY(vec_handle)
        z = _lib.BrlVector3DZ(vec_handle)
        _lib.BrlDeleteHandle(vec_handle)
        return (x, y, z)

    @embedding_plane_y.setter
    def embedding_plane_y(self, value):
        if not self._handle:
            return
        x, y, z = value
        _lib.BrlSketchSetEmbeddingPlaneY(self._handle, x, y, z)

    @property
    def embedding_plane_origin(self):
        if not self._handle:
            return (0.0, 0.0, 0.0)
        vec_handle = _lib.BrlSketchEmbeddingPlaneOrigin(self._handle)
        if not vec_handle:
            return (0.0, 0.0, 0.0)
        x = _lib.BrlVector3DX(vec_handle)
        y = _lib.BrlVector3DY(vec_handle)
        z = _lib.BrlVector3DZ(vec_handle)
        _lib.BrlDeleteHandle(vec_handle)
        return (x, y, z)

    @embedding_plane_origin.setter
    def embedding_plane_origin(self, value):
        if not self._handle:
            return
        x, y, z = value
        _lib.BrlSketchSetEmbeddingPlaneOrigin(self._handle, x, y, z)

    @property
    def number_of_segments(self):
        if not self._handle:
            return 0
        return _lib.BrlSketchNumberOfSegments(self._handle)

    def get_segment(self, index):
        if not self._handle:
            return None
        seg_handle = _lib.BrlSketchGetSegment(self._handle, index)
        if not seg_handle:
            return None
        return SketchSegment(handle=seg_handle).cast()

    def append_line(self):
        if not self._handle:
            return None
        h = _lib.BrlSketchAppendLine(self._handle)
        return SketchLine(handle=h) if h else None

    def insert_line(self, index):
        if not self._handle:
            return None
        h = _lib.BrlSketchInsertLine(self._handle, index)
        return SketchLine(handle=h) if h else None

    def append_arc(self):
        if not self._handle:
            return None
        h = _lib.BrlSketchAppendArc(self._handle)
        return SketchCircularArc(handle=h) if h else None

    def insert_arc(self, index):
        if not self._handle:
            return None
        h = _lib.BrlSketchInsertArc(self._handle, index)
        return SketchCircularArc(handle=h) if h else None

    def append_nurb(self):
        if not self._handle:
            return None
        h = _lib.BrlSketchAppendNurb(self._handle)
        return SketchNurb(handle=h) if h else None

    def insert_nurb(self, index):
        if not self._handle:
            return None
        h = _lib.BrlSketchInsertNurb(self._handle, index)
        return SketchNurb(handle=h) if h else None

    def append_bezier(self):
        if not self._handle:
            return None
        h = _lib.BrlSketchAppendBezier(self._handle)
        return SketchBezier(handle=h) if h else None

    def insert_bezier(self, index):
        if not self._handle:
            return None
        h = _lib.BrlSketchInsertBezier(self._handle, index)
        return SketchBezier(handle=h) if h else None

    def delete_segment(self, index):
        if not self._handle:
            return
        _lib.BrlSketchDeleteSegment(self._handle, index)

    @classmethod
    def class_name(cls):
        """Returns the internal C++ class name."""
        return _lib.BrlSketchClassName().decode('utf-8')
