/*                         H A N D L E . C P P
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
/** @file handle.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements the basic handle's and destructor function
 */

#include <cassert>

#include "casts.h"

#include <brlcad/C/handle.h>


using namespace BRLCAD;


void BrlDeleteHandle
(
    BrlHandle handle
) {
    if (handle != nullptr) {
        Handle* hd = CastHandle(handle);

        assert(hd != nullptr);

        if (hd != nullptr)
            delete hd;
    }
}
