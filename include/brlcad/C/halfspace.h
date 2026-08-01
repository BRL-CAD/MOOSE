/*                      H A L F S P A C E . H
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
/** @file halfspace.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares a handle and functions for Halfspace solid handling
 */


#ifndef BRLCAD_C_HALFSPACE_INCLUDED
#define BRLCAD_C_HALFSPACE_INCLUDED

#include <brlcad/C/globals.h>
#include <brlcad/C/object.h>
#include <brlcad/C/vector.h>

#ifdef __cplusplus
extern "C" {
#endif


BRLCAD_MOOSE_EXPORT BrlObject   BrlNewHalfspace(void);
BRLCAD_MOOSE_EXPORT BrlObject   BrlNewHalfspaceAsHalfspace(double normalX, double normalY, double normalZ,
                                                           double distance);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlHalfspaceNormal(BrlObject halfspace);
BRLCAD_MOOSE_EXPORT void        BrlHalfspaceSetNormal(BrlObject halfspace,
                                                      double    normalX, double normalY, double normalZ);

BRLCAD_MOOSE_EXPORT double      BrlHalfspaceDistanceFromOrigin(BrlObject halfspace);
BRLCAD_MOOSE_EXPORT void        BrlHalfspaceSetDistanceFromOrigin(BrlObject halfspace,
                                                                  double    distance);

BRLCAD_MOOSE_EXPORT void        BrlHalfspaceSet(BrlObject halfspace,
                                                double    normalX, double normalY, double normalZ,
                                                double    distance);

BRLCAD_MOOSE_EXPORT const char* BrlHalfspaceClassName(void);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_HALFSPACE_INCLUDED
