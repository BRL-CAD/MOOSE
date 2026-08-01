/*                      P A R T I C L E . H
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
/** @file particle.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares a handle and functions for Particle solid handling
 */


#ifndef BRLCAD_C_PARTICLE_INCLUDED
#define BRLCAD_C_PARTICLE_INCLUDED

#include <brlcad/C/object.h>
#include <brlcad/C/vector.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef BrlObject BrlParticle;


BRLCAD_MOOSE_EXPORT BrlParticle BrlNewParticle(void);
BRLCAD_MOOSE_EXPORT BrlParticle BrlNewParticleAsParticle(double baseX,   double baseY,   double baseZ,
                                                         double heightX, double heightY, double heightZ,
                                                         double baseRadius,
                                                         double topRadius);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlParticleBasePoint(BrlParticle particle);
BRLCAD_MOOSE_EXPORT void        BrlParticleSetBasePoint(BrlParticle particle,
                                                        double      baseX, double baseY, double baseZ);

BRLCAD_MOOSE_EXPORT BrlVector3D BrlParticleHeight(BrlParticle particle);
BRLCAD_MOOSE_EXPORT void        BrlParticleSetHeight(BrlParticle particle,
                                                     double      heightX, double heightY, double heightZ);

BRLCAD_MOOSE_EXPORT double      BrlParticleBaseRadius(BrlParticle particle);
BRLCAD_MOOSE_EXPORT void        BrlParticleSetBaseRadius(BrlParticle particle,
                                                         double      radius);

BRLCAD_MOOSE_EXPORT double      BrlParticleTopRadius(BrlParticle particle);
BRLCAD_MOOSE_EXPORT void        BrlParticleSetTopRadius(BrlParticle particle,
                                                        double      radius);

BRLCAD_MOOSE_EXPORT void        BrlParticleSet(BrlParticle particle,
                                               double      baseX,   double baseY,   double baseZ,
                                               double      heightX, double heightY, double heightZ,
                                               double      baseRadius,
                                               double      topRadius);

BRLCAD_MOOSE_EXPORT const char* BrlParticleClassName(void);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_PARTICLE_INCLUDED
