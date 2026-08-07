/*                    V E C T O R L I S T . H
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
/** @file vectorList.h
 *
 *  BRL-CAD core simplified C interface:
 *      header for VectorList opaque wrapper
 */


#ifndef BRLCAD_C_VECTORLIST_INCLUDED
#define BRLCAD_C_VECTORLIST_INCLUDED

#include <stdbool.h>

#include <brlcad/C/globals.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef BrlHandle BrlVectorList;
typedef BrlHandle BrlVectorListElement;


BRLCAD_MOOSE_EXPORT BrlVectorList        BrlNewVectorList(void);

BRLCAD_MOOSE_EXPORT bool                 BrlVectorListAppend(BrlVectorList        vlist,
                                                             BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT void                 BrlVectorListClear(BrlVectorList vlist);

BRLCAD_MOOSE_EXPORT int                  BrlVectorListElementType(BrlVectorListElement element);

BRLCAD_MOOSE_EXPORT BrlVectorListElement BrlNewVectorListPointDraw(double x,
                                                                   double y,
                                                                   double z);
BRLCAD_MOOSE_EXPORT BrlVectorListElement BrlNewVectorListPointSize(double size);
BRLCAD_MOOSE_EXPORT BrlVectorListElement BrlNewVectorListLineMove(double x,
                                                                  double y,
                                                                  double z);
BRLCAD_MOOSE_EXPORT BrlVectorListElement BrlNewVectorListLineDraw(double x,
                                                                  double y,
                                                                  double z);
BRLCAD_MOOSE_EXPORT BrlVectorListElement BrlNewVectorListLineWidth(double width);
BRLCAD_MOOSE_EXPORT BrlVectorListElement BrlNewVectorListTriangleStart(double nx,
                                                                       double ny,
                                                                       double nz);
BRLCAD_MOOSE_EXPORT BrlVectorListElement BrlNewVectorListTriangleMove(double x,
                                                                      double y,
                                                                      double z);
BRLCAD_MOOSE_EXPORT BrlVectorListElement BrlNewVectorListTriangleDraw(double x,
                                                                      double y,
                                                                      double z);
BRLCAD_MOOSE_EXPORT BrlVectorListElement BrlNewVectorListTriangleEnd(double x,
                                                                     double y,
                                                                     double z);
BRLCAD_MOOSE_EXPORT BrlVectorListElement BrlNewVectorListTriangleVertexNormal(double nx,
                                                                              double ny,
                                                                              double nz);
BRLCAD_MOOSE_EXPORT BrlVectorListElement BrlNewVectorListPolygonStart(double nx,
                                                                      double ny,
                                                                      double nz);
BRLCAD_MOOSE_EXPORT BrlVectorListElement BrlNewVectorListPolygonMove(double x,
                                                                     double y,
                                                                     double z);
BRLCAD_MOOSE_EXPORT BrlVectorListElement BrlNewVectorListPolygonDraw(double x,
                                                                     double y,
                                                                     double z);
BRLCAD_MOOSE_EXPORT BrlVectorListElement BrlNewVectorListPolygonEnd(double x,
                                                                    double y,
                                                                    double z);
BRLCAD_MOOSE_EXPORT BrlVectorListElement BrlNewVectorListPolygonVertexNormal(double nx,
                                                                             double ny,
                                                                             double nz);
BRLCAD_MOOSE_EXPORT BrlVectorListElement BrlNewVectorListDisplaySpace(double x,
                                                                      double y,
                                                                      double z);
BRLCAD_MOOSE_EXPORT BrlVectorListElement BrlNewVectorListModelSpace(void);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_VECTORLIST_INCLUDED
