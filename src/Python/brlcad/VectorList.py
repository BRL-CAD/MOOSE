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

    def clear(self):
        """Clears all points currently stored inside the vector list container."""
        if not self._handle:
            return
        _lib.BrlVectorListClear(self._handle)
