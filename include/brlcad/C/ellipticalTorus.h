/*                      E L L I P T I C A L T O R U S . H
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
/** @file ellipticalTorus.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares a handle and functions for EllipticalTorus solid handling
 */

#ifndef BRLCAD_C_ELLIPTICALTORUS_INCLUDED
#define BRLCAD_C_ELLIPTICALTORUS_INCLUDED

#include <brlcad/C/object.h>
#include <brlcad/C/vector.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef BrlObject BrlEllipticalTorus;


BRLCAD_MOOSE_EXPORT BrlEllipticalTorus BrlNewEllipticalTorus(void);
BRLCAD_MOOSE_EXPORT BrlEllipticalTorus BrlNewEllipticalTorusAsEllipticalTorus(double centerX,            double centerY,            double centerZ,
                                                                              double normalX,            double normalY,            double normalZ,
                                                                              double tubeCenterLineRadius,
                                                                              double tubeSemiMajorAxisX, double tubeSemiMajorAxisY, double tubeSemiMajorAxisZ,
                                                                              double tubeSemiMinorAxisLength);

BRLCAD_MOOSE_EXPORT BrlVector3D        BrlEllipticalTorusCenter(BrlEllipticalTorus ellipticalTorus);
BRLCAD_MOOSE_EXPORT void               BrlEllipticalTorusSetCenter(BrlEllipticalTorus ellipticalTorus,
                                                                   double             centerX, double centerY, double centerZ);

BRLCAD_MOOSE_EXPORT BrlVector3D        BrlEllipticalTorusNormal(BrlEllipticalTorus ellipticalTorus);
BRLCAD_MOOSE_EXPORT void               BrlEllipticalTorusSetNormal(BrlEllipticalTorus ellipticalTorus,
                                                                   double             normalX, double normalY, double normalZ);

BRLCAD_MOOSE_EXPORT double             BrlEllipticalTorusTubeCenterLineRadius(BrlEllipticalTorus ellipticalTorus);
BRLCAD_MOOSE_EXPORT void               BrlEllipticalTorusSetTubeCenterLineRadius(BrlEllipticalTorus ellipticalTorus,
                                                                                 double             radius);

BRLCAD_MOOSE_EXPORT BrlVector3D        BrlEllipticalTorusTubeSemiMajorAxis(BrlEllipticalTorus ellipticalTorus);
BRLCAD_MOOSE_EXPORT void               BrlEllipticalTorusSetTubeSemiMajorAxis(BrlEllipticalTorus ellipticalTorus,
                                                                              double             tubeSemiMajorAxisX, double tubeSemiMajorAxisY, double tubeSemiMajorAxisZ);

BRLCAD_MOOSE_EXPORT double             BrlEllipticalTorusTubeSemiMinorAxis(BrlEllipticalTorus ellipticalTorus);
BRLCAD_MOOSE_EXPORT void               BrlEllipticalTorusSetTubeSemiMinorAxis(BrlEllipticalTorus ellipticalTorus,
                                                                              double             length);

BRLCAD_MOOSE_EXPORT void               BrlEllipticalTorusSet(BrlEllipticalTorus ellipticalTorus,
                                                             double             centerX,            double centerY,            double centerZ,
                                                             double             normalX,            double normalY,            double normalZ,
                                                             double             tubeCenterLineRadius,
                                                             double             tubeSemiMajorAxisX, double tubeSemiMajorAxisY, double tubeSemiMajorAxisZ,
                                                             double             tubeSemiMinorAxisLength);

BRLCAD_MOOSE_EXPORT const char*        BrlEllipticalTorusClassName(void);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_ELLIPTICALTORUS_INCLUDED
