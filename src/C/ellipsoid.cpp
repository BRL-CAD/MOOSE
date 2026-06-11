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

#include "BrlData.h"

#include "casts.h"


using namespace BRLCAD;


BrlEllipsoid BrlNewEllipsoid
(
    void
) {
    return new EllipsoidData(new Ellipsoid());
}


BrlEllipsoid BrlNewEllipsoidFromAxis
(
    double centerX, double centerY, double centerZ,
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


BrlEllipsoid BrlNewEllipsoidAsEllipsoidHyperboloid
(
    double centerX, double centerY, double centerZ,
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
        BrlData* data = CastHandle(ellipsoid);
        assert(data != nullptr);
        if (data != nullptr && data->Magic() == EllipsoidMagic) {
            Vector3D center = static_cast<EllipsoidData*>(data)->Pointer()->Center();
            ret = new Vector3DData(center);
        }
    }
    return ret;
}


void BrlEllipsoidSetCenter
(
    BrlEllipsoid ellipsoid, 
    double centerX, double centerY, double centerZ
) {
    if (ellipsoid != nullptr) {
        BrlData* data = CastHandle(ellipsoid);
        assert(data != nullptr);
        if (data != nullptr && data->Magic() == EllipsoidMagic) {
            Vector3D cpp_center(centerX, centerY, centerZ);
            static_cast<EllipsoidData*>(data)->Pointer()->SetCenter(cpp_center);
        }
    }
}


BrlVector3D BrlEllipsoidSemiPrincipalAxis
(
    BrlEllipsoid ellipsoid, 
    int index
) {
    BrlVector3D ret = nullptr;
    if (ellipsoid != nullptr) {
        BrlData* data = CastHandle(ellipsoid);
        assert(data != nullptr);
        if (data != nullptr && data->Magic() == EllipsoidMagic) {
            Vector3D semiPrincipalAxis = static_cast<EllipsoidData*>(data)->Pointer()->SemiPrincipalAxis(index);
            ret = new Vector3DData(semiPrincipalAxis);
        }
    }
    return ret;
}


void BrlEllipsoidSetSemiPrincipalAxis
(
    BrlEllipsoid ellipsoid, 
    int index, 
    double axisX, double axisY, double axisZ
) {
    if (ellipsoid != nullptr) {
        BrlData* data = CastHandle(ellipsoid);
        assert(data != nullptr);
        if (data != nullptr && data->Magic() == EllipsoidMagic) {
            Vector3D cpp_axis(axisX, axisY, axisZ);
            static_cast<EllipsoidData*>(data)->Pointer()->SetSemiPrincipalAxis(index, cpp_axis);
        }
    }
}


void BrlEllipsoidSet
(
    BrlEllipsoid ellipsoid,
    double centerX, double centerY, double centerZ,
    double semiPrincipalAxisAX, double semiPrincipalAxisAY, double semiPrincipalAxisAZ,
    double semiPrincipalAxisBX, double semiPrincipalAxisBY, double semiPrincipalAxisBZ,
    double semiPrincipalAxisCX, double semiPrincipalAxisCY, double semiPrincipalAxisCZ
) {
    if (ellipsoid != nullptr) {
        BrlData* data = CastHandle(ellipsoid);
        assert(data != nullptr);
        if (data != nullptr && data->Magic() == EllipsoidMagic) {
            Vector3D cpp_center(centerX, centerY, centerZ);
            Vector3D cpp_a(semiPrincipalAxisAX, semiPrincipalAxisAY, semiPrincipalAxisAZ);
            Vector3D cpp_b(semiPrincipalAxisBX, semiPrincipalAxisBY, semiPrincipalAxisBZ);
            Vector3D cpp_c(semiPrincipalAxisCX, semiPrincipalAxisCY, semiPrincipalAxisCZ);
            static_cast<EllipsoidData*>(data)->Pointer()->Set(cpp_center, cpp_a, cpp_b, cpp_c);
        }
    }
}


void BrlEllipsoidSetFocals
(
    BrlEllipsoid ellipsoid,
    double focalAX, double focalAY, double focalAZ,
    double focalBX, double focalBY, double focalBZ,
    double          majorAxisLength
) {
    if (ellipsoid != nullptr) {
        BrlData* data = CastHandle(ellipsoid);
        assert(data != nullptr);
        if (data != nullptr && data->Magic() == EllipsoidMagic) {
            Vector3D cpp_focalA(focalAX, focalAY, focalAZ);
            Vector3D cpp_focalB(focalBX, focalBY, focalBZ);
            static_cast<EllipsoidData*>(data)->Pointer()->SetFocals(cpp_focalA, cpp_focalB, majorAxisLength);
        }
    }
}


void BrlEllipsoidSetSphere
(
    BrlEllipsoid ellipsoid,
    double centerX, double centerY, double centerZ,
    double          radius
) {
    if (ellipsoid != nullptr) {
        BrlData* data = CastHandle(ellipsoid);
        assert(data != nullptr);
        if (data != nullptr && data->Magic() == EllipsoidMagic) {
            Vector3D cpp_center(centerX, centerY, centerZ);
            static_cast<EllipsoidData*>(data)->Pointer()->SetSphere(cpp_center, radius);
        }
    }
}
