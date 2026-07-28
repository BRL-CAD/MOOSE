/*                      H A L F S P A C E . C P P
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
/** @file halfspace.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements a handle and functions for Halfspace solid handling
 */

#include <cassert>

#include <brlcad/Database/Halfspace.h>

#include <brlcad/C/halfspace.h>

#include "BrlData.h"

#include "casts.h"


using namespace BRLCAD;


BrlObject BrlNewHalfspace(void) {
    return DowncastObject(new Halfspace());
}


BrlObject BrlNewHalfspaceAsHalfspace
(
    double normalX, double normalY, double normalZ,
    double distance
) {
    Vector3D normal(normalX, normalY, normalZ);

    return new HalfspaceData(new Halfspace(normal, distance));
}


BrlVector3D BrlHalfspaceNormal
(
    BrlObject halfspace
) {
    BrlVector3D ret = nullptr;

    if (halfspace != nullptr) {
        Halfspace* halfIntern = CastHalfspace(halfspace);

        assert(halfIntern != nullptr);

        if (halfIntern != nullptr)
            ret = new Vector3DData(halfIntern->Normal());
    }

    return ret;
}


void BrlHalfspaceSetNormal
(
    BrlObject halfspace,
    double    normalX, double normalY, double normalZ
) {
    if (halfspace != nullptr) {
        Halfspace* halfIntern = CastHalfspace(halfspace);

        assert(halfIntern != nullptr);

        if (halfIntern != nullptr) {
            Vector3D normal(normalX, normalY, normalZ);

            halfIntern->SetNormal(normal);
        }
    }
}


double BrlHalfspaceDistanceFromOrigin
(
    BrlObject halfspace
) {
    double ret = 0.0;

    if (halfspace != nullptr) {
        Halfspace* halfIntern = CastHalfspace(halfspace);

        assert(halfIntern != nullptr);

        if (halfIntern != nullptr)
            ret = halfIntern->DistanceFromOrigin();
    }

    return ret;
}


void BrlHalfspaceSetDistanceFromOrigin
(
    BrlObject halfspace,
    double    distance
) {
    if (halfspace != nullptr) {
        Halfspace* halfIntern = CastHalfspace(halfspace);

        assert(halfIntern != nullptr);

        if (halfIntern != nullptr)
            halfIntern->SetDistanceFromOrigin(distance);
    }
}


void BrlHalfspaceSet
(
    BrlObject halfspace,
    double    normalX, double normalY, double normalZ,
    double    distance
) {
    if (halfspace != nullptr) {
        Halfspace* halfIntern = CastHalfspace(halfspace);

        assert(halfIntern != nullptr);

        if (halfIntern != nullptr) {
            Vector3D normal(normalX, normalY, normalZ);

            halfIntern->Set(normal, distance);
        }
    }
}


const char* BrlHalfspaceClassName(void) {
    return Halfspace::ClassName();
}
