/*                          N O N M A N I F O L D G E O M E T R Y . C P P
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
/** @file nonManifoldGeometry.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements a handle and functions for NonManifoldGeometry solid handling
 */

#include <cassert>

#include <brlcad/Database/NonManifoldGeometry.h>

#include <brlcad/C/nonManifoldGeometry.h>

#include "BrlData.h"

#include "casts.h"


using namespace BRLCAD;


BrlNonManifoldGeometry BrlNewNonManifoldGeometry(void) {
    return new NonManifoldGeometryData(new NonManifoldGeometry());
}


void BrlNonManifoldGeometryTriangulate
(
    BrlNonManifoldGeometry nonManifoldGeometry
) {
    if (nonManifoldGeometry != nullptr) {
        NonManifoldGeometry* nmg = CastNonManifoldGeometry(nonManifoldGeometry);

        assert(nmg != nullptr);

        if (nmg != nullptr)
            nmg->Triangulate();
    }
}


const char* BrlNonManifoldGeometryClassName(void) {
    return NonManifoldGeometry::ClassName();
}
