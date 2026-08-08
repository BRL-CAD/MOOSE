/*          P A R A B O L I C C Y L I N D E R . H
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
/** @file parabolicCylinder.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares a handle and functions for ParabolicCylinder solid handling
 */


#ifndef BRLCAD_C_PARABOLICCYLINDER_INCLUDED
#define BRLCAD_C_PARABOLICCYLINDER_INCLUDED

#include <brlcad/C/globals.h>
#include <brlcad/C/object.h>
#include <brlcad/C/vector.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef BrlObject BrlParabolicCylinder;


BRLCAD_MOOSE_EXPORT BrlParabolicCylinder BrlNewParabolicCylinder(void);
BRLCAD_MOOSE_EXPORT BrlParabolicCylinder BrlNewParabolicCylinderAsParabolicCylinder(double baseX,   double baseY,   double baseZ,
                                                                                    double heightX, double heightY, double heightZ,
                                                                                    double depthX,  double depthY,  double depthZ,
                                                                                    double halfWidth);

BRLCAD_MOOSE_EXPORT BrlVector3D          BrlParabolicCylinderBasePoint(BrlParabolicCylinder parabolicCylinder);
BRLCAD_MOOSE_EXPORT void                 BrlParabolicCylinderSetBasePoint(BrlParabolicCylinder parabolicCylinder,
                                                                          double               baseX, double baseY, double baseZ);

BRLCAD_MOOSE_EXPORT BrlVector3D          BrlParabolicCylinderHeight(BrlParabolicCylinder parabolicCylinder);
BRLCAD_MOOSE_EXPORT void                 BrlParabolicCylinderSetHeight(BrlParabolicCylinder parabolicCylinder,
                                                                       double               heightX, double heightY, double heightZ);

BRLCAD_MOOSE_EXPORT BrlVector3D          BrlParabolicCylinderDepth(BrlParabolicCylinder parabolicCylinder);
BRLCAD_MOOSE_EXPORT void                 BrlParabolicCylinderSetDepth(BrlParabolicCylinder parabolicCylinder,
                                                                      double               depthX, double depthY, double depthZ);

BRLCAD_MOOSE_EXPORT double               BrlParabolicCylinderHalfWidth(BrlParabolicCylinder parabolicCylinder);
BRLCAD_MOOSE_EXPORT void                 BrlParabolicCylinderSetHalfWidth(BrlParabolicCylinder parabolicCylinder,
                                                                          double               halfWidth);

BRLCAD_MOOSE_EXPORT void                 BrlParabolicCylinderSet(BrlParabolicCylinder parabolicCylinder,
                                                                 double               baseX,   double baseY,   double baseZ,
                                                                 double               heightX, double heightY, double heightZ,
                                                                 double               depthX,  double depthY,  double depthZ,
                                                                 double               halfWidth);

BRLCAD_MOOSE_EXPORT const char*          BrlParabolicCylinderClassName(void);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_PARABOLICCYLINDER_INCLUDED
