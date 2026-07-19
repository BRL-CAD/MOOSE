#                       _ B I N D I N G S . P Y
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
# @file _bindings.py
#
# BRL-CAD core simplified Python interface:
#       includes all the ctypes for Python Interface
#

import ctypes

_lib = ctypes.CDLL("libbrlcad.so")

# Type Aliases
c_void_p = ctypes.c_void_p
c_char_p = ctypes.c_char_p
c_int    = ctypes.c_int
c_double = ctypes.c_double
c_size_t = ctypes.c_size_t
p_double = ctypes.POINTER(ctypes.c_double)

def _bind(func_name, restype, argtypes):
    """Helper to cleanly bind ctypes function signatures."""
    func = getattr(_lib, func_name)
    func.restype = restype
    func.argtypes = argtypes

# -----------------------------------------------------------------------------
# Destructor Lifecycle Binding
# -----------------------------------------------------------------------------
_bind("BrlDeleteHandle",                      None,       [c_void_p])

# -----------------------------------------------------------------------------
# ConstDatabase Function Signatures
# -----------------------------------------------------------------------------
_bind("BrlNewConstDatabase",                  c_void_p,   [])
_bind("BrlConstDatabaseTitle",                c_char_p,   [c_void_p])
_bind("BrlConstDatabasePlot",                 None,       [c_void_p, c_char_p, c_void_p])
_bind("BrlConstDatabaseLoad",                 c_int,      [c_void_p, c_char_p])
_bind("BrlConstDatabaseGet",                  c_void_p,   [c_void_p, c_char_p])
_bind("BrlConstDatabaseFacetize",             c_void_p,   [c_void_p, c_char_p])
_bind("BrlConstDatabaseSelect",               None,       [c_void_p, c_char_p])
_bind("BrlConstDatabaseUnSelectAll",          None,       [c_void_p])
_bind("BrlConstDatabaseSelectionIsEmpty",     c_int,      [c_void_p])
_bind("BrlConstDatabaseBoundingBoxMinima",    None,       [c_void_p, p_double, p_double, p_double])
_bind("BrlConstDatabaseBoundingBoxMaxima",    None,       [c_void_p, p_double, p_double, p_double])
_bind("BrlConstDatabaseFirstTopObject",       c_void_p,   [c_void_p])

# -----------------------------------------------------------------------------
# File Database Function Signatures
# -----------------------------------------------------------------------------
_bind("BrlNewFileDatabase",                   c_void_p,   [])

# -----------------------------------------------------------------------------
# Memory Database Function Signatures
# -----------------------------------------------------------------------------
_bind("BrlNewMemoryDatabase",                 c_void_p,   [])

# -----------------------------------------------------------------------------
# Database Function Signatures
# -----------------------------------------------------------------------------
_bind("BrlDatabaseSetTitle",                  None,       [c_void_p, c_char_p])

# -----------------------------------------------------------------------------
# TopObjectIterator Function Signatures
# -----------------------------------------------------------------------------
_bind("BrlTopObjectIteratorGood",             c_int,      [c_void_p])
_bind("BrlTopObjectIteratorNext",             None,       [c_void_p])
_bind("BrlTopObjectIteratorName",             c_char_p,   [c_void_p])
_bind("BrlDeleteTopObjectIterator",           None,       [c_void_p])

# -----------------------------------------------------------------------------
# Object Function Signatures
# -----------------------------------------------------------------------------
_bind("BrlObjectClone",                       c_void_p,   [c_void_p])
_bind("BrlObjectIsValid",                     c_int,      [c_void_p])
_bind("BrlObjectType",                        c_char_p,   [c_void_p])
_bind("BrlObjectName",                        c_char_p,   [c_void_p])
_bind("BrlObjectSetName",                     None,       [c_void_p, c_char_p])
_bind("BrlObjectHasAttribute",                c_int,      [c_void_p, c_char_p])
_bind("BrlObjectAttribute",                   c_char_p,   [c_void_p, c_char_p])
_bind("BrlObjectSetAttribute",                None,       [c_void_p, c_char_p, c_char_p])
_bind("BrlObjectAddMultiAttribute",           None,       [c_void_p, c_char_p, c_char_p])
_bind("BrlObjectRemoveAttribute",             None,       [c_void_p, c_char_p])
_bind("BrlObjectClearAttributes",             None,       [c_void_p])
_bind("BrlObjectFirstAttribute",              c_void_p,   [c_void_p])
_bind("BrlObjectMultiAttribute",              c_void_p,   [c_void_p, c_char_p])
_bind("BrlObjectAttributeIteratorGood",       c_int,      [c_void_p])
_bind("BrlObjectAttributeIteratorNext",       None,       [c_void_p])
_bind("BrlObjectAttributeIteratorKey",        c_char_p,   [c_void_p])
_bind("BrlObjectAttributeIteratorValue",      c_char_p,   [c_void_p])

