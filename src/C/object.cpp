/*                  O B J E C T . C P P
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
/** @file object.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements database objects
 */

#include <cassert>

#include <brlcad/C/object.h>

#include "casts.h"


using namespace BRLCAD;


const char* BrlObjectType
(
    BrlObject object
) {
    const char* ret = nullptr;

    if (object != nullptr) {
        Object* objectIntern = CastObject(object);

        assert(objectIntern != nullptr);

        if (objectIntern != nullptr)
            ret = objectIntern->Type();
    }

    return ret;
}


int BrlObjectIsValid
(
    BrlObject object
) {
    int ret = 0;

    if (object != nullptr) {
        Object* objectIntern = CastObject(object);

        assert(objectIntern != nullptr);

        if (objectIntern != nullptr)
            ret = objectIntern->IsValid() ? 1 : 0;
    }

    return ret;
}


void BrlObjectSetName
(
    BrlObject   object,
    const char* name
) {
    if (object != nullptr) {
        Object* objectIntern = CastObject(object);

        assert(objectIntern != nullptr);

        if (objectIntern != nullptr)
            objectIntern->SetName(name);
    }
}
