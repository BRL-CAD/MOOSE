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

#include <cstring>

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
            (handleMagic == ObjectAttributeIteratorMagic) ||
            (handleMagic == Arb8Magic) ||
            (handleMagic == BagOfTrianglesMagic) ||
            (handleMagic == BagOfTrianglesFaceMagic) ||
            (handleMagic == CombinationMagic) ||
            (handleMagic == CombinationTreeNodeMagic) ||
            (handleMagic == ConeMagic) ||
            (handleMagic == EllipsoidMagic) ||
            (handleMagic == EllipticalTorusMagic) ||
            (handleMagic == HyperbolicCylinderMagic) ||
            (handleMagic == NonManifoldGeometryMagic) ||
            (handleMagic == NonManifoldGeometryVertexMagic) ||
            (handleMagic == NonManifoldGeometryEdgeMagic) ||
            (handleMagic == NonManifoldGeometryLoopMagic) ||
            (handleMagic == NonManifoldGeometryFaceMagic) ||
            (handleMagic == NonManifoldGeometryShellMagic) ||
            (handleMagic == NonManifoldGeometryRegionMagic) ||
            (handleMagic == NonManifoldGeometryRegionIteratorMagic) ||
            (handleMagic == SphereMagic) ||
            (handleMagic == TorusMagic))
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
            bu_log("CastVector3D: wrong handle");
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
        else if (handleMagic == BagOfTrianglesMagic)
            ret = static_cast<BagOfTrianglesData*>(handle)->Pointer();
        else if (handleMagic == CombinationMagic)
            ret = static_cast<CombinationData*>(handle)->Pointer();
        else if (handleMagic == ConeMagic)
            ret = static_cast<ConeData*>(handle)->Pointer();
        else if (handleMagic == EllipsoidMagic)
            ret = static_cast<EllipsoidData*>(handle)->Pointer();
        else if (handleMagic == EllipticalTorusMagic)
            ret = static_cast<EllipticalTorusData*>(handle)->Pointer();
        else if (handleMagic == HyperbolicCylinderMagic)
            ret = static_cast<HyperbolicCylinderData*>(handle)->Pointer();
        else if (handleMagic == NonManifoldGeometryMagic)
            ret = static_cast<NonManifoldGeometryData*>(handle)->Pointer();
        else if (handleMagic == SphereMagic)
            ret = static_cast<SphereData*>(handle)->Pointer();
        else if (handleMagic == TorusMagic)
            ret = static_cast<TorusData*>(handle)->Pointer();
        else
            bu_log("CastObject: wrong handle");
    }

    return ret;
}


Object::AttributeIterator* CastObjectAttributeIterator
(
    BrlHandle handle
) {
    Object::AttributeIterator* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == ObjectAttributeIteratorMagic)
            ret = &static_cast<ObjectAttributeIteratorData*>(handle)->Value();
        else
            bu_log("CastObjectAttributeIterator: wrong handle");
    }

    return ret;
}


BrlObject DowncastObject
(
    BRLCAD::Object* object
) {
    BrlObject ret = nullptr;

    if (object != nullptr) {
        const char* typeName = object->Type();

        if (typeName == BRLCAD::Arb8::ClassName())
            ret = new Arb8Data(static_cast<BRLCAD::Arb8*>(object));
        else if (typeName == BRLCAD::BagOfTriangles::ClassName())
            ret = new BagOfTrianglesData(static_cast<BRLCAD::BagOfTriangles*>(object));
        else if (typeName == BRLCAD::Combination::ClassName())
            ret = new CombinationData(static_cast<BRLCAD::Combination*>(object));
        else if (typeName == BRLCAD::Cone::ClassName())
            ret = new ConeData(static_cast<BRLCAD::Cone*>(object));
        else if (typeName == BRLCAD::Ellipsoid::ClassName())
            ret = new EllipsoidData(static_cast<BRLCAD::Ellipsoid*>(object));
        else if (typeName == BRLCAD::EllipticalTorus::ClassName())
            ret = new EllipticalTorusData(static_cast<BRLCAD::EllipticalTorus*>(object));
        else if (typeName == BRLCAD::HyperbolicCylinder::ClassName())
            ret = new HyperbolicCylinderData(static_cast<BRLCAD::HyperbolicCylinder*>(object));
        else if (typeName == BRLCAD::NonManifoldGeometry::ClassName())
            ret = new NonManifoldGeometryData(static_cast<BRLCAD::NonManifoldGeometry*>(object));
        else if (typeName == BRLCAD::Sphere::ClassName())
            ret = new SphereData(static_cast<BRLCAD::Sphere*>(object));
        else if (typeName == BRLCAD::Torus::ClassName())
            ret = new TorusData(static_cast<BRLCAD::Torus*>(object));
        else
            // Fallback for types not explicitly wrapped or unknown
            ret = new ObjectData(object);
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


BagOfTriangles* CastBagOfTriangles
(
    BrlHandle handle
) {
    BagOfTriangles* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == BagOfTrianglesMagic)
            ret = static_cast<BagOfTrianglesData*>(handle)->Pointer();
        else
            bu_log("CastBagOfTriangles: wrong handle");
    }

    return ret;
}


BagOfTriangles::Face* CastBagOfTrianglesFace
(
    BrlHandle handle
) {
    BagOfTriangles::Face* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == BagOfTrianglesFaceMagic)
            ret = &static_cast<BagOfTrianglesFaceData*>(handle)->Value();
        else
            bu_log("CastBagOfTrianglesFace: wrong handle");
    }

    return ret;
}


