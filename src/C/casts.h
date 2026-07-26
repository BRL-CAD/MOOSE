/*                         C A S T S . H
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
/** @file casts.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares helper functions to cast void* handles to the correct C++ class
 */

#ifndef BRLCAD_C_CASTS_INCLUDED
#define BRLCAD_C_CASTS_INCLUDED

#include <brlcad/C/globals.h>
#include <brlcad/C/object.h>

#include "BrlData.h"


BrlData*                                     CastHandle(BrlHandle handle);

BRLCAD::Vector3D*                            CastVector3D(BrlHandle handle);
BRLCAD::VectorList*                          CastVectorList(BrlHandle handle);

BRLCAD::ConstDatabase*                       CastConstDatabase(BrlHandle handle);
BRLCAD::Database*                            CastDatabase(BrlHandle handle);
BRLCAD::FileDatabase*                        CastFileDatabase(BrlHandle handle);
BRLCAD::MemoryDatabase*                      CastMemoryDatabase(BrlHandle handle);

BRLCAD::Object*                              CastObject(BrlHandle handle);
BRLCAD::Object::AttributeIterator*           CastObjectAttributeIterator(BrlHandle handle);
BrlObject                                    DowncastObject(BRLCAD::Object* object);
BRLCAD::Arb8*                                CastArb8(BrlHandle handle);
BRLCAD::BagOfTriangles*                      CastBagOfTriangles(BrlHandle handle);
BRLCAD::BagOfTriangles::Face*                CastBagOfTrianglesFace(BrlHandle handle);
BRLCAD::Combination*                         CastCombination(BrlHandle handle);
BRLCAD::Combination::TreeNode*               CastCombinationTreeNode(BrlHandle handle);
BRLCAD::Cone*                                CastCone(BrlHandle handle);
BRLCAD::Ellipsoid*                           CastEllipsoid(BrlHandle handle);
BRLCAD::EllipticalTorus*                     CastEllipticalTorus(BrlHandle handle);
BRLCAD::HyperbolicCylinder*                  CastHyperbolicCylinder(BrlHandle handle);
BRLCAD::NonManifoldGeometry*                 CastNonManifoldGeometry(BrlHandle handle);

BRLCAD::NonManifoldGeometry::Vertex*         CastNonManifoldGeometryVertex(BrlHandle handle);
BRLCAD::NonManifoldGeometry::Edge*           CastNonManifoldGeometryEdge(BrlHandle handle);
BRLCAD::NonManifoldGeometry::Loop*           CastNonManifoldGeometryLoop(BrlHandle handle);
BRLCAD::NonManifoldGeometry::Face*           CastNonManifoldGeometryFace(BrlHandle handle);
BRLCAD::NonManifoldGeometry::Shell*          CastNonManifoldGeometryShell(BrlHandle handle);
BRLCAD::NonManifoldGeometry::Region*         CastNonManifoldGeometryRegion(BrlHandle handle);
BRLCAD::NonManifoldGeometry::RegionIterator* CastNonManifoldGeometryRegionIterator(BrlHandle handle);

BRLCAD::Sphere*                              CastSphere(BrlHandle handle);
BRLCAD::Torus*                               CastTorus(BrlHandle handle);


#endif // BRLCAD_C_CASTS_INCLUDED
