/*                      S P H E R E . H
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
/** @file sphere.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares a handle and functions for Sphere solid handling
 */


#ifndef BRLCAD_C_SPHERE_INCLUDED
#define BRLCAD_C_SPHERE_INCLUDED

#include <brlcad/C/object.h>
#include <brlcad/C/vector.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef BrlObject BrlSphere;


BRLCAD_MOOSE_EXPORT BrlSphere   BrlNewSphere(void);
BRLCAD_MOOSE_EXPORT BrlSphere   BrlNewSphereAsSphere(double centerX, double centerY, double centerZ,
                                                     double radius);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlSphereCenter(BrlSphere sphere);
BRLCAD_MOOSE_EXPORT void        BrlSphereSetCenter(BrlSphere sphere,
                                                   double    centerX, double centerY, double centerZ);
BRLCAD_MOOSE_EXPORT double      BrlSphereRadius(BrlSphere sphere);
BRLCAD_MOOSE_EXPORT void        BrlSphereSetRadius(BrlSphere sphere, double radius);
BRLCAD_MOOSE_EXPORT void        BrlSphereSet(BrlSphere sphere,
                                             double    centerX, double centerY, double centerZ,
                                             double    radius);

BRLCAD_MOOSE_EXPORT const char* BrlSphereClassName(void);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_SPHERE_INCLUDED
