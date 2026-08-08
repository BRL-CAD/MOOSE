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

#include <stdbool.h>

#include <brlcad/C/object.h>
#include <brlcad/C/vector.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef BrlObject BrlSketch;
typedef BrlHandle BrlSketchSegment;
typedef BrlHandle BrlSketchLine;
typedef BrlHandle BrlSketchCircularArc;
typedef BrlHandle BrlSketchNurb;
typedef BrlHandle BrlSketchBezier;


BRLCAD_MOOSE_EXPORT BrlSketch            BrlNewSketch(void);

BRLCAD_MOOSE_EXPORT BrlVector3D          BrlSketchEmbeddingPlaneX(BrlSketch sketch);
BRLCAD_MOOSE_EXPORT void                 BrlSketchSetEmbeddingPlaneX(BrlSketch sketch,
                                                                     double    x, double y, double z);

BRLCAD_MOOSE_EXPORT BrlVector3D          BrlSketchEmbeddingPlaneY(BrlSketch sketch);
BRLCAD_MOOSE_EXPORT void                 BrlSketchSetEmbeddingPlaneY(BrlSketch sketch, 
                                                                     double    x, double y, double z);

BRLCAD_MOOSE_EXPORT BrlVector3D          BrlSketchEmbeddingPlaneOrigin(BrlSketch sketch);
BRLCAD_MOOSE_EXPORT void                 BrlSketchSetEmbeddingPlaneOrigin(BrlSketch sketch,
                                                                          double    x, double y, double z);

BRLCAD_MOOSE_EXPORT int                  BrlSketchNumberOfSegments(BrlSketch sketch);
BRLCAD_MOOSE_EXPORT BrlSketchSegment     BrlSketchGetSegment(BrlSketch sketch,
                                                             int       index);

BRLCAD_MOOSE_EXPORT BrlSketchLine        BrlSketchAppendLine(BrlSketch sketch);
BRLCAD_MOOSE_EXPORT BrlSketchLine        BrlSketchInsertLine(BrlSketch sketch,
                                                             int       index);

BRLCAD_MOOSE_EXPORT BrlSketchCircularArc BrlSketchAppendArc(BrlSketch sketch);
BRLCAD_MOOSE_EXPORT BrlSketchCircularArc BrlSketchInsertArc(BrlSketch sketch,
                                                            int       index);

BRLCAD_MOOSE_EXPORT BrlSketchNurb        BrlSketchAppendNurb(BrlSketch sketch);
BRLCAD_MOOSE_EXPORT BrlSketchNurb        BrlSketchInsertNurb(BrlSketch sketch,
                                                             int       index);

BRLCAD_MOOSE_EXPORT BrlSketchBezier      BrlSketchAppendBezier(BrlSketch sketch);
BRLCAD_MOOSE_EXPORT BrlSketchBezier      BrlSketchInsertBezier(BrlSketch sketch,
                                                               int       index);

BRLCAD_MOOSE_EXPORT void                 BrlSketchDeleteSegment(BrlSketch sketch,
                                                                int       index);

BRLCAD_MOOSE_EXPORT const char*          BrlSketchClassName(void);


BRLCAD_MOOSE_EXPORT int                  BrlSketchSegmentType(BrlSketchSegment segment);
BRLCAD_MOOSE_EXPORT BrlVector3D          BrlSketchSegmentStartPoint(BrlSketchSegment segment);
BRLCAD_MOOSE_EXPORT BrlVector3D          BrlSketchSegmentEndPoint(BrlSketchSegment segment);
BRLCAD_MOOSE_EXPORT bool                 BrlSketchSegmentReverse(BrlSketchSegment segment);
BRLCAD_MOOSE_EXPORT void                 BrlSketchSegmentSetReverse(BrlSketchSegment segment,
                                                                    bool             reverse);

BRLCAD_MOOSE_EXPORT BrlSketchLine        BrlCastToSketchLine(BrlSketchSegment segment);
BRLCAD_MOOSE_EXPORT BrlSketchCircularArc BrlCastToSketchCircularArc(BrlSketchSegment segment);
BRLCAD_MOOSE_EXPORT BrlSketchNurb        BrlCastToSketchNurb(BrlSketchSegment segment);
BRLCAD_MOOSE_EXPORT BrlSketchBezier      BrlCastToSketchBezier(BrlSketchSegment segment);

BRLCAD_MOOSE_EXPORT void                 BrlSketchLineSetStartPoint(BrlSketchLine line,
                                                                    double        x, double y);
