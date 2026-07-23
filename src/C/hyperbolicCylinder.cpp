/*                      H Y P E R B O L I C C Y L I N D E R . C P P
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
/** @file hyperbolicCylinder.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements a handle and functions for HyperbolicCylinder solid handling
 */

#include <cassert>

#include <brlcad/Database/HyperbolicCylinder.h>

#include <brlcad/C/hyperbolicCylinder.h>

#include "BrlData.h"

#include "casts.h"


using namespace BRLCAD;


BrlHyperbolicCylinder BrlNewHyperbolicCylinder(void) {
    return new HyperbolicCylinderData(new HyperbolicCylinder());
}


BrlHyperbolicCylinder BrlNewHyperbolicCylinderAsHyperbolicCylinder
(
    double basePointX,    double basePointY,    double basePointZ,
    double heightX,       double heightY,       double heightZ,
    double depthX,        double depthY,        double depthZ,
    double halfWidth,
    double apexAsymptoteDistance
) {
    Vector3D basePoint(basePointX, basePointY, basePointZ);
    Vector3D height(heightX, heightY, heightZ);
    Vector3D depth(depthX, depthY, depthZ);

    return new HyperbolicCylinderData(new HyperbolicCylinder(basePoint, height, depth, halfWidth, apexAsymptoteDistance));
}


BrlVector3D BrlHyperbolicCylinderBasePoint
(
    BrlHyperbolicCylinder hyperbolicCylinder
) {
    BrlVector3D ret = nullptr;

    if (hyperbolicCylinder != nullptr) {
        HyperbolicCylinder* hc = CastHyperbolicCylinder(hyperbolicCylinder);

        assert(hc != nullptr);

        if (hc != nullptr)
            ret = new Vector3DData(hc->BasePoint());
    }

    return ret;
}


void BrlHyperbolicCylinderSetBasePoint
(
    BrlHyperbolicCylinder hyperbolicCylinder,
    double                basePointX,       double basePointY,       double basePointZ
) {
    if (hyperbolicCylinder != nullptr) {
        HyperbolicCylinder* hc = CastHyperbolicCylinder(hyperbolicCylinder);

        assert(hc != nullptr);

        if (hc != nullptr) {
            Vector3D basePoint(basePointX, basePointY, basePointZ);

            hc->SetBasePoint(basePoint);
        }
    }
}


BrlVector3D BrlHyperbolicCylinderHeight
(
    BrlHyperbolicCylinder hyperbolicCylinder
) {
    BrlVector3D ret = nullptr;

    if (hyperbolicCylinder != nullptr) {
        HyperbolicCylinder* hc = CastHyperbolicCylinder(hyperbolicCylinder);

        assert(hc != nullptr);

        if (hc != nullptr)
            ret = new Vector3DData(hc->Height());
    }

    return ret;
}


void BrlHyperbolicCylinderSetHeight
(
    BrlHyperbolicCylinder hyperbolicCylinder,
    double                heightX,          double heightY,       double heightZ
) {
    if (hyperbolicCylinder != nullptr) {
        HyperbolicCylinder* hc = CastHyperbolicCylinder(hyperbolicCylinder);

        assert(hc != nullptr);

        if (hc != nullptr) {
            Vector3D height(heightX, heightY, heightZ);

            hc->SetHeight(height);
        }
    }
}


BrlVector3D BrlHyperbolicCylinderDepth
(
    BrlHyperbolicCylinder hyperbolicCylinder
) {
    BrlVector3D ret = nullptr;

    if (hyperbolicCylinder != nullptr) {
        HyperbolicCylinder* hc = CastHyperbolicCylinder(hyperbolicCylinder);

        assert(hc != nullptr);

        if (hc != nullptr)
            ret = new Vector3DData(hc->Depth());
    }

    return ret;
}


void BrlHyperbolicCylinderSetDepth
(
    BrlHyperbolicCylinder hyperbolicCylinder,
    double                depthX,       double depthY,      double depthZ
) {
    if (hyperbolicCylinder != nullptr) {
        HyperbolicCylinder* hc = CastHyperbolicCylinder(hyperbolicCylinder);

        assert(hc != nullptr);

        if (hc != nullptr) {
            Vector3D depth(depthX, depthY, depthZ);

            hc->SetDepth(depth);
        }
    }
}


double BrlHyperbolicCylinderHalfWidth
(
    BrlHyperbolicCylinder hyperbolicCylinder
) {
    double ret = 0.0;

    if (hyperbolicCylinder != nullptr) {
        HyperbolicCylinder* hc = CastHyperbolicCylinder(hyperbolicCylinder);

        assert(hc != nullptr);

        if (hc != nullptr)
            ret = hc->HalfWidth();
    }

    return ret;
}


void BrlHyperbolicCylinderSetHalfWidth
(
    BrlHyperbolicCylinder hyperbolicCylinder,
    double                halfWidth
) {
    if (hyperbolicCylinder != nullptr) {
        HyperbolicCylinder* hc = CastHyperbolicCylinder(hyperbolicCylinder);

        assert(hc != nullptr);

        if (hc != nullptr)
            hc->SetHalfWidth(halfWidth);
    }
}


double BrlHyperbolicCylinderApexAsymptoteDistance
(
    BrlHyperbolicCylinder hyperbolicCylinder
) {
    double ret = 0.0;

    if (hyperbolicCylinder != nullptr) {
        HyperbolicCylinder* hc = CastHyperbolicCylinder(hyperbolicCylinder);

        assert(hc != nullptr);

        if (hc != nullptr)
            ret = hc->ApexAsymptoteDistance();
    }

    return ret;
}


void BrlHyperbolicCylinderSetApexAsymptoteDistance
(
    BrlHyperbolicCylinder hyperbolicCylinder,
    double                apexAsymptoteDistance
) {
    if (hyperbolicCylinder != nullptr) {
        HyperbolicCylinder* hc = CastHyperbolicCylinder(hyperbolicCylinder);

        assert(hc != nullptr);

        if (hc != nullptr)
            hc->SetApexAsymptoteDistance(apexAsymptoteDistance);
    }
}


void BrlHyperbolicCylinderSet
(
    BrlHyperbolicCylinder hyperbolicCylinder,
    double                basePointX,    double basePointY,    double basePointZ,
    double                heightX,       double heightY,       double heightZ,
    double                depthX,        double depthY,        double depthZ,
    double                halfWidth,     double apexAsymptoteDistance
) {
    if (hyperbolicCylinder != nullptr) {
        HyperbolicCylinder* hc = CastHyperbolicCylinder(hyperbolicCylinder);

        assert(hc != nullptr);

        if (hc != nullptr) {
            Vector3D basePoint(basePointX, basePointY, basePointZ);
            Vector3D height(heightX, heightY, heightZ);
            Vector3D depth(depthX, depthY, depthZ);

            hc->Set(basePoint, height, depth, halfWidth, apexAsymptoteDistance);
        }
    }
}


const char* BrlHyperbolicCylinderClassName(void) {
    return HyperbolicCylinder::ClassName();
}
