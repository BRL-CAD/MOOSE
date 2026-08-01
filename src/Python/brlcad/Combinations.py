#                       C O M B I N A T I O N . P Y
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
# @file Combination.py
#
# BRL-CAD core simplified Python interface:
#       Python interface implementation for the Combination.cpp
#

import ctypes
from ._bindings import _lib
from .Object import Object


class Combinations(Object):
    """Combination database group primitive tracking container."""

    def __init__(self, *args, **kwargs):
        handle = None
        owned = kwargs.get('owned', True)

        if len(args) == 1 and isinstance(args[0], (int, ctypes.c_void_p)):
            handle = args[0]
        else:
            handle = _lib.BrlNewCombination()

        super().__init__(handle=handle, owned=owned)

    def IsRegion(self):
        """Returns True if the combination is flag-configured as a region."""
        return _lib.BrlCombinationIsRegion(self._handle) != 0

    def SetIsRegion(self, value):
        """Sets the active internal region boolean status flag."""
        _lib.BrlCombinationSetIsRegion(self._handle, 1 if value else 0)

    def GetFastgenRegion(self):
        """Returns the internal Fastgen layout configuration flag enum index."""
        return int(_lib.BrlCombinationFastgenRegion(self._handle))

    def SetFastgenRegion(self, value):
        """Sets the target Fastgen region structural layout type configuration."""
        _lib.BrlCombinationSetFastgenRegion(self._handle, int(value))

    def GetRegionId(self):
        """Returns the specific layout region index identification integer."""
        return _lib.BrlCombinationRegionId(self._handle)

    def SetRegionId(self, value):
        """Modifies the active combination structural region index code tracking."""
        _lib.BrlCombinationSetRegionId(self._handle, int(value))

    def GetAircode(self):
        """Returns the structural air tracking contextual assignment code integer."""
        return _lib.BrlCombinationAircode(self._handle)

    def SetAircode(self, value):
        """Sets the specific structural system air code assignment metrics."""
        _lib.BrlCombinationSetAircode(self._handle, int(value))

    def GetGiftMaterial(self):
        """Returns the associated legacy GIFT evaluation identifier number."""
        return _lib.BrlCombinationGiftMaterial(self._handle)

    def SetGiftMaterial(self, value):
        """Updates the legacy GIFT engine physics evaluation component identification."""
        _lib.BrlCombinationSetGiftMaterial(self._handle, int(value))

    def GetLineOfSight(self):
        """Returns the active internal thickness structural parameter percentage."""
        return _lib.BrlCombinationLineOfSight(self._handle)

    def SetLineOfSight(self, value):
        """Sets the line of sight evaluation density thickness percentage property."""
        _lib.BrlCombinationSetLineOfSight(self._handle, int(value))

    def HasColor(self):
        """Returns True if explicit RGB color channels properties are configured valid."""
        return _lib.BrlCombinationHasColor(self._handle) != 0

    def SetHasColor(self, value):
        """Sets the active valid status flag metadata tracking parameter for colors."""
        _lib.BrlCombinationSetHasColor(self._handle, 1 if value else 0)

    def GetRed(self):
        """Returns the localized normalized value [0, 1] for the red component color channel."""
        return _lib.BrlCombinationRed(self._handle)

    def SetRed(self, value):
        """Modifies the red color channel metrics directly."""
        _lib.BrlCombinationSetRed(self._handle, float(value))

    def GetGreen(self):
        """Returns the localized normalized value [0, 1] for the green component color channel."""
        return _lib.BrlCombinationGreen(self._handle)

    def SetGreen(self, value):
        """Modifies the green color channel metrics directly."""
        _lib.BrlCombinationSetGreen(self._handle, float(value))

    def GetBlue(self):
        """Returns the localized normalized value [0, 1] for the blue component color channel."""
        return _lib.BrlCombinationBlue(self._handle)

    def SetBlue(self, value):
        """Modifies the blue color channel metrics directly."""
        _lib.BrlCombinationSetBlue(self._handle, float(value))

    def GetShader(self):
        """Returns the target layout character tracking path context text string."""
        res = _lib.BrlCombinationShader(self._handle)
        return res.decode('utf-8') if res else ""

    def SetShader(self, value):
        """Applies a target character tracker path property context configuration."""
        _lib.BrlCombinationSetShader(self._handle, value.encode('utf-8'))

    def Inherit(self):
        """Returns True if properties are flag-configured to drop down hierarchy paths."""
        return _lib.BrlCombinationInherit(self._handle) != 0

    def SetInherit(self, value):
        """Sets the system flag configuration metric toggling structural properties cascading."""
        _lib.BrlCombinationSetInherit(self._handle, 1 if value else 0)

    def GetMaterial(self):
        """Returns the target material specification context tracking text string."""
        res = _lib.BrlCombinationMaterial(self._handle)
        return res.decode('utf-8') if res else ""

    def SetMaterial(self, value):
        """Applies an explicit string format tracking context configuration for tracking materials."""
        _lib.BrlCombinationSetMaterial(self._handle, value.encode('utf-8'))

    def GetTemperature(self):
        """Returns the physics evaluation system heat context metric floating float point value."""
        return _lib.BrlCombinationTemperature(self._handle)

    def SetTemperature(self, value):
        """Applies an explicit system heat context parameter tracking target value."""
        _lib.BrlCombinationSetTemperature(self._handle, float(value))

    def AddLeaf(self, leaf_name):
        """Appends a primitive geometry identifying token identifier to the active framework tree."""
        _lib.BrlCombinationAddLeaf(self._handle, leaf_name.encode('utf-8'))

    def GetTree(self):
        """Returns a wrapped TreeNode tracking reference holding the CSG root layout context handle."""
        raw_node = _lib.BrlCombinationTree(self._handle)
        return TreeNode(raw_node, owned=True) if raw_node else None

    def ClassName(self):
        """Returns the static C++ class designator identification string."""
        res = _lib.BrlCombinationClassName()
        return res.decode('utf-8') if res else ""


