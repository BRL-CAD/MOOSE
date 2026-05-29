/*                         C A S T S . C P P 
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
/** @file casts.h
 *
 *  BRL-CAD core simplified C interface:
 *      implements helper functions to cast void* handles to the correct C++ class
 */

#include "bu/log.h"

#include "casts.h"


using namespace BRLCAD;


static const char* Magic
(
    void* handle
) {
    const char* ret = nullptr;

    class HandleMagic : public Handle {
    public:
        const char* Magic(void) const {
            return m_magic;
        }
    };

    if (handle != nullptr) {
        HandleMagic* testClass = static_cast<HandleMagic*>(handle);

        ret = testClass->Magic();
    }

    return ret;
}


Handle* CastHandle
(
    void* handle
) {
    Handle* ret = nullptr;

    const char* handleMagic = Magic(handle);

    if ((handleMagic == Arb8Magic) ||
        (handleMagic == ConstDatabaseMagic) ||
        (handleMagic == FileDatabaseMagic) ||
        (handleMagic == MemoryDatabaseMagic) ||
        (handleMagic == ObjectMagic) ||
        (handleMagic == VectorListMagic))
        ret = static_cast<Handle*>(handle);
    else if (handle != nullptr)
        bu_log("CastHandle: invalid handle");

    return ret;
}


ConstDatabase* CastConstDatabase
(
    void* handle
) {
    ConstDatabase* ret = nullptr;

    const char* handleMagic = Magic(handle);

    if ((handleMagic == ConstDatabaseMagic) ||
        (handleMagic == DatabaseMagic) ||
        (handleMagic == FileDatabaseMagic) ||
        (handleMagic == MemoryDatabaseMagic))
        ret = static_cast<ConstDatabase*>(handle);
    else if (handle != nullptr)
        bu_log("CastConstDatabase: wrong handle");

    return ret;
}


Database* CastDatabase
(
    void* handle
) {
    Database* ret = nullptr;

    const char* handleMagic = Magic(handle);

    // Only accept writable database types (NOT ConstDatabaseMagic)
    if ((handleMagic == DatabaseMagic) ||
        (handleMagic == FileDatabaseMagic) ||
        (handleMagic == MemoryDatabaseMagic))
        ret = static_cast<Database*>(handle);
    else if (handle != nullptr)
        bu_log("CastDatabase: wrong handle or read-only database");

    return ret;
}


Object* CastObject
(
    void* handle
) {
    Object* ret = nullptr;

    const char* handleMagic = Magic(handle);

    if ((handleMagic == Arb8Magic) ||
        (handleMagic == ObjectMagic))
        ret = static_cast<Object*>(handle);
    else if (handle != nullptr)
        bu_log("CastObject: wrong handle");

    return ret;
}
