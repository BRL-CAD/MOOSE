/*                          E L L I P T I C A L T O R U S . C P P
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
/** @file ellipticalTorus.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements a handle and functions for EllipticalTorus solid handling
 */

#include <cassert>

#include <brlcad/Database/EllipticalTorus.h>

#include <brlcad/C/ellipticalTorus.h>

#include "BrlData.h"

#include "casts.h"


using namespace BRLCAD;


BrlEllipticalTorus BrlNewEllipticalTorus(void) {
    return new EllipticalTorusData(new EllipticalTorus());
}


BrlEllipticalTorus BrlNewEllipticalTorusAsEllipticalTorus
(
    double centerX,            double centerY,            double centerZ,
    double normalX,            double normalY,            double normalZ,
    double tubeCenterLineRadius,
    double tubeSemiMajorAxisX, double tubeSemiMajorAxisY, double tubeSemiMajorAxisZ,
    double tubeSemiMinorAxisLength
) {
    Vector3D center(centerX, centerY, centerZ);
    Vector3D normal(normalX, normalY, normalZ);
    Vector3D tubeSemiMajorAxis(tubeSemiMajorAxisX, tubeSemiMajorAxisY, tubeSemiMajorAxisZ);

    return new EllipticalTorusData(new EllipticalTorus(center, normal, tubeCenterLineRadius, tubeSemiMajorAxis, tubeSemiMinorAxisLength));
}


BrlVector3D BrlEllipticalTorusCenter
(
    BrlEllipticalTorus ellipticalTorus
) {
    BrlVector3D ret = nullptr;

    if (ellipticalTorus != nullptr) {
        EllipticalTorus* et = CastEllipticalTorus(ellipticalTorus);

        assert(et != nullptr);

        if (et != nullptr)
            ret = new Vector3DData(et->Center());
    }

    return ret;
}


void BrlEllipticalTorusSetCenter
(
    BrlEllipticalTorus ellipticalTorus,
    double             centerX, double centerY, double centerZ
) {
    if (ellipticalTorus != nullptr) {
        EllipticalTorus* et = CastEllipticalTorus(ellipticalTorus);

        assert(et != nullptr);

        if (et != nullptr) {
            Vector3D center(centerX, centerY, centerZ);

            et->SetCenter(center);
        }
    }
}


BrlVector3D BrlEllipticalTorusNormal
(
    BrlEllipticalTorus ellipticalTorus
) {
    BrlVector3D ret = nullptr;

    if (ellipticalTorus != nullptr) {
        EllipticalTorus* et = CastEllipticalTorus(ellipticalTorus);

        assert(et != nullptr);

        if (et != nullptr)
            ret = new Vector3DData(et->Normal());
    }

    return ret;
}


void BrlEllipticalTorusSetNormal
(
    BrlEllipticalTorus ellipticalTorus,
    double             normalX, double normalY, double normalZ
) {
    if (ellipticalTorus != nullptr) {
        EllipticalTorus* et = CastEllipticalTorus(ellipticalTorus);

        assert(et != nullptr);

        if (et != nullptr) {
            Vector3D normal(normalX, normalY, normalZ);

            et->SetNormal(normal);
        }
    }
}


double BrlEllipticalTorusTubeCenterLineRadius
(
    BrlEllipticalTorus ellipticalTorus
) {
    double ret = 0.0;

    if (ellipticalTorus != nullptr) {
        EllipticalTorus* et = CastEllipticalTorus(ellipticalTorus);

        assert(et != nullptr);

        if (et != nullptr)
            ret = et->TubeCenterLineRadius();
    }

    return ret;
}


void BrlEllipticalTorusSetTubeCenterLineRadius
(
    BrlEllipticalTorus ellipticalTorus,
    double             radius
) {
    if (ellipticalTorus != nullptr) {
        EllipticalTorus* et = CastEllipticalTorus(ellipticalTorus);

        assert(et != nullptr);

        if (et != nullptr)
            et->SetTubeCenterLineRadius(radius);
    }
}


BrlVector3D BrlEllipticalTorusTubeSemiMajorAxis
(
    BrlEllipticalTorus ellipticalTorus
) {
    BrlVector3D ret = nullptr;

    if (ellipticalTorus != nullptr) {
        EllipticalTorus* et = CastEllipticalTorus(ellipticalTorus);

        assert(et != nullptr);

        if (et != nullptr)
            ret = new Vector3DData(et->TubeSemiMajorAxis());
    }

    return ret;
}


void BrlEllipticalTorusSetTubeSemiMajorAxis
(
    BrlEllipticalTorus ellipticalTorus,
    double             tubeSemiMajorAxisX, double tubeSemiMajorAxisY, double tubeSemiMajorAxisZ
) {
    if (ellipticalTorus != nullptr) {
        EllipticalTorus* et = CastEllipticalTorus(ellipticalTorus);

        assert(et != nullptr);

        if (et != nullptr) {
            Vector3D axis(tubeSemiMajorAxisX, tubeSemiMajorAxisY, tubeSemiMajorAxisZ);

            et->SetTubeSemiMajorAxis(axis);
        }
    }
}


double BrlEllipticalTorusTubeSemiMinorAxis
(
    BrlEllipticalTorus ellipticalTorus
) {
    double ret = 0.0;

    if (ellipticalTorus != nullptr) {
        EllipticalTorus* et = CastEllipticalTorus(ellipticalTorus);

        assert(et != nullptr);

        if (et != nullptr)
            ret = et->TubeSemiMinorAxis();
    }

    return ret;
}


void BrlEllipticalTorusSetTubeSemiMinorAxis
(
    BrlEllipticalTorus ellipticalTorus,
    double             length
) {
    if (ellipticalTorus != nullptr) {
        EllipticalTorus* et = CastEllipticalTorus(ellipticalTorus);

        assert(et != nullptr);

        if (et != nullptr)
            et->SetTubeSemiMinorAxis(length);
    }
}


void BrlEllipticalTorusSet
(
    BrlEllipticalTorus ellipticalTorus,
    double             centerX,            double centerY,            double centerZ,
    double             normalX,            double normalY,            double normalZ,
    double             tubeCenterLineRadius,
    double             tubeSemiMajorAxisX, double tubeSemiMajorAxisY, double tubeSemiMajorAxisZ,
    double             tubeSemiMinorAxisLength
) {
    if (ellipticalTorus != nullptr) {
        EllipticalTorus* et = CastEllipticalTorus(ellipticalTorus);

        assert(et != nullptr);

        if (et != nullptr) {
            Vector3D center(centerX, centerY, centerZ);
            Vector3D normal(normalX, normalY, normalZ);
            Vector3D tubeSemiMajorAxis(tubeSemiMajorAxisX, tubeSemiMajorAxisY, tubeSemiMajorAxisZ);

            et->Set(center, normal, tubeCenterLineRadius, tubeSemiMajorAxis, tubeSemiMinorAxisLength);
        }
    }
}


const char* BrlEllipticalTorusClassName(void) {
    return EllipticalTorus::ClassName();
}
