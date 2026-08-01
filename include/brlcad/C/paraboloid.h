/*                      P A R A B O L O I D . H
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
/** @file paraboloid.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares a handle and functions for Paraboloid solid handling
 */


#ifndef BRLCAD_C_PARABOLOID_INCLUDED
#define BRLCAD_C_PARABOLOID_INCLUDED

#include <brlcad/C/globals.h>
#include <brlcad/C/object.h>
#include <brlcad/C/vector.h>

#ifdef __cplusplus
extern "C" {
#endif


BRLCAD_MOOSE_EXPORT BrlObject   BrlNewParaboloid(void);
BRLCAD_MOOSE_EXPORT BrlObject   BrlNewParaboloidAsParaboloid(double baseX,          double baseY,          double baseZ,
                                                             double heightX,        double heightY,        double heightZ,
                                                             double semiMajorAxisX, double semiMajorAxisY, double semiMajorAxisZ,
                                                             double semiMinorAxisLength);
BRLCAD_MOOSE_EXPORT BrlObject   BrlNewParaboloidAsParaboloidWithLength(double baseX,               double baseY,               double baseZ,
                                                                       double heightX,             double heightY,             double heightZ,
                                                                       double directionX,          double directionY,          double directionZ,
                                                                       double semiMajorAxisLength,
                                                                       double semiMinorAxisLength);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlParaboloidBasePoint(BrlObject paraboloid);
BRLCAD_MOOSE_EXPORT void        BrlParaboloidSetBasePoint(BrlObject paraboloid,
                                                          double    baseX, double baseY, double baseZ);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlParaboloidHeight(BrlObject paraboloid);
BRLCAD_MOOSE_EXPORT void        BrlParaboloidSetHeight(BrlObject paraboloid,
                                                       double    heightX, double heightY, double heightZ);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlParaboloidSemiMajorAxis(BrlObject paraboloid);
BRLCAD_MOOSE_EXPORT void        BrlParaboloidSetSemiMajorAxis(BrlObject paraboloid,
                                                              double    semiMajorAxisX, double semiMajorAxisY, double semiMajorAxisZ);

BRLCAD_MOOSE_EXPORT void        BrlParaboloidSetSemiMajorAxisWithLength(BrlObject paraboloid,
                                                                        double    directionX, double directionY, double directionZ,
                                                                        double    length);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlParaboloidSemiMajorAxisDirection(BrlObject paraboloid);
BRLCAD_MOOSE_EXPORT void        BrlParaboloidSetSemiMajorAxisDirection(BrlObject paraboloid,
                                                                       double    directionX, double directionY, double directionZ);

BRLCAD_MOOSE_EXPORT double      BrlParaboloidSemiMajorAxisLength(BrlObject paraboloid);
BRLCAD_MOOSE_EXPORT void        BrlParaboloidSetSemiMajorAxisLength(BrlObject paraboloid,
                                                                    double    length);

BRLCAD_MOOSE_EXPORT double      BrlParaboloidSemiMinorAxisLength(BrlObject paraboloid);
BRLCAD_MOOSE_EXPORT void        BrlParaboloidSetSemiMinorAxisLength(BrlObject paraboloid,
                                                                    double    length);

BRLCAD_MOOSE_EXPORT void        BrlParaboloidSet(BrlObject paraboloid,
                                                 double    baseX,          double baseY,          double baseZ,
                                                 double    heightX,        double heightY,        double heightZ,
                                                 double    semiMajorAxisX, double semiMajorAxisY, double semiMajorAxisZ,
                                                 double    semiMinorAxisLength);

BRLCAD_MOOSE_EXPORT void        BrlParaboloidSetWithLength(BrlObject paraboloid,
                                                           double    baseX,               double baseY,               double baseZ,
                                                           double    heightX,             double heightY,             double heightZ,
                                                           double    directionX,          double directionY,          double directionZ,
                                                           double    semiMajorAxisLength,
                                                           double    semiMinorAxisLength);

BRLCAD_MOOSE_EXPORT const char* BrlParaboloidClassName(void);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_PARABOLOID_INCLUDED
