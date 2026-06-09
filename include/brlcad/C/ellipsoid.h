/*                      E L L I P S O I D . h
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
/** @file ellipsoid
 *
 *  BRL-CAD core simplified C interface:
 *      Declares a handle and functions for Ellipsoid solid handling
 */


#ifndef BRLCAD_C_ELLIPSOID_INCLUDED
#define BRLCAD_C_ELLIPSOID_INCLUDED

#include <brlcad/C/object.h>
#include <brlcad/C/vector.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef BrlObject BrlEllipsoid;


BRLCAD_MOOSE_EXPORT BrlEllipsoid BrlNewEllipsoid(double centerX, double centerY, double centerZ,
                                                 double semiPrincipalAxisAX, double semiPrincipalAxisAY, double semiPrincipalAxisAZ,
                                                 double semiPrincipalAxisBX, double semiPrincipalAxisBY, double semiPrincipalAxisBZ,
                                                 double semiPrincipalAxisCX, double semiPrincipalAxisCY, double semiPrincipalAxisCZ);

BRLCAD_MOOSE_EXPORT BrlEllipsoid BrlNewEllipsoidFromAxisRadius(double centerX, double centerY, double centerZ,
                                                               double semiPrincipalAxisX, double semiPrincipalAxisY, double semiPrincipalAxisZ,
                                                               double radius);

BRLCAD_MOOSE_EXPORT BrlEllipsoid BrlNewEllipsoidSphere(double centerX, double centerY, double centerZ,
                                                       double radius);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlEllipsoidCenter(BrlEllipsoid ellipsoid);

BRLCAD_MOOSE_EXPORT void        BrlEllipsoidSetCenter(BrlEllipsoid ellipsoid, 
                                                      double centerX, double centerY, double centerZ);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlEllipsoidSemiPrincipalAxis(BrlEllipsoid ellipsoid, size_t index);

BRLCAD_MOOSE_EXPORT void        BrlEllipsoidSetSemiPrincipalAxis(BrlEllipsoid ellipsoid, 
                                                                 size_t index, 
                                                                 double axisX, double axisY, double axisZ);

BRLCAD_MOOSE_EXPORT void        BrlEllipsoidSet(BrlEllipsoid ellipsoid,
                                                double centerX, double centerY, double centerZ,
                                                double semiPrincipalAxisAX, double semiPrincipalAxisAY, double semiPrincipalAxisAZ,
                                                double semiPrincipalAxisBX, double semiPrincipalAxisBY, double semiPrincipalAxisBZ,
                                                double semiPrincipalAxisCX, double semiPrincipalAxisCY, double semiPrincipalAxisCZ);

BRLCAD_MOOSE_EXPORT void        BrlEllipsoidSetFocals(BrlEllipsoid ellipsoid,
                                                      double focalAX, double focalAY, double focalAZ,
                                                      double focalBX, double focalBY, double focalBZ,
                                                      double majorAxisLength);

BRLCAD_MOOSE_EXPORT void        BrlEllipsoidSetSphere(BrlEllipsoid ellipsoid,
                                                      double centerX, double centerY, double centerZ,
                                                      double radius);

BRLCAD_MOOSE_EXPORT int         BrlEllipsoidIsValid(BrlEllipsoid ellipsoid);

BRLCAD_MOOSE_EXPORT const char* BrlEllipsoidType(BrlEllipsoid ellipsoid);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_ELLIPSOID_INCLUDED
