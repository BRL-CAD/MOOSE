/*                      H A N D L E . H
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
/** @file Handle.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares the base for all handles
 */

#ifndef BRLCAD_C_HANDLE_INCLUDED
#define BRLCAD_C_HANDLE_INCLUDED

#include <brlcad/VectorList.h>
#include <brlcad/Database/FileDatabase.h>
#include <brlcad/Database/MemoryDatabase.h>
#include <brlcad/Database/Arb8.h>
#include <brlcad/Database/NonManifoldGeometry.h>


class Handle {
public:
    Handle(void) : m_magic(nullptr) {}

    Handle(const char* magic) : m_magic(magic) {}

    virtual ~Handle(void) {
        m_magic = nullptr;
    }

    const char* Magic(void) const {
        return m_magic;
    }

protected:
    const char* m_magic;

    // protect not implemented methods
    Handle(const Handle& original);
    const Handle& operator=(const Handle& original);
};


extern const char* const VectorListMagic;
extern const char* const ConstDatabaseMagic;
extern const char* const FileDatabaseMagic;
extern const char* const MemoryDatabaseMagic;
extern const char* const Arb8Magic;
extern const char* const NonManifoldGeometryMagic;


template<class PointerType> class PointerHandle : public Handle {
public:
    PointerHandle(const char*  magic,
                  PointerType* pointer) : Handle(magic), m_pointer(pointer) {}

    ~PointerHandle(void) override {
        if (m_pointer != nullptr)
            delete m_pointer;
    }

    const PointerType* Pointer(void) const {
        return m_pointer;
    }

    PointerType*       Pointer(void) {
        return m_pointer;
    }

private:
    PointerType* m_pointer;

    // protect not implemented methods
    PointerHandle(void);
    PointerHandle(const PointerHandle& original);
    const PointerHandle& operator=(const PointerHandle& original);
};


class VectorListHandle : public PointerHandle<BRLCAD::VectorList> {
public:
    VectorListHandle(BRLCAD::VectorList* pointer) : PointerHandle(VectorListMagic, pointer) {}
};


class ConstDatabaseHandle : public PointerHandle<BRLCAD::ConstDatabase> {
public:
    ConstDatabaseHandle(BRLCAD::ConstDatabase* pointer) : PointerHandle(ConstDatabaseMagic, pointer) {}
};


class FileDatabaseHandle : public PointerHandle<BRLCAD::FileDatabase> {
public:
    FileDatabaseHandle(BRLCAD::FileDatabase* pointer) : PointerHandle(FileDatabaseMagic, pointer) {}
};


class MemoryDatabaseHandle : public PointerHandle<BRLCAD::MemoryDatabase> {
public:
    MemoryDatabaseHandle(BRLCAD::MemoryDatabase* pointer) : PointerHandle(MemoryDatabaseMagic, pointer) {}
};


class Arb8Handle : public PointerHandle<BRLCAD::Arb8> {
public:
    Arb8Handle(BRLCAD::Arb8* pointer) : PointerHandle(Arb8Magic, pointer) {}
};


class NonManifoldGeometryHandle : public PointerHandle<BRLCAD::NonManifoldGeometry> {
public:
    NonManifoldGeometryHandle(BRLCAD::NonManifoldGeometry* pointer) : PointerHandle(NonManifoldGeometryMagic, pointer) {}
};


#endif // BRLCAD_C_HANDLE_INCLUDED
