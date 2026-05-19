/*                      C O N S T D A T A B A S E . C P P
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
/** @file ConstDatabase.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements a handle and functions for a read-only database
 */

#include <cassert>

#include <brlcad/C/ConstDatabase.h>

#include "casts.h"

#include <brlcad/Database/FileDatabase.h>

#include <brlcad/Database/MemoryDatabase.h>


using namespace BRLCAD;


BrlConstDatabase BrlNewConstDatabase(void) {
    return reinterpret_cast<BrlConstDatabase>(new BRLCAD::ConstDatabase());
}

BrlConstDatabase BrlNewFileDatabase(void) {
    return reinterpret_cast<BrlConstDatabase>(new BRLCAD::FileDatabase());
}

BrlConstDatabase BrlNewMemoryDatabase(void) {
    return reinterpret_cast<BrlConstDatabase>(new BRLCAD::MemoryDatabase());
}


void BrlDeleteConstDatabase
(
    BrlConstDatabase db
) {
    if (db != nullptr) {
        ConstDatabase* constDatabase = CastConstDatabase(db);

        assert(constDatabase != nullptr);

        if (constDatabase != nullptr)
            delete constDatabase;
    }
}


int BrlConstDatabaseLoad
(
    BrlConstDatabase db,
    const char*      fileName
) {
    int ret = 1;

    if (db != nullptr) {
        ConstDatabase* constDatabase = CastConstDatabase(db);

        assert(constDatabase != nullptr);

        if (constDatabase != nullptr)
            ret = constDatabase->Load(fileName) ? 0 : 1;
    }

    return ret;
}


const char* BrlConstDatabaseTitle
(
    BrlConstDatabase db
) {
    const char* ret = nullptr;

    if (db != nullptr) {
        ConstDatabase* constDatabase = CastConstDatabase(db);

        assert(constDatabase != nullptr);

        if (constDatabase != nullptr)
            ret = constDatabase->Title();
    }

    return ret;
}
