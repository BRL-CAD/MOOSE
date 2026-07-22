#                       B A G O F T R I A N G L E S . P Y
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
# @file BagOfTriangles.py
#
# BRL-CAD core simplified Python interface:
#       Python interface implementation for the BagOfTriangles.cpp
#

import ctypes
from ._bindings import _lib
from .Object import Object
from .Handle import Handle


class BrlVector3D(Handle):
    """Opaque BRL-CAD Vector3D handle that behaves like a 3-item sequence."""

    def __init__(self, handle=None, owned=True):
        super().__init__(handle=handle, owned=owned)




class BagOfTriangles(Object):
    """Bag of Triangles (BoT) geometry primitive tracking container."""

    def __init__(self, *args, **kwargs):
        handle = None
        owned = kwargs.get('owned', True)

        if len(args) == 1 and isinstance(args[0], (int, ctypes.c_void_p)):
            handle = args[0]
        else:
            handle = _lib.BrlNewBagOfTriangles()

        super().__init__(handle=handle, owned=owned)

    def GetMode(self):
        """Returns the internal BrlBagOfTrianglesBotMode integer flag identification index."""
        return int(_lib.BrlBagOfTrianglesMode(self._handle))

    def SetMode(self, value):
        """Sets the active internal BagOfTriangles mode configuration flag index."""
        _lib.BrlBagOfTrianglesSetMode(self._handle, int(value))

    def GetOrientation(self):
        """Returns the internal BrlBagOfTrianglesBotOrientation integer flag identification index."""
        return int(_lib.BrlBagOfTrianglesOrientation(self._handle))

    def SetOrientation(self, value):
        """Sets the active internal BagOfTriangles orientation configuration flag index."""
        _lib.BrlBagOfTrianglesSetOrientation(self._handle, int(value))

    def GetFacesHaveNormals(self):
        """Returns True if the BoT faces have explicit normals configured valid."""
        return _lib.BrlBagOfTrianglesFacesHaveNormals(self._handle) != 0

    def SetFacesHaveNormals(self, value):
        """Sets the active valid status flag metadata tracking parameter for explicit normals."""
        _lib.BrlBagOfTrianglesSetFacesHaveNormals(self._handle, 1 if value else 0)

    def GetUseFaceNormals(self):
        """Returns True if the active calculation framework should utilize face normals."""
        return _lib.BrlBagOfTrianglesUseFaceNormals(self._handle) != 0

    def SetUseFaceNormals(self, value):
        """Sets the system flag configuration metric toggling structural use of face normals."""
        _lib.BrlBagOfTrianglesSetUseFaceNormals(self._handle, 1 if value else 0)

    def GetUseFloats(self):
        """Returns True if floating point coordinates are used instead of double precisions."""
        return _lib.BrlBagOfTrianglesUseFloats(self._handle) != 0

    def SetUseFloats(self, value):
        """Sets the active float representation flag metrics directly."""
        _lib.BrlBagOfTrianglesSetUseFloats(self._handle, 1 if value else 0)

    def GetNumberOfFaces(self):
        """Returns the total structural face element counter tracking integer."""
        return int(_lib.BrlBagOfTrianglesNumberOfFaces(self._handle))

    def GetFace(self, index):
        """Retrieves a wrapped Face reference tracking slot index identification."""
        raw_face = _lib.BrlBagOfTrianglesGetFace(self._handle, int(index))
        return Face(raw_face, owned=False) if raw_face else None

    def AddFace(self, point1X, point1Y, point1Z, point2X, point2Y, point2Z, point3X, point3Y, point3Z):
        """Appends a single triangle tracking component flat layout down the active framework mesh context."""
        raw_face = _lib.BrlBagOfTrianglesAddFace(
            self._handle,
            float(point1X), float(point1Y), float(point1Z),
            float(point2X), float(point2Y), float(point2Z),
            float(point3X), float(point3Y), float(point3Z)
        )
        return Face(raw_face, owned=False) if raw_face else None

    def DeleteFace(self, index):
        """Modifies active primitive stack data layout by deleting localized target mesh component indices."""
        _lib.BrlBagOfTrianglesDeleteFace(self._handle, int(index))

    def ClassName(self):
        """Returns the static C++ class designator identification string."""
        res = _lib.BrlBagOfTrianglesClassName()
        return res.decode('utf-8') if res else ""


class Face:
    """Encapsulates a managed pointer mapping tracking the heap-allocated BagOfTriangles::Face value copy frames."""

    def __init__(self, handle, owned=True):
        self._handle = handle
        self._owned = owned



    def GetPoint(self, index):
        """Returns the face point as a BrlVector3D wrapper."""
        vector_handle = _lib.BrlBagOfTrianglesFacePoint(self._handle, int(index))
        if not vector_handle:
            return None

        return BrlVector3D(vector_handle, owned=True)

    def SetPoint(self, index, pointX, pointY, pointZ):
        """Updates a localized unique vertex position point utilizing flat layout tracking coordinates."""
        _lib.BrlBagOfTrianglesFaceSetPoint(self._handle, int(index), float(pointX), float(pointY), float(pointZ))

    def SetPoints(self, point1X, point1Y, point1Z, point2X, point2Y, point2Z, point3X, point3Y, point3Z):
        """Applies explicit flat structural values configurations for all three triangle vertex structures simultaneously."""
        _lib.BrlBagOfTrianglesFaceSetPoints(
            self._handle,
            float(point1X), float(point1Y), float(point1Z),
            float(point2X), float(point2Y), float(point2Z),
            float(point3X), float(point3Y), float(point3Z)
        )

    def GetThickness(self):
        """Returns the physics thickness evaluation component tracking value metrics."""
        return _lib.BrlBagOfTrianglesFaceThickness(self._handle)

    def SetThickness(self, value):
        """Applies an explicit thickness evaluation target value modifier metric directly."""
        _lib.BrlBagOfTrianglesFaceSetThickness(self._handle, float(value))

    def GetAppendThickness(self):
        """Returns True if thickness parameter codes cascading logic drop down hierarchy values paths."""
        return _lib.BrlBagOfTrianglesFaceApendThickness(self._handle) != 0

    def SetAppendThickness(self, value):
        """Sets the structural toggle parameter for appended thickness evaluation parameters logic layouts."""
        _lib.BrlBagOfTrianglesFaceSetApendThickness(self._handle, 1 if value else 0)

    def GetNormal(self, index):
        """Returns the face normal as a BrlVector3D wrapper."""
        vector_handle = _lib.BrlBagOfTrianglesFaceNormal(self._handle, int(index))
        if not vector_handle:
            return None

        return BrlVector3D(vector_handle, owned=True)

    def SetNormal(self, index, normalX, normalY, normalZ):
        """Updates a localized unique vertex target vector orientation utilizing flat layout tracking coordinates."""
        _lib.BrlBagOfTrianglesFaceSetNormal(self._handle, int(index), float(normalX), float(normalY), float(normalZ))

    def SetNormals(self, normal1X, normal1Y, normal1Z, normal2X, normal2Y, normal2Z, normal3X, normal3Y, normal3Z):
        """Applies explicit flat structural normal metrics configurations for all three triangle vectors simultaneously."""
        _lib.BrlBagOfTrianglesFaceSetNormals(
            self._handle,
            float(normal1X), float(normal1Y), float(normal1Z),
            float(normal2X), float(normal2Y), float(normal2Z),
            float(normal3X), float(normal3Y), float(normal3Z)
        )
