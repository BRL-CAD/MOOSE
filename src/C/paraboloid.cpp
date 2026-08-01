/*                      P A R A B O L O I D . C P P
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
/** @file paraboloid.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements a handle and functions for Paraboloid solid handling
 */

#include <cassert>

#include <brlcad/Database/Paraboloid.h>

#include <brlcad/C/paraboloid.h>

#include "BrlData.h"

#include "casts.h"


using namespace BRLCAD;


BrlObject BrlNewParaboloid(void) {
    return DowncastObject(new Paraboloid());
}


BrlObject BrlNewParaboloidAsParaboloid
(
    double baseX,          double baseY,          double baseZ,
    double heightX,        double heightY,        double heightZ,
    double semiMajorAxisX, double semiMajorAxisY, double semiMajorAxisZ,
    double semiMinorAxisLength
) {
    Vector3D bp(baseX, baseY, baseZ);
    Vector3D h(heightX, heightY, heightZ);
    Vector3D sma(semiMajorAxisX, semiMajorAxisY, semiMajorAxisZ);

    return new ParaboloidData(new Paraboloid(bp, h, sma, semiMinorAxisLength));
}


BrlObject BrlNewParaboloidAsParaboloidWithLength
(
    double baseX,               double baseY,               double baseZ,
    double heightX,             double heightY,             double heightZ,
    double directionX,          double directionY,          double directionZ,
    double semiMajorAxisLength,
    double semiMinorAxisLength
) {
    Vector3D bp(baseX, baseY, baseZ);
    Vector3D h(heightX, heightY, heightZ);
    Vector3D dir(directionX, directionY, directionZ);

    return new ParaboloidData(new Paraboloid(bp, h, dir, semiMajorAxisLength, semiMinorAxisLength));
}


BrlVector3D BrlParaboloidBasePoint
(
    BrlObject paraboloid
) {
    BrlVector3D ret = nullptr;

    if (paraboloid != nullptr) {
        Paraboloid* paraIntern = CastParaboloid(paraboloid);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr)
            ret = new Vector3DData(paraIntern->BasePoint());
    }

    return ret;
}


void BrlParaboloidSetBasePoint
(
    BrlObject paraboloid,
    double    baseX, double baseY, double baseZ
) {
    if (paraboloid != nullptr) {
        Paraboloid* paraIntern = CastParaboloid(paraboloid);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr) {
            Vector3D bp(baseX, baseY, baseZ);

            paraIntern->SetBasePoint(bp);
        }
    }
}


BrlVector3D BrlParaboloidHeight
(
    BrlObject paraboloid
) {
    BrlVector3D ret = nullptr;

    if (paraboloid != nullptr) {
        Paraboloid* paraIntern = CastParaboloid(paraboloid);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr)
            ret = new Vector3DData(paraIntern->Height());
    }

    return ret;
}


void BrlParaboloidSetHeight
(
    BrlObject paraboloid,
    double    heightX, double heightY, double heightZ
) {
    if (paraboloid != nullptr) {
        Paraboloid* paraIntern = CastParaboloid(paraboloid);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr) {
            Vector3D h(heightX, heightY, heightZ);

            paraIntern->SetHeight(h);
        }
    }
}


BrlVector3D BrlParaboloidSemiMajorAxis
(
    BrlObject paraboloid
) {
    BrlVector3D ret = nullptr;

    if (paraboloid != nullptr) {
        Paraboloid* paraIntern = CastParaboloid(paraboloid);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr)
            ret = new Vector3DData(paraIntern->SemiMajorAxis());
    }

    return ret;
}


void BrlParaboloidSetSemiMajorAxis
(
    BrlObject paraboloid,
    double    semiMajorAxisX, double semiMajorAxisY, double semiMajorAxisZ
) {
    if (paraboloid != nullptr) {
        Paraboloid* paraIntern = CastParaboloid(paraboloid);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr) {
            Vector3D sma(semiMajorAxisX, semiMajorAxisY, semiMajorAxisZ);

            paraIntern->SetSemiMajorAxis(sma);
        }
    }
}


