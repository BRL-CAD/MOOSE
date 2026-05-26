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
 *      implements wrappers for constructing Arb8 geometry objects
 *      from a box diagonal or from 8 explicit points
 */

#include <brlcad/C/arb8.h>

#include <brlcad/Database/Arb8.h>

#include <brlcad/vector.h>


using namespace BRLCAD;


//box coordinates as separate doubles
BrlArb8 BrlNewArb8FromBoxCoords
(
    double p1x, double p1y, double p1z,
    double p2x, double p2y, double p2z
) {
    Vector3D v1(p1x, p1y, p1z);
    Vector3D v2(p2x, p2y, p2z);
    BrlArb8 arb_handle = nullptr;
    arb_handle = static_cast<BrlArb8>(new Arb8(v1, v2));
    return arb_handle;
}

//four points (12 doubles)
BrlArb8 BrlNewArb8From4Points
(
    double p1x, double p1y, double p1z,
    double p2x, double p2y, double p2z,
    double p3x, double p3y, double p3z,
    double p4x, double p4y, double p4z
) {
    Vector3D p1(p1x, p1y, p1z);
    Vector3D p2(p2x, p2y, p2z);
    Vector3D p3(p3x, p3y, p3z);
    Vector3D p4(p4x, p4y, p4z);
    BrlArb8 arb_handle = nullptr;
    arb_handle = static_cast<BrlArb8>(new Arb8(p1, p2, p3, p4));
    return arb_handle;
}

//eight points (24 doubles)
BrlArb8 BrlNewArb8From8Points
(
    double p1x, double p1y, double p1z,
    double p2x, double p2y, double p2z,
    double p3x, double p3y, double p3z,
    double p4x, double p4y, double p4z,
    double p5x, double p5y, double p5z,
    double p6x, double p6y, double p6z,
    double p7x, double p7y, double p7z,
    double p8x, double p8y, double p8z
) {
    Vector3D pts[8] = {
        Vector3D(p1x,p1y,p1z), Vector3D(p2x,p2y,p2z),
        Vector3D(p3x,p3y,p3z), Vector3D(p4x,p4y,p4z),
        Vector3D(p5x,p5y,p5z), Vector3D(p6x,p6y,p6z),
        Vector3D(p7x,p7y,p7z), Vector3D(p8x,p8y,p8z)
    };
    BrlArb8 arb_handle = nullptr;
    arb_handle = static_cast<BrlArb8>(new Arb8(pts[0], pts[1], pts[2], pts[3],
                                               pts[4], pts[5], pts[6], pts[7]));
    return arb_handle;
}
