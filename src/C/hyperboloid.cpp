/*                      H Y P E R B O L O I D . C P P
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
/** @file hyperboloid.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements a handle and functions for Hyperboloid solid handling
 */

#include <cassert>

#include <brlcad/Database/Hyperboloid.h>

#include <brlcad/C/hyperboloid.h>

#include "casts.h"


using namespace BRLCAD;


BrlHyperboloid BrlNewHyperboloid(void) {
    return new HyperboloidData(new Hyperboloid());
}


BrlHyperboloid BrlNewHyperboloidAsHyperboloid
(
    double baseX,          double baseY,          double baseZ,
    double heightX,        double heightY,        double heightZ,
    double semiMajorAxisX, double semiMajorAxisY, double semiMajorAxisZ,
    double semiMinorAxisLength,
    double apexAsymptoteDistance
) {
    Vector3D bp(baseX, baseY, baseZ);
    Vector3D h(heightX, heightY, heightZ);
    Vector3D sma(semiMajorAxisX, semiMajorAxisY, semiMajorAxisZ);

    return new HyperboloidData(new Hyperboloid(bp, h, sma, semiMinorAxisLength, apexAsymptoteDistance));
}


BrlHyperboloid BrlNewHyperboloidAsHyperboloidWithLength
(
    double baseX,      double baseY,      double baseZ,
    double heightX,    double heightY,    double heightZ,
    double directionX, double directionY, double directionZ,
    double semiMajorAxisLength,
    double semiMinorAxisLength,
    double apexAsymptoteDistance
) {
    Vector3D bp(baseX, baseY, baseZ);
    Vector3D h(heightX, heightY, heightZ);
    Vector3D dir(directionX, directionY, directionZ);

    return new HyperboloidData(new Hyperboloid(bp, h, dir, semiMajorAxisLength, semiMinorAxisLength, apexAsymptoteDistance));
}


BrlVector3D BrlHyperboloidBasePoint
(
    BrlHyperboloid hyperboloid
) {
    BrlVector3D ret = nullptr;

    if (hyperboloid != nullptr) {
        Hyperboloid* hyperIntern = CastHyperboloid(hyperboloid);

        assert(hyperIntern != nullptr);

        if (hyperIntern != nullptr)
            ret = new Vector3DData(hyperIntern->BasePoint());
    }

    return ret;
}


void BrlHyperboloidSetBasePoint
(
    BrlHyperboloid hyperboloid,
    double         baseX, double baseY, double baseZ
) {
    if (hyperboloid != nullptr) {
        Hyperboloid* hyperIntern = CastHyperboloid(hyperboloid);

        assert(hyperIntern != nullptr);

        if (hyperIntern != nullptr) {
            Vector3D bp(baseX, baseY, baseZ);

            hyperIntern->SetBasePoint(bp);
        }
    }
}


BrlVector3D BrlHyperboloidHeight
(
    BrlHyperboloid hyperboloid
) {
    BrlVector3D ret = nullptr;

    if (hyperboloid != nullptr) {
        Hyperboloid* hyperIntern = CastHyperboloid(hyperboloid);

        assert(hyperIntern != nullptr);

        if (hyperIntern != nullptr)
            ret = new Vector3DData(hyperIntern->Height());
    }

    return ret;
}


void BrlHyperboloidSetHeight
(
    BrlHyperboloid hyperboloid,
    double         heightX, double heightY, double heightZ
) {
    if (hyperboloid != nullptr) {
        Hyperboloid* hyperIntern = CastHyperboloid(hyperboloid);

        assert(hyperIntern != nullptr);

        if (hyperIntern != nullptr) {
            Vector3D h(heightX, heightY, heightZ);

            hyperIntern->SetHeight(h);
        }
    }
}


BrlVector3D BrlHyperboloidSemiMajorAxis
(
    BrlHyperboloid hyperboloid
) {
    BrlVector3D ret = nullptr;

    if (hyperboloid != nullptr) {
        Hyperboloid* hyperIntern = CastHyperboloid(hyperboloid);

        assert(hyperIntern != nullptr);

        if (hyperIntern != nullptr)
            ret = new Vector3DData(hyperIntern->SemiMajorAxis());
    }

    return ret;
}


void BrlHyperboloidSetSemiMajorAxis
(
    BrlHyperboloid hyperboloid,
    double         semiMajorAxisX, double semiMajorAxisY, double semiMajorAxisZ
) {
    if (hyperboloid != nullptr) {
        Hyperboloid* hyperIntern = CastHyperboloid(hyperboloid);

        assert(hyperIntern != nullptr);

        if (hyperIntern != nullptr) {
            Vector3D sma(semiMajorAxisX, semiMajorAxisY, semiMajorAxisZ);

            hyperIntern->SetSemiMajorAxis(sma);
        }
    }
}


void BrlHyperboloidSetSemiMajorAxisWithLength
(
    BrlHyperboloid hyperboloid,
    double         directionX, double directionY, double directionZ,
    double         length
) {
    if (hyperboloid != nullptr) {
        Hyperboloid* hyperIntern = CastHyperboloid(hyperboloid);

        assert(hyperIntern != nullptr);

        if (hyperIntern != nullptr) {
            Vector3D dir(directionX, directionY, directionZ);

            hyperIntern->SetSemiMajorAxis(dir, length);
        }
    }
}


