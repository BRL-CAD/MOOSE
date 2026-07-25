/*                  N O N M A N I F O L D G E O M E T R Y . H
 * BRL-CAD
 *
 * Copyright (c) 2026 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this file; see the file named COPYING for more
 * information.
 */
/** @file nonManifoldGeometry.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      declares a handle type for a non-manifold geometry mesh
 */

#ifndef BRLCAD_C_NONMANIFOLDGEOMETRY_INCLUDED
#define BRLCAD_C_NONMANIFOLDGEOMETRY_INCLUDED

#include <brlcad/C/object.h>
#include <brlcad/C/vector.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef BrlObject BrlNonManifoldGeometry;

typedef BrlHandle BrlNonManifoldGeometryVertex;
typedef BrlHandle BrlNonManifoldGeometryEdge;
typedef BrlHandle BrlNonManifoldGeometryLoop;
typedef BrlHandle BrlNonManifoldGeometryFace;
typedef BrlHandle BrlNonManifoldGeometryShell;
typedef BrlHandle BrlNonManifoldGeometryRegion;
typedef BrlHandle BrlNonManifoldGeometryRegionIterator;


BRLCAD_MOOSE_EXPORT BrlNonManifoldGeometry BrlNewNonManifoldGeometry(void);

BRLCAD_MOOSE_EXPORT BrlNonManifoldGeometryRegionIterator BrlNonManifoldGeometryRegions(BrlNonManifoldGeometry nonManifoldGeometry);
BRLCAD_MOOSE_EXPORT void                   BrlNonManifoldGeometryTriangulate(BrlNonManifoldGeometry nonManifoldGeometry);
BRLCAD_MOOSE_EXPORT void                   BrlNonManifoldGeometryTriangulateShell(BrlNonManifoldGeometry nonManifoldGeometry, BrlNonManifoldGeometryShell shell);
BRLCAD_MOOSE_EXPORT void                   BrlNonManifoldGeometryTriangulateFace(BrlNonManifoldGeometry nonManifoldGeometry, BrlNonManifoldGeometryFace face);

BRLCAD_MOOSE_EXPORT const char*            BrlNonManifoldGeometryClassName(void);


BRLCAD_MOOSE_EXPORT void BrlNonManifoldGeometryRegionIteratorGotoFirstRegion(BrlNonManifoldGeometryRegionIterator iterator);
BRLCAD_MOOSE_EXPORT BrlNonManifoldGeometryRegionIterator BrlNonManifoldGeometryRegionIteratorNextRegion(BrlNonManifoldGeometryRegionIterator iterator);
BRLCAD_MOOSE_EXPORT BrlNonManifoldGeometryRegion BrlNonManifoldGeometryRegionIteratorCurrentRegion(BrlNonManifoldGeometryRegionIterator iterator);

BRLCAD_MOOSE_EXPORT void BrlNonManifoldGeometryRegionGotoFirstShell(BrlNonManifoldGeometryRegion region);
BRLCAD_MOOSE_EXPORT BrlNonManifoldGeometryRegion BrlNonManifoldGeometryRegionNextShell(BrlNonManifoldGeometryRegion region);
BRLCAD_MOOSE_EXPORT BrlNonManifoldGeometryShell BrlNonManifoldGeometryRegionCurrentShell(BrlNonManifoldGeometryRegion region);

BRLCAD_MOOSE_EXPORT void BrlNonManifoldGeometryShellGotoFirstFace(BrlNonManifoldGeometryShell shell);
BRLCAD_MOOSE_EXPORT BrlNonManifoldGeometryShell BrlNonManifoldGeometryShellNextFace(BrlNonManifoldGeometryShell shell);
BRLCAD_MOOSE_EXPORT BrlNonManifoldGeometryFace BrlNonManifoldGeometryShellCurrentFace(BrlNonManifoldGeometryShell shell);

BRLCAD_MOOSE_EXPORT void BrlNonManifoldGeometryShellGotoFirstLoop(BrlNonManifoldGeometryShell shell);
BRLCAD_MOOSE_EXPORT BrlNonManifoldGeometryShell BrlNonManifoldGeometryShellNextLoop(BrlNonManifoldGeometryShell shell);
BRLCAD_MOOSE_EXPORT BrlNonManifoldGeometryLoop BrlNonManifoldGeometryShellCurrentLoop(BrlNonManifoldGeometryShell shell);

BRLCAD_MOOSE_EXPORT void BrlNonManifoldGeometryShellGotoFirstEdge(BrlNonManifoldGeometryShell shell);
BRLCAD_MOOSE_EXPORT BrlNonManifoldGeometryShell BrlNonManifoldGeometryShellNextEdge(BrlNonManifoldGeometryShell shell);
BRLCAD_MOOSE_EXPORT BrlNonManifoldGeometryEdge BrlNonManifoldGeometryShellCurrentEdge(BrlNonManifoldGeometryShell shell);

BRLCAD_MOOSE_EXPORT void BrlNonManifoldGeometryShellGotoFirstVertex(BrlNonManifoldGeometryShell shell);
BRLCAD_MOOSE_EXPORT BrlNonManifoldGeometryShell BrlNonManifoldGeometryShellNextVertex(BrlNonManifoldGeometryShell shell);
BRLCAD_MOOSE_EXPORT BrlNonManifoldGeometryVertex BrlNonManifoldGeometryShellCurrentVertex(BrlNonManifoldGeometryShell shell);

BRLCAD_MOOSE_EXPORT void BrlNonManifoldGeometryFaceGotoFirstLoop(BrlNonManifoldGeometryFace face);
BRLCAD_MOOSE_EXPORT BrlNonManifoldGeometryFace BrlNonManifoldGeometryFaceNextLoop(BrlNonManifoldGeometryFace face);
BRLCAD_MOOSE_EXPORT BrlNonManifoldGeometryLoop BrlNonManifoldGeometryFaceCurrentLoop(BrlNonManifoldGeometryFace face);

BRLCAD_MOOSE_EXPORT int BrlNonManifoldGeometryLoopIsHole(BrlNonManifoldGeometryLoop loop);
BRLCAD_MOOSE_EXPORT void BrlNonManifoldGeometryLoopGotoFirstEdge(BrlNonManifoldGeometryLoop loop);
BRLCAD_MOOSE_EXPORT BrlNonManifoldGeometryLoop BrlNonManifoldGeometryLoopNextEdge(BrlNonManifoldGeometryLoop loop);
BRLCAD_MOOSE_EXPORT BrlNonManifoldGeometryEdge BrlNonManifoldGeometryLoopCurrentEdge(BrlNonManifoldGeometryLoop loop);

BRLCAD_MOOSE_EXPORT BrlNonManifoldGeometryVertex BrlNonManifoldGeometryEdgeForwardVertex(BrlNonManifoldGeometryEdge edge);
BRLCAD_MOOSE_EXPORT BrlNonManifoldGeometryVertex BrlNonManifoldGeometryEdgeBackwardVertex(BrlNonManifoldGeometryEdge edge);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlNonManifoldGeometryVertexPoint(BrlNonManifoldGeometryVertex vertex);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_NONMANIFOLDGEOMETRY_INCLUDED
