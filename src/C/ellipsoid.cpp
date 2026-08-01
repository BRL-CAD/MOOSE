/*                      E L L I P S O I D . C P P
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
/** @file ellipsoid.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      Implements a handle and functions for Ellipsoid solid handling
 */

#include <cassert>

#include <brlcad/Database/Ellipsoid.h>

#include <brlcad/C/ellipsoid.h>

#include "casts.h"


using namespace BRLCAD;


BrlEllipsoid BrlNewEllipsoid(void) {
    return new EllipsoidData(new Ellipsoid());
}


BrlEllipsoid BrlNewEllipsoidAsGeneralEllipsoid
(
    double centerX,             double centerY,             double centerZ,
    double semiPrincipalAxisAX, double semiPrincipalAxisAY, double semiPrincipalAxisAZ,
    double semiPrincipalAxisBX, double semiPrincipalAxisBY, double semiPrincipalAxisBZ,
    double semiPrincipalAxisCX, double semiPrincipalAxisCY, double semiPrincipalAxisCZ
) {
    Vector3D center(centerX, centerY, centerZ);
    Vector3D semiPrincipalAxisA(semiPrincipalAxisAX, semiPrincipalAxisAY, semiPrincipalAxisAZ);
    Vector3D semiPrincipalAxisB(semiPrincipalAxisBX, semiPrincipalAxisBY, semiPrincipalAxisBZ);
    Vector3D semiPrincipalAxisC(semiPrincipalAxisCX, semiPrincipalAxisCY, semiPrincipalAxisCZ);

    return new EllipsoidData(new Ellipsoid(center, semiPrincipalAxisA, semiPrincipalAxisB, semiPrincipalAxisC));
}


BrlEllipsoid BrlNewEllipsoidAsEllipsoid1
(
    double centerX,            double centerY,            double centerZ,
    double semiPrincipalAxisX, double semiPrincipalAxisY, double semiPrincipalAxisZ,
    double radius
) {
    Vector3D center(centerX, centerY, centerZ);
    Vector3D semiPrincipalAxis(semiPrincipalAxisX, semiPrincipalAxisY, semiPrincipalAxisZ);

    return new EllipsoidData(new Ellipsoid(center, semiPrincipalAxis, radius));
}


BrlEllipsoid BrlNewEllipsoidAsSphere
(
    double centerX, double centerY, double centerZ,
    double radius
) {
    Vector3D center(centerX, centerY, centerZ);

    return new EllipsoidData(new Ellipsoid(center, radius));
}


BrlVector3D BrlEllipsoidCenter
(
    BrlEllipsoid ellipsoid
) {
    BrlVector3D ret = nullptr;

    if (ellipsoid != nullptr) {
        Ellipsoid* ell = CastEllipsoid(ellipsoid);

        assert(ell != nullptr);

        if (ell != nullptr)
            ret = new Vector3DData(ell->Center());
    }
    return ret;
}


void BrlEllipsoidSetCenter
(
    BrlEllipsoid ellipsoid,
    double       centerX, double centerY, double centerZ
) {
    if (ellipsoid != nullptr) {
        Ellipsoid* ell = CastEllipsoid(ellipsoid);

        assert(ell != nullptr);

        if (ell != nullptr) {
            Vector3D center(centerX, centerY, centerZ);

            ell->SetCenter(center);
        }
    }
}


BrlVector3D BrlEllipsoidSemiPrincipalAxis
(
    BrlEllipsoid ellipsoid,
    int          index
) {
    BrlVector3D ret = nullptr;

    if (ellipsoid != nullptr) {
        Ellipsoid* ell = CastEllipsoid(ellipsoid);

        assert(ell != nullptr);

        if (ell != nullptr)
            ret = new Vector3DData(ell->SemiPrincipalAxis(index));
    }
    return ret;
}


void BrlEllipsoidSetSemiPrincipalAxis
(
    BrlEllipsoid ellipsoid,
    int          index,
    double       axisX, double axisY, double axisZ
) {
    if (ellipsoid != nullptr) {
        Ellipsoid* ell = CastEllipsoid(ellipsoid);

        assert(ell != nullptr);

        if (ell != nullptr) {
            Vector3D axis(axisX, axisY, axisZ);

            ell->SetSemiPrincipalAxis(index, axis);
        }
    }
}


void BrlEllipsoidSetAsGeneralEllipsoid
(
    BrlEllipsoid ellipsoid,
    double       centerX,             double centerY,             double centerZ,
    double       semiPrincipalAxisAX, double semiPrincipalAxisAY, double semiPrincipalAxisAZ,
    double       semiPrincipalAxisBX, double semiPrincipalAxisBY, double semiPrincipalAxisBZ,
    double       semiPrincipalAxisCX, double semiPrincipalAxisCY, double semiPrincipalAxisCZ
) {
    if (ellipsoid != nullptr) {
        Ellipsoid* ell = CastEllipsoid(ellipsoid);

        assert(ell != nullptr);

        if (ell != nullptr) {
            Vector3D center(centerX, centerY, centerZ);
            Vector3D a(semiPrincipalAxisAX, semiPrincipalAxisAY, semiPrincipalAxisAZ);
            Vector3D b(semiPrincipalAxisBX, semiPrincipalAxisBY, semiPrincipalAxisBZ);
            Vector3D c(semiPrincipalAxisCX, semiPrincipalAxisCY, semiPrincipalAxisCZ);

            ell->Set(center, a, b, c);
        }
    }
}


void BrlEllipsoidSetAsEllipsoid1
(
    BrlEllipsoid ellipsoid,
    double       centerX,            double centerY,            double centerZ,
    double       semiPrincipalAxisX, double semiPrincipalAxisY, double semiPrincipalAxisZ,
    double       radius
) {
    if (ellipsoid != nullptr) {
        Ellipsoid* ell = CastEllipsoid(ellipsoid);

        assert(ell != nullptr);

        if (ell != nullptr) {
            Vector3D center(centerX, centerY, centerZ);
            Vector3D axis(semiPrincipalAxisX, semiPrincipalAxisY, semiPrincipalAxisZ);

            ell->Set(center, axis, radius);
        }
    }
}


void BrlEllipsoidSetFocals
(
    BrlEllipsoid ellipsoid,
    double       focalAX, double focalAY, double focalAZ,
    double       focalBX, double focalBY, double focalBZ,
    double       majorAxisLength
) {
    if (ellipsoid != nullptr) {
        Ellipsoid* ell = CastEllipsoid(ellipsoid);

        assert(ell != nullptr);

        if (ell != nullptr) {
            Vector3D focalA(focalAX, focalAY, focalAZ);
            Vector3D focalB(focalBX, focalBY, focalBZ);

            ell->SetFocals(focalA, focalB, majorAxisLength);
        }
    }
}


void BrlEllipsoidSetSphere
(
    BrlEllipsoid ellipsoid,
    double       centerX, double centerY, double centerZ,
    double       radius
) {
    if (ellipsoid != nullptr) {
        Ellipsoid* ell = CastEllipsoid(ellipsoid);

        assert(ell != nullptr);

        if (ell != nullptr) {
            Vector3D center(centerX, centerY, centerZ);

            ell->SetSphere(center, radius);
        }
    }
}


const char* BrlEllipsoidClassName(void) {
  return Ellipsoid::ClassName();
}
