#                           U N K N O W N . P Y
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
# @file Unknown.py
#
# BRL-CAD core simplified Python interface:
#       Python interface implementation for Unknown.cpp

from ._bindings import _lib
from .Object import Object

class Unknown(Object):
    """
    Object-oriented Python interface for a BRL-CAD Unknown primitive.
    """

    def __init__(self, handle=None):
        super().__init__(handle=handle)
        
    @classmethod
    def class_name(cls):
        """Returns the internal C++ class name."""
        return _lib.BrlUnknownClassName().decode('utf-8')
