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

#include <brlcad/Database/Arb8.h>
#include <brlcad/Database/BagOfTriangles.h>
#include <brlcad/Database/Combination.h>
#include <brlcad/Database/Cone.h>
#include <brlcad/Database/Ellipsoid.h>
#include <brlcad/Database/EllipticalTorus.h>
#include <brlcad/Database/FileDatabase.h>
#include <brlcad/Database/Halfspace.h>
#include <brlcad/Database/HyperbolicCylinder.h>
#include <brlcad/Database/Hyperboloid.h>
#include <brlcad/Database/MemoryDatabase.h>
#include <brlcad/Database/NonManifoldGeometry.h>
#include <brlcad/Database/ParabolicCylinder.h>
#include <brlcad/Database/Paraboloid.h>
#include <brlcad/Database/Particle.h>
#include <brlcad/Database/Pipe.h>
#include <brlcad/Database/Sketch.h>
#include <brlcad/Database/Sphere.h>
#include <brlcad/Database/Torus.h>
#include <brlcad/Database/Unknown.h>
#include <brlcad/VectorList.h>


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


extern const char* const Vector2DMagic;
extern const char* const Vector3DMagic;
extern const char* const VectorListMagic;
extern const char* const VectorListElementMagic;
extern const char* const VectorListDisplaySpaceMagic;
extern const char* const VectorListPointDrawMagic;
extern const char* const VectorListPointSizeMagic;
extern const char* const VectorListLineMoveMagic;
extern const char* const VectorListLineDrawMagic;
extern const char* const VectorListLineWidthMagic;
extern const char* const VectorListModelSpaceMagic;
extern const char* const VectorListPolygonStartMagic;
extern const char* const VectorListPolygonMoveMagic;
extern const char* const VectorListPolygonDrawMagic;
extern const char* const VectorListPolygonEndMagic;
extern const char* const VectorListPolygonVertexNormalMagic;
extern const char* const VectorListTriangleStartMagic;
extern const char* const VectorListTriangleMoveMagic;
extern const char* const VectorListTriangleDrawMagic;
extern const char* const VectorListTriangleEndMagic;
extern const char* const VectorListTriangleVertexNormalMagic;
extern const char* const ConstDatabaseMagic;
extern const char* const FileDatabaseMagic;
extern const char* const MemoryDatabaseMagic;
extern const char* const ObjectMagic;
extern const char* const ObjectAttributeIteratorMagic;
extern const char* const Arb8Magic;
extern const char* const BagOfTrianglesMagic;
extern const char* const BagOfTrianglesFaceMagic;
extern const char* const CombinationMagic;
extern const char* const CombinationTreeNodeMagic;
extern const char* const ConeMagic;
extern const char* const EllipsoidMagic;
extern const char* const EllipticalTorusMagic;
extern const char* const HalfspaceMagic;
extern const char* const HyperbolicCylinderMagic;
extern const char* const HyperboloidMagic;
extern const char* const NonManifoldGeometryMagic;
extern const char* const NonManifoldGeometryVertexMagic;
extern const char* const NonManifoldGeometryEdgeMagic;
extern const char* const NonManifoldGeometryLoopMagic;
extern const char* const NonManifoldGeometryFaceMagic;
extern const char* const NonManifoldGeometryShellMagic;
extern const char* const NonManifoldGeometryRegionMagic;
extern const char* const NonManifoldGeometryRegionIteratorMagic;
extern const char* const ParabolicCylinderMagic;
extern const char* const ParaboloidMagic;
extern const char* const ParticleMagic;
extern const char* const PipeMagic;
extern const char* const PipeControlPointMagic;
extern const char* const SketchMagic;
extern const char* const SketchSegmentMagic;
extern const char* const SketchLineMagic;
extern const char* const SketchCircularArcMagic;
extern const char* const SketchNurbMagic;
extern const char* const SketchBezierMagic;
extern const char* const SphereMagic;
extern const char* const TorusMagic;
extern const char* const UnknownMagic;


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
                PointerType* pointer, bool owned = true) : BrlData(magic), m_pointer(pointer), m_owned(owned) {}

    ~PointerData(void) override {
        if (m_owned && m_pointer != nullptr)
            delete m_pointer;
    }

    const PointerType* Pointer(void) const {
        return m_pointer;
    }

    PointerType*       Pointer(void) {
        return m_pointer;
    }

protected:
    bool m_owned;
private:
    PointerType* m_pointer;

    // protect not implemented methods
    PointerData(void);
    PointerData(const PointerData& original);
    const PointerData& operator=(const PointerData& original);
};


class Vector2DData : public ValueData<BRLCAD::Vector2D> {
public:
    Vector2DData(const BRLCAD::Vector2D& value) : ValueData(Vector2DMagic, value) {}
};


