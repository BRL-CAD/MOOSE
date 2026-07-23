/*                      H Y P E R B O L I C C Y L I N D E R . H
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
/** @file hyperbolicCylinder.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares a handle and functions for HyperbolicCylinder solid handling
 */

#ifndef BRLCAD_C_HYPERBOLICCYLINDER_INCLUDED
#define BRLCAD_C_HYPERBOLICCYLINDER_INCLUDED

#include <brlcad/C/object.h>
#include <brlcad/C/vector.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef BrlObject BrlHyperbolicCylinder;


BRLCAD_MOOSE_EXPORT BrlHyperbolicCylinder BrlNewHyperbolicCylinder(void);
BRLCAD_MOOSE_EXPORT BrlHyperbolicCylinder BrlNewHyperbolicCylinderAsHyperbolicCylinder(double basePointX,    double basePointY,    double basePointZ,
                                                                                       double heightX,       double heightY,       double heightZ,
                                                                                       double depthX,        double depthY,        double depthZ,
                                                                                       double halfWidth,     double apexAsymptoteDistance);

BRLCAD_MOOSE_EXPORT BrlVector3D           BrlHyperbolicCylinderBasePoint(BrlHyperbolicCylinder hyperbolicCylinder);
BRLCAD_MOOSE_EXPORT void                  BrlHyperbolicCylinderSetBasePoint(BrlHyperbolicCylinder hyperbolicCylinder,
                                                                            double                basePointX, double basePointY, double basePointZ);

BRLCAD_MOOSE_EXPORT BrlVector3D           BrlHyperbolicCylinderHeight(BrlHyperbolicCylinder hyperbolicCylinder);
BRLCAD_MOOSE_EXPORT void                  BrlHyperbolicCylinderSetHeight(BrlHyperbolicCylinder hyperbolicCylinder,
                                                                         double                heightX, double heightY, double heightZ);

BRLCAD_MOOSE_EXPORT BrlVector3D           BrlHyperbolicCylinderDepth(BrlHyperbolicCylinder hyperbolicCylinder);
BRLCAD_MOOSE_EXPORT void                  BrlHyperbolicCylinderSetDepth(BrlHyperbolicCylinder hyperbolicCylinder,
                                                                        double                depthX, double depthY, double depthZ);

BRLCAD_MOOSE_EXPORT double                BrlHyperbolicCylinderHalfWidth(BrlHyperbolicCylinder hyperbolicCylinder);
BRLCAD_MOOSE_EXPORT void                  BrlHyperbolicCylinderSetHalfWidth(BrlHyperbolicCylinder hyperbolicCylinder, 
                                                                            double                halfWidth);

BRLCAD_MOOSE_EXPORT double                BrlHyperbolicCylinderApexAsymptoteDistance(BrlHyperbolicCylinder hyperbolicCylinder);
BRLCAD_MOOSE_EXPORT void                  BrlHyperbolicCylinderSetApexAsymptoteDistance(BrlHyperbolicCylinder hyperbolicCylinder, double apexAsymptoteDistance);

BRLCAD_MOOSE_EXPORT void                  BrlHyperbolicCylinderSet(BrlHyperbolicCylinder hyperbolicCylinder,
                                                                   double                basePointX, double basePointY, double basePointZ,
                                                                   double                heightX,    double heightY,    double heightZ,
                                                                   double                depthX,     double depthY,     double depthZ,
                                                                   double                halfWidth,  double apexAsymptoteDistance);

BRLCAD_MOOSE_EXPORT const char*           BrlHyperbolicCylinderClassName(void);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_HYPERBOLICCYLINDER_INCLUDED
