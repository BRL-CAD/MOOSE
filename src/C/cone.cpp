/*                      C O N E . C P P
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
/** @file cone.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      Implements a handle and functions for Cone solid handling
 */

#include <cassert>

#include <brlcad/Database/Cone.h>

#include <brlcad/C/cone.h>

#include "casts.h"


using namespace BRLCAD;


BrlCone BrlNewCone
(
    void
) {
    return new ConeData(new Cone());
}


BrlCone BrlNewConeAsTruncatedGeneralCone
(
    double baseX,               double baseY,               double baseZ,
    double heightX,             double heightY,             double heightZ,
    double semiPrincipalAxisAX, double semiPrincipalAxisAY, double semiPrincipalAxisAZ,
    double semiPrincipalAxisBX, double semiPrincipalAxisBY, double semiPrincipalAxisBZ,
    double ratioCtoA,
    double ratioDtoB
) {
    Vector3D basePoint(baseX, baseY, baseZ);
    Vector3D height(heightX, heightY, heightZ);
    Vector3D semiPrincipalAxisA(semiPrincipalAxisAX, semiPrincipalAxisAY, semiPrincipalAxisAZ);
    Vector3D semiPrincipalAxisB(semiPrincipalAxisBX, semiPrincipalAxisBY, semiPrincipalAxisBZ);

    return new ConeData(new Cone(basePoint, height, semiPrincipalAxisA, semiPrincipalAxisB, ratioCtoA, ratioDtoB));
}


BrlCone BrlNewConeAsTruncatedErectedCone
(
    double baseX,               double baseY,               double baseZ,
    double heightX,             double heightY,             double heightZ,
    double semiPrincipalAxisAX, double semiPrincipalAxisAY, double semiPrincipalAxisAZ,
    double semiPrincipalAxisBX, double semiPrincipalAxisBY, double semiPrincipalAxisBZ,
    double scale
) {
    Vector3D basePoint(baseX, baseY, baseZ);
    Vector3D height(heightX, heightY, heightZ);
    Vector3D semiPrincipalAxisA(semiPrincipalAxisAX, semiPrincipalAxisAY, semiPrincipalAxisAZ);
    Vector3D semiPrincipalAxisB(semiPrincipalAxisBX, semiPrincipalAxisBY, semiPrincipalAxisBZ);

    return new ConeData(new Cone(basePoint, height, semiPrincipalAxisA, semiPrincipalAxisB, scale));
}


BrlCone BrlNewConeAsRightEllipticalCylinder
(
    double baseX,               double baseY,               double baseZ,
    double heightX,             double heightY,             double heightZ,
    double semiPrincipalAxisAX, double semiPrincipalAxisAY, double semiPrincipalAxisAZ,
    double semiPrincipalAxisBX, double semiPrincipalAxisBY, double semiPrincipalAxisBZ
) {
    Vector3D basePoint(baseX, baseY, baseZ);
    Vector3D height(heightX, heightY, heightZ);
    Vector3D semiPrincipalAxisA(semiPrincipalAxisAX, semiPrincipalAxisAY, semiPrincipalAxisAZ);
    Vector3D semiPrincipalAxisB(semiPrincipalAxisBX, semiPrincipalAxisBY, semiPrincipalAxisBZ);

    return new ConeData(new Cone(basePoint, height, semiPrincipalAxisA, semiPrincipalAxisB));
}


BrlCone BrlNewConeAsTruncatedRightCircularCone
(
    double baseX,   double baseY,   double baseZ,
    double heightX, double heightY, double heightZ,
    double radiusBase,
    double radiusTop
) {
    Vector3D basePoint(baseX, baseY, baseZ);
    Vector3D height(heightX, heightY, heightZ);

    return new ConeData(new Cone(basePoint, height, radiusBase, radiusTop));
}


BrlCone BrlNewConeAsRightCircularCylinder
(
    double baseX,   double baseY,   double baseZ,
    double heightX, double heightY, double heightZ,
    double radius
) {
    Vector3D basePoint(baseX, baseY, baseZ);
    Vector3D height(heightX, heightY, heightZ);

    return new ConeData(new Cone(basePoint, height, radius));
}


BrlVector3D BrlConeBasePoint
(
    BrlCone cone
) {
    BrlVector3D ret = nullptr;

    if (cone != nullptr) {
        Cone* cn = CastCone(cone);

        assert(cn != nullptr);

        if (cn != nullptr)
            ret = new Vector3DData(cn->BasePoint());
    }
    return ret;
}


void BrlConeSetBasePoint
(
    BrlCone cone, 
    double  baseX, double baseY, double baseZ
) {
    if (cone != nullptr) {
        Cone* cn = CastCone(cone);

        assert(cn != nullptr);

        if (cn != nullptr) {
            Vector3D basePoint(baseX, baseY, baseZ);

            cn->SetBasePoint(basePoint);
        }
    }
}


BrlVector3D BrlConeHeight
(
    BrlCone cone
) {
    BrlVector3D ret = nullptr;

    if (cone != nullptr) {
        Cone* cn = CastCone(cone);

        assert(cn != nullptr);

        if (cn != nullptr)
            ret = new Vector3DData(cn->Height());
    }
    return ret;
}


void BrlConeSetHeight
(
    BrlCone cone,
    double  heightX, double heightY, double heightZ
) {
    if (cone != nullptr) {
        Cone* cn = CastCone(cone);

        assert(cn != nullptr);

        if (cn != nullptr) {
            Vector3D height(heightX, heightY, heightZ);

            cn->SetHeight(height);
        }
    }
}