BRLCAD_MOOSE_EXPORT void                 BrlSketchLineSetEndPoint(BrlSketchLine line,
                                                                  double        x, double y);

BRLCAD_MOOSE_EXPORT void                 BrlSketchCircularArcSetStartPoint(BrlSketchCircularArc arc,
                                                                           double               x, double y);
BRLCAD_MOOSE_EXPORT void                 BrlSketchCircularArcSetEndPoint(BrlSketchCircularArc arc,
                                                                         double               x, double y);
BRLCAD_MOOSE_EXPORT BrlVector3D          BrlSketchCircularArcCenter(BrlSketchCircularArc arc);
BRLCAD_MOOSE_EXPORT void                 BrlSketchCircularArcSetCenter(BrlSketchCircularArc arc,
                                                                       double               x, double y);
BRLCAD_MOOSE_EXPORT double               BrlSketchCircularArcRadius(BrlSketchCircularArc arc);
BRLCAD_MOOSE_EXPORT void                 BrlSketchCircularArcSetRadius(BrlSketchCircularArc arc,
                                                                       double               radius);
BRLCAD_MOOSE_EXPORT bool                 BrlSketchCircularArcCenterIsLeft(BrlSketchCircularArc arc);
BRLCAD_MOOSE_EXPORT void                 BrlSketchCircularArcSetCenterIsLeft(BrlSketchCircularArc arc,
                                                                             bool                 isLeft);
BRLCAD_MOOSE_EXPORT bool                 BrlSketchCircularArcClockwiseOriented(BrlSketchCircularArc arc);
BRLCAD_MOOSE_EXPORT void                 BrlSketchCircularArcSetClockwiseOriented(BrlSketchCircularArc arc,
                                                                                  bool                 clockwise);

BRLCAD_MOOSE_EXPORT void                 BrlSketchNurbSetStartPoint(BrlSketchNurb nurb,
                                                                    double        x, double y);
BRLCAD_MOOSE_EXPORT void                 BrlSketchNurbSetEndPoint(BrlSketchNurb nurb,
                                                                  double        x, double y);
BRLCAD_MOOSE_EXPORT int                  BrlSketchNurbOrder(BrlSketchNurb nurb);
BRLCAD_MOOSE_EXPORT void                 BrlSketchNurbSetOrder(BrlSketchNurb nurb,
                                                               int           order);
BRLCAD_MOOSE_EXPORT bool                 BrlSketchNurbIsRational(BrlSketchNurb nurb);
BRLCAD_MOOSE_EXPORT int                  BrlSketchNurbNumberOfKnots(BrlSketchNurb nurb);
BRLCAD_MOOSE_EXPORT double               BrlSketchNurbKnot(BrlSketchNurb nurb,
                                                           int           index);
BRLCAD_MOOSE_EXPORT void                 BrlSketchNurbAddKnot(BrlSketchNurb nurb,
                                                              double        knot);
BRLCAD_MOOSE_EXPORT int                  BrlSketchNurbNumberOfControlPoints(BrlSketchNurb nurb);
BRLCAD_MOOSE_EXPORT BrlVector3D          BrlSketchNurbControlPoint(BrlSketchNurb nurb,
                                                                   int           index);
BRLCAD_MOOSE_EXPORT double               BrlSketchNurbControlPointWeight(BrlSketchNurb nurb,
                                                                         int           index);
BRLCAD_MOOSE_EXPORT void                 BrlSketchNurbAddControlPoint(BrlSketchNurb nurb,
                                                                      double        x,
                                                                      double        y);
BRLCAD_MOOSE_EXPORT void                 BrlSketchNurbAddControlPointWeight(BrlSketchNurb nurb,
                                                                            double        x, double y,
                                                                            double        weight);

BRLCAD_MOOSE_EXPORT void                 BrlSketchBezierSetStartPoint(BrlSketchBezier bezier,
                                                                      double          x, double y);
BRLCAD_MOOSE_EXPORT void                 BrlSketchBezierSetEndPoint(BrlSketchBezier bezier,
                                                                    double          x, double y);
BRLCAD_MOOSE_EXPORT int                  BrlSketchBezierDegree(BrlSketchBezier bezier);
BRLCAD_MOOSE_EXPORT BrlVector3D          BrlSketchBezierControlPoint(BrlSketchBezier bezier,
                                                                     int             index);
BRLCAD_MOOSE_EXPORT void                 BrlSketchBezierAddControlPoint(BrlSketchBezier bezier,
                                                                        double          x, double y);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_SKETCH_INCLUDED
