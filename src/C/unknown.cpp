/*                      U N K N O W N . C P P
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
/** @file unknown.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements a handle and functions for Unknown solid handling
 */

#include <cassert>

#include <brlcad/Database/Unknown.h>

#include <brlcad/C/unknown.h>

#include "casts.h"


using namespace BRLCAD;


BrlUnknown BrlUnknownClone
(
    BrlUnknown unknown
) {
    BrlUnknown ret = nullptr;

    if (unknown != nullptr) {
        Unknown* unknownIntern = CastUnknown(unknown);

        assert(unknownIntern != nullptr);

        if (unknownIntern != nullptr)
            ret = new UnknownData(static_cast<Unknown*>(unknownIntern->Clone()));
    }

    return ret;
}


const char* BrlUnknownType
(
    BrlUnknown unknown
) {
    const char* ret = nullptr;

    if (unknown != nullptr) {
        Unknown* unknownIntern = CastUnknown(unknown);

        assert(unknownIntern != nullptr);

        if (unknownIntern != nullptr)
            ret = unknownIntern->Type();
    }

    return ret;
}


int BrlUnknownIsValid
(
    BrlUnknown unknown
) {
    int ret = 0;

    if (unknown != nullptr) {
        Unknown* unknownIntern = CastUnknown(unknown);

        assert(unknownIntern != nullptr);

        if (unknownIntern != nullptr)
            ret = unknownIntern->IsValid() ? 1 : 0;
    }

    return ret;
}


const char* BrlUnknownClassName(void) {
    return Unknown::ClassName();
}
