/*                      T O R U S . C P P
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
/** @file torus.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements a handle and functions for Torus solid handling
 */

#include <cassert>

#include <brlcad/Database/Torus.h>

#include <brlcad/C/torus.h>

#include "BrlData.h"

#include "casts.h"


using namespace BRLCAD;


BrlTorus BrlNewTorus(void) {
    return new TorusData(new Torus());
}


BrlTorus BrlNewTorusAsTorus
(
    double centerX, double centerY, double centerZ,
    double normalX, double normalY, double normalZ,
    double tubeCenterLineRadius,
    double tubeRadius
) {
    Vector3D center(centerX, centerY, centerZ);
    Vector3D normal(normalX, normalY, normalZ);

    return new TorusData(new Torus(center, normal, tubeCenterLineRadius, tubeRadius));
}


BrlVector3D BrlTorusCenter
(
    BrlTorus torus
) {
    BrlVector3D ret = nullptr;

    if (torus != nullptr) {
        Torus* t = CastTorus(torus);

        assert(t != nullptr);

        if (t != nullptr)
            ret = new Vector3DData(t->Center());
    }

    return ret;
}


void BrlTorusSetCenter
(
    BrlTorus torus,
    double   centerX, double centerY, double centerZ
) {
    if (torus != nullptr) {
        Torus* t = CastTorus(torus);

        assert(t != nullptr);

        if (t != nullptr) {
            Vector3D center(centerX, centerY, centerZ);

            t->SetCenter(center);
        }
    }
}


BrlVector3D BrlTorusNormal
(
    BrlTorus torus
) {
    BrlVector3D ret = nullptr;

    if (torus != nullptr) {
        Torus* t = CastTorus(torus);

        assert(t != nullptr);

        if (t != nullptr)
            ret = new Vector3DData(t->Normal());
    }

    return ret;
}


void BrlTorusSetNormal
(
    BrlTorus torus,
    double   normalX, double normalY, double normalZ
) {
    if (torus != nullptr) {
        Torus* t = CastTorus(torus);

        assert(t != nullptr);

        if (t != nullptr) {
            Vector3D normal(normalX, normalY, normalZ);

            t->SetNormal(normal);
        }
    }
}


double BrlTorusTubeCenterLineRadius
(
    BrlTorus torus
) {
    double ret = 0.0;

    if (torus != nullptr) {
        Torus* t = CastTorus(torus);

        assert(t != nullptr);

        if (t != nullptr)
            ret = t->TubeCenterLineRadius();
    }

    return ret;
}


void BrlTorusSetTubeCenterLineRadius
(
    BrlTorus torus,
    double   radius
) {
    if (torus != nullptr) {
        Torus* t = CastTorus(torus);

        assert(t != nullptr);

        if (t != nullptr)
            t->SetTubeCenterLineRadius(radius);
    }
}


double BrlTorusTubeRadius
(
    BrlTorus torus
) {
    double ret = 0.0;

    if (torus != nullptr) {
        Torus* t = CastTorus(torus);

        assert(t != nullptr);

        if (t != nullptr)
            ret = t->TubeRadius();
    }

    return ret;
}


void BrlTorusSetTubeRadius
(
    BrlTorus torus,
    double   radius
) {
    if (torus != nullptr) {
        Torus* t = CastTorus(torus);

        assert(t != nullptr);

        if (t != nullptr)
            t->SetTubeRadius(radius);
    }
}


void BrlTorusSet
(
    BrlTorus torus,
    double   centerX, double centerY, double centerZ,
    double   normalX, double normalY, double normalZ,
    double   tubeCenterLineRadius,
    double   tubeRadius
) {
    if (torus != nullptr) {
        Torus* t = CastTorus(torus);

        assert(t != nullptr);

        if (t != nullptr) {
            Vector3D center(centerX, centerY, centerZ);
            Vector3D normal(normalX, normalY, normalZ);

            t->Set(center, normal, tubeCenterLineRadius, tubeRadius);
        }
    }
}


const char* BrlTorusClassName(void) {
    return Torus::ClassName();
}
