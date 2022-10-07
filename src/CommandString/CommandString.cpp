/*                  C O M M A N D S T R I N G . C P P
 * BRL-CAD
 *
 * Copyright (c) 2022 United States Government as represented by
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
/** @file CommandString.cpp
 *
 *  BRL-CAD core C++ interface:
 *      libged command string parser module
 */

#include "bu/malloc.h"
#include "bu/parallel.h"
#include "ged/defines.h"

#include <brlcad/CommandString/CommandString.h>


using namespace BRLCAD;


CommandString::CommandString
(
    Database& database
) {
    if (!BU_SETJUMP) {
        BU_GET(m_ged, ged);
        GED_INIT(m_ged, database.m_wdbp);
    }
    else {
        BU_UNSETJUMP;

        m_ged = nullptr;
    }

    BU_UNSETJUMP;
}


CommandString::~CommandString(void) {
    if (m_ged != nullptr) {
        if (!BU_SETJUMP)
            ged_close(m_ged);

        BU_UNSETJUMP;
    }
}