class TreeNode:
    """Encapsulates a managed pointer mapping tracking the heap-allocated Combination::TreeNode value copy frames."""

    def __init__(self, handle, owned=True):
        self._handle = handle
        self._owned = owned

    def __del__(self):
        if getattr(self, '_owned', False) and getattr(self, '_handle', None):
            _lib.BrlDeleteHandle(self._handle)

    def GetOperator(self):
        """Returns the internal BrlCombinationTreeNodeOperator integer to identify node type (Union, Leaf, etc.)."""
        return int(_lib.BrlCombinationTreeNodeOperation(self._handle))

    def GetName(self):
        """Returns the geometry identifier string if the current node is a Leaf."""
        res = _lib.BrlCombinationTreeNodeName(self._handle)
        return res.decode('utf-8') if res else ""

    def SetName(self, name):
        """Updates the geometry identifier string if the current node is a Leaf."""
        _lib.BrlCombinationTreeNodeSetName(self._handle, name.encode('utf-8'))

    def GetLeftOperand(self):
        """Traverses the tracking sub-frame and returns a wrapped left target component reference."""
        raw = _lib.BrlCombinationTreeNodeLeftOperand(self._handle)
        return TreeNode(raw, owned=True) if raw else None

    def GetRightOperand(self):
        """Traverses the tracking sub-frame and returns a wrapped right target component reference."""
        raw = _lib.BrlCombinationTreeNodeRightOperand(self._handle)
        return TreeNode(raw, owned=True) if raw else None

    def GetOperand(self):
        """Traverses the single-target tracking child sub-frame matching unary nodes."""
        raw = _lib.BrlCombinationTreeNodeOperand(self._handle)
        return TreeNode(raw, owned=True) if raw else None

    def GetMatrix(self):
        """Returns the 16-element transformation matrix as a list of floats."""
        raw_ptr = _lib.BrlCombinationTreeNodeMatrix(self._handle)
        if not raw_ptr:
            return None
        return [float(raw_ptr[i]) for i in range(16)]

    def SetMatrix(self, matrix_values_list):
        """Applies a flat array of 16 float double elements transformation layout tracking parameters."""
        if len(matrix_values_list) != 16:
            raise ValueError("BRL-CAD coordinate modification transformations require exactly 16 floating values layouts.")
        c_array = (ctypes.c_double * 16)(*matrix_values_list)
        _lib.BrlCombinationTreeNodeSetMatrix(self._handle, c_array)

    def Apply(self, operator_enum_id):
        """Wraps the structural frame with a new transformation operation modifier layout context."""
        raw = _lib.BrlCombinationTreeNodeApplyUnary(self._handle, int(operator_enum_id))
        return TreeNode(raw, owned=True) if raw else None

    def ApplyWithOther(self, operator_enum_id, other_node_instance):
        """Appends a new operation tracking configuration branch interacting with a separate structural sub-frame node."""
        raw = _lib.BrlCombinationTreeNodeApplyNodeRight(self._handle, int(operator_enum_id), other_node_instance._handle)
        return TreeNode(raw, owned=True) if raw else None

    def ApplyWithLeaf(self, operator_enum_id, leaf_name_string):
        """Appends a new execution path targeting a freshly generated tracking token leaf component string identifier."""
        raw = _lib.BrlCombinationTreeNodeApplyLeafRight(self._handle, int(operator_enum_id), leaf_name_string.encode('utf-8'))
        return TreeNode(raw, owned=True) if raw else None

    def ApplyOtherWith(self, other_node_instance, operator_enum_id):
        """Generates a tracking layout frame placing a separate sub-tree context step first within the new operation frame."""
        raw = _lib.BrlCombinationTreeNodeApplyNodeLeft(self._handle, other_node_instance._handle, int(operator_enum_id))
        return TreeNode(raw, owned=True) if raw else None

    def ApplyLeafWith(self, leaf_name_string, operator_enum_id):
        """Generates a tracking layout placing a raw target tracking leaf component string context first within the branch layout."""
        raw = _lib.BrlCombinationTreeNodeApplyLeafLeft(self._handle, leaf_name_string.encode('utf-8'), int(operator_enum_id))
        return TreeNode(raw, owned=True) if raw else None