class Vector3DData : public ValueData<BRLCAD::Vector3D> {
public:
    Vector3DData(const BRLCAD::Vector3D& value) : ValueData(Vector3DMagic, value) {}
};


class VectorListData : public PointerData<BRLCAD::VectorList> {
public:
    VectorListData(BRLCAD::VectorList* pointer) : PointerData(VectorListMagic, pointer) {}
};


class VectorListElementData : public PointerData<BRLCAD::VectorList::Element> {
public:
    VectorListElementData(BRLCAD::VectorList::Element* pointer, bool owned = true) : PointerData(VectorListElementMagic, pointer, owned) {}
};


class VectorListDisplaySpaceData : public PointerData<BRLCAD::VectorList::DisplaySpace> {
public:
    VectorListDisplaySpaceData(BRLCAD::VectorList::DisplaySpace* pointer, bool owned = true) : PointerData(VectorListDisplaySpaceMagic, pointer, owned) {}
};


class VectorListPointDrawData : public PointerData<BRLCAD::VectorList::PointDraw> {
public:
    VectorListPointDrawData(BRLCAD::VectorList::PointDraw* pointer, bool owned = true) : PointerData(VectorListPointDrawMagic, pointer, owned) {}
};


class VectorListPointSizeData : public PointerData<BRLCAD::VectorList::PointSize> {
public:
    VectorListPointSizeData(BRLCAD::VectorList::PointSize* pointer, bool owned = true) : PointerData(VectorListPointSizeMagic, pointer, owned) {}
};


class VectorListLineMoveData : public PointerData<BRLCAD::VectorList::LineMove> {
public:
    VectorListLineMoveData(BRLCAD::VectorList::LineMove* pointer, bool owned = true) : PointerData(VectorListLineMoveMagic, pointer, owned) {}
};


class VectorListLineDrawData : public PointerData<BRLCAD::VectorList::LineDraw> {
public:
    VectorListLineDrawData(BRLCAD::VectorList::LineDraw* pointer, bool owned = true) : PointerData(VectorListLineDrawMagic, pointer, owned) {}
};


class VectorListLineWidthData : public PointerData<BRLCAD::VectorList::LineWidth> {
public:
    VectorListLineWidthData(BRLCAD::VectorList::LineWidth* pointer, bool owned = true) : PointerData(VectorListLineWidthMagic, pointer, owned) {}
};


class VectorListModelSpaceData : public PointerData<BRLCAD::VectorList::ModelSpace> {
public:
    VectorListModelSpaceData(BRLCAD::VectorList::ModelSpace* pointer, bool owned = true) : PointerData(VectorListModelSpaceMagic, pointer, owned) {}
};


class VectorListPolygonStartData : public PointerData<BRLCAD::VectorList::PolygonStart> {
public:
    VectorListPolygonStartData(BRLCAD::VectorList::PolygonStart* pointer, bool owned = true) : PointerData(VectorListPolygonStartMagic, pointer, owned) {}
};


class VectorListPolygonMoveData : public PointerData<BRLCAD::VectorList::PolygonMove> {
public:
    VectorListPolygonMoveData(BRLCAD::VectorList::PolygonMove* pointer, bool owned = true) : PointerData(VectorListPolygonMoveMagic, pointer, owned) {}
};


class VectorListPolygonDrawData : public PointerData<BRLCAD::VectorList::PolygonDraw> {
public:
    VectorListPolygonDrawData(BRLCAD::VectorList::PolygonDraw* pointer, bool owned = true) : PointerData(VectorListPolygonDrawMagic, pointer, owned) {}
};


class VectorListPolygonEndData : public PointerData<BRLCAD::VectorList::PolygonEnd> {
public:
    VectorListPolygonEndData(BRLCAD::VectorList::PolygonEnd* pointer, bool owned = true) : PointerData(VectorListPolygonEndMagic, pointer, owned) {}
};


class VectorListPolygonVertexNormalData : public PointerData<BRLCAD::VectorList::PolygonVertexNormal> {
public:
    VectorListPolygonVertexNormalData(BRLCAD::VectorList::PolygonVertexNormal* pointer, bool owned = true) : PointerData(VectorListPolygonVertexNormalMagic, pointer, owned) {}
};


class VectorListTriangleStartData : public PointerData<BRLCAD::VectorList::TriangleStart> {
public:
    VectorListTriangleStartData(BRLCAD::VectorList::TriangleStart* pointer, bool owned = true) : PointerData(VectorListTriangleStartMagic, pointer, owned) {}
};


