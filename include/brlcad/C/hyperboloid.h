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

#include <brlcad/C/object.h>
#include <brlcad/C/vector.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef BrlObject BrlHyperboloid;


BRLCAD_MOOSE_EXPORT BrlHyperboloid BrlNewHyperboloid(void);
BRLCAD_MOOSE_EXPORT BrlHyperboloid BrlNewHyperboloidAsHyperboloid(double baseX,          double baseY,          double baseZ,
                                                                  double heightX,        double heightY,        double heightZ,
                                                                  double semiMajorAxisX, double semiMajorAxisY, double semiMajorAxisZ,
                                                                  double semiMinorAxisLength,
                                                                  double apexAsymptoteDistance);
BRLCAD_MOOSE_EXPORT BrlHyperboloid BrlNewHyperboloidAsHyperboloidWithLength(double baseX,      double baseY,      double baseZ,
                                                                            double heightX,    double heightY,    double heightZ,
                                                                            double directionX, double directionY, double directionZ,
                                                                            double semiMajorAxisLength,
                                                                            double semiMinorAxisLength,
                                                                            double apexAsymptoteDistance);

BRLCAD_MOOSE_EXPORT BrlVector3D    BrlHyperboloidBasePoint(BrlHyperboloid hyperboloid);
BRLCAD_MOOSE_EXPORT void           BrlHyperboloidSetBasePoint(BrlHyperboloid hyperboloid,
                                                              double         baseX, double baseY, double baseZ);

BRLCAD_MOOSE_EXPORT BrlVector3D    BrlHyperboloidHeight(BrlHyperboloid hyperboloid);
BRLCAD_MOOSE_EXPORT void           BrlHyperboloidSetHeight(BrlHyperboloid hyperboloid,
                                                           double         heightX, double heightY, double heightZ);

BRLCAD_MOOSE_EXPORT BrlVector3D    BrlHyperboloidSemiMajorAxis(BrlHyperboloid hyperboloid);
BRLCAD_MOOSE_EXPORT void           BrlHyperboloidSetSemiMajorAxis(BrlHyperboloid hyperboloid,
                                                                  double         semiMajorAxisX, double semiMajorAxisY, double semiMajorAxisZ);

BRLCAD_MOOSE_EXPORT void           BrlHyperboloidSetSemiMajorAxisWithLength(BrlHyperboloid hyperboloid,
                                                                            double         directionX, double directionY, double directionZ,
                                                                            double         length);

BRLCAD_MOOSE_EXPORT BrlVector3D    BrlHyperboloidSemiMajorAxisDirection(BrlHyperboloid hyperboloid);
BRLCAD_MOOSE_EXPORT void           BrlHyperboloidSetSemiMajorAxisDirection(BrlHyperboloid hyperboloid,
                                                                           double         directionX, double directionY, double directionZ);

BRLCAD_MOOSE_EXPORT double         BrlHyperboloidSemiMajorAxisLength(BrlHyperboloid hyperboloid);
BRLCAD_MOOSE_EXPORT void           BrlHyperboloidSetSemiMajorAxisLength(BrlHyperboloid hyperboloid,
                                                                        double         length);

BRLCAD_MOOSE_EXPORT double         BrlHyperboloidSemiMinorAxisLength(BrlHyperboloid hyperboloid);
BRLCAD_MOOSE_EXPORT void           BrlHyperboloidSetSemiMinorAxisLength(BrlHyperboloid hyperboloid,
                                                                        double         length);

BRLCAD_MOOSE_EXPORT double         BrlHyperboloidApexAsymptoteDistance(BrlHyperboloid hyperboloid);
BRLCAD_MOOSE_EXPORT void           BrlHyperboloidSetApexAsymptoteDistance(BrlHyperboloid hyperboloid,
                                                                          double         distance);

BRLCAD_MOOSE_EXPORT void           BrlHyperboloidSet(BrlHyperboloid hyperboloid,
                                                     double         baseX,          double baseY,          double baseZ,
                                                     double         heightX,        double heightY,        double heightZ,
                                                     double         semiMajorAxisX, double semiMajorAxisY, double semiMajorAxisZ,
                                                     double         semiMinorAxisLength,
                                                     double         apexAsymptoteDistance);

BRLCAD_MOOSE_EXPORT void           BrlHyperboloidSetWithLength(BrlHyperboloid hyperboloid,
                                                               double         baseX,      double baseY,      double baseZ,
                                                               double         heightX,    double heightY,    double heightZ,
                                                               double         directionX, double directionY, double directionZ,
                                                               double         semiMajorAxisLength,
                                                               double         semiMinorAxisLength,
                                                               double         apexAsymptoteDistance);

BRLCAD_MOOSE_EXPORT const char*    BrlHyperboloidClassName(void);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_HYPERBOLOID_INCLUDED
