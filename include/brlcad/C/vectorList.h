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
 *      declares a handle and functions for VectorList reading
 */


#ifndef BRLCAD_C_VECTORLIST_INCLUDED
#define BRLCAD_C_VECTORLIST_INCLUDED

#include <brlcad/C/globals.h>
#include <brlcad/C/vector.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef BrlHandle BrlVectorList;


BRLCAD_MOOSE_EXPORT BrlVectorList                     BrlNewVectorList(void);


typedef BrlHandle BrlVectorListElement;

typedef enum BrlVectorListElementElementType {
    BrlVectorListElementElementTypePointDraw,
    BrlVectorListElementElementTypePointSize,
    BrlVectorListElementElementTypeLineMove,
    BrlVectorListElementElementTypeLineDraw,
    BrlVectorListElementElementTypeLineWidth,
    BrlVectorListElementElementTypeTriangleStart,
    BrlVectorListElementElementTypeTriangleMove,
    BrlVectorListElementElementTypeTriangleDraw,
    BrlVectorListElementElementTypeTriangleEnd,
    BrlVectorListElementElementTypeTriangleVertexNormal,
    BrlVectorListElementElementTypePolygonStart,
    BrlVectorListElementElementTypePolygonMove,
    BrlVectorListElementElementTypePolygonDraw,
    BrlVectorListElementElementTypePolygonEnd,
    BrlVectorListElementElementTypePolygonVertexNormal,
    BrlVectorListElementElementTypeDisplaySpace,
    BrlVectorListElementElementTypeModelSpace
} BrlVectorListElementElementType;


BRLCAD_MOOSE_EXPORT BrlVectorListElementElementType   BrlVectorListElementType(BrlVectorListElement element);


typedef BrlVectorListElement BrlVectorListPointDraw;

BRLCAD_MOOSE_EXPORT BrlVectorListPointDraw            BrlNewVectorListPointDraw(void);
BRLCAD_MOOSE_EXPORT BrlVectorListPointDraw            BrlNewVectorListPointDrawAsPoint(double x, double y, double z);

BRLCAD_MOOSE_EXPORT BrlVector3D                       BrlVectorListPointDrawPoint(BrlVectorListPointDraw pointDraw);
BRLCAD_MOOSE_EXPORT void                              BrlVectorListPointDrawSetPoint(BrlVectorListPointDraw pointDraw,
                                                                                     double                 x, double y, double z);


typedef BrlVectorListElement BrlVectorListPointSize;

BRLCAD_MOOSE_EXPORT BrlVectorListPointSize            BrlNewVectorListPointSize(void);
BRLCAD_MOOSE_EXPORT BrlVectorListPointSize            BrlNewVectorListPointSizeAsSize(double size);

BRLCAD_MOOSE_EXPORT double                            BrlVectorListPointSizeSize(BrlVectorListPointSize pointSize);
BRLCAD_MOOSE_EXPORT void                              BrlVectorListPointSizeSetSize(BrlVectorListPointSize pointSize,
                                                                                    double                 size);


typedef BrlVectorListElement BrlVectorListLineMove;

BRLCAD_MOOSE_EXPORT BrlVectorListLineMove             BrlNewVectorListLineMove(void);
BRLCAD_MOOSE_EXPORT BrlVectorListLineMove             BrlNewVectorListLineMoveAsPoint(double x, double y, double z);

BRLCAD_MOOSE_EXPORT BrlVector3D                       BrlVectorListLineMovePoint(BrlVectorListLineMove lineMove);
BRLCAD_MOOSE_EXPORT void                              BrlVectorListLineMoveSetPoint(BrlVectorListLineMove lineMove,
                                                                                    double                x, double y, double z);


typedef BrlVectorListElement BrlVectorListLineDraw;

BRLCAD_MOOSE_EXPORT BrlVectorListLineDraw             BrlNewVectorListLineDraw(void);
BRLCAD_MOOSE_EXPORT BrlVectorListLineDraw             BrlNewVectorListLineDrawAsPoint(double x, double y, double z);

BRLCAD_MOOSE_EXPORT BrlVector3D                       BrlVectorListLineDrawPoint(BrlVectorListLineDraw lineDraw);
BRLCAD_MOOSE_EXPORT void                              BrlVectorListLineDrawSetPoint(BrlVectorListLineDraw lineDraw,
                                                                                    double                x, double y, double z);


typedef BrlVectorListElement BrlVectorListLineWidth;

BRLCAD_MOOSE_EXPORT BrlVectorListLineWidth            BrlNewVectorListLineWidth(void);
BRLCAD_MOOSE_EXPORT BrlVectorListLineWidth            BrlNewVectorListLineWidthAsWidth(double width);

