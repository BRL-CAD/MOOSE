/*                      P A R T I C L E . C P P
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
/** @file particle.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements a handle and functions for Particle solid handling
 */

#include <cassert>

#include <brlcad/Database/Particle.h>

#include <brlcad/C/particle.h>

#include "casts.h"


using namespace BRLCAD;


BrlParticle BrlNewParticle(void) {
    return new ParticleData(new Particle());
}


BrlParticle BrlNewParticleAsParticle
(
    double baseX,   double baseY,   double baseZ,
    double heightX, double heightY, double heightZ,
    double baseRadius,
    double topRadius
) {
    Vector3D bp(baseX, baseY, baseZ);
    Vector3D h(heightX, heightY, heightZ);

    return new ParticleData(new Particle(bp, h, baseRadius, topRadius));
}


BrlVector3D BrlParticleBasePoint
(
    BrlParticle particle
) {
    BrlVector3D ret = nullptr;

    if (particle != nullptr) {
        Particle* partIntern = CastParticle(particle);

        assert(partIntern != nullptr);

        if (partIntern != nullptr)
            ret = new Vector3DData(partIntern->BasePoint());
    }

    return ret;
}


void BrlParticleSetBasePoint
(
    BrlParticle particle,
    double      baseX, double baseY, double baseZ
) {
    if (particle != nullptr) {
        Particle* partIntern = CastParticle(particle);

        assert(partIntern != nullptr);

        if (partIntern != nullptr) {
            Vector3D bp(baseX, baseY, baseZ);

            partIntern->SetBasePoint(bp);
        }
    }
}


BrlVector3D BrlParticleHeight
(
    BrlParticle particle
) {
    BrlVector3D ret = nullptr;

    if (particle != nullptr) {
        Particle* partIntern = CastParticle(particle);

        assert(partIntern != nullptr);

        if (partIntern != nullptr)
            ret = new Vector3DData(partIntern->Height());
    }

    return ret;
}


void BrlParticleSetHeight
(
    BrlParticle particle,
    double      heightX, double heightY, double heightZ
) {
    if (particle != nullptr) {
        Particle* partIntern = CastParticle(particle);

        assert(partIntern != nullptr);

        if (partIntern != nullptr) {
            Vector3D h(heightX, heightY, heightZ);

            partIntern->SetHeight(h);
        }
    }
}


double BrlParticleBaseRadius
(
    BrlParticle particle
) {
    double ret = 0.;

    if (particle != nullptr) {
        Particle* partIntern = CastParticle(particle);

        assert(partIntern != nullptr);

        if (partIntern != nullptr)
            ret = partIntern->BaseRadius();
    }

    return ret;
}


void BrlParticleSetBaseRadius
(
    BrlParticle particle,
    double      radius
) {
    if (particle != nullptr) {
        Particle* partIntern = CastParticle(particle);

        assert(partIntern != nullptr);

        if (partIntern != nullptr)
            partIntern->SetBaseRadius(radius);
    }
}


double BrlParticleTopRadius
(
    BrlParticle particle
) {
    double ret = 0.;

    if (particle != nullptr) {
        Particle* partIntern = CastParticle(particle);

        assert(partIntern != nullptr);

        if (partIntern != nullptr)
            ret = partIntern->TopRadius();
    }

    return ret;
}


void BrlParticleSetTopRadius
(
    BrlParticle particle,
    double      radius
) {
    if (particle != nullptr) {
        Particle* partIntern = CastParticle(particle);

        assert(partIntern != nullptr);

        if (partIntern != nullptr)
            partIntern->SetTopRadius(radius);
    }
}


void BrlParticleSet
(
    BrlParticle particle,
    double      baseX,   double baseY,   double baseZ,
    double      heightX, double heightY, double heightZ,
    double      baseRadius,
    double      topRadius
) {
    if (particle != nullptr) {
        Particle* partIntern = CastParticle(particle);

        assert(partIntern != nullptr);

        if (partIntern != nullptr) {
            Vector3D bp(baseX, baseY, baseZ);
            Vector3D h(heightX, heightY, heightZ);

            partIntern->Set(bp, h, baseRadius, topRadius);
        }
    }
}


const char* BrlParticleClassName(void) {
    return Particle::ClassName();
}
