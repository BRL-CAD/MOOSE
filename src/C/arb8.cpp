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
 *      implements a handle and functions for a read-only database
 */

#include <brlcad/C/arb8.h>

#include <brlcad/Database/Arb8.h>

#include <brlcad/vector.h>


using namespace BRLCAD;


BrlHandle BrlNewArb8FromBox
(
    const double* p1, const double* p2
) {
    if (!p1 || !p2) return nullptr;
    
    Vector3D vec1(p1[0], p1[1], p1[2]);
    Vector3D vec2(p2[0], p2[1], p2[2]);
        BrlHandle arb_handle = nullptr;
        arb_handle = static_cast<BrlHandle>(new Arb8(vec1, vec2));
        return arb_handle;
}

BrlHandle BrlNewArb8FromPoints
(
    const double* flatPoints24
) {
    if (!flatPoints24) return nullptr;
    
    // Unpack the 24 flat doubles into 8 Vector3D objects
    Vector3D pts[8];
    int idx = 0;
    for(int i = 0; i < 8; ++i) {
        pts[i] = Vector3D(flatPoints24[idx], flatPoints24[idx+1], flatPoints24[idx+2]);
        idx += 3;
    }
        BrlHandle arb_handle = nullptr;
        arb_handle = static_cast<BrlHandle>(new Arb8(pts[0], pts[1], pts[2], pts[3],
                                                   pts[4], pts[5], pts[6], pts[7]));
        return arb_handle;
}