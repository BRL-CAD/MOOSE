/*          P A R A B O L I C C Y L I N D E R . C P P
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
/** @file parabolicCylinder.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements a handle and functions for ParabolicCylinder solid handling
 */

#include <cassert>

#include <brlcad/Database/ParabolicCylinder.h>

#include <brlcad/C/parabolicCylinder.h>

#include "casts.h"


using namespace BRLCAD;


BrlParabolicCylinder BrlNewParabolicCylinder(void) {
    return DowncastObject(new ParabolicCylinder());
}


BrlParabolicCylinder BrlNewParabolicCylinderAsParabolicCylinder
(
    double               baseX,
    double               baseY,
    double               baseZ,
    double               heightX,
    double               heightY,
    double               heightZ,
    double               depthX,
    double               depthY,
    double               depthZ,
    double               halfWidth
) {
    Vector3D bp(baseX, baseY, baseZ);
    Vector3D h(heightX, heightY, heightZ);
    Vector3D d(depthX, depthY, depthZ);

    return new ParabolicCylinderData(new ParabolicCylinder(bp, h, d, halfWidth));
}


BrlVector3D BrlParabolicCylinderBasePoint
(
    BrlParabolicCylinder parabolicCylinder
) {
    BrlVector3D ret = nullptr;

    if (parabolicCylinder != nullptr) {
        ParabolicCylinder* paraIntern = CastParabolicCylinder(parabolicCylinder);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr)
            ret = new Vector3DData(paraIntern->BasePoint());
    }

    return ret;
}


void BrlParabolicCylinderSetBasePoint
(
    BrlParabolicCylinder parabolicCylinder,
    double               baseX,
    double               baseY,
    double               baseZ
) {
    if (parabolicCylinder != nullptr) {
        ParabolicCylinder* paraIntern = CastParabolicCylinder(parabolicCylinder);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr) {
            Vector3D bp(baseX, baseY, baseZ);

            paraIntern->SetBasePoint(bp);
        }
    }
}


BrlVector3D BrlParabolicCylinderHeight
(
    BrlParabolicCylinder parabolicCylinder
) {
    BrlVector3D ret = nullptr;

    if (parabolicCylinder != nullptr) {
        ParabolicCylinder* paraIntern = CastParabolicCylinder(parabolicCylinder);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr)
            ret = new Vector3DData(paraIntern->Height());
    }

    return ret;
}


void BrlParabolicCylinderSetHeight
(
    BrlParabolicCylinder parabolicCylinder,
    double               heightX,
    double               heightY,
    double               heightZ
) {
    if (parabolicCylinder != nullptr) {
        ParabolicCylinder* paraIntern = CastParabolicCylinder(parabolicCylinder);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr) {
            Vector3D h(heightX, heightY, heightZ);

            paraIntern->SetHeight(h);
        }
    }
}


BrlVector3D BrlParabolicCylinderDepth
(
    BrlParabolicCylinder parabolicCylinder
) {
    BrlVector3D ret = nullptr;

    if (parabolicCylinder != nullptr) {
        ParabolicCylinder* paraIntern = CastParabolicCylinder(parabolicCylinder);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr)
            ret = new Vector3DData(paraIntern->Depth());
    }

    return ret;
}


void BrlParabolicCylinderSetDepth
(
    BrlParabolicCylinder parabolicCylinder,
    double               depthX,
    double               depthY,
    double               depthZ
) {
    if (parabolicCylinder != nullptr) {
        ParabolicCylinder* paraIntern = CastParabolicCylinder(parabolicCylinder);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr) {
            Vector3D d(depthX, depthY, depthZ);

            paraIntern->SetDepth(d);
        }
    }
}


double BrlParabolicCylinderHalfWidth
(
    BrlParabolicCylinder parabolicCylinder
) {
    double ret = 0.0;

    if (parabolicCylinder != nullptr) {
        ParabolicCylinder* paraIntern = CastParabolicCylinder(parabolicCylinder);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr)
            ret = paraIntern->HalfWidth();
    }

    return ret;
}


void BrlParabolicCylinderSetHalfWidth
(
    BrlParabolicCylinder parabolicCylinder,
    double               halfWidth
) {
    if (parabolicCylinder != nullptr) {
        ParabolicCylinder* paraIntern = CastParabolicCylinder(parabolicCylinder);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr)
            paraIntern->SetHalfWidth(halfWidth);
    }
}


void BrlParabolicCylinderSet
(
    BrlParabolicCylinder parabolicCylinder,
    double               baseX,
    double               baseY,
    double               baseZ,
    double               heightX,
    double               heightY,
    double               heightZ,
    double               depthX,
    double               depthY,
    double               depthZ,
    double               halfWidth
) {
    if (parabolicCylinder != nullptr) {
        ParabolicCylinder* paraIntern = CastParabolicCylinder(parabolicCylinder);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr) {
            Vector3D bp(baseX, baseY, baseZ);
            Vector3D h(heightX, heightY, heightZ);
            Vector3D d(depthX, depthY, depthZ);

            paraIntern->Set(bp, h, d, halfWidth);
        }
    }
}


const char* BrlParabolicCylinderClassName(void) {
    return ParabolicCylinder::ClassName();
}