BRLCAD_MOOSE_EXPORT double                            BrlVectorListLineWidthWidth(BrlVectorListLineWidth lineWidth);
BRLCAD_MOOSE_EXPORT void                              BrlVectorListLineWidthSetWidth(BrlVectorListLineWidth lineWidth,
                                                                                     double                 width);


typedef BrlVectorListElement BrlVectorListTriangleStart;

BRLCAD_MOOSE_EXPORT BrlVectorListTriangleStart        BrlNewVectorListTriangleStart(void);
BRLCAD_MOOSE_EXPORT BrlVectorListTriangleStart        BrlNewVectorListTriangleStartAsNormal(double x, double y, double z);

BRLCAD_MOOSE_EXPORT BrlVector3D                       BrlVectorListTriangleStartNormal(BrlVectorListTriangleStart triangleStart);
BRLCAD_MOOSE_EXPORT void                              BrlVectorListTriangleStartSetNormal(BrlVectorListTriangleStart triangleStart,
                                                                                          double                     x, double y, double z);


typedef BrlVectorListElement BrlVectorListTriangleMove;

BRLCAD_MOOSE_EXPORT BrlVectorListTriangleMove         BrlNewVectorListTriangleMove(void);
BRLCAD_MOOSE_EXPORT BrlVectorListTriangleMove         BrlNewVectorListTriangleMoveAsPoint(double x, double y, double z);

BRLCAD_MOOSE_EXPORT BrlVector3D                       BrlVectorListTriangleMovePoint(BrlVectorListTriangleMove triangleMove);
BRLCAD_MOOSE_EXPORT void                              BrlVectorListTriangleMoveSetPoint(BrlVectorListTriangleMove triangleMove,
                                                                                        double                    x, double y, double z);


typedef BrlVectorListElement BrlVectorListTriangleDraw;

BRLCAD_MOOSE_EXPORT BrlVectorListTriangleDraw         BrlNewVectorListTriangleDraw(void);
BRLCAD_MOOSE_EXPORT BrlVectorListTriangleDraw         BrlNewVectorListTriangleDrawAsPoint(double x, double y, double z);

BRLCAD_MOOSE_EXPORT BrlVector3D                       BrlVectorListTriangleDrawPoint(BrlVectorListTriangleDraw triangleDraw);
BRLCAD_MOOSE_EXPORT void                              BrlVectorListTriangleDrawSetPoint(BrlVectorListTriangleDraw triangleDraw,
                                                                                        double                    x, double y, double z);


typedef BrlVectorListElement BrlVectorListTriangleEnd;

BRLCAD_MOOSE_EXPORT BrlVectorListTriangleEnd          BrlNewVectorListTriangleEnd(void);
BRLCAD_MOOSE_EXPORT BrlVectorListTriangleEnd          BrlNewVectorListTriangleEndAsPoint(double x, double y, double z);

BRLCAD_MOOSE_EXPORT BrlVector3D                       BrlVectorListTriangleEndPoint(BrlVectorListTriangleEnd triangleEnd);
BRLCAD_MOOSE_EXPORT void                              BrlVectorListTriangleEndSetPoint(BrlVectorListTriangleEnd triangleEnd,
                                                                                       double                   x, double y, double z);


typedef BrlVectorListElement BrlVectorListTriangleVertexNormal;

BRLCAD_MOOSE_EXPORT BrlVectorListTriangleVertexNormal BrlNewVectorListTriangleVertexNormal(void);
BRLCAD_MOOSE_EXPORT BrlVectorListTriangleVertexNormal BrlNewVectorListTriangleVertexNormalAsNormal(double x, double y, double z);

BRLCAD_MOOSE_EXPORT BrlVector3D                       BrlVectorListTriangleVertexNormalNormal(BrlVectorListTriangleVertexNormal triangleVertexNormal);
BRLCAD_MOOSE_EXPORT void                              BrlVectorListTriangleVertexNormalSetNormal(BrlVectorListTriangleVertexNormal triangleVertexNormal,
                                                                                                 double                            x, double y, double z);


typedef BrlVectorListElement BrlVectorListPolygonStart;

BRLCAD_MOOSE_EXPORT BrlVectorListPolygonStart         BrlNewVectorListPolygonStart(void);
BRLCAD_MOOSE_EXPORT BrlVectorListPolygonStart         BrlNewVectorListPolygonStartAsNormal(double x, double y, double z);

BRLCAD_MOOSE_EXPORT BrlVector3D                       BrlVectorListPolygonStartNormal(BrlVectorListPolygonStart polygonStart);
BRLCAD_MOOSE_EXPORT void                              BrlVectorListPolygonStartSetNormal(BrlVectorListPolygonStart polygonStart,
                                                                                         double                    x, double y, double z);


