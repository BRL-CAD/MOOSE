/*                      B R L D A T A . H
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
/** @file BrlData.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares the base for all handles
 */

#ifndef BRLCAD_C_BRLDATA_INCLUDED
#define BRLCAD_C_BRLDATA_INCLUDED

#include <brlcad/VectorList.h>
#include <brlcad/Database/FileDatabase.h>
#include <brlcad/Database/MemoryDatabase.h>
#include <brlcad/Database/Arb8.h>
#include <brlcad/Database/Cone.h>
#include <brlcad/Database/Ellipsoid.h>
#include <brlcad/Database/NonManifoldGeometry.h>
#include <brlcad/Database/Sphere.h>
#include <brlcad/Database/Combination.h>


class BrlData {
public:
    BrlData(void) : m_magic(nullptr) {}

    BrlData(const char* magic) : m_magic(magic) {}

    virtual ~BrlData(void) {
        m_magic = nullptr;
    }

    const char* Magic(void) const {
        return m_magic;
    }

protected:
    const char* m_magic;

    // protect not implemented methods
    BrlData(const BrlData& original);
    const BrlData& operator=(const BrlData& original);
};


extern const char* const Vector3DMagic;
extern const char* const VectorListMagic;
extern const char* const ConstDatabaseMagic;
extern const char* const FileDatabaseMagic;
extern const char* const MemoryDatabaseMagic;
extern const char* const ObjectMagic;
extern const char* const Arb8Magic;
extern const char* const ConeMagic;
extern const char* const EllipsoidMagic;
extern const char* const NonManifoldGeometryMagic;
extern const char* const SphereMagic;
extern const char* const CombinationMagic;
extern const char* const TreeNodeMagic;
extern const char* const AttributeIteratorMagic;


template<class ValueType> class ValueData : public BrlData {
public:
    ValueData(const char*      magic,
              const ValueType& value) : BrlData(magic), m_value(value) {}

    ~ValueData(void) override {}

    const ValueType& Value(void) const {
        return m_value;
    }

    ValueType&       Value(void) {
        return m_value;
    }

private:
    ValueType m_value;

    // protect not implemented methods
    ValueData(void);
    ValueData(const ValueData& original);
    const ValueData& operator=(const ValueData& original);
};


template<class PointerType> class PointerData : public BrlData {
public:
    PointerData(const char*  magic,
                PointerType* pointer) : BrlData(magic), m_pointer(pointer) {}

    ~PointerData(void) override {
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
    PointerData(void);
    PointerData(const PointerData& original);
    const PointerData& operator=(const PointerData& original);
};


class Vector3DData : public ValueData<BRLCAD::Vector3D> {
public:
    Vector3DData(const BRLCAD::Vector3D& value) : ValueData(Vector3DMagic, value) {}
};


class VectorListData : public PointerData<BRLCAD::VectorList> {
public:
    VectorListData(BRLCAD::VectorList* pointer) : PointerData(VectorListMagic, pointer) {}
};


class ConstDatabaseData : public PointerData<BRLCAD::ConstDatabase> {
public:
    ConstDatabaseData(BRLCAD::ConstDatabase* pointer) : PointerData(ConstDatabaseMagic, pointer) {}
};


class FileDatabaseData : public PointerData<BRLCAD::FileDatabase> {
public:
    FileDatabaseData(BRLCAD::FileDatabase* pointer) : PointerData(FileDatabaseMagic, pointer) {}
};


class MemoryDatabaseData : public PointerData<BRLCAD::MemoryDatabase> {
public:
    MemoryDatabaseData(BRLCAD::MemoryDatabase* pointer) : PointerData(MemoryDatabaseMagic, pointer) {}
};


class ObjectData : public PointerData<BRLCAD::Object> {
public:
    ObjectData(BRLCAD::Object* pointer) : PointerData(ObjectMagic, pointer) {}
};


class Arb8Data : public PointerData<BRLCAD::Arb8> {
public:
    Arb8Data(BRLCAD::Arb8* pointer) : PointerData(Arb8Magic, pointer) {}
};


class ConeData : public PointerData<BRLCAD::Cone> {
public:
    ConeData(BRLCAD::Cone* pointer) : PointerData(ConeMagic, pointer) {}
};


class EllipsoidData : public PointerData<BRLCAD::Ellipsoid> {
public:
    EllipsoidData(BRLCAD::Ellipsoid* pointer) : PointerData(EllipsoidMagic, pointer) {}
};


class NonManifoldGeometryData : public PointerData<BRLCAD::NonManifoldGeometry> {
public:
    NonManifoldGeometryData(BRLCAD::NonManifoldGeometry* pointer) : PointerData(NonManifoldGeometryMagic, pointer) {}
};


class SphereData : public PointerData<BRLCAD::Sphere> {
public:
    SphereData(BRLCAD::Sphere* pointer) : PointerData(SphereMagic, pointer) {}
};


class CombinationData : public PointerData<BRLCAD::Combination> {
public:
    CombinationData(BRLCAD::Combination* pointer) : PointerData(CombinationMagic, pointer) {}
};


class TreeNodeData : public ValueData<BRLCAD::Combination::TreeNode> {
public:
    TreeNodeData(const BRLCAD::Combination::TreeNode& value) : ValueData(TreeNodeMagic, value) {}
};


class AttributeIteratorData : public ValueData<BRLCAD::Object::AttributeIterator> {
public:
    AttributeIteratorData(const BRLCAD::Object::AttributeIterator& value) : ValueData(AttributeIteratorMagic, value) {}
};


#endif // BRLCAD_C_BRLDATA_INCLUDED