class VectorListTriangleMoveData : public PointerData<BRLCAD::VectorList::TriangleMove> {
public:
    VectorListTriangleMoveData(BRLCAD::VectorList::TriangleMove* pointer, bool owned = true) : PointerData(VectorListTriangleMoveMagic, pointer, owned) {}
};


class VectorListTriangleDrawData : public PointerData<BRLCAD::VectorList::TriangleDraw> {
public:
    VectorListTriangleDrawData(BRLCAD::VectorList::TriangleDraw* pointer, bool owned = true) : PointerData(VectorListTriangleDrawMagic, pointer, owned) {}
};


class VectorListTriangleEndData : public PointerData<BRLCAD::VectorList::TriangleEnd> {
public:
    VectorListTriangleEndData(BRLCAD::VectorList::TriangleEnd* pointer, bool owned = true) : PointerData(VectorListTriangleEndMagic, pointer, owned) {}
};


class VectorListTriangleVertexNormalData : public PointerData<BRLCAD::VectorList::TriangleVertexNormal> {
public:
    VectorListTriangleVertexNormalData(BRLCAD::VectorList::TriangleVertexNormal* pointer, bool owned = true) : PointerData(VectorListTriangleVertexNormalMagic, pointer, owned) {}
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


class ObjectAttributeIteratorData : public ValueData<BRLCAD::Object::AttributeIterator> {
public:
    ObjectAttributeIteratorData(const BRLCAD::Object::AttributeIterator& value) : ValueData(ObjectAttributeIteratorMagic, value) {}
};


class Arb8Data : public PointerData<BRLCAD::Arb8> {
public:
    Arb8Data(BRLCAD::Arb8* pointer) : PointerData(Arb8Magic, pointer) {}
};


class BagOfTrianglesData : public PointerData<BRLCAD::BagOfTriangles> {
public:
    BagOfTrianglesData(BRLCAD::BagOfTriangles* pointer) : PointerData(BagOfTrianglesMagic, pointer) {}
};


class BagOfTrianglesFaceData : public ValueData<BRLCAD::BagOfTriangles::Face> {
public:
    BagOfTrianglesFaceData(const BRLCAD::BagOfTriangles::Face& value) : ValueData(BagOfTrianglesFaceMagic, value) {}
};


class CombinationData : public PointerData<BRLCAD::Combination> {
public:
    CombinationData(BRLCAD::Combination* pointer) : PointerData(CombinationMagic, pointer) {}
};


class CombinationTreeNodeData : public ValueData<BRLCAD::Combination::TreeNode> {
public:
    CombinationTreeNodeData(const BRLCAD::Combination::TreeNode& value) : ValueData(CombinationTreeNodeMagic, value) {}
};


class ConeData : public PointerData<BRLCAD::Cone> {
public:
    ConeData(BRLCAD::Cone* pointer) : PointerData(ConeMagic, pointer) {}
};


class EllipsoidData : public PointerData<BRLCAD::Ellipsoid> {
public:
    EllipsoidData(BRLCAD::Ellipsoid* pointer) : PointerData(EllipsoidMagic, pointer) {}
};


class EllipticalTorusData : public PointerData<BRLCAD::EllipticalTorus> {
public:
    EllipticalTorusData(BRLCAD::EllipticalTorus* pointer) : PointerData(EllipticalTorusMagic, pointer) {}
};


class HalfspaceData : public PointerData<BRLCAD::Halfspace> {
public:
    HalfspaceData(BRLCAD::Halfspace* pointer) : PointerData(HalfspaceMagic, pointer) {}
};


class HyperbolicCylinderData : public PointerData<BRLCAD::HyperbolicCylinder> {
public:
    HyperbolicCylinderData(BRLCAD::HyperbolicCylinder* pointer) : PointerData(HyperbolicCylinderMagic, pointer) {}
};


class HyperboloidData : public PointerData<BRLCAD::Hyperboloid> {
public:
    HyperboloidData(BRLCAD::Hyperboloid* pointer) : PointerData(HyperboloidMagic, pointer) {}
};


class NonManifoldGeometryData : public PointerData<BRLCAD::NonManifoldGeometry> {
public:
    NonManifoldGeometryData(BRLCAD::NonManifoldGeometry* pointer) : PointerData(NonManifoldGeometryMagic, pointer) {}
};


class NonManifoldGeometryVertexData : public ValueData<BRLCAD::NonManifoldGeometry::Vertex> {
public:
    NonManifoldGeometryVertexData(const BRLCAD::NonManifoldGeometry::Vertex& value) : ValueData(NonManifoldGeometryVertexMagic, value) {}
};


class NonManifoldGeometryEdgeData : public ValueData<BRLCAD::NonManifoldGeometry::Edge> {
public:
    NonManifoldGeometryEdgeData(const BRLCAD::NonManifoldGeometry::Edge& value) : ValueData(NonManifoldGeometryEdgeMagic, value) {}
};


class NonManifoldGeometryLoopData : public ValueData<BRLCAD::NonManifoldGeometry::Loop> {
public:
    NonManifoldGeometryLoopData(const BRLCAD::NonManifoldGeometry::Loop& value) : ValueData(NonManifoldGeometryLoopMagic, value) {}
};


class NonManifoldGeometryFaceData : public ValueData<BRLCAD::NonManifoldGeometry::Face> {
public:
    NonManifoldGeometryFaceData(const BRLCAD::NonManifoldGeometry::Face& value) : ValueData(NonManifoldGeometryFaceMagic, value) {}
};


class NonManifoldGeometryShellData : public ValueData<BRLCAD::NonManifoldGeometry::Shell> {
public:
    NonManifoldGeometryShellData(const BRLCAD::NonManifoldGeometry::Shell& value) : ValueData(NonManifoldGeometryShellMagic, value) {}
};


class NonManifoldGeometryRegionData : public ValueData<BRLCAD::NonManifoldGeometry::Region> {
public:
    NonManifoldGeometryRegionData(const BRLCAD::NonManifoldGeometry::Region& value) : ValueData(NonManifoldGeometryRegionMagic, value) {}
};


class NonManifoldGeometryRegionIteratorData : public ValueData<BRLCAD::NonManifoldGeometry::RegionIterator> {
public:
    NonManifoldGeometryRegionIteratorData(const BRLCAD::NonManifoldGeometry::RegionIterator& value) : ValueData(NonManifoldGeometryRegionIteratorMagic, value) {}
};


class ParabolicCylinderData : public PointerData<BRLCAD::ParabolicCylinder> {
public:
    ParabolicCylinderData(BRLCAD::ParabolicCylinder* pointer) : PointerData(ParabolicCylinderMagic, pointer) {}
};


class ParaboloidData : public PointerData<BRLCAD::Paraboloid> {
public:
    ParaboloidData(BRLCAD::Paraboloid* pointer) : PointerData(ParaboloidMagic, pointer) {}
};


class ParticleData : public PointerData<BRLCAD::Particle> {
public:
    ParticleData(BRLCAD::Particle* pointer) : PointerData(ParticleMagic, pointer) {}
};


class PipeData : public PointerData<BRLCAD::Pipe> {
public:
    PipeData(BRLCAD::Pipe* pointer) : PointerData(PipeMagic, pointer) {}
};


class PipeControlPointData : public ValueData<BRLCAD::Pipe::ControlPoint> {
public:
    PipeControlPointData(const BRLCAD::Pipe::ControlPoint& value) : ValueData(PipeControlPointMagic, value) {}
};


class SketchData : public PointerData<BRLCAD::Sketch> {
public:
    SketchData(BRLCAD::Sketch* pointer) : PointerData(SketchMagic, pointer) {}
};


class SketchSegmentData : public PointerData<BRLCAD::Sketch::Segment> {
public:
    SketchSegmentData(BRLCAD::Sketch::Segment* pointer) : PointerData(SketchSegmentMagic, pointer) {}
};


class SketchLineData : public PointerData<BRLCAD::Sketch::Line> {
public:
    SketchLineData(BRLCAD::Sketch::Line* pointer) : PointerData(SketchLineMagic, pointer) {}
};


class SketchCircularArcData : public PointerData<BRLCAD::Sketch::CircularArc> {
public:
    SketchCircularArcData(BRLCAD::Sketch::CircularArc* pointer) : PointerData(SketchCircularArcMagic, pointer) {}
};


class SketchNurbData : public PointerData<BRLCAD::Sketch::Nurb> {
public:
    SketchNurbData(BRLCAD::Sketch::Nurb* pointer) : PointerData(SketchNurbMagic, pointer) {}
};


class SketchBezierData : public PointerData<BRLCAD::Sketch::Bezier> {
public:
    SketchBezierData(BRLCAD::Sketch::Bezier* pointer) : PointerData(SketchBezierMagic, pointer) {}
};


class SphereData : public PointerData<BRLCAD::Sphere> {
public:
    SphereData(BRLCAD::Sphere* pointer) : PointerData(SphereMagic, pointer) {}
};


class TorusData : public PointerData<BRLCAD::Torus> {
public:
    TorusData(BRLCAD::Torus* pointer) : PointerData(TorusMagic, pointer) {}
};


class UnknownData : public PointerData<BRLCAD::Unknown> {
public:
    UnknownData(BRLCAD::Unknown* pointer) : PointerData(UnknownMagic, pointer) {}
};

#endif // BRLCAD_C_BRLDATA_INCLUDED