BrlVector3D BrlConeSemiPrincipalAxis
(
    BrlCone cone,
    int     index
) {
    BrlVector3D ret = nullptr;

    if (cone != nullptr) {
        Cone* cn = CastCone(cone);

        assert(cn != nullptr);

        if (cn != nullptr)
            ret = new Vector3DData(cn->SemiPrincipalAxis(index));
    }
    return ret;
}


void BrlConeSetSemiPrincipalAxis
(
    BrlCone cone,
    int     index,
    double  axisX, double axisY, double axisZ
) {
    if (cone != nullptr) {
        Cone* cn = CastCone(cone);

        assert(cn != nullptr);

        if (cn != nullptr) {
            Vector3D axis(axisX, axisY, axisZ);

            cn->SetSemiPrincipalAxis(index, axis);
        }
    }
}


void BrlConeSetAsTruncatedGeneralCone
(
    BrlCone cone,
    double  baseX,               double baseY,               double baseZ,
    double  heightX,             double heightY,             double heightZ,
    double  semiPrincipalAxisAX, double semiPrincipalAxisAY, double semiPrincipalAxisAZ,
    double  semiPrincipalAxisBX, double semiPrincipalAxisBY, double semiPrincipalAxisBZ,
    double  ratioCtoA,
    double  ratioDtoB
) {
    if (cone != nullptr) {
        Cone* cn = CastCone(cone);

        assert(cn != nullptr);

        if (cn != nullptr) {
            Vector3D basePoint(baseX, baseY, baseZ);
            Vector3D height(heightX, heightY, heightZ);
            Vector3D semiPrincipalAxisA(semiPrincipalAxisAX, semiPrincipalAxisAY, semiPrincipalAxisAZ);
            Vector3D semiPrincipalAxisB(semiPrincipalAxisBX, semiPrincipalAxisBY, semiPrincipalAxisBZ);

            cn->Set(basePoint, height, semiPrincipalAxisA, semiPrincipalAxisB, ratioCtoA, ratioDtoB);
        }
    }
}


void BrlConeSetAsTruncatedErectedCone
(
    BrlCone cone,
    double  baseX,               double baseY,               double baseZ,
    double  heightX,             double heightY,             double heightZ,
    double  semiPrincipalAxisAX, double semiPrincipalAxisAY, double semiPrincipalAxisAZ,
    double  semiPrincipalAxisBX, double semiPrincipalAxisBY, double semiPrincipalAxisBZ,
    double  scale
) {
    if (cone != nullptr) {
        Cone* cn = CastCone(cone);

        assert(cn != nullptr);

        if (cn != nullptr) {
            Vector3D basePoint(baseX, baseY, baseZ);
            Vector3D height(heightX, heightY, heightZ);
            Vector3D semiPrincipalAxisA(semiPrincipalAxisAX, semiPrincipalAxisAY, semiPrincipalAxisAZ);
            Vector3D semiPrincipalAxisB(semiPrincipalAxisBX, semiPrincipalAxisBY, semiPrincipalAxisBZ);

            cn->Set(basePoint, height, semiPrincipalAxisA, semiPrincipalAxisB, scale);
        }
    }
}


void BrlConeSetAsRightEllipticalCylinder
(
    BrlCone cone,
    double  baseX,               double baseY,               double baseZ,
    double  heightX,             double heightY,             double heightZ,
    double  semiPrincipalAxisAX, double semiPrincipalAxisAY, double semiPrincipalAxisAZ,
    double  semiPrincipalAxisBX, double semiPrincipalAxisBY, double semiPrincipalAxisBZ
) {
    if (cone != nullptr) {
        Cone* cn = CastCone(cone);

        assert(cn != nullptr);

        if (cn != nullptr) {
            Vector3D basePoint(baseX, baseY, baseZ);
            Vector3D height(heightX, heightY, heightZ);
            Vector3D semiPrincipalAxisA(semiPrincipalAxisAX, semiPrincipalAxisAY, semiPrincipalAxisAZ);
            Vector3D semiPrincipalAxisB(semiPrincipalAxisBX, semiPrincipalAxisBY, semiPrincipalAxisBZ);

            cn->Set(basePoint, height, semiPrincipalAxisA, semiPrincipalAxisB);
        }
    }
}


void BrlConeSetAsTruncatedRightCircularCone
(
    BrlCone cone,
    double  baseX,   double baseY,   double baseZ,
    double  heightX, double heightY, double heightZ,
    double  radiusBase,
    double  radiusTop
) {
    if (cone != nullptr) {
        Cone* cn = CastCone(cone);

        assert(cn != nullptr);

        if (cn != nullptr) {
            Vector3D basePoint(baseX, baseY, baseZ);
            Vector3D height(heightX, heightY, heightZ);

            cn->Set(basePoint, height, radiusBase, radiusTop);
        }
    }
}


void BrlConeSetAsRightCircularCylinder
(
    BrlCone cone,
    double  baseX,   double baseY,   double baseZ,
    double  heightX, double heightY, double heightZ,
    double  radius
) {
    if (cone != nullptr) {
        Cone* cn = CastCone(cone);

        assert(cn != nullptr);

        if (cn != nullptr) {
            Vector3D basePoint(baseX, baseY, baseZ);
            Vector3D height(heightX, heightY, heightZ);

            cn->Set(basePoint, height, radius);
        }
    }
}
