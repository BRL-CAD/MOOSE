/*                      C O N E . H
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
/** @file cone.h
 *
 *  BRL-CAD core simplified C interface:
 *      Declares a handle and functions for Cone solid handling
 */

#ifndef BRLCAD_C_CONE_INCLUDED
#define BRLCAD_C_CONE_INCLUDED

#include <brlcad/C/object.h>
#include <brlcad/C/vector.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef BrlObject BrlCone;


BRLCAD_MOOSE_EXPORT BrlCone     BrlNewCone(void);
BRLCAD_MOOSE_EXPORT BrlCone     BrlNewConeAsTruncatedGeneralCone(double baseX,               double baseY,               double baseZ,
                                                                 double heightX,             double heightY,             double heightZ,
                                                                 double semiPrincipalAxisAX, double semiPrincipalAxisAY, double semiPrincipalAxisAZ,
                                                                 double semiPrincipalAxisBX, double semiPrincipalAxisBY, double semiPrincipalAxisBZ,
                                                                 double ratioCtoA,
                                                                 double ratioDtoB);
BRLCAD_MOOSE_EXPORT BrlCone     BrlNewConeAsTruncatedErectedCone(double baseX,               double baseY,               double baseZ,
                                                                 double heightX,             double heightY,             double heightZ,
                                                                 double semiPrincipalAxisAX, double semiPrincipalAxisAY, double semiPrincipalAxisAZ,
                                                                 double semiPrincipalAxisBX, double semiPrincipalAxisBY, double semiPrincipalAxisBZ,
                                                                 double scale);
BRLCAD_MOOSE_EXPORT BrlCone     BrlNewConeAsRightEllipticalCylinder(double baseX,               double baseY,               double baseZ,
                                                                    double heightX,             double heightY,             double heightZ,
                                                                    double semiPrincipalAxisAX, double semiPrincipalAxisAY, double semiPrincipalAxisAZ,
                                                                    double semiPrincipalAxisBX, double semiPrincipalAxisBY, double semiPrincipalAxisBZ);
BRLCAD_MOOSE_EXPORT BrlCone     BrlNewConeAsTruncatedRightCircularCone(double baseX,   double baseY,   double baseZ,
                                                                       double heightX, double heightY, double heightZ,
                                                                       double radiusBase,
                                                                       double radiusTop);
BRLCAD_MOOSE_EXPORT BrlCone     BrlNewConeAsRightCircularCylinder(double baseX,   double baseY,   double baseZ,
                                                                  double heightX, double heightY, double heightZ,
                                                                  double radius);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlConeBasePoint(BrlCone cone);
BRLCAD_MOOSE_EXPORT void        BrlConeSetBasePoint(BrlCone cone, 
                                                    double  baseX, double baseY, double baseZ);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlConeHeight(BrlCone cone);
BRLCAD_MOOSE_EXPORT void        BrlConeSetHeight(BrlCone cone,
                                                 double  heightX, double heightY, double heightZ);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlConeSemiPrincipalAxis(BrlCone cone, int index);
BRLCAD_MOOSE_EXPORT void        BrlConeSetSemiPrincipalAxis(BrlCone cone,
                                                            int     index,
                                                            double  axisX, double axisY, double axisZ);

BRLCAD_MOOSE_EXPORT void        BrlConeSetAsTruncatedGeneralCone(BrlCone cone,
                                                                 double  baseX,               double baseY,               double baseZ,
                                                                 double  heightX,             double heightY,             double heightZ,
                                                                 double  semiPrincipalAxisAX, double semiPrincipalAxisAY, double semiPrincipalAxisAZ,
                                                                 double  semiPrincipalAxisBX, double semiPrincipalAxisBY, double semiPrincipalAxisBZ,
                                                                 double  ratioCtoA,
                                                                 double  ratioDtoB);
BRLCAD_MOOSE_EXPORT void        BrlConeSetAsTruncatedErectedCone(BrlCone cone,
                                                                 double  baseX,               double baseY,               double baseZ,
                                                                 double  heightX,             double heightY,             double heightZ,
                                                                 double  semiPrincipalAxisAX, double semiPrincipalAxisAY, double semiPrincipalAxisAZ,
                                                                 double  semiPrincipalAxisBX, double semiPrincipalAxisBY, double semiPrincipalAxisBZ,
                                                                 double  scale);
BRLCAD_MOOSE_EXPORT void        BrlConeSetAsRightEllipticalCylinder(BrlCone cone,
                                                                    double  baseX,               double baseY,               double baseZ,
                                                                    double  heightX,             double heightY,             double heightZ,
                                                                    double  semiPrincipalAxisAX, double semiPrincipalAxisAY, double semiPrincipalAxisAZ,
                                                                    double  semiPrincipalAxisBX, double semiPrincipalAxisBY, double semiPrincipalAxisBZ);
BRLCAD_MOOSE_EXPORT void        BrlConeSetAsTruncatedRightCircularCone(BrlCone cone,
                                                                       double  baseX,   double baseY,   double baseZ,
                                                                       double  heightX, double heightY, double heightZ,
                                                                       double  radiusBase,
                                                                       double  radiusTop);
BRLCAD_MOOSE_EXPORT void        BrlConeSetAsRightCircularCylinder(BrlCone cone,
                                                                  double  baseX,   double baseY,   double baseZ,
                                                                  double  heightX, double heightY, double heightZ,
                                                                  double  radius);

BRLCAD_MOOSE_EXPORT const char* BrlConeClassName(void);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_CONE_INCLUDED