void BrlParaboloidSetSemiMajorAxisWithLength
(
    BrlObject paraboloid,
    double    directionX, double directionY, double directionZ,
    double    length
) {
    if (paraboloid != nullptr) {
        Paraboloid* paraIntern = CastParaboloid(paraboloid);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr) {
            Vector3D dir(directionX, directionY, directionZ);

            paraIntern->SetSemiMajorAxis(dir, length);
        }
    }
}


BrlVector3D BrlParaboloidSemiMajorAxisDirection
(
    BrlObject paraboloid
) {
    BrlVector3D ret = nullptr;

    if (paraboloid != nullptr) {
        Paraboloid* paraIntern = CastParaboloid(paraboloid);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr)
            ret = new Vector3DData(paraIntern->SemiMajorAxisDirection());
    }

    return ret;
}


void BrlParaboloidSetSemiMajorAxisDirection
(
    BrlObject paraboloid,
    double    directionX, double directionY, double directionZ
) {
    if (paraboloid != nullptr) {
        Paraboloid* paraIntern = CastParaboloid(paraboloid);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr) {
            Vector3D dir(directionX, directionY, directionZ);

            paraIntern->SetSemiMajorAxisDirection(dir);
        }
    }
}


double BrlParaboloidSemiMajorAxisLength
(
    BrlObject paraboloid
) {
    double ret = 0.0;

    if (paraboloid != nullptr) {
        Paraboloid* paraIntern = CastParaboloid(paraboloid);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr)
            ret = paraIntern->SemiMajorAxisLength();
    }

    return ret;
}


void BrlParaboloidSetSemiMajorAxisLength
(
    BrlObject paraboloid,
    double    length
) {
    if (paraboloid != nullptr) {
        Paraboloid* paraIntern = CastParaboloid(paraboloid);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr)
            paraIntern->SetSemiMajorAxisLength(length);
    }
}


double BrlParaboloidSemiMinorAxisLength
(
    BrlObject paraboloid
) {
    double ret = 0.0;

    if (paraboloid != nullptr) {
        Paraboloid* paraIntern = CastParaboloid(paraboloid);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr)
            ret = paraIntern->SemiMinorAxisLength();
    }

    return ret;
}


void BrlParaboloidSetSemiMinorAxisLength
(
    BrlObject paraboloid,
    double    length
) {
    if (paraboloid != nullptr) {
        Paraboloid* paraIntern = CastParaboloid(paraboloid);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr)
            paraIntern->SetSemiMinorAxisLength(length);
    }
}


void BrlParaboloidSet
(
    BrlObject paraboloid,
    double    baseX,          double baseY,          double baseZ,
    double    heightX,        double heightY,        double heightZ,
    double    semiMajorAxisX, double semiMajorAxisY, double semiMajorAxisZ,
    double    semiMinorAxisLength
) {
    if (paraboloid != nullptr) {
        Paraboloid* paraIntern = CastParaboloid(paraboloid);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr) {
            Vector3D bp(baseX, baseY, baseZ);
            Vector3D h(heightX, heightY, heightZ);
            Vector3D sma(semiMajorAxisX, semiMajorAxisY, semiMajorAxisZ);

            paraIntern->Set(bp, h, sma, semiMinorAxisLength);
        }
    }
}


void BrlParaboloidSetWithLength
(
    BrlObject paraboloid,
    double    baseX,               double baseY,               double baseZ,
    double    heightX,             double heightY,             double heightZ,
    double    directionX,          double directionY,          double directionZ,
    double    semiMajorAxisLength,
    double    semiMinorAxisLength
) {
    if (paraboloid != nullptr) {
        Paraboloid* paraIntern = CastParaboloid(paraboloid);

        assert(paraIntern != nullptr);

        if (paraIntern != nullptr) {
            Vector3D bp(baseX, baseY, baseZ);
            Vector3D h(heightX, heightY, heightZ);
            Vector3D dir(directionX, directionY, directionZ);

            paraIntern->Set(bp, h, dir, semiMajorAxisLength, semiMinorAxisLength);
        }
    }
}


const char* BrlParaboloidClassName(void) {
    return Paraboloid::ClassName();
}
