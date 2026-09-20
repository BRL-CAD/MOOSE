/*                      S K E T C H . H
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
/** @file sketch.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares a handle and functions for Sketch solid handling
 */

#ifndef BRLCAD_C_SKETCH_INCLUDED
#define BRLCAD_C_SKETCH_INCLUDED

#include <brlcad/C/object.h>
#include <brlcad/C/vector.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef BrlObject BrlSketch;


BRLCAD_MOOSE_EXPORT BrlSketch                        BrlNewSketch(void);


typedef BrlHandle BrlSketchSegment;

enum BrlSketchSegmentSegmentType {
    BrlSketchSegmentSegmentTypeNull,
    BrlSketchSegmentSegmentTypeLine,
    BrlSketchSegmentSegmentTypeCircularArc,
    BrlSketchSegmentSegmentTypeNurb,
    BrlSketchSegmentSegmentTypeBezier
};


BRLCAD_MOOSE_EXPORT enum BrlSketchSegmentSegmentType BrlSketchSegmentType(BrlSketchSegment segment);
BRLCAD_MOOSE_EXPORT BrlSketchSegment                 BrlSketchSegmentClone(BrlSketchSegment segment);

BRLCAD_MOOSE_EXPORT BrlVector2D                      BrlSketchSegmentStartPoint(BrlSketchSegment segment);
BRLCAD_MOOSE_EXPORT void                             BrlSketchSegmentSetStartPoint(BrlSketchSegment segment,
                                                                                   double           x, double y);
BRLCAD_MOOSE_EXPORT BrlVector2D                      BrlSketchSegmentEndPoint(BrlSketchSegment segment);
BRLCAD_MOOSE_EXPORT void                             BrlSketchSegmentSetEndPoint(BrlSketchSegment segment,
                                                                                 double           x, double y);

BRLCAD_MOOSE_EXPORT int                              BrlSketchSegmentReverse(BrlSketchSegment segment);
BRLCAD_MOOSE_EXPORT void                             BrlSketchSegmentSetReverse(BrlSketchSegment segment,
                                                                                int              reverse);


typedef BrlSketchSegment BrlSketchLine;
typedef BrlSketchSegment BrlSketchCircularArc;


BRLCAD_MOOSE_EXPORT BrlVector2D                      BrlSketchCircularArcCenter(BrlSketchCircularArc arc);
BRLCAD_MOOSE_EXPORT void                             BrlSketchCircularArcSetCenter(BrlSketchCircularArc arc,
                                                                                   double               x, double y);
BRLCAD_MOOSE_EXPORT double                           BrlSketchCircularArcRadius(BrlSketchCircularArc arc);
BRLCAD_MOOSE_EXPORT void                             BrlSketchCircularArcSetRadius(BrlSketchCircularArc arc,
                                                                                   double               radius);
BRLCAD_MOOSE_EXPORT int                              BrlSketchCircularArcCenterIsLeft(BrlSketchCircularArc arc);
BRLCAD_MOOSE_EXPORT void                             BrlSketchCircularArcSetCenterIsLeft(BrlSketchCircularArc arc,
                                                                                         int                  isLeft);
BRLCAD_MOOSE_EXPORT int                              BrlSketchCircularArcClockwiseOriented(BrlSketchCircularArc arc);
BRLCAD_MOOSE_EXPORT void                             BrlSketchCircularArcSetClockwiseOriented(BrlSketchCircularArc arc,
                                                                                              int                  clockwise);


typedef BrlSketchSegment BrlSketchNurb;


BRLCAD_MOOSE_EXPORT int                              BrlSketchNurbOrder(BrlSketchNurb nurb);
BRLCAD_MOOSE_EXPORT int                              BrlSketchNurbIsRational(BrlSketchNurb nurb);
BRLCAD_MOOSE_EXPORT int                              BrlSketchNurbNumberOfKnots(BrlSketchNurb nurb);
BRLCAD_MOOSE_EXPORT double                           BrlSketchNurbKnot(BrlSketchNurb nurb,
                                                                       int           index);
