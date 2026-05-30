/*                      D A T A B A S E . C P P
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
/** @file database.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements functions for a database
 */

#include <brlcad/Database/Database.h>

#include <brlcad/C/database.h>

#include "casts.h"

#include <cassert>


using namespace BRLCAD;


void BrlDatabaseSetTitle
(
    BrlDatabase db,
    const char* title
) {
    if (db != nullptr) {
        Database* database = CastDatabase(db);

        assert(database != nullptr);

        if (database != nullptr)
            database->SetTitle(title);
    }
}
