/*                      T O R U S . H
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
/** @file torus.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares a handle and functions for Torus solid handling
 */

#ifndef BRLCAD_C_TORUS_INCLUDED
#define BRLCAD_C_TORUS_INCLUDED

#include <brlcad/C/object.h>
#include <brlcad/C/vector.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef BrlObject BrlTorus;


BRLCAD_MOOSE_EXPORT BrlTorus    BrlNewTorus(void);
BRLCAD_MOOSE_EXPORT BrlTorus    BrlNewTorusAsTorus(double centerX, double centerY, double centerZ,
                                                   double normalX, double normalY, double normalZ,
                                                   double tubeCenterLineRadius,
                                                   double tubeRadius);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlTorusCenter(BrlTorus torus);
BRLCAD_MOOSE_EXPORT void        BrlTorusSetCenter(BrlTorus torus,
                                                  double centerX, double centerY, double centerZ);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlTorusNormal(BrlTorus torus);
BRLCAD_MOOSE_EXPORT void        BrlTorusSetNormal(BrlTorus torus,
                                                  double normalX, double normalY, double normalZ);

BRLCAD_MOOSE_EXPORT double      BrlTorusTubeCenterLineRadius(BrlTorus torus);
BRLCAD_MOOSE_EXPORT void        BrlTorusSetTubeCenterLineRadius(BrlTorus torus, double radius);

BRLCAD_MOOSE_EXPORT double      BrlTorusTubeRadius(BrlTorus torus);
BRLCAD_MOOSE_EXPORT void        BrlTorusSetTubeRadius(BrlTorus torus, double radius);

BRLCAD_MOOSE_EXPORT void        BrlTorusSet(BrlTorus torus,
                                            double   centerX, double centerY, double centerZ,
                                            double   normalX, double normalY, double normalZ,
                                            double   tubeCenterLineRadius,
                                            double   tubeRadius);

BRLCAD_MOOSE_EXPORT const char* BrlTorusClassName(void);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_TORUS_INCLUDED
