#                       M E M O R Y D A T A B A S E . P Y
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
# @file MemoryDatabase.py
#
# BRL-CAD core simplified Python interface:
#       Python interface implementation for the MemoryDatabase.cpp


from ._bindings import _lib
from .Database import Database

class MemoryDatabase(Database):
    """Object-oriented Python interface for the in-memory BRL-CAD MemoryDatabase."""
    
    def __init__(self):
        self._handle = _lib.BrlNewMemoryDatabase()
        if not self._handle:
            self._handle = None
