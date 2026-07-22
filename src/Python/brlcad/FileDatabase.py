#                       F I L E D A T A B A S E . P Y
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
# @file FileDatabase.py
#
# BRL-CAD core simplified Python interface:
#       Python interface implementation for the FileDatabase.cpp


from ._bindings import _lib
from .Database import Database

class FileDatabase(Database):
    """Object-oriented Python interface for the read-write BRL-CAD FileDatabase."""
    
    def __init__(self):
        self._handle = _lib.BrlNewFileDatabase()
        if not self._handle:
            self._handle = None
