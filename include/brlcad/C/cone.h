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
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef BrlObject BrlCone;


BRLCAD_MOOSE_EXPORT BrlCone     BrlNewCone(double baseX, double baseY, double baseZ,
                                           double heightX, double heightY, double heightZ,
                                           double semiPrincipalAxisAX, double semiPrincipalAxisAY, double semiPrincipalAxisAZ,
                                           double semiPrincipalAxisBX, double semiPrincipalAxisBY, double semiPrincipalAxisBZ,
                                           double ratioCtoA, double ratioDtoB);

BRLCAD_MOOSE_EXPORT BrlCone     BrlNewConeScaled(double baseX, double baseY, double baseZ,
                                                 double heightX, double heightY, double heightZ,
                                                 double semiPrincipalAxisAX, double semiPrincipalAxisAY, double semiPrincipalAxisAZ,
                                                 double semiPrincipalAxisBX, double semiPrincipalAxisBY, double semiPrincipalAxisBZ,
                                                 double scale);

BRLCAD_MOOSE_EXPORT BrlCone     BrlNewConeUnscaled(double baseX, double baseY, double baseZ,
                                                   double heightX, double heightY, double heightZ,
                                                   double semiPrincipalAxisAX, double semiPrincipalAxisAY, double semiPrincipalAxisAZ,
                                                   double semiPrincipalAxisBX, double semiPrincipalAxisBY, double semiPrincipalAxisBZ);

BRLCAD_MOOSE_EXPORT BrlCone     BrlNewConeRadii(double baseX, double baseY, double baseZ,
                                                double heightX, double heightY, double heightZ,
                                                double radiusBase, double radiusTop);

BRLCAD_MOOSE_EXPORT BrlCone     BrlNewConeCylinder(double baseX, double baseY, double baseZ,
                                                   double heightX, double heightY, double heightZ,
                                                   double radius);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlConeBasePoint(BrlCone cone);

BRLCAD_MOOSE_EXPORT void        BrlConeSetBasePoint(BrlCone cone, double baseX, double baseY, double baseZ);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlConeHeight(BrlCone cone);

BRLCAD_MOOSE_EXPORT void        BrlConeSetHeight(BrlCone cone, double heightX, double heightY, double heightZ);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlConeSemiPrincipalAxis(BrlCone cone, size_t index);

BRLCAD_MOOSE_EXPORT void        BrlConeSetSemiPrincipalAxis(BrlCone cone, size_t index, double axisX, double axisY, double axisZ);

BRLCAD_MOOSE_EXPORT void BrlConeSet(
    BrlCone cone,
    double          baseX,
    double          baseY,
    double          baseZ,
    double          heightX,
    double          heightY,
    double          heightZ,
    double          semiPrincipalAxisAX,
    double          semiPrincipalAxisAY,
    double          semiPrincipalAxisAZ,
    double          semiPrincipalAxisBX,
    double          semiPrincipalAxisBY,
    double          semiPrincipalAxisBZ,
    double          ratioCtoA,
    double          ratioDtoB
);

BRLCAD_MOOSE_EXPORT void BrlConeSetScaled(
    BrlCone cone,
    double          baseX,
    double          baseY,
    double          baseZ,
    double          heightX,
    double          heightY,
    double          heightZ,
    double          semiPrincipalAxisAX,
    double          semiPrincipalAxisAY,
    double          semiPrincipalAxisAZ,
    double          semiPrincipalAxisBX,
    double          semiPrincipalAxisBY,
    double          semiPrincipalAxisBZ,
    double          scale
);

BRLCAD_MOOSE_EXPORT void BrlConeSetUnscaled(
    BrlCone cone,
    double          baseX,
    double          baseY,
    double          baseZ,
    double          heightX,
    double          heightY,
    double          heightZ,
    double          semiPrincipalAxisAX,
    double          semiPrincipalAxisAY,
    double          semiPrincipalAxisAZ,
    double          semiPrincipalAxisBX,
    double          semiPrincipalAxisBY,
    double          semiPrincipalAxisBZ
);

BRLCAD_MOOSE_EXPORT void BrlConeSetRadii(
    BrlCone cone,
    double          baseX,
    double          baseY,
    double          baseZ,
    double          heightX,
    double          heightY,
    double          heightZ,
    double          radiusBase,
    double          radiusTop
);

BRLCAD_MOOSE_EXPORT void BrlConeSetCylinder(
    BrlCone cone,
    double          baseX,
    double          baseY,
    double          baseZ,
    double          heightX,
    double          heightY,
    double          heightZ,
    double          radius
);

BRLCAD_MOOSE_EXPORT int         BrlConeIsValid(BrlCone cone);

BRLCAD_MOOSE_EXPORT const char* BrlConeType(BrlCone cone);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_CONE_INCLUDED
