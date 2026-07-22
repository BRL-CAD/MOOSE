#                       O B J E C T . P Y
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
# @file Object.py
#
# BRL-CAD core simplified Python interface:
#       Python interface implementation for the Object.cpp


import ctypes
from ._bindings import _lib
from .Handle import Handle

class Object(Handle):
    """Base class for all BRL-CAD geometric primitives."""
    
    def __init__(self, handle=None, owned=True):
        super().__init__(handle=handle, owned=owned)

    def SetName(self, name: str):
        """Sets the structural database lookup name key for this shape."""
        if not self._handle:
            return 
        c_name = ctypes.c_char_p(name.encode('utf-8'))
        _lib.BrlObjectSetName(self._handle, c_name)
        
    def IsValid(self):
        """Returns True if the geometric primitive is valid."""
        return _lib.BrlObjectIsValid(self._handle) == 1

    def GetType(self):
        """Returns the core primitive engine type string."""
        type_str = _lib.BrlObjectType(self._handle)
        return type_str.decode('utf-8') if type_str else ""
    
    def GetName(self):
        """Returns the structural database lookup name key string."""
        if not self._handle:
            return ""
        name_str = _lib.BrlObjectName(self._handle)
        return name_str.decode('utf-8') if name_str else ""

    def HasAttribute(self, key: str):
        """Returns True if the object contains an attribute matching the specified key."""
        if not self._handle:
            return False
        c_key = ctypes.c_char_p(key.encode('utf-8'))
        return _lib.BrlObjectHasAttribute(self._handle, c_key) == 1

    def Attribute(self, key: str):
        """Returns the value string associated with the specified attribute key."""
        if not self._handle:
            return ""
        c_key = ctypes.c_char_p(key.encode('utf-8'))
        val_str = _lib.BrlObjectAttribute(self._handle, c_key)
        return val_str.decode('utf-8') if val_str else ""

    def SetAttribute(self, key: str, value: str):
        """Sets a clean unique attribute key-value pair mapping on the object."""
        if not self._handle:
            return
        c_key = ctypes.c_char_p(key.encode('utf-8'))
        c_value = ctypes.c_char_p(value.encode('utf-8'))
        _lib.BrlObjectSetAttribute(self._handle, c_key, c_value)

    def AddMultiAttribute(self, key: str, value: str):
        """Appends a non-unique, variadic attribute key-value entry group."""
        if not self._handle:
            return
        c_key = ctypes.c_char_p(key.encode('utf-8'))
        c_value = ctypes.c_char_p(value.encode('utf-8'))
        _lib.BrlObjectAddMultiAttribute(self._handle, c_key, c_value)

    def RemoveAttribute(self, key: str):
        """Removes all matching occurrences of an attribute target key identifier."""
        if not self._handle:
            return
        c_key = ctypes.c_char_p(key.encode('utf-8'))
        _lib.BrlObjectRemoveAttribute(self._handle, c_key)

    def ClearAttributes(self):
        """Flushes and completely drops all attribute set structures allocated to the object."""
        if not self._handle:
            return
        _lib.BrlObjectClearAttributes(self._handle)
        
    def IterAttributes(self):
        """Yields all (key, value) attribute string pairs assigned to this object."""
        if not self._handle:
            return

        it = _lib.BrlObjectFirstAttribute(self._handle)
        if not it:
            return

        while _lib.BrlObjectAttributeIteratorGood(it) == 1:
            key_ptr = _lib.BrlObjectAttributeIteratorKey(it)
            val_ptr = _lib.BrlObjectAttributeIteratorValue(it)
            
            key = key_ptr.decode('utf-8') if key_ptr else ""
            val = val_ptr.decode('utf-8') if val_ptr else ""
            
            yield key, val
            _lib.BrlObjectAttributeIteratorNext(it)
            
        _lib.BrlDeleteHandle(it)

    def IterMultiAttributes(self, key: str):
        """Yields all (key, value) pairs matching a specific non-unique key stream."""
        if not self._handle:
            return

        c_key = ctypes.c_char_p(key.encode('utf-8'))
        it = _lib.BrlObjectMultiAttribute(self._handle, c_key)
        if not it:
            return

        while _lib.BrlObjectAttributeIteratorGood(it) == 1:
            key_ptr = _lib.BrlObjectAttributeIteratorKey(it)
            val_ptr = _lib.BrlObjectAttributeIteratorValue(it)
            
            k = key_ptr.decode('utf-8') if key_ptr else ""
            v = val_ptr.decode('utf-8') if val_ptr else ""
            
            yield k, v
            _lib.BrlObjectAttributeIteratorNext(it)
            
        _lib.BrlDeleteHandle(it)
        
    def Clone(self):
        """Creates a deep duplicate tracking copy of the primitive shape."""
        raw_clone = _lib.BrlObjectClone(self._handle)
        # Dynamic look-up optimization instantiates the proper subclass layout context
        return self.__class__(raw_clone, owned=True) if raw_clone else None