# -----------------------------------------------------------------------------
# Arb8 Function Signatures
# -----------------------------------------------------------------------------
_bind("BrlNewArb8",                                 c_void_p,   [])
_bind("BrlNewArb8AsArb4",                           c_void_p,   [c_double] * 12)
_bind("BrlNewArb8AsArb8",                           c_void_p,   [c_double] * 24)
_bind("BrlNewArb8AsRectengularParallelPiped",       c_void_p,   [c_double] * 6)
_bind("BrlArb8ClassName",                           c_char_p,   [])
_bind("BrlArb8NumberOfVertices",                    c_int,      [c_void_p])
_bind("BrlArb8Point",                               c_void_p,   [c_void_p, c_int])
_bind("BrlArb8RawPoint",                            c_void_p,   [c_void_p, c_int])
_bind("BrlArb8SetPoint",                            None,       [c_void_p, c_int, c_double, c_double, c_double])
_bind("BrlArb8SetRawPoint",                         None,       [c_void_p, c_int, c_double, c_double, c_double])
_bind("BrlArb8SetPointsAsArb4",                     None,       [c_void_p] + [c_double] * 12)
_bind("BrlArb8SetPointsAsArb5",                     None,       [c_void_p] + [c_double] * 15)
_bind("BrlArb8SetPointsAsArb6",                     None,       [c_void_p] + [c_double] * 18)
_bind("BrlArb8SetPointsAsArb7",                     None,       [c_void_p] + [c_double] * 21)
_bind("BrlArb8SetPointsAsArb8",                     None,       [c_void_p] + [c_double] * 24)
_bind("BrlArb8SetPointsAsRectengularParallelPiped", None,       [c_void_p] + [c_double] * 6)

# -----------------------------------------------------------------------------
# Ellipsoid Function Signatures
# -----------------------------------------------------------------------------
_bind("BrlNewEllipsoid",                            c_void_p,   [])
_bind("BrlNewEllipsoidAsGeneralEllipsoid",          c_void_p,   [c_double] * 12)
_bind("BrlNewEllipsoidAsEllipsoid1",                c_void_p,   [c_double] * 7)
_bind("BrlNewEllipsoidAsSphere",                    c_void_p,   [c_double] * 4)
_bind("BrlEllipsoidClassName",                      c_char_p,   [])
_bind("BrlEllipsoidCenter",                         c_void_p,   [c_void_p])
_bind("BrlEllipsoidSetCenter",                      None,       [c_void_p, c_double, c_double, c_double])
_bind("BrlEllipsoidSemiPrincipalAxis",              c_void_p,   [c_void_p, c_size_t])
_bind("BrlEllipsoidSetSemiPrincipalAxis",           None,       [c_void_p, c_int, c_double, c_double, c_double])
_bind("BrlEllipsoidSetFocals",                      None,       [c_void_p] + [c_double] * 7)
_bind("BrlEllipsoidSetSphere",                      None,       [c_void_p, c_double, c_double, c_double, c_double])
_bind("BrlEllipsoidSetAsGeneralEllipsoid",          None,       [c_void_p] + [c_double] * 12)
_bind("BrlEllipsoidSetAsEllipsoid1",                None,       [c_void_p] + [c_double] * 7)

# -----------------------------------------------------------------------------
# Sphere Function Signatures
# -----------------------------------------------------------------------------
_bind("BrlNewSphere",                         c_void_p,   [])
_bind("BrlNewSphereAsSphere",                 c_void_p,   [c_double, c_double, c_double, c_double])
_bind("BrlSphereClassName",                   c_char_p,   [])
_bind("BrlSphereRadius",                      c_double,   [c_void_p])
_bind("BrlSphereSetRadius",                   None,       [c_void_p, c_double])
_bind("BrlSphereCenter",                      c_void_p,   [c_void_p])
_bind("BrlSphereSetCenter",                   None,       [c_void_p, c_double, c_double, c_double])
_bind("BrlSphereSet",                         None,       [c_void_p, c_double, c_double, c_double, c_double])

