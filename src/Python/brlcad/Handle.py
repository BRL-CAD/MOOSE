#                       H A N D L E . P Y
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
# @file Handle.py
#
# BRL-CAD core simplified Python interface:
#       Python interface declares the base for all handles


from ._bindings import _lib

class Handle:
    """
    Absolute base class for all BRL-CAD tracking resources.
    Implements unified polymorphic memory lifecycle management.
    """
    def __init__(self, handle=None, owned=True):
        if handle == 0 or handle == 0x0:
            self._handle = None
        else:
            self._handle = handle
        self._owned = owned  

    def close(self):
        """Explicitly drops the pointer into the unified C++ destructor if owned."""
        if hasattr(self, '_handle') and self._handle is not None and self._handle != 0:
            is_owned = getattr(self, '_owned', True)
            
            if is_owned:  
                _lib.BrlDeleteHandle(self._handle)
            self._handle = None

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.close()

    def __del__(self):
        self.close()
