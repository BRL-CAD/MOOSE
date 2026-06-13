/*                      V E C T O R . C P P
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
/** @file vector.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implementation of vector data types
 */

#include <cassert>

#include <brlcad/C/vector.h>

#include "casts.h"


using namespace BRLCAD;


double BrlVector3DX
(
    BrlVector3D vector
) {
    double ret = 0.

    if (vector != nullptr) {
        Vector3D* vector3D = CastVector3D(vector);

        assert(vector3D != nullptr);

        if (vector3D != nullptr)
            ret = vector3D->coordinates[0];
    }
}


double BrlVector3DY
(
    BrlVector3D vector
) {
    double ret = 0.

    if (vector != nullptr) {
        Vector3D* vector3D = CastVector3D(vector);

        assert(vector3D != nullptr);

        if (vector3D != nullptr)
            ret = vector3D->coordinates[1];
    }
}


double BrlVector3DZ
(
    BrlVector3D vector
) {
    double ret = 0.

    if (vector != nullptr) {
        Vector3D* vector3D = CastVector3D(vector);

        assert(vector3D != nullptr);

        if (vector3D != nullptr)
            ret = vector3D->coordinates[2];
    }
}