# -----------------------------------------------------------------------------
# Cone Function Signatures
# -----------------------------------------------------------------------------
_bind("BrlNewCone",                                 c_void_p,   [])
_bind("BrlNewConeAsTruncatedGeneralCone",           c_void_p,   [c_double] * 14)
_bind("BrlNewConeAsTruncatedErectedCone",           c_void_p,   [c_double] * 13)
_bind("BrlNewConeAsRightEllipticalCylinder",        c_void_p,   [c_double] * 12)
_bind("BrlNewConeAsTruncatedRightCircularCone",     c_void_p,   [c_double] * 8)
_bind("BrlNewConeAsRightCircularCylinder",          c_void_p,   [c_double] * 7)
_bind("BrlConeClassName",                           c_char_p,   [])
_bind("BrlConeBasePoint",                           c_void_p,   [c_void_p])
_bind("BrlConeSetBasePoint",                        None,       [c_void_p, c_double, c_double, c_double])
_bind("BrlConeHeight",                              c_void_p,   [c_void_p])
_bind("BrlConeSetHeight",                           None,       [c_void_p, c_double, c_double, c_double])
_bind("BrlConeSemiPrincipalAxis",                   c_void_p,   [c_void_p, c_int])
_bind("BrlConeSetSemiPrincipalAxis",                None,       [c_void_p, c_int, c_double, c_double, c_double])
_bind("BrlConeSetAsTruncatedGeneralCone",           None,       [c_void_p] + [c_double] * 14)
_bind("BrlConeSetAsTruncatedErectedCone",           None,       [c_void_p] + [c_double] * 13)
_bind("BrlConeSetAsRightEllipticalCylinder",        None,       [c_void_p] + [c_double] * 12)
_bind("BrlConeSetAsTruncatedRightCircularCone",     None,       [c_void_p] + [c_double] * 8)
_bind("BrlConeSetAsRightCircularCylinder",          None,       [c_void_p] + [c_double] * 7)

# -----------------------------------------------------------------------------
# VectorList Function Signatures
# -----------------------------------------------------------------------------
_bind("BrlNewVectorList",                     c_void_p,   [])
_bind("BrlVectorListClear",                   None,       [c_void_p])

# -----------------------------------------------------------------------------
# Combinations Function Signatures
# -----------------------------------------------------------------------------
_bind("BrlNewCombination",                    c_void_p,   [])
_bind("BrlCombinationClassName",              c_char_p,   [])
_bind("BrlCombinationIsRegion",               c_int,      [c_void_p])
_bind("BrlCombinationSetIsRegion",            None,       [c_void_p, c_int])
_bind("BrlCombinationFastgenRegion",          c_int,      [c_void_p])
_bind("BrlCombinationSetFastgenRegion",       None,       [c_void_p, c_int])
_bind("BrlCombinationRegionId",               c_int,      [c_void_p])
_bind("BrlCombinationSetRegionId",            None,       [c_void_p, c_int])
_bind("BrlCombinationAircode",                c_int,      [c_void_p])
_bind("BrlCombinationSetAircode",             None,       [c_void_p, c_int])
_bind("BrlCombinationGiftMaterial",           c_int,      [c_void_p])
_bind("BrlCombinationSetGiftMaterial",        None,       [c_void_p, c_int])
_bind("BrlCombinationLineOfSight",            c_int,      [c_void_p])
_bind("BrlCombinationSetLineOfSight",         None,       [c_void_p, c_int])
_bind("BrlCombinationHasColor",               c_int,      [c_void_p])
_bind("BrlCombinationSetHasColor",            None,       [c_void_p, c_int])
_bind("BrlCombinationRed",                    c_double,   [c_void_p])
_bind("BrlCombinationSetRed",                 None,       [c_void_p, c_double])
_bind("BrlCombinationGreen",                  c_double,   [c_void_p])
_bind("BrlCombinationSetGreen",               None,       [c_void_p, c_double])
_bind("BrlCombinationBlue",                   c_double,   [c_void_p])
_bind("BrlCombinationSetBlue",                None,       [c_void_p, c_double])
_bind("BrlCombinationShader",                 c_char_p,   [c_void_p])
_bind("BrlCombinationSetShader",              None,       [c_void_p, c_char_p])
_bind("BrlCombinationInherit",                c_int,      [c_void_p])
_bind("BrlCombinationSetInherit",             None,       [c_void_p, c_int])
_bind("BrlCombinationMaterial",               c_char_p,   [c_void_p])
_bind("BrlCombinationSetMaterial",            None,       [c_void_p, c_char_p])
_bind("BrlCombinationTemperature",            c_double,   [c_void_p])
_bind("BrlCombinationSetTemperature",         None,       [c_void_p, c_double])
_bind("BrlCombinationTree",                   c_void_p,   [c_void_p])
_bind("BrlCombinationAddLeaf",                None,       [c_void_p, c_char_p])

