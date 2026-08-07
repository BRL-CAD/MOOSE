/*                        P I P E . H
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
/** @file pipe.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares a handle and functions for Pipe solid handling
 */


#ifndef BRLCAD_C_PIPE_INCLUDED
#define BRLCAD_C_PIPE_INCLUDED

#include <brlcad/C/object.h>
#include <brlcad/C/vector.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef BrlObject BrlPipe;
typedef BrlHandle BrlPipeControlPoint;


BRLCAD_MOOSE_EXPORT BrlPipe             BrlNewPipe(void);

BRLCAD_MOOSE_EXPORT int                 BrlPipeNumberOfControlPoints(BrlPipe pipe);
BRLCAD_MOOSE_EXPORT BrlPipeControlPoint BrlPipeGetControlPoint(BrlPipe pipe,
                                                               int     index);
BRLCAD_MOOSE_EXPORT BrlPipeControlPoint BrlPipeAppendControlPoint(BrlPipe pipe,
                                                                  double  pointX,
                                                                  double  pointY,
                                                                  double  pointZ,
                                                                  double  innerDiameter,
                                                                  double  outerDiameter,
                                                                  double  bendRadius);
BRLCAD_MOOSE_EXPORT BrlPipeControlPoint BrlPipeInsertControlPoint(BrlPipe pipe,
                                                                  int     index,
                                                                  double  pointX,
                                                                  double  pointY,
                                                                  double  pointZ,
                                                                  double  innerDiameter,
                                                                  double  outerDiameter,
                                                                  double  bendRadius);
BRLCAD_MOOSE_EXPORT void                BrlPipeDeleteControlPoint(BrlPipe pipe,
                                                                  int     index);

BRLCAD_MOOSE_EXPORT BrlVector3D         BrlPipeControlPointPoint(BrlPipeControlPoint controlPoint);
BRLCAD_MOOSE_EXPORT void                BrlPipeControlPointSetPoint(BrlPipeControlPoint controlPoint,
                                                                    double              pointX,
                                                                    double              pointY,
                                                                    double              pointZ);

BRLCAD_MOOSE_EXPORT double              BrlPipeControlPointInnerDiameter(BrlPipeControlPoint controlPoint);
BRLCAD_MOOSE_EXPORT void                BrlPipeControlPointSetInnerDiameter(BrlPipeControlPoint controlPoint,
                                                                            double              id);

BRLCAD_MOOSE_EXPORT double              BrlPipeControlPointOuterDiameter(BrlPipeControlPoint controlPoint);
BRLCAD_MOOSE_EXPORT void                BrlPipeControlPointSetOuterDiameter(BrlPipeControlPoint controlPoint,
                                                                            double              od);

BRLCAD_MOOSE_EXPORT double              BrlPipeControlPointBendRadius(BrlPipeControlPoint controlPoint);
BRLCAD_MOOSE_EXPORT void                BrlPipeControlPointSetBendRadius(BrlPipeControlPoint controlPoint,
                                                                         double              br);

BRLCAD_MOOSE_EXPORT const char*         BrlPipeClassName(void);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_PIPE_INCLUDED
