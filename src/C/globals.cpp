/*                       G L O B A L S . C P P
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
/** @file globals.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implementation of general stuff
 */

#include <cassert>
#include <map>

#include <brlcad/globals.h>

#include <brlcad/C/globals.h>

#include "casts.h"


using namespace BRLCAD;


int BrlMajorVersion(void) {
    return MajorVersion();
}


int BrlMinorVersion(void) {
    return MinorVersion();
}


int BrlPatchVersion(void) {
    return PatchVersion();
}


const char* const Vector3DMagic            = "BRLCAD::Vector3D";
const char* const VectorListMagic          = "BRLCAD::VectorList";
const char* const ConstDatabaseMagic       = "BRLCAD::ConstDatabase";
const char* const FileDatabaseMagic        = "BRLCAD::FileDatabase";
const char* const MemoryDatabaseMagic      = "BRLCAD::MemoryDatabase";
const char* const ObjectMagic              = "BRLCAD::Object";
const char* const Arb8Magic                = "BRLCAD::Arb8";
const char* const SphereMagic              = "BRLCAD::Sphere";    
const char* const EllipsoidMagic           = "BRLCAD::Ellipsoid";   
const char* const ConeMagic                = "BRLCAD::Cone";
const char* const NonManifoldGeometryMagic = "BRLCAD::NonManifoldGeometry";


void BrlDeleteHandle
(
    BrlHandle handle
) {
    if (handle != nullptr) {
        BrlData* data = CastHandle(handle);

        assert(data != nullptr);

        if (data != nullptr)
            delete data;
    }
}


static std::map<BrlLogHandler, void*> CLogHandlers;


static BRLCAD::LogHandler CLogger = [](const char* logString) {
    for (std::map<BrlLogHandler, void*>::const_iterator it = CLogHandlers.begin(); it != CLogHandlers.end(); ++it)
        it->first(logString, it->second);
};


void BrlRegisterLogHandler
(
    BrlLogHandler logHandler,
    void*         environmentHandle
) {
    static bool registered = false;

    if (!registered) {
        RegisterLogHandler(CLogger);
        registered = true;
    }

    CLogHandlers[logHandler] = environmentHandle;
}


void BrlDeRegisterLogHandler
(
    BrlLogHandler logHandler
) {
    CLogHandlers.erase(logHandler);
}
