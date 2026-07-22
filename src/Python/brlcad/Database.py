#                       D A T A B A S E . P Y
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
# @file Database.py
#
# BRL-CAD core simplified Python interface:
#       Python interface implementation for the Database.py


import ctypes
from ._bindings import _lib
from .ConstDatabase import ConstDatabase

class Database(ConstDatabase):
    """Intermediate parent class providing read-write capabilities (SetTitle)."""
    
    def __init__(self):
        super().__init__()

    def SetTitle(self, title: str):
        """Modifies the internal title tracking string inside the database header."""
        if not self._handle:
            raise ValueError("Cannot invoke SetTitle on an explicitly closed session.")
            
        c_title = ctypes.c_char_p(title.encode('utf-8'))
        _lib.BrlDatabaseSetTitle(self._handle, c_title)
