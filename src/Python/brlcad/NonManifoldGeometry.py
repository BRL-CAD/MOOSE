#               N O N M A N I F O L D G E O M E T R Y . P Y
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
# @file NonManifoldGeometry.py
#
# BRL-CAD core simplified Python interface:
#       includes the python interface for non-manifold geometry
#
from ._bindings import _lib
from .Object import Object

class NonManifoldGeometryVertex:
    def __init__(self, handle):
        self._handle = handle

    @property
    def point(self):
        return _lib.BrlNonManifoldGeometryVertexPoint(self._handle)

class NonManifoldGeometryEdge:
    def __init__(self, handle):
        self._handle = handle

    @property
    def forward_vertex(self):
        v = _lib.BrlNonManifoldGeometryEdgeForwardVertex(self._handle)
        return NonManifoldGeometryVertex(v) if v else None

    @property
    def backward_vertex(self):
        v = _lib.BrlNonManifoldGeometryEdgeBackwardVertex(self._handle)
        return NonManifoldGeometryVertex(v) if v else None

class NonManifoldGeometryLoop:
    def __init__(self, handle):
        self._handle = handle

    @property
    def is_hole(self):
        return bool(_lib.BrlNonManifoldGeometryLoopIsHole(self._handle))

    def goto_first_edge(self):
        _lib.BrlNonManifoldGeometryLoopGotoFirstEdge(self._handle)

    def __next__(self):
        handle = _lib.BrlNonManifoldGeometryLoopNextEdge(self._handle)
        if not handle:
            raise StopIteration
        return self

    @property
    def current_edge(self):
        h = _lib.BrlNonManifoldGeometryLoopCurrentEdge(self._handle)
        return NonManifoldGeometryEdge(h) if h else None


class NonManifoldGeometryFace:
    def __init__(self, handle):
        self._handle = handle

    def goto_first_loop(self):
        _lib.BrlNonManifoldGeometryFaceGotoFirstLoop(self._handle)

    def __next__(self):
        handle = _lib.BrlNonManifoldGeometryFaceNextLoop(self._handle)
        if not handle:
            raise StopIteration
        return self

    @property
    def current_loop(self):
        h = _lib.BrlNonManifoldGeometryFaceCurrentLoop(self._handle)
        return NonManifoldGeometryLoop(h) if h else None

class NonManifoldGeometryShell:
    def __init__(self, handle):
        self._handle = handle

    def goto_first_face(self):
        _lib.BrlNonManifoldGeometryShellGotoFirstFace(self._handle)

    def next_face(self):
        return _lib.BrlNonManifoldGeometryShellNextFace(self._handle)

    @property
    def current_face(self):
        h = _lib.BrlNonManifoldGeometryShellCurrentFace(self._handle)
        return NonManifoldGeometryFace(h) if h else None

    def goto_first_loop(self):
        _lib.BrlNonManifoldGeometryShellGotoFirstLoop(self._handle)

    def next_loop(self):
        return _lib.BrlNonManifoldGeometryShellNextLoop(self._handle)

    @property
    def current_loop(self):
        h = _lib.BrlNonManifoldGeometryShellCurrentLoop(self._handle)
        return NonManifoldGeometryLoop(h) if h else None

    def goto_first_edge(self):
        _lib.BrlNonManifoldGeometryShellGotoFirstEdge(self._handle)

    def next_edge(self):
        return _lib.BrlNonManifoldGeometryShellNextEdge(self._handle)

    @property
    def current_edge(self):
        h = _lib.BrlNonManifoldGeometryShellCurrentEdge(self._handle)
        return NonManifoldGeometryEdge(h) if h else None

    def goto_first_vertex(self):
        _lib.BrlNonManifoldGeometryShellGotoFirstVertex(self._handle)

    def next_vertex(self):
        return _lib.BrlNonManifoldGeometryShellNextVertex(self._handle)

    @property
    def current_vertex(self):
        h = _lib.BrlNonManifoldGeometryShellCurrentVertex(self._handle)
        return NonManifoldGeometryVertex(h) if h else None

class NonManifoldGeometryRegion:
    def __init__(self, handle):
        self._handle = handle

    def goto_first_shell(self):
        _lib.BrlNonManifoldGeometryRegionGotoFirstShell(self._handle)

    def __next__(self):
        handle = _lib.BrlNonManifoldGeometryRegionNextShell(self._handle)
        if not handle:
            raise StopIteration
        return self

    @property
    def current_shell(self):
        h = _lib.BrlNonManifoldGeometryRegionCurrentShell(self._handle)
        return NonManifoldGeometryShell(h) if h else None


class NonManifoldGeometryRegionIterator:
    def __init__(self, handle):
        self._handle = handle

    def goto_first_region(self):
        _lib.BrlNonManifoldGeometryRegionIteratorGotoFirstRegion(self._handle)

    def __next__(self):
        handle = _lib.BrlNonManifoldGeometryRegionIteratorNextRegion(self._handle)
        if not handle:
            raise StopIteration
        return self

    @property
    def current_region(self):
        h = _lib.BrlNonManifoldGeometryRegionIteratorCurrentRegion(self._handle)
        return NonManifoldGeometryRegion(h) if h else None


class NonManifoldGeometry(Object):
    def __init__(self, handle=None, owned=None):
        if handle is None:
            handle = _lib.BrlNewNonManifoldGeometry()
            if owned is None:
                owned = True
        elif owned is None:
            owned = False
        super().__init__(handle=handle, owned=owned)

    def triangulate(self):
        _lib.BrlNonManifoldGeometryTriangulate(self._handle)

    def triangulate_shell(self, shell):
        _lib.BrlNonManifoldGeometryTriangulateShell(self._handle, shell._handle)

    def triangulate_face(self, face):
        _lib.BrlNonManifoldGeometryTriangulateFace(self._handle, face._handle)

    @property
    def regions(self):
        handle = _lib.BrlNonManifoldGeometryRegions(self._handle)
        return NonManifoldGeometryRegionIterator(handle) if handle else None

    @classmethod
    def class_name(cls):
        return _lib.BrlNonManifoldGeometryClassName().decode('utf-8')
