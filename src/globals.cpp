/*                      G L O B A L S . C P P
 * BRL-CAD
 *
 * Copyright (c) 2011-2025 United States Government as represented by
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
/** @file globals.cpp
 *
 *  BRL-CAD core C++ interface:
 *      implementats global functions which influence the behavior
 *      of the BRL-CAD core
 */

#include "bu.h"
#include "raytrace.h"

#include <brlcad/version.h>
#include <brlcad/globals.h>


using namespace BRLCAD;


static int NullLogger
(
    void* data,
    void* string
) {
    return 0;
}


static struct BrlCadGlobal {
    BrlCadGlobal() {
        if (!BU_SETJUMP)
            bu_log_add_hook(NullLogger, nullptr);

        BU_UNSETJUMP;
    }

    ~BrlCadGlobal() {}

    int MajorVersion(void) {
        return BRLCAD_LIB_MAJOR;
    }

    int MinorVersion(void) {
        return BRLCAD_LIB_MINOR;
    }

    int PatchVersion(void) {
        return BRLCAD_LIB_PATCH;
    }
} Globals;


int BRLCAD_MOOSE_EXPORT BRLCAD::MajorVersion(void) {
    return Globals.MajorVersion();
}


int BRLCAD_MOOSE_EXPORT BRLCAD::MinorVersion(void) {
    return Globals.MinorVersion();
}


int BRLCAD_MOOSE_EXPORT BRLCAD::PatchVersion(void) {
    return Globals.PatchVersion();
}


static int Logger
(
    void* data,
    void* string
) {
    if (data != 0) {
        LogHandler* logHandler = static_cast<LogHandler*>(data);
        const char* logString  = static_cast<const char*>(string);

        (*logHandler)(logString);
    }

    return 0;
}


void BRLCAD_MOOSE_EXPORT BRLCAD::RegisterLogHandler
(
    LogHandler& logHandler
) {
    if (!BU_SETJUMP)
        bu_log_add_hook(Logger, &logHandler);
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


void BRLCAD_MOOSE_EXPORT BRLCAD::DeRegisterLogHandler
(
    LogHandler& logHandler
) {
    if (!BU_SETJUMP)
        bu_log_delete_hook(Logger, &logHandler);

    BU_UNSETJUMP;
}
