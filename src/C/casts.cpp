/*                         C A S T S . H
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

    return ret;
}