Combination* CastCombination
(
    BrlHandle handle
) {
    Combination* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == CombinationMagic)
            ret = static_cast<CombinationData*>(handle)->Pointer();
        else
            bu_log("CastCombination: wrong handle");
    }

    return ret;
}


Combination::TreeNode* CastCombinationTreeNode
(
    BrlHandle handle
) {
    Combination::TreeNode* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == CombinationTreeNodeMagic)
            ret = &static_cast<CombinationTreeNodeData*>(handle)->Value();
        else
            bu_log("CastCombinationTreeNode: wrong handle");
    }

    return ret;
}


Cone* CastCone
(
    BrlHandle handle
) {
    Cone* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == ConeMagic)
            ret = static_cast<ConeData*>(handle)->Pointer();
        else
            bu_log("CastCone: wrong handle");
    }

    return ret;
}


Ellipsoid* CastEllipsoid
(
    BrlHandle handle
) {
    Ellipsoid* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == EllipsoidMagic)
            ret = static_cast<EllipsoidData*>(handle)->Pointer();
        else
            bu_log("CastEllipsoid: wrong handle");
    }

    return ret;
}


EllipticalTorus* CastEllipticalTorus
(
    BrlHandle handle
) {
    EllipticalTorus* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == EllipticalTorusMagic)
            ret = static_cast<EllipticalTorusData*>(handle)->Pointer();
        else
            bu_log("CastEllipticalTorus: wrong handle");
    }

    return ret;
}


HyperbolicCylinder* CastHyperbolicCylinder
(
    BrlHandle handle
) {
    HyperbolicCylinder* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == HyperbolicCylinderMagic)
            ret = static_cast<HyperbolicCylinderData*>(handle)->Pointer();
        else
            bu_log("CastHyperbolicCylinder: wrong handle");
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
            bu_log("CastNonManifoldGeometry: wrong handle");
    }

    return ret;
}


NonManifoldGeometry::Vertex* CastNonManifoldGeometryVertex
(
    BrlHandle handle
) {
    NonManifoldGeometry::Vertex* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == NonManifoldGeometryVertexMagic)
            ret = &(static_cast<NonManifoldGeometryVertexData*>(handle)->Value());
        else
            bu_log("CastNonManifoldGeometryVertex: wrong handle");
    }

    return ret;
}


NonManifoldGeometry::Edge* CastNonManifoldGeometryEdge
(
    BrlHandle handle
) {
    NonManifoldGeometry::Edge* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == NonManifoldGeometryEdgeMagic)
            ret = &(static_cast<NonManifoldGeometryEdgeData*>(handle)->Value());
        else
            bu_log("CastNonManifoldGeometryEdge: wrong handle");
    }

    return ret;
}


NonManifoldGeometry::Loop* CastNonManifoldGeometryLoop
(
    BrlHandle handle
) {
    NonManifoldGeometry::Loop* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == NonManifoldGeometryLoopMagic)
            ret = &(static_cast<NonManifoldGeometryLoopData*>(handle)->Value());
        else
            bu_log("CastNonManifoldGeometryLoop: wrong handle");
    }

    return ret;
}


NonManifoldGeometry::Face* CastNonManifoldGeometryFace
(
    BrlHandle handle
) {
    NonManifoldGeometry::Face* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == NonManifoldGeometryFaceMagic)
            ret = &(static_cast<NonManifoldGeometryFaceData*>(handle)->Value());
        else
            bu_log("CastNonManifoldGeometryFace: wrong handle");
    }

    return ret;
}


NonManifoldGeometry::Shell* CastNonManifoldGeometryShell
(
    BrlHandle handle
) {
    NonManifoldGeometry::Shell* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == NonManifoldGeometryShellMagic)
            ret = &(static_cast<NonManifoldGeometryShellData*>(handle)->Value());
        else
            bu_log("CastNonManifoldGeometryShell: wrong handle");
    }

    return ret;
}


NonManifoldGeometry::Region* CastNonManifoldGeometryRegion
(
    BrlHandle handle
) {
    NonManifoldGeometry::Region* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == NonManifoldGeometryRegionMagic)
            ret = &(static_cast<NonManifoldGeometryRegionData*>(handle)->Value());
        else
            bu_log("CastNonManifoldGeometryRegion: wrong handle");
    }

    return ret;
}


NonManifoldGeometry::RegionIterator* CastNonManifoldGeometryRegionIterator
(
    BrlHandle handle
) {
    NonManifoldGeometry::RegionIterator* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == NonManifoldGeometryRegionIteratorMagic)
            ret = &(static_cast<NonManifoldGeometryRegionIteratorData*>(handle)->Value());
        else
            bu_log("CastNonManifoldGeometryRegionIterator: wrong handle");
    }

    return ret;
}


Sphere* CastSphere
(
    BrlHandle handle
) {
    Sphere* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == SphereMagic)
            ret = static_cast<SphereData*>(handle)->Pointer();
        else
            bu_log("CastSphere: wrong handle");
    }

    return ret;
}


Torus* CastTorus
(
    BrlHandle handle
) {
    Torus* ret = nullptr;

    if (handle != nullptr) {
        const char* handleMagic = handle->Magic();

        if (handleMagic == TorusMagic)
            ret = static_cast<TorusData*>(handle)->Pointer();
        else
            bu_log("CastTorus: wrong handle");
    }

    return ret;
}