typedef BrlVectorListElement BrlVectorListPolygonMove;

BRLCAD_MOOSE_EXPORT BrlVectorListPolygonMove          BrlNewVectorListPolygonMove(void);
BRLCAD_MOOSE_EXPORT BrlVectorListPolygonMove          BrlNewVectorListPolygonMoveAsPoint(double x, double y, double z);

BRLCAD_MOOSE_EXPORT BrlVector3D                       BrlVectorListPolygonMovePoint(BrlVectorListPolygonMove polygonMove);
BRLCAD_MOOSE_EXPORT void                              BrlVectorListPolygonMoveSetPoint(BrlVectorListPolygonMove polygonMove,
                                                                                       double                   x, double y, double z);


typedef BrlVectorListElement BrlVectorListPolygonDraw;

BRLCAD_MOOSE_EXPORT BrlVectorListPolygonDraw          BrlNewVectorListPolygonDraw(void);
BRLCAD_MOOSE_EXPORT BrlVectorListPolygonDraw          BrlNewVectorListPolygonDrawAsPoint(double x, double y, double z);

BRLCAD_MOOSE_EXPORT BrlVector3D                       BrlVectorListPolygonDrawPoint(BrlVectorListPolygonDraw polygonDraw);
BRLCAD_MOOSE_EXPORT void                              BrlVectorListPolygonDrawSetPoint(BrlVectorListPolygonDraw polygonDraw,
                                                                                       double                   x, double y, double z);


typedef BrlVectorListElement BrlVectorListPolygonEnd;

BRLCAD_MOOSE_EXPORT BrlVectorListPolygonEnd           BrlNewVectorListPolygonEnd(void);
BRLCAD_MOOSE_EXPORT BrlVectorListPolygonEnd           BrlNewVectorListPolygonEndAsPoint(double x, double y, double z);

BRLCAD_MOOSE_EXPORT BrlVector3D                       BrlVectorListPolygonEndPoint(BrlVectorListPolygonEnd polygonEnd);
BRLCAD_MOOSE_EXPORT void                              BrlVectorListPolygonEndSetPoint(BrlVectorListPolygonEnd polygonEnd,
                                                                                      double                  x, double y, double z);


typedef BrlVectorListElement BrlVectorListPolygonVertexNormal;

BRLCAD_MOOSE_EXPORT BrlVectorListPolygonVertexNormal  BrlNewVectorListPolygonVertexNormal(void);
BRLCAD_MOOSE_EXPORT BrlVectorListPolygonVertexNormal  BrlNewVectorListPolygonVertexNormalAsNormal(double x, double y, double z);

BRLCAD_MOOSE_EXPORT BrlVector3D                       BrlVectorListPolygonVertexNormalNormal(BrlVectorListPolygonVertexNormal polygonVertexNormal);
BRLCAD_MOOSE_EXPORT void                              BrlVectorListPolygonVertexNormalSetNormal(BrlVectorListPolygonVertexNormal polygonVertexNormal,
                                                                                                double                           x, double y, double z);


typedef BrlVectorListElement BrlVectorListDisplaySpace;

BRLCAD_MOOSE_EXPORT BrlVectorListDisplaySpace         BrlNewVectorListDisplaySpace(void);
BRLCAD_MOOSE_EXPORT BrlVectorListDisplaySpace         BrlNewVectorListDisplaySpaceAsReferencePoint(double x, double y, double z);

BRLCAD_MOOSE_EXPORT BrlVector3D                       BrlVectorListDisplaySpaceReferencePoint(BrlVectorListDisplaySpace displaySpace);
BRLCAD_MOOSE_EXPORT void                              BrlVectorListDisplaySpaceSetReferencePoint(BrlVectorListDisplaySpace displaySpace,
                                                                                                 double                    x, double y, double z);


typedef BrlVectorListElement BrlVectorListModelSpace;

BRLCAD_MOOSE_EXPORT BrlVectorListModelSpace           BrlNewVectorListModelSpace(void);


typedef int (*BrlVectorListCallback)(BrlVectorListElement element,
                                     void*                userdata);

BRLCAD_MOOSE_EXPORT void                              BrlVectorListIterate(BrlVectorList         vlist,
                                                                           BrlVectorListCallback callback,
                                                                           void*                 userdata);

BRLCAD_MOOSE_EXPORT int                               BrlVectorListAppend(BrlVectorList        vlist,
                                                                          BrlVectorListElement element);
BRLCAD_MOOSE_EXPORT void                              BrlVectorListClear(BrlVectorList vlist);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_VECTORLIST_INCLUDED
