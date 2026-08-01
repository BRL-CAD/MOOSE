/*                      H Y P E R B O L O I D . H
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
/** @file hyperboloid.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares a handle and functions for Hyperboloid solid handling
 */


#ifndef BRLCAD_C_HYPERBOLOID_INCLUDED
#define BRLCAD_C_HYPERBOLOID_INCLUDED

#include <brlcad/C/globals.h>
#include <brlcad/C/object.h>
#include <brlcad/C/vector.h>

#ifdef __cplusplus
extern "C" {
#endif


BRLCAD_MOOSE_EXPORT BrlObject   BrlNewHyperboloid(void);
BRLCAD_MOOSE_EXPORT BrlObject   BrlNewHyperboloidAsHyperboloid(double baseX,          double baseY,          double baseZ,
                                                               double heightX,        double heightY,        double heightZ,
                                                               double semiMajorAxisX, double semiMajorAxisY, double semiMajorAxisZ,
                                                               double semiMinorAxisLength,
                                                               double apexAsymptoteDistance);
BRLCAD_MOOSE_EXPORT BrlObject   BrlNewHyperboloidAsHyperboloidWithLength(double baseX,               double baseY,               double baseZ,
                                                                         double heightX,             double heightY,             double heightZ,
                                                                         double directionX,          double directionY,          double directionZ,
                                                                         double semiMajorAxisLength,
                                                                         double semiMinorAxisLength,
                                                                         double apexAsymptoteDistance);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlHyperboloidBasePoint(BrlObject hyperboloid);
BRLCAD_MOOSE_EXPORT void        BrlHyperboloidSetBasePoint(BrlObject hyperboloid,
                                                           double    baseX, double baseY, double baseZ);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlHyperboloidHeight(BrlObject hyperboloid);
BRLCAD_MOOSE_EXPORT void        BrlHyperboloidSetHeight(BrlObject hyperboloid,
                                                        double    heightX, double heightY, double heightZ);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlHyperboloidSemiMajorAxis(BrlObject hyperboloid);
BRLCAD_MOOSE_EXPORT void        BrlHyperboloidSetSemiMajorAxis(BrlObject hyperboloid,
                                                               double    semiMajorAxisX, double semiMajorAxisY, double semiMajorAxisZ);

BRLCAD_MOOSE_EXPORT void        BrlHyperboloidSetSemiMajorAxisWithLength(BrlObject hyperboloid,
                                                                         double    directionX, double directionY, double directionZ,
                                                                         double    length);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlHyperboloidSemiMajorAxisDirection(BrlObject hyperboloid);
BRLCAD_MOOSE_EXPORT void        BrlHyperboloidSetSemiMajorAxisDirection(BrlObject hyperboloid,
                                                                        double    directionX, double directionY, double directionZ);

BRLCAD_MOOSE_EXPORT double      BrlHyperboloidSemiMajorAxisLength(BrlObject hyperboloid);
BRLCAD_MOOSE_EXPORT void        BrlHyperboloidSetSemiMajorAxisLength(BrlObject hyperboloid,
                                                                     double    length);

BRLCAD_MOOSE_EXPORT double      BrlHyperboloidSemiMinorAxisLength(BrlObject hyperboloid);
BRLCAD_MOOSE_EXPORT void        BrlHyperboloidSetSemiMinorAxisLength(BrlObject hyperboloid,
                                                                     double    length);

BRLCAD_MOOSE_EXPORT double      BrlHyperboloidApexAsymptoteDistance(BrlObject hyperboloid);
BRLCAD_MOOSE_EXPORT void        BrlHyperboloidSetApexAsymptoteDistance(BrlObject hyperboloid,
                                                                       double    distance);

BRLCAD_MOOSE_EXPORT void        BrlHyperboloidSet(BrlObject hyperboloid,
                                                  double    baseX,          double baseY,          double baseZ,
                                                  double    heightX,        double heightY,        double heightZ,
                                                  double    semiMajorAxisX, double semiMajorAxisY, double semiMajorAxisZ,
                                                  double    semiMinorAxisLength,
                                                  double    apexAsymptoteDistance);

BRLCAD_MOOSE_EXPORT void        BrlHyperboloidSetWithLength(BrlObject hyperboloid,
                                                            double    baseX,               double baseY,               double baseZ,
                                                            double    heightX,             double heightY,             double heightZ,
                                                            double    directionX,          double directionY,          double directionZ,
                                                            double    semiMajorAxisLength,
                                                            double    semiMinorAxisLength,
                                                            double    apexAsymptoteDistance);

BRLCAD_MOOSE_EXPORT const char* BrlHyperboloidClassName(void);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_HYPERBOLOID_INCLUDED
