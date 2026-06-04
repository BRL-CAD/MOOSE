/*                      V E C T O R L I S T . C P P
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
/** @file vectorList.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implementation for VectorList opaque wrapper
 */

#include <cassert>

#include <brlcad/VectorList.h>

#include <brlcad/C/vectorList.h>

#include "casts.h"


using namespace BRLCAD;


BrlVectorList BrlNewVectorList
(
    void
) {
    return new VectorListHandle(new VectorList());
}


void BrlVectorListClear
(
    BrlVectorList vlist
) {
    if (vlist != nullptr) {
        VectorList* vl = CastVectorList(vlist);

        assert(vl != nullptr);

        if (vl != nullptr)
            vl->Clear();
    }
}
