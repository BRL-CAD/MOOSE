#                       C O N S T D A T A B A S E . P Y
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
# @file ConstDatabase.py
#
# BRL-CAD core simplified Python interface:
#       Python interface implementation for the ConstDatabase.cpp

import os
import ctypes
from ._bindings import _lib
from .Handle import Handle

class ConstDatabase(Handle):
    """Object-oriented Python interface for the BRL-CAD ConstDatabase."""

    def __init__(self, *args, **kwargs):
        handle = kwargs.get('handle', None)
        owned = kwargs.get('owned', True)

        # Allow passing the handle as a positional argument too: ConstDatabase(db_handle)
        if len(args) == 1 and isinstance(args[0], (int, ctypes.c_void_p)):
            handle = args[0]

        # If no handle was passed, allocate a new one using the C-bindings
        if handle is None:
            handle = _lib.BrlNewConstDatabase()

        # Pass it up to the parent Object class
        super().__init__(handle=handle, owned=owned)

    def Load(self, file_name: str) -> bool:
        """Loads a BRL-CAD database file using the existing handle."""
        if not self._handle:
            native_handle = _lib.BrlNewConstDatabase()
            self._handle = native_handle if native_handle else None
            if not self._handle:
                return False

        if not os.path.exists(file_name):
            return False
        c_file = ctypes.c_char_p(file_name.encode('utf-8'))
        status = _lib.BrlConstDatabaseLoad(self._handle, c_file)

        if status == 0:
            self.close()
            return False

        return True

    def Title(self) -> str:
        """Extracts and decodes the database internal title header."""
        if not self._handle:
            return ""

        raw_ptr = _lib.BrlConstDatabaseTitle(self._handle)
        return raw_ptr.decode('utf-8') if raw_ptr else ""

    def Plot(self, object_name: str, vector_list: Handle):
        """Plots the targeted database geometry element data into a VectorList."""
        if not self._handle:
            return

        c_name = ctypes.c_char_p(object_name.encode('utf-8'))
        _lib.BrlConstDatabasePlot(self._handle, c_name, vector_list._handle)

    def Get(self, object_name):
        """
        Fetches an object from the database and automatically wraps it
        in its concrete Python primitive class (Combination, Sphere, etc.).
        """
        # Fetch the raw C-pointer from the database
        raw_handle = _lib.BrlConstDatabaseGet(self._handle, object_name.encode('utf-8'))

        if not raw_handle:
            return None

        # Ask the C++ backend what specific type this pointer represents
        type_bytes = _lib.BrlObjectType(raw_handle)

        if not type_bytes:
            from .Object import Object
            return Object(handle=raw_handle)

        obj_type = type_bytes.decode('utf-8')

        # --- THE FACTORY ROUTER ---
        # Match the C++ string to our Python classes
        if obj_type == "Combination":
            from .Combinations import Combinations
            return Combinations(handle=raw_handle)

        elif obj_type == "Sphere":
            from .Sphere import Sphere
            return Sphere(handle=raw_handle)

        elif obj_type == "Arb8":
            from .Arb8 import Arb8
            return Arb8(handle=raw_handle)

        # Add new primitives here as you build them (Cone, Ellipsoid, etc.)

        else:
            # Fallback: If we haven't written the Python wrapper for this shape yet,
            # just return it as a generic Object so the user can still hold it.
            from .Object import Object
            return Object(handle=raw_handle)

    def Facetize(self, object_name: str) -> ctypes.c_void_p:
        """Generates a Non-Manifold Geometry mesh pointer managed by the database."""
        if not self._handle:
            return None

        c_name = ctypes.c_char_p(object_name.encode('utf-8'))
        raw_mesh = _lib.BrlConstDatabaseFacetize(self._handle, c_name)
        return raw_mesh

    def Select(self, object_name: str):
        """Adds a target object item to the active selection group cluster state."""
        if not self._handle:
            return

        c_name = ctypes.c_char_p(object_name.encode('utf-8'))
        _lib.BrlConstDatabaseSelect(self._handle, c_name)

    def UnselectAll(self):
        """Clears all objects from the active database selection group array."""
        if self._handle:
            _lib.BrlConstDatabaseUnSelectAll(self._handle)

    def IsSelectionEmpty(self) -> bool:
        """Checks if the active database selection group is empty."""
        if not self._handle:
            return True

        return _lib.BrlConstDatabaseSelectionIsEmpty(self._handle) == 1

    def BoundingBoxMinima(self):
        """Returns a 3-tuple (x, y, z) indicating the minimum bounding space corner coordinates."""
        if not self._handle:
            return (0.0, 0.0, 0.0)

        x, y, z = ctypes.c_double(), ctypes.c_double(), ctypes.c_double()
        _lib.BrlConstDatabaseBoundingBoxMinima(self._handle, ctypes.byref(x), ctypes.byref(y), ctypes.byref(z))
        return (x.value, y.value, z.value)

    def BoundingBoxMaxima(self):
        """Returns a 3-tuple (x, y, z) indicating the maximum bounding space corner coordinates."""
        if not self._handle:
            return (0.0, 0.0, 0.0)

        x, y, z = ctypes.c_double(), ctypes.c_double(), ctypes.c_double()
        _lib.BrlConstDatabaseBoundingBoxMaxima(self._handle, ctypes.byref(x), ctypes.byref(y), ctypes.byref(z))
        return (x.value, y.value, z.value)

    def FirstTopObject(self) -> ctypes.c_void_p:
        """Returns the raw pointer to the first top-level object iterator."""
        if not self._handle:
            return None

        return _lib.BrlConstDatabaseFirstTopObject(self._handle)

    def IteratorGood(self, iterator_handle) -> bool:
        """Checks if the iterator pointer is still valid."""
        if not iterator_handle:
            return False

        return _lib.BrlTopObjectIteratorGood(iterator_handle) == 1

    def IteratorNext(self, iterator_handle):
        """Advances the iterator to the next top-level object."""
        if iterator_handle:
            _lib.BrlTopObjectIteratorNext(iterator_handle)

    def IteratorName(self, iterator_handle) -> str:
        """Gets the string name of the object at the current iterator position."""
        if not iterator_handle:
            return ""

        raw_ptr = _lib.BrlTopObjectIteratorName(iterator_handle)
        return raw_ptr.decode('utf-8') if raw_ptr else ""

    def DeleteIterator(self, iterator_handle):
        """Manually deletes the iterator tracking structure from the heap."""
        if iterator_handle:
            _lib.BrlDeleteTopObjectIterator(iterator_handle)