# -----------------------------------------------------------------------------
# Combination::TreeNode Function Signatures
# -----------------------------------------------------------------------------
_bind("BrlCombinationTreeNodeName",           c_char_p,   [c_void_p])
_bind("BrlCombinationTreeNodeSetName",        None,       [c_void_p, c_char_p])
_bind("BrlCombinationTreeNodeOperation",      c_int,      [c_void_p])
_bind("BrlCombinationTreeNodeMatrix",         p_double,   [c_void_p])
_bind("BrlCombinationTreeNodeSetMatrix",      None,       [c_void_p, p_double])
_bind("BrlCombinationTreeNodeLeftOperand",    c_void_p,   [c_void_p])
_bind("BrlCombinationTreeNodeRightOperand",   c_void_p,   [c_void_p])
_bind("BrlCombinationTreeNodeOperand",        c_void_p,   [c_void_p])
_bind("BrlCombinationTreeNodeApplyUnary",     c_void_p,   [c_void_p, c_int])
_bind("BrlCombinationTreeNodeApplyNodeRight", c_void_p,   [c_void_p, c_int, c_void_p])
_bind("BrlCombinationTreeNodeApplyLeafRight", c_void_p,   [c_void_p, c_int, c_char_p])
_bind("BrlCombinationTreeNodeApplyNodeLeft",  c_void_p,   [c_void_p, c_void_p, c_int])
_bind("BrlCombinationTreeNodeApplyLeafLeft",  c_void_p,   [c_void_p, c_char_p, c_int])
_bind("BrlCombinationTreeNodeDelete",         None,       [c_void_p])

# -----------------------------------------------------------------------------
# BagOfTriangles Function Signatures
# -----------------------------------------------------------------------------
_bind("BrlNewBagOfTriangles",                 c_void_p,   [])
_bind("BrlBagOfTrianglesClassName",           c_char_p,   [])
_bind("BrlBagOfTrianglesMode",                c_int,      [c_void_p])
_bind("BrlBagOfTrianglesSetMode",             None,       [c_void_p, c_int])
_bind("BrlBagOfTrianglesOrientation",         c_int,      [c_void_p])
_bind("BrlBagOfTrianglesSetOrientation",      None,       [c_void_p, c_int])
_bind("BrlBagOfTrianglesFacesHaveNormals",    c_int,      [c_void_p])
_bind("BrlBagOfTrianglesSetFacesHaveNormals", None,       [c_void_p, c_int])
_bind("BrlBagOfTrianglesUseFaceNormals",      c_int,      [c_void_p])
_bind("BrlBagOfTrianglesSetUseFaceNormals",   None,       [c_void_p, c_int])
_bind("BrlBagOfTrianglesUseFloats",           c_int,      [c_void_p])
_bind("BrlBagOfTrianglesSetUseFloats",        None,       [c_void_p, c_int])
_bind("BrlBagOfTrianglesNumberOfFaces",       c_int,      [c_void_p])
_bind("BrlBagOfTrianglesAddFace",             c_void_p,   [c_void_p] + [c_double] * 9)
_bind("BrlBagOfTrianglesGetFace",             c_void_p,   [c_void_p, c_int])
_bind("BrlBagOfTrianglesDeleteFace",          None,       [c_void_p, c_int])

# Changed: Returns an opaque BrlVector3D data pointer (ctypes.c_void_p) and takes no out-pointers
_bind("BrlBagOfTrianglesFacePoint",           c_void_p,   [c_void_p, c_int])
_bind("BrlBagOfTrianglesFaceNormal",          c_void_p,   [c_void_p, c_int])

# -----------------------------------------------------------------------------
# BagOfTriangles::Face (Inner Class) Function Signatures
# -----------------------------------------------------------------------------
_bind("BrlBagOfTrianglesFaceSetPoint",          None,     [c_void_p, c_int, c_double, c_double, c_double])
_bind("BrlBagOfTrianglesFaceSetPoints",         None,     [c_void_p] + [c_double] * 9)
_bind("BrlBagOfTrianglesFaceThickness",         c_double, [c_void_p])
_bind("BrlBagOfTrianglesFaceSetThickness",      None,     [c_void_p, c_double])
_bind("BrlBagOfTrianglesFaceApendThickness",    c_int,    [c_void_p])
_bind("BrlBagOfTrianglesFaceSetApendThickness", None,     [c_void_p, c_int])
_bind("BrlBagOfTrianglesFaceSetNormal",         None,     [c_void_p, c_int, c_double, c_double, c_double])
_bind("BrlBagOfTrianglesFaceSetNormals",        None,     [c_void_p] + [c_double] * 9)

