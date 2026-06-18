/*                      A R B 8 . C P P
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
/** @file arb8.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements a handle and functions for Arb8 solid handling
 */

#include <cassert>

#include <brlcad/Database/Arb8.h>

#include <brlcad/C/arb8.h>

#include "BrlData.h"

#include "casts.h"


using namespace BRLCAD;


BrlArb8 BrlNewArb8
(
    void
) {
    return new Arb8Data(new Arb8());
}

BrlArb8 BrlNewArb8AsArb4
(
    double point1X, double point1Y, double point1Z,
    double point2X, double point2Y, double point2Z,
    double point3X, double point3Y, double point3Z,
    double point4X, double point4Y, double point4Z
) {
    Vector3D point1(point1X, point1Y, point1Z);
    Vector3D point2(point2X, point2Y, point2Z);
    Vector3D point3(point3X, point3Y, point3Z);
    Vector3D point4(point4X, point4Y, point4Z);

    return new Arb8Data(new Arb8(point1, point2, point3, point4));
}


BrlArb8 BrlNewArb8AsArb8
(
    double point1X, double point1Y, double point1Z,
    double point2X, double point2Y, double point2Z,
    double point3X, double point3Y, double point3Z,
    double point4X, double point4Y, double point4Z,
    double point5X, double point5Y, double point5Z,
    double point6X, double point6Y, double point6Z,
    double point7X, double point7Y, double point7Z,
    double point8X, double point8Y, double point8Z
) {
    Vector3D point1(point1X, point1Y, point1Z);
    Vector3D point2(point2X, point2Y, point2Z);
    Vector3D point3(point3X, point3Y, point3Z);
    Vector3D point4(point4X, point4Y, point4Z);
    Vector3D point5(point5X, point5Y, point5Z);
    Vector3D point6(point6X, point6Y, point6Z);
    Vector3D point7(point7X, point7Y, point7Z);
    Vector3D point8(point8X, point8Y, point8Z);

    return new Arb8Data(new Arb8(point1, point2, point3, point4, point5, point6, point7, point8));
}


BrlArb8 BrlNewArb8AsRectengularParallelPiped
(
    double point1X, double point1Y, double point1Z,
    double point2X, double point2Y, double point2Z
) {
    Vector3D point1(point1X, point1Y, point1Z);
    Vector3D point2(point2X, point2Y, point2Z);

    return new Arb8Data(new Arb8(point1, point2));
}


int BrlArb8NumberOfVertices
(
    BrlArb8 arb8
) {
    int ret = 0;

    if (arb8 != nullptr) {
        Arb8* ab = CastArb8(arb8);

        assert(ab != nullptr);

        if (ab != nullptr)
            ret = static_cast<int>(ab->NumberOfVertices());
    }
    return ret;
}


BrlVector3D BrlArb8Point
(
    BrlArb8 arb8,
    int     number
) {
    BrlVector3D ret = nullptr;

    if (arb8 != nullptr) {
        Arb8* ab = CastArb8(arb8);

        assert(ab != nullptr);

        if (ab != nullptr)
            ret = new Vector3DData(ab->Point(number));
    }
    return ret;
}


BrlVector3D BrlArb8RawPoint
(
    BrlArb8 arb8,
    int     index
) {
    BrlVector3D ret = nullptr;

    if (arb8 != nullptr) {
        Arb8* ab = CastArb8(arb8);

        assert(ab != nullptr);

        if (ab != nullptr)
            ret = new Vector3DData(ab->RawPoint(index));
    }
    return ret;
}


void BrlArb8SetPoint
(
    BrlArb8 arb8,
    int  number,
    double  x, double y, double z
) {
    if (arb8 != nullptr) {
        Arb8* ab = CastArb8(arb8);

        assert(ab != nullptr);

        if (ab != nullptr) {
            Vector3D point(x, y, z);
            ab->SetPoint(number, point);
        }
    }
}


void BrlArb8SetRawPoint
(
    BrlArb8 arb8,
    int  index,
    double  x, double y, double z
) {
    if (arb8 != nullptr) {
        Arb8* ab = CastArb8(arb8);

        assert(ab != nullptr);

        if (ab != nullptr) {
            Vector3D point(x, y, z);
            ab->SetRawPoint(index, point);
        }
    }
}


void BrlArb8SetPoints2
(
    BrlArb8 arb8,
    double  p1x, double p1y, double p1z,
    double  p2x, double p2y, double p2z
) {
    if (arb8 != nullptr) {
        Arb8* ab = CastArb8(arb8);

        assert(ab != nullptr);

        if (ab != nullptr) {
            Vector3D point1(p1x, p1y, p1z);
            Vector3D point2(p2x, p2y, p2z);

            ab->SetPoints(point1, point2);
        }
    }
}


