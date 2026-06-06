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


BrlData* CastHandle
(
    BrlHandle handle
) {
    BrlData* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if ((handleMagic == Vector3DMagic) ||
            (handleMagic == VectorListMagic) ||
            (handleMagic == ConstDatabaseMagic) ||
            (handleMagic == FileDatabaseMagic) ||
            (handleMagic == MemoryDatabaseMagic) ||
            (handleMagic == ObjectMagic) ||
            (handleMagic == Arb8Magic) ||
            (handleMagic == NonManifoldGeometryMagic))
            ret = handle;
        else
            bu_log("CastHandle: invalid handle");
    }

    return ret;
}


Vector3D* CastVector3D
(
    BrlHandle handle
) {
    Vector3D* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == Vector3DMagic)
            ret = &static_cast<Vector3DData*>(handle)->Value();
        else
            bu_log("CastVectorList: wrong handle");
    }

    return ret;
}


VectorList* CastVectorList
(
    BrlHandle handle
) {
    VectorList* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == VectorListMagic)
            ret = static_cast<VectorListData*>(handle)->Pointer();
        else
            bu_log("CastVectorList: wrong handle");
    }

    return ret;
}


ConstDatabase* CastConstDatabase
(
    BrlHandle handle
) {
    ConstDatabase* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == ConstDatabaseMagic)
            ret = static_cast<ConstDatabaseData*>(handle)->Pointer();
        else if (handleMagic == FileDatabaseMagic)
            ret = static_cast<FileDatabaseData*>(handle)->Pointer();
        else if (handleMagic == MemoryDatabaseMagic)
            ret = static_cast<MemoryDatabaseData*>(handle)->Pointer();
        else
            bu_log("CastConstDatabase: wrong handle");
    }

    return ret;
}


Database* CastDatabase
(
    BrlHandle handle
) {
    Database* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == FileDatabaseMagic)
            ret = static_cast<FileDatabaseData*>(handle)->Pointer();
        else if (handleMagic == MemoryDatabaseMagic)
            ret = static_cast<MemoryDatabaseData*>(handle)->Pointer();
        else
            bu_log("CastDatabase: wrong handle or read-only database");
    }

    return ret;
}


FileDatabase* CastFileDatabase
(
    BrlHandle handle
) {
    FileDatabase* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == FileDatabaseMagic)
            ret = static_cast<FileDatabaseData*>(handle)->Pointer();
        else
            bu_log("CastFileDatabase: wrong handle or read-only database");
    }

    return ret;
}


MemoryDatabase* CastMemoryDatabase
(
    BrlHandle handle
) {
    MemoryDatabase* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == MemoryDatabaseMagic)
            ret = static_cast<MemoryDatabaseData*>(handle)->Pointer();
        else
            bu_log("CastMemoryDatabase: wrong handle or read-only database");
    }

    return ret;
}


Object* CastObject
(
    BrlHandle handle
) {
    Object* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == ObjectMagic)
            ret = static_cast<ObjectData*>(handle)->Pointer();
        else if (handleMagic == Arb8Magic)
            ret = static_cast<Arb8Data*>(handle)->Pointer();
        else if (handleMagic == NonManifoldGeometryMagic)
            ret = static_cast<NonManifoldGeometryData*>(handle)->Pointer();
        else
            bu_log("CastObject: wrong handle");
    }

    return ret;
}


Arb8* CastArb8
(
    BrlHandle handle
) {
    Arb8* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == Arb8Magic)
            ret = static_cast<Arb8Data*>(handle)->Pointer();
        else
            bu_log("CastArb8: wrong handle");
    }

    return ret;
}


NonManifoldGeometry* CastNonManifoldGeometry
(
    BrlHandle handle
) {
    NonManifoldGeometry* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == NonManifoldGeometryMagic)
            ret = static_cast<NonManifoldGeometryData*>(handle)->Pointer();
        else
            bu_log("NonManifoldGeometry: wrong handle");
    }

    return ret;
}
