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


Handle* CastHandle
(
    void* handle
) {
    Handle* ret = nullptr;

    if (handle != nullptr) {
        Handle* testHandle = static_cast<Handle*>(handle);

        const char* handleMagic = testHandle->Magic();

        if ((handleMagic == VectorListMagic) ||
            (handleMagic == ConstDatabaseMagic) ||
            (handleMagic == FileDatabaseMagic) ||
            (handleMagic == MemoryDatabaseMagic) ||
            (handleMagic == Arb8Magic) ||
            (handleMagic == NonManifoldGeometryMagic))
            ret = testHandle;
        else
            bu_log("CastHandle: invalid handle");
    }

    return ret;
}


VectorList* CastVectorList
(
    void* handle
) {
    VectorList* ret = nullptr;

    if (handle != nullptr) {
        Handle* testHandle = static_cast<Handle*>(handle);

        const char* handleMagic = testHandle->Magic();

        if (handleMagic == VectorListMagic)
            ret = static_cast<VectorListHandle*>(handle)->Pointer();
        else
            bu_log("CastVectorList: wrong handle");
    }

    return ret;
}


ConstDatabase* CastConstDatabase
(
    void* handle
) {
    ConstDatabase* ret = nullptr;

    if (handle != nullptr) {
        Handle* testHandle = static_cast<Handle*>(handle);

        const char* handleMagic = testHandle->Magic();

        if (handleMagic == ConstDatabaseMagic)
            ret = static_cast<ConstDatabaseHandle*>(handle)->Pointer();
        else if (handleMagic == FileDatabaseMagic)
            ret = static_cast<FileDatabaseHandle*>(handle)->Pointer();
        else if (handleMagic == MemoryDatabaseMagic)
            ret = static_cast<MemoryDatabaseHandle*>(handle)->Pointer();
        else
            bu_log("CastConstDatabase: wrong handle");
    }

    return ret;
}


Database* CastDatabase
(
    void* handle
) {
    Database* ret = nullptr;

    if (handle != nullptr) {
        Handle* testHandle = static_cast<Handle*>(handle);

        const char* handleMagic = testHandle->Magic();

        if (handleMagic == FileDatabaseMagic)
            ret = static_cast<FileDatabaseHandle*>(handle)->Pointer();
        else if (handleMagic == MemoryDatabaseMagic)
            ret = static_cast<MemoryDatabaseHandle*>(handle)->Pointer();
        else
            bu_log("CastDatabase: wrong handle or read-only database");
    }

    return ret;
}


FileDatabase* CastFileDatabase
(
    void* handle
) {
    FileDatabase* ret = nullptr;

    if (handle != nullptr) {
        Handle* testHandle = static_cast<Handle*>(handle);

        const char* handleMagic = testHandle->Magic();

        if (handleMagic == FileDatabaseMagic)
            ret = static_cast<FileDatabaseHandle*>(handle)->Pointer();
        else
            bu_log("CastFileDatabase: wrong handle or read-only database");
    }

    return ret;
}


MemoryDatabase* CastMemoryDatabase
(
    void* handle
) {
    MemoryDatabase* ret = nullptr;

    if (handle != nullptr) {
        Handle* testHandle = static_cast<Handle*>(handle);

        const char* handleMagic = testHandle->Magic();

        if (handleMagic == MemoryDatabaseMagic)
            ret = static_cast<MemoryDatabaseHandle*>(handle)->Pointer();
        else
            bu_log("CastMemoryDatabase: wrong handle or read-only database");
    }

    return ret;
}


Object* CastObject
(
    void* handle
) {
    Object* ret = nullptr;

    if (handle != nullptr) {
        Handle* testHandle = static_cast<Handle*>(handle);

        const char* handleMagic = testHandle->Magic();

        if (handleMagic == Arb8Magic)
            ret = static_cast<Arb8Handle*>(handle)->Pointer();
        else if (handleMagic == NonManifoldGeometryMagic)
            ret = static_cast<NonManifoldGeometryHandle*>(handle)->Pointer();
        else
            bu_log("CastObject: wrong handle");
    }

    return ret;
}


Arb8* CastArb8
(
    void* handle
) {
    Arb8* ret = nullptr;

    if (handle != nullptr) {
        Handle* testHandle = static_cast<Handle*>(handle);

        const char* handleMagic = testHandle->Magic();

        if (handleMagic == Arb8Magic)
            ret = static_cast<Arb8Handle*>(handle)->Pointer();
        else
            bu_log("CastArb8: wrong handle");
    }

    return ret;
}


NonManifoldGeometry* CastNonManifoldGeometry
(
    void* handle
) {
    NonManifoldGeometry* ret = nullptr;

    if (handle != nullptr) {
        Handle* testHandle = static_cast<Handle*>(handle);

        const char* handleMagic = testHandle->Magic();

        if (handleMagic == NonManifoldGeometryMagic)
            ret = static_cast<NonManifoldGeometryHandle*>(handle)->Pointer();
        else
            bu_log("NonManifoldGeometry: wrong handle");
    }

    return ret;
}