BRLCAD_MOOSE_EXPORT int                              BrlSketchNurbNumberOfControlPoints(BrlSketchNurb nurb);
BRLCAD_MOOSE_EXPORT BrlVector2D                      BrlSketchNurbControlPoint(BrlSketchNurb nurb,
                                                                               int           index);
BRLCAD_MOOSE_EXPORT double                           BrlSketchNurbControlPointWeight(BrlSketchNurb nurb,
                                                                                     int           index);

BRLCAD_MOOSE_EXPORT void                             BrlSketchNurbSetOrder(BrlSketchNurb nurb,
                                                                           int           order);
BRLCAD_MOOSE_EXPORT void                             BrlSketchNurbAddKnot(BrlSketchNurb nurb,
                                                                          double        knot);
BRLCAD_MOOSE_EXPORT void                             BrlSketchNurbAddControlPoint(BrlSketchNurb nurb,
                                                                                  double        x, double y);
BRLCAD_MOOSE_EXPORT void                             BrlSketchNurbAddControlPointWeight(BrlSketchNurb nurb,
                                                                                        double        x, double y,
                                                                                        double        weight);


typedef BrlSketchSegment BrlSketchBezier;


BRLCAD_MOOSE_EXPORT int                              BrlSketchBezierDegree(BrlSketchBezier bezier);
BRLCAD_MOOSE_EXPORT BrlVector2D                      BrlSketchBezierControlPoint(BrlSketchBezier bezier,
                                                                                 int             index);
BRLCAD_MOOSE_EXPORT void                             BrlSketchBezierAddControlPoint(BrlSketchBezier bezier,
                                                                                    double          x, double y);


BRLCAD_MOOSE_EXPORT int                              BrlSketchNumberOfSegments(BrlSketch sketch);

BRLCAD_MOOSE_EXPORT BrlSketchSegment                 BrlSketchGetSegment(BrlSketch sketch,
                                                                         int       index);

BRLCAD_MOOSE_EXPORT BrlSketchLine                    BrlSketchAppendLine(BrlSketch sketch);
BRLCAD_MOOSE_EXPORT BrlSketchLine                    BrlSketchInsertLine(BrlSketch sketch,
                                                                         int       index);
BRLCAD_MOOSE_EXPORT BrlSketchCircularArc             BrlSketchAppendArc(BrlSketch sketch);
BRLCAD_MOOSE_EXPORT BrlSketchCircularArc             BrlSketchInsertArc(BrlSketch sketch,
                                                                        int       index);
BRLCAD_MOOSE_EXPORT BrlSketchNurb                    BrlSketchAppendNurb(BrlSketch sketch);
BRLCAD_MOOSE_EXPORT BrlSketchNurb                    BrlSketchInsertNurb(BrlSketch sketch,
                                                                         int       index);
BRLCAD_MOOSE_EXPORT BrlSketchBezier                  BrlSketchAppendBezier(BrlSketch sketch);
BRLCAD_MOOSE_EXPORT BrlSketchBezier                  BrlSketchInsertBezier(BrlSketch sketch,
                                                                           int       index);

BRLCAD_MOOSE_EXPORT void                             BrlSketchDeleteSegment(BrlSketch sketch,
                                                                            int       index);

BRLCAD_MOOSE_EXPORT BrlVector3D                      BrlSketchEmbeddingPlaneX(BrlSketch sketch);
BRLCAD_MOOSE_EXPORT BrlVector3D                      BrlSketchEmbeddingPlaneY(BrlSketch sketch);
BRLCAD_MOOSE_EXPORT void                             BrlSketchSetEmbeddingPlaneX(BrlSketch sketch,
                                                                                 double    x, double y, double z);
BRLCAD_MOOSE_EXPORT void                             BrlSketchSetEmbeddingPlaneY(BrlSketch sketch,
                                                                                 double    x, double y, double z);
BRLCAD_MOOSE_EXPORT BrlVector3D                      BrlSketchEmbeddingPlaneOrigin(BrlSketch sketch);
BRLCAD_MOOSE_EXPORT void                             BrlSketchSetEmbeddingPlaneOrigin(BrlSketch sketch,
                                                                                      double    x, double y, double z);

BRLCAD_MOOSE_EXPORT const char*                      BrlSketchClassName(void);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_SKETCH_INCLUDED