BrlVector3D BrlHyperboloidSemiMajorAxisDirection
(
    BrlHyperboloid hyperboloid
) {
    BrlVector3D ret = nullptr;

    if (hyperboloid != nullptr) {
        Hyperboloid* hyperIntern = CastHyperboloid(hyperboloid);

        assert(hyperIntern != nullptr);

        if (hyperIntern != nullptr)
            ret = new Vector3DData(hyperIntern->SemiMajorAxisDirection());
    }

    return ret;
}


void BrlHyperboloidSetSemiMajorAxisDirection
(
    BrlHyperboloid hyperboloid,
    double         directionX, double directionY, double directionZ
) {
    if (hyperboloid != nullptr) {
        Hyperboloid* hyperIntern = CastHyperboloid(hyperboloid);

        assert(hyperIntern != nullptr);

        if (hyperIntern != nullptr) {
            Vector3D dir(directionX, directionY, directionZ);

            hyperIntern->SetSemiMajorAxisDirection(dir);
        }
    }
}


double BrlHyperboloidSemiMajorAxisLength
(
    BrlHyperboloid hyperboloid
) {
    double ret = 0.;

    if (hyperboloid != nullptr) {
        Hyperboloid* hyperIntern = CastHyperboloid(hyperboloid);

        assert(hyperIntern != nullptr);

        if (hyperIntern != nullptr)
            ret = hyperIntern->SemiMajorAxisLength();
    }

    return ret;
}


void BrlHyperboloidSetSemiMajorAxisLength
(
    BrlHyperboloid hyperboloid,
    double         length
) {
    if (hyperboloid != nullptr) {
        Hyperboloid* hyperIntern = CastHyperboloid(hyperboloid);

        assert(hyperIntern != nullptr);

        if (hyperIntern != nullptr)
            hyperIntern->SetSemiMajorAxisLength(length);
    }
}


double BrlHyperboloidSemiMinorAxisLength
(
    BrlHyperboloid hyperboloid
) {
    double ret = 0.;

    if (hyperboloid != nullptr) {
        Hyperboloid* hyperIntern = CastHyperboloid(hyperboloid);

        assert(hyperIntern != nullptr);

        if (hyperIntern != nullptr)
            ret = hyperIntern->SemiMinorAxisLength();
    }

    return ret;
}


void BrlHyperboloidSetSemiMinorAxisLength
(
    BrlHyperboloid hyperboloid,
    double         length
) {
    if (hyperboloid != nullptr) {
        Hyperboloid* hyperIntern = CastHyperboloid(hyperboloid);

        assert(hyperIntern != nullptr);

        if (hyperIntern != nullptr)
            hyperIntern->SetSemiMinorAxisLength(length);
    }
}


double BrlHyperboloidApexAsymptoteDistance
(
    BrlHyperboloid hyperboloid
) {
    double ret = 0.;

    if (hyperboloid != nullptr) {
        Hyperboloid* hyperIntern = CastHyperboloid(hyperboloid);

        assert(hyperIntern != nullptr);

        if (hyperIntern != nullptr)
            ret = hyperIntern->ApexAsymptoteDistance();
    }

    return ret;
}


void BrlHyperboloidSetApexAsymptoteDistance
(
    BrlHyperboloid hyperboloid,
    double         distance
) {
    if (hyperboloid != nullptr) {
        Hyperboloid* hyperIntern = CastHyperboloid(hyperboloid);

        assert(hyperIntern != nullptr);

        if (hyperIntern != nullptr)
            hyperIntern->SetApexAsymptoteDistance(distance);
    }
}


void BrlHyperboloidSet
(
    BrlHyperboloid hyperboloid,
    double         baseX,          double baseY,          double baseZ,
    double         heightX,        double heightY,        double heightZ,
    double         semiMajorAxisX, double semiMajorAxisY, double semiMajorAxisZ,
    double         semiMinorAxisLength,
    double         apexAsymptoteDistance
) {
    if (hyperboloid != nullptr) {
        Hyperboloid* hyperIntern = CastHyperboloid(hyperboloid);

        assert(hyperIntern != nullptr);

        if (hyperIntern != nullptr) {
            Vector3D bp(baseX, baseY, baseZ);
            Vector3D h(heightX, heightY, heightZ);
            Vector3D sma(semiMajorAxisX, semiMajorAxisY, semiMajorAxisZ);

            hyperIntern->Set(bp, h, sma, semiMinorAxisLength, apexAsymptoteDistance);
        }
    }
}


void BrlHyperboloidSetWithLength
(
    BrlHyperboloid hyperboloid,
    double         baseX,      double baseY,      double baseZ,
    double         heightX,    double heightY,    double heightZ,
    double         directionX, double directionY, double directionZ,
    double         semiMajorAxisLength,
    double         semiMinorAxisLength,
    double         apexAsymptoteDistance
) {
    if (hyperboloid != nullptr) {
        Hyperboloid* hyperIntern = CastHyperboloid(hyperboloid);

        assert(hyperIntern != nullptr);

        if (hyperIntern != nullptr) {
            Vector3D bp(baseX, baseY, baseZ);
            Vector3D h(heightX, heightY, heightZ);
            Vector3D dir(directionX, directionY, directionZ);

            hyperIntern->Set(bp, h, dir, semiMajorAxisLength, semiMinorAxisLength, apexAsymptoteDistance);
        }
    }
}


const char* BrlHyperboloidClassName(void) {
    return Hyperboloid::ClassName();
}