void BrlArb8SetPoints4
(
    BrlArb8 arb8,
    double  p1x, double p1y, double p1z,
    double  p2x, double p2y, double p2z,
    double  p3x, double p3y, double p3z,
    double  p4x, double p4y, double p4z
) {
    if (arb8 != nullptr) {
        Arb8* ab = CastArb8(arb8);

        assert(ab != nullptr);

        if (ab != nullptr) {
            Vector3D point1(p1x, p1y, p1z);
            Vector3D point2(p2x, p2y, p2z);
            Vector3D point3(p3x, p3y, p3z);
            Vector3D point4(p4x, p4y, p4z);

            ab->SetPoints(point1, point2, point3, point4);
        }
    }
}


void BrlArb8SetPoints5
(
    BrlArb8 arb8,
    double  p1x, double p1y, double p1z,
    double  p2x, double p2y, double p2z,
    double  p3x, double p3y, double p3z,
    double  p4x, double p4y, double p4z,
    double  p5x, double p5y, double p5z
) {
    if (arb8 != nullptr) {
        Arb8* ab = CastArb8(arb8);

        assert(ab != nullptr);

        if (ab != nullptr) {
            Vector3D point1(p1x, p1y, p1z);
            Vector3D point2(p2x, p2y, p2z);
            Vector3D point3(p3x, p3y, p3z);
            Vector3D point4(p4x, p4y, p4z);
            Vector3D point5(p5x, p5y, p5z);

            ab->SetPoints(point1, point2, point3, point4, point5);
        }
    }
}


void BrlArb8SetPoints6
(
    BrlArb8 arb8,
    double  p1x, double p1y, double p1z,
    double  p2x, double p2y, double p2z,
    double  p3x, double p3y, double p3z,
    double  p4x, double p4y, double p4z,
    double  p5x, double p5y, double p5z,
    double  p6x, double p6y, double p6z
) {
    if (arb8 != nullptr) {
        Arb8* ab = CastArb8(arb8);

        assert(ab != nullptr);

        if (ab != nullptr) {
            Vector3D point1(p1x, p1y, p1z);
            Vector3D point2(p2x, p2y, p2z);
            Vector3D point3(p3x, p3y, p3z);
            Vector3D point4(p4x, p4y, p4z);
            Vector3D point5(p5x, p5y, p5z);
            Vector3D point6(p6x, p6y, p6z);

            ab->SetPoints(point1, point2, point3, point4, point5, point6);
        }
    }
}


void BrlArb8SetPoints7
(
    BrlArb8 arb8,
    double  p1x, double p1y, double p1z,
    double  p2x, double p2y, double p2z,
    double  p3x, double p3y, double p3z,
    double  p4x, double p4y, double p4z,
    double  p5x, double p5y, double p5z,
    double  p6x, double p6y, double p6z,
    double  p7x, double p7y, double p7z
) {
    if (arb8 != nullptr) {
        Arb8* ab = CastArb8(arb8);

        assert(ab != nullptr);

        if (ab != nullptr) {
            Vector3D point1(p1x, p1y, p1z);
            Vector3D point2(p2x, p2y, p2z);
            Vector3D point3(p3x, p3y, p3z);
            Vector3D point4(p4x, p4y, p4z);
            Vector3D point5(p5x, p5y, p5z);
            Vector3D point6(p6x, p6y, p6z);
            Vector3D point7(p7x, p7y, p7z);

            ab->SetPoints(point1, point2, point3, point4, point5, point6, point7);
        }
    }
}


void BrlArb8SetPoints8
(
    BrlArb8 arb8,
    double  p1x, double p1y, double p1z,
    double  p2x, double p2y, double p2z,
    double  p3x, double p3y, double p3z,
    double  p4x, double p4y, double p4z,
    double  p5x, double p5y, double p5z,
    double  p6x, double p6y, double p6z,
    double  p7x, double p7y, double p7z,
    double  p8x, double p8y, double p8z
) {
    if (arb8 != nullptr) {
        Arb8* ab = CastArb8(arb8);

        assert(ab != nullptr);

        if (ab != nullptr) {
            Vector3D point1(p1x, p1y, p1z);
            Vector3D point2(p2x, p2y, p2z);
            Vector3D point3(p3x, p3y, p3z);
            Vector3D point4(p4x, p4y, p4z);
            Vector3D point5(p5x, p5y, p5z);
            Vector3D point6(p6x, p6y, p6z);
            Vector3D point7(p7x, p7y, p7z);
            Vector3D point8(p8x, p8y, p8z);

            ab->SetPoints(point1, point2, point3, point4, point5, point6, point7, point8);
        }
    }
}
