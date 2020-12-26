/*                    V E C T O R L I S T. C P P
 * BRL-CAD
 *
 * Copyright (c) 2020 United States Government as represented by
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
/** @file VectorList.cpp
 *
 *  BRL-CAD core C++ interface:
 *      vlist implementation
 */

#include <cassert>

#include "bu/parallel.h"
#include "rt/global.h"
#include "rt/vlist.h"

#include "init.h"

#include <brlcad/VectorList.h>


using namespace BRLCAD;


//
// BRLCAD::VectorList::PointDraw
//
const VectorList::PointDraw& VectorList::PointDraw::operator=
(
    const PointDraw& original
) {
    if (this != &original)
        SetPoint(original.Point());

    return *this;
}


VectorList::Element::ElementType VectorList::PointDraw::Type(void) const {
    return VectorList::Element::ElementType::PointDraw;
}


Vector3D VectorList::PointDraw::Point(void) const {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        return m_chunk->pt[m_index];
    }
    else
        return m_point;
}


void VectorList::PointDraw::SetPoint
(
    const Vector3D& point
) {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        VMOVE(m_chunk->pt[m_index], point.coordinates);
    }
    else
        m_point = point;
}


VectorList::PointDraw::PointDraw
(
    bn_vlist* chunk,
    size_t    index
) : VectorList::Element(chunk, index), m_point() {}


//
// BRLCAD::VectorList::PointSize
//
const VectorList::PointSize& VectorList::PointSize::operator=
(
    const PointSize& original
) {
    if (this != &original)
        SetSize(original.Size());

    return *this;
}


VectorList::Element::ElementType VectorList::PointSize::Type(void) const {
    return VectorList::Element::ElementType::PointSize;
}


double VectorList::PointSize::Size(void) const {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        return m_chunk->pt[m_index][0];
    }
    else
        return m_size;
}


void VectorList::PointSize::SetSize
(
    double size
) {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        m_chunk->pt[m_index][0] = size;
    }
    else
        m_size = size;
}


VectorList::PointSize::PointSize
(
    bn_vlist* chunk,
    size_t    index
) : VectorList::Element(chunk, index), m_size(1.) {}


//
// BRLCAD::VectorList::LineMove
//
const VectorList::LineMove& VectorList::LineMove::operator=
(
    const LineMove& original
) {
    if (this != &original)
        SetPoint(original.Point());

    return *this;
}


VectorList::Element::ElementType VectorList::LineMove::Type(void) const {
    return VectorList::Element::ElementType::LineMove;
}


Vector3D VectorList::LineMove::Point(void) const {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        return m_chunk->pt[m_index];
    }
    else
        return m_point;
}


void VectorList::LineMove::SetPoint
(
    const Vector3D& point
) {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        VMOVE(m_chunk->pt[m_index], point.coordinates);
    }
    else
        m_point = point;
}


VectorList::LineMove::LineMove
(
    bn_vlist* chunk,
    size_t    index
) : VectorList::Element(chunk, index), m_point() {}


//
// BRLCAD::VectorList::LineDraw
//
const VectorList::LineDraw& VectorList::LineDraw::operator=
(
    const LineDraw& original
) {
    if (this != &original)
        SetPoint(original.Point());

    return *this;
}


VectorList::Element::ElementType VectorList::LineDraw::Type(void) const {
    return VectorList::Element::ElementType::LineDraw;
}


Vector3D VectorList::LineDraw::Point(void) const {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        return m_chunk->pt[m_index];
    }
    else
        return m_point;
}


void VectorList::LineDraw::SetPoint
(
    const Vector3D& point
) {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        VMOVE(m_chunk->pt[m_index], point.coordinates);
    }
    else
        m_point = point;
}


VectorList::LineDraw::LineDraw
(
    bn_vlist* chunk,
    size_t    index
) : VectorList::Element(chunk, index), m_point() {}


//
// BRLCAD::VectorList::LineWidth
//
const VectorList::LineWidth& VectorList::LineWidth::operator=
(
    const LineWidth& original
) {
    if (this != &original)
        SetWidth(original.Width());

    return *this;
}


VectorList::Element::ElementType VectorList::LineWidth::Type(void) const {
    return VectorList::Element::ElementType::LineWidth;
}


double VectorList::LineWidth::Width(void) const {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        return m_chunk->pt[m_index][0];
    }
    else
        return m_width;
}


void VectorList::LineWidth::SetWidth
(
    double width
) {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        m_chunk->pt[m_index][0] = width;
    }
    else
        m_width = width;
}


VectorList::LineWidth::LineWidth
(
    bn_vlist* chunk,
    size_t    index
) : VectorList::Element(chunk, index), m_width(1.) {}


//
// BRLCAD::VectorList::TriangleStart
//
const VectorList::TriangleStart& VectorList::TriangleStart::operator=
(
    const TriangleStart& original
) {
    if (this != &original)
        SetNormal(original.Normal());

    return *this;
}


VectorList::Element::ElementType VectorList::TriangleStart::Type(void) const {
    return VectorList::Element::ElementType::TriangleStart;
}


Vector3D VectorList::TriangleStart::Normal(void) const {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        return m_chunk->pt[m_index];
    }
    else
        return m_normal;
}


void VectorList::TriangleStart::SetNormal
(
    const Vector3D& normal
) {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        VMOVE(m_chunk->pt[m_index], normal.coordinates);
    }
    else
        m_normal = normal;
}


VectorList::TriangleStart::TriangleStart
(
    bn_vlist* chunk,
    size_t    index
) : VectorList::Element(chunk, index), m_normal() {}


//
// BRLCAD::VectorList::TriangleMove
//
const VectorList::TriangleMove& VectorList::TriangleMove::operator=
(
    const TriangleMove& original
) {
    if (this != &original)
        SetPoint(original.Point());

    return *this;
}


VectorList::Element::ElementType VectorList::TriangleMove::Type(void) const {
    return VectorList::Element::ElementType::TriangleMove;
}


Vector3D VectorList::TriangleMove::Point(void) const {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        return m_chunk->pt[m_index];
    }
    else
        return m_point;
}


void VectorList::TriangleMove::SetPoint
(
    const Vector3D& point
) {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        VMOVE(m_chunk->pt[m_index], point.coordinates);
    }
    else
        m_point = point;
}


VectorList::TriangleMove::TriangleMove
(
    bn_vlist* chunk,
    size_t    index
) : VectorList::Element(chunk, index), m_point() {}


//
// BRLCAD::VectorList::TriangleDraw
//
const VectorList::TriangleDraw& VectorList::TriangleDraw::operator=
(
    const TriangleDraw& original
) {
    if (this != &original)
        SetPoint(original.Point());

    return *this;
}


VectorList::Element::ElementType VectorList::TriangleDraw::Type(void) const {
    return VectorList::Element::ElementType::TriangleDraw;
}


Vector3D VectorList::TriangleDraw::Point(void) const {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        return m_chunk->pt[m_index];
    }
    else
        return m_point;
}


void VectorList::TriangleDraw::SetPoint
(
    const Vector3D& point
) {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        VMOVE(m_chunk->pt[m_index], point.coordinates);
    }
    else
        m_point = point;
}


VectorList::TriangleDraw::TriangleDraw
(
    bn_vlist* chunk,
    size_t    index
) : VectorList::Element(chunk, index), m_point() {}


//
// BRLCAD::VectorList::TriangleEnd
//
const VectorList::TriangleEnd& VectorList::TriangleEnd::operator=
(
    const TriangleEnd& original
) {
    if (this != &original)
        SetPoint(original.Point());

    return *this;
}


VectorList::Element::ElementType VectorList::TriangleEnd::Type(void) const {
    return VectorList::Element::ElementType::TriangleEnd;
}


Vector3D VectorList::TriangleEnd::Point(void) const {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        return m_chunk->pt[m_index];
    }
    else
        return m_point;
}


void VectorList::TriangleEnd::SetPoint
(
    const Vector3D& point
) {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        VMOVE(m_chunk->pt[m_index], point.coordinates);
    }
    else
        m_point = point;
}


VectorList::TriangleEnd::TriangleEnd
(
    bn_vlist* chunk,
    size_t    index
) : VectorList::Element(chunk, index), m_point() {}


//
// BRLCAD::VectorList::TriangleVertexNormal
//
const VectorList::TriangleVertexNormal& VectorList::TriangleVertexNormal::operator=
(
    const TriangleVertexNormal& original
) {
    if (this != &original)
        SetNormal(original.Normal());

    return *this;
}


VectorList::Element::ElementType VectorList::TriangleVertexNormal::Type(void) const {
    return VectorList::Element::ElementType::TriangleVertexNormal;
}


Vector3D VectorList::TriangleVertexNormal::Normal(void) const {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        return m_chunk->pt[m_index];
    }
    else
        return m_normal;
}


void VectorList::TriangleVertexNormal::SetNormal
(
    const Vector3D& normal
) {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        VMOVE(m_chunk->pt[m_index], normal.coordinates);
    }
    else
        m_normal = normal;
}


VectorList::TriangleVertexNormal::TriangleVertexNormal
(
    bn_vlist* chunk,
    size_t    index
) : VectorList::Element(chunk, index), m_normal() {}


//
// BRLCAD::VectorList::PolygonStart
//
const VectorList::PolygonStart& VectorList::PolygonStart::operator=
(
    const PolygonStart& original
) {
    if (this != &original)
        SetNormal(original.Normal());

    return *this;
}


VectorList::Element::ElementType VectorList::PolygonStart::Type(void) const {
    return VectorList::Element::ElementType::PolygonStart;
}


Vector3D VectorList::PolygonStart::Normal(void) const {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        return m_chunk->pt[m_index];
    }
    else
        return m_normal;
}


void VectorList::PolygonStart::SetNormal
(
    const Vector3D& normal
) {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        VMOVE(m_chunk->pt[m_index], normal.coordinates);
    }
    else
        m_normal = normal;
}


VectorList::PolygonStart::PolygonStart
(
    bn_vlist* chunk,
    size_t    index
) : VectorList::Element(chunk, index), m_normal() {}


//
// BRLCAD::VectorList::PolygonMove
//
const VectorList::PolygonMove& VectorList::PolygonMove::operator=
(
    const PolygonMove& original
) {
    if (this != &original)
        SetPoint(original.Point());

    return *this;
}


VectorList::Element::ElementType VectorList::PolygonMove::Type(void) const {
    return VectorList::Element::ElementType::PolygonMove;
}


Vector3D VectorList::PolygonMove::Point(void) const {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        return m_chunk->pt[m_index];
    }
    else
        return m_point;
}


void VectorList::PolygonMove::SetPoint
(
    const Vector3D& point
) {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        VMOVE(m_chunk->pt[m_index], point.coordinates);
    }
    else
        m_point = point;
}


VectorList::PolygonMove::PolygonMove
(
    bn_vlist* chunk,
    size_t    index
) : VectorList::Element(chunk, index), m_point() {}


//
// BRLCAD::VectorList::PolygonDraw
//
const VectorList::PolygonDraw& VectorList::PolygonDraw::operator=
(
    const PolygonDraw& original
) {
    if (this != &original)
        SetPoint(original.Point());

    return *this;
}


VectorList::Element::ElementType VectorList::PolygonDraw::Type(void) const {
    return VectorList::Element::ElementType::PolygonDraw;
}


Vector3D VectorList::PolygonDraw::Point(void) const {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        return m_chunk->pt[m_index];
    }
    else
        return m_point;
}


void VectorList::PolygonDraw::SetPoint
(
    const Vector3D& point
) {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        VMOVE(m_chunk->pt[m_index], point.coordinates);
    }
    else
        m_point = point;
}


VectorList::PolygonDraw::PolygonDraw
(
    bn_vlist* chunk,
    size_t    index
) : VectorList::Element(chunk, index), m_point() {}


//
// BRLCAD::VectorList::PolygonEnd
//
const VectorList::PolygonEnd& VectorList::PolygonEnd::operator=
(
    const PolygonEnd& original
) {
    if (this != &original)
        SetPoint(original.Point());

    return *this;
}


VectorList::Element::ElementType VectorList::PolygonEnd::Type(void) const {
    return VectorList::Element::ElementType::PolygonEnd;
}


Vector3D VectorList::PolygonEnd::Point(void) const {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        return m_chunk->pt[m_index];
    }
    else
        return m_point;
}


void VectorList::PolygonEnd::SetPoint
(
    const Vector3D& point
) {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        VMOVE(m_chunk->pt[m_index], point.coordinates);
    }
    else
        m_point = point;
}


VectorList::PolygonEnd::PolygonEnd
(
    bn_vlist* chunk,
    size_t    index
) : VectorList::Element(chunk, index), m_point() {}


//
// BRLCAD::VectorList::PolygonVertexNormal
//
const VectorList::PolygonVertexNormal& VectorList::PolygonVertexNormal::operator=
(
    const PolygonVertexNormal& original
) {
    if (this != &original)
        SetNormal(original.Normal());

    return *this;
}


VectorList::Element::ElementType VectorList::PolygonVertexNormal::Type(void) const {
    return VectorList::Element::ElementType::PolygonVertexNormal;
}


Vector3D VectorList::PolygonVertexNormal::Normal(void) const {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        return m_chunk->pt[m_index];
    }
    else
        return m_normal;
}


void VectorList::PolygonVertexNormal::SetNormal
(
    const Vector3D& normal
) {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        VMOVE(m_chunk->pt[m_index], normal.coordinates);
    }
    else
        m_normal = normal;
}


VectorList::PolygonVertexNormal::PolygonVertexNormal
(
    bn_vlist* chunk,
    size_t    index
) : VectorList::Element(chunk, index), m_normal() {}


//
// BRLCAD::VectorList::DisplaySpace
//
const VectorList::DisplaySpace& VectorList::DisplaySpace::operator=
(
    const DisplaySpace& original
) {
    if (this != &original)
        SetReferencePoint(original.ReferencePoint());

    return *this;
}


VectorList::Element::ElementType VectorList::DisplaySpace::Type(void) const {
    return VectorList::Element::ElementType::DisplaySpace;
}


Vector3D VectorList::DisplaySpace::ReferencePoint(void) const {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        return m_chunk->pt[m_index];
    }
    else
        return m_referencePoint;
}


void VectorList::DisplaySpace::SetReferencePoint
(
    const Vector3D& referencePoint
) {
    if (m_chunk != 0) {
        assert(m_index < m_chunk->nused);
        VMOVE(m_chunk->pt[m_index], referencePoint.coordinates);
    }
    else
        m_referencePoint = referencePoint;
}


VectorList::DisplaySpace::DisplaySpace
(
    bn_vlist* chunk,
    size_t    index
) : VectorList::Element(chunk, index), m_referencePoint() {}


//
// BRLCAD::VectorList::ModelSpace
//
const VectorList::ModelSpace& VectorList::ModelSpace::operator=
(
    const ModelSpace& original
) {
    return *this;
}


VectorList::Element::ElementType VectorList::ModelSpace::Type(void) const {
    return VectorList::Element::ElementType::ModelSpace;
}


VectorList::ModelSpace::ModelSpace
(
    bn_vlist* chunk,
    size_t    index
) : VectorList::Element(chunk, index) {}


//
// BRLCAD::VectorList
//
VectorList::VectorList(void) {
    InitBrlCad();

    m_vlist = new bu_list;
    BU_LIST_INIT(m_vlist);
}


VectorList::VectorList
(
    const VectorList& original
) {
    m_vlist = new bu_list;
    BU_LIST_INIT(m_vlist);

    if (!BU_SETJUMP)
        rt_vlist_copy(m_vlist, original.m_vlist);
    else
        BU_UNSETJUMP;

    BU_UNSETJUMP;
}


VectorList::~VectorList(void) {
    RT_FREE_VLIST(m_vlist);
    delete m_vlist;
}


const VectorList& VectorList::operator=
(
    const VectorList& original
) {
    if (&original != this) {
        RT_FREE_VLIST(m_vlist);

        if (!BU_SETJUMP)
            rt_vlist_copy(m_vlist, original.m_vlist);
        else
            BU_UNSETJUMP;

        BU_UNSETJUMP;
    }

    return *this;
}


void VectorList::Iterate
(
    VectorList::ConstElementCallback& callBack
) const {
    if (m_vlist != 0) {
        bool      cont = true;
        bn_vlist* chunk;

        for (BU_LIST_FOR(chunk, bn_vlist, m_vlist)) {
            for (size_t i = 0; i < chunk->nused; ++i) {
                switch (chunk->cmd[i]) {
                    case BN_VLIST_LINE_MOVE: {
                        LineMove element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_LINE_DRAW: {
                        LineDraw element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_POLY_START: {
                        PolygonStart element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_POLY_MOVE: {
                        PolygonMove element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_POLY_DRAW: {
                        PolygonDraw element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_POLY_END: {
                        PolygonEnd element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_POLY_VERTNORM: {
                        PolygonVertexNormal element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_TRI_START: {
                        TriangleStart element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_TRI_MOVE: {
                        TriangleMove element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_TRI_DRAW: {
                        TriangleDraw element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_TRI_END: {
                        TriangleEnd element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_TRI_VERTNORM: {
                        TriangleVertexNormal element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_POINT_DRAW: {
                        PointDraw element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_POINT_SIZE: {
                        PointSize element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_LINE_WIDTH: {
                        LineWidth element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_DISPLAY_MAT: {
                        DisplaySpace element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_MODEL_MAT: {
                        ModelSpace element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    default:
                        if (!callBack(0))
                            cont = false;
                }

                if (!cont)
                    return;
            }
        }
    }
}


void VectorList::Iterate
(
    VectorList::ElementCallback& callBack
) {
    if (m_vlist != 0) {
        bool      cont = true;
        bn_vlist* chunk;

        for (BU_LIST_FOR(chunk, bn_vlist, m_vlist)) {
            for (size_t i = 0; i < chunk->nused; ++i) {
                switch (chunk->cmd[i]) {
                    case BN_VLIST_LINE_MOVE: {
                        LineMove element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_LINE_DRAW: {
                        LineDraw element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_POLY_START: {
                        PolygonStart element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_POLY_MOVE: {
                        PolygonMove element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_POLY_DRAW: {
                        PolygonDraw element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_POLY_END: {
                        PolygonEnd element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_POLY_VERTNORM: {
                        PolygonVertexNormal element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_TRI_START: {
                        TriangleStart element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_TRI_MOVE: {
                        TriangleMove element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_TRI_DRAW: {
                        TriangleDraw element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_TRI_END: {
                        TriangleEnd element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_TRI_VERTNORM: {
                        TriangleVertexNormal element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_POINT_DRAW: {
                        PointDraw element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_POINT_SIZE: {
                        PointSize element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_LINE_WIDTH: {
                        LineWidth element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_DISPLAY_MAT: {
                        DisplaySpace element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    case BN_VLIST_MODEL_MAT: {
                        ModelSpace element(chunk, i);

                        if (!callBack(&element))
                            cont = false;

                        break;
                    }

                    default:
                        if (!callBack(0))
                            cont = false;
                }

                if (!cont)
                    return;
            }
        }
    }
}


bool VectorList::Append
(
    const Element& element
) {
    bool ret = false;

    if (!BU_SETJUMP) {
        switch (element.Type()) {
            case Element::ElementType::PointDraw: {
                const PointDraw& actualElement = static_cast<const PointDraw&>(element);

                RT_ADD_VLIST(m_vlist, actualElement.Point().coordinates, BN_VLIST_POINT_DRAW);
                break;
            }

            case Element::ElementType::PointSize: {
                const PointSize& actualElement = static_cast<const PointSize&>(element);

                RT_VLIST_SET_POINT_SIZE(m_vlist, actualElement.Size());
                break;
            }

            case Element::ElementType::LineMove: {
                const LineMove& actualElement = static_cast<const LineMove&>(element);

                RT_ADD_VLIST(m_vlist, actualElement.Point().coordinates, BN_VLIST_LINE_MOVE);
                break;
            }

            case Element::ElementType::LineDraw: {
                const LineDraw& actualElement = static_cast<const LineDraw&>(element);

                RT_ADD_VLIST(m_vlist, actualElement.Point().coordinates, BN_VLIST_LINE_DRAW);
                break;
            }

            case Element::ElementType::LineWidth: {
                const LineWidth& actualElement = static_cast<const LineWidth&>(element);

                RT_VLIST_SET_LINE_WIDTH(m_vlist, actualElement.Width());
                break;
            }

            case Element::ElementType::TriangleStart: {
                const TriangleStart& actualElement = static_cast<const TriangleStart&>(element);

                RT_ADD_VLIST(m_vlist, actualElement.Normal().coordinates, BN_VLIST_TRI_START);
                break;
            }

            case Element::ElementType::TriangleMove: {
                const TriangleMove& actualElement = static_cast<const TriangleMove&>(element);

                RT_ADD_VLIST(m_vlist, actualElement.Point().coordinates, BN_VLIST_TRI_MOVE);
                break;
            }

            case Element::ElementType::TriangleDraw: {
                const TriangleDraw& actualElement = static_cast<const TriangleDraw&>(element);

                RT_ADD_VLIST(m_vlist, actualElement.Point().coordinates, BN_VLIST_TRI_DRAW);
                break;
            }

            case Element::ElementType::TriangleEnd: {
                const TriangleEnd& actualElement = static_cast<const TriangleEnd&>(element);

                RT_ADD_VLIST(m_vlist, actualElement.Point().coordinates, BN_VLIST_TRI_END);
                break;
            }

            case Element::ElementType::TriangleVertexNormal: {
                const TriangleVertexNormal& actualElement = static_cast<const TriangleVertexNormal&>(element);

                RT_ADD_VLIST(m_vlist, actualElement.Normal().coordinates, BN_VLIST_TRI_VERTNORM);
                break;
            }

            case Element::ElementType::PolygonStart: {
                const PolygonStart& actualElement = static_cast<const PolygonStart&>(element);

                RT_ADD_VLIST(m_vlist, actualElement.Normal().coordinates, BN_VLIST_POLY_START);
                break;
            }

            case Element::ElementType::PolygonMove: {
                const PolygonMove& actualElement = static_cast<const PolygonMove&>(element);

                RT_ADD_VLIST(m_vlist, actualElement.Point().coordinates, BN_VLIST_POLY_MOVE);
                break;
            }

            case Element::ElementType::PolygonDraw: {
                const PolygonDraw& actualElement = static_cast<const PolygonDraw&>(element);

                RT_ADD_VLIST(m_vlist, actualElement.Point().coordinates, BN_VLIST_POLY_DRAW);
                break;
            }

            case Element::ElementType::PolygonEnd: {
                const PolygonEnd& actualElement = static_cast<const PolygonEnd&>(element);

                RT_ADD_VLIST(m_vlist, actualElement.Point().coordinates, BN_VLIST_POLY_END);
                break;
            }

            case Element::ElementType::PolygonVertexNormal: {
                const PolygonVertexNormal& actualElement = static_cast<const PolygonVertexNormal&>(element);

                RT_ADD_VLIST(m_vlist, actualElement.Normal().coordinates, BN_VLIST_POLY_VERTNORM);
                break;
            }

            case Element::ElementType::DisplaySpace: {
                const DisplaySpace& actualElement = static_cast<const DisplaySpace&>(element);

                RT_VLIST_SET_DISP_MAT(m_vlist, actualElement.ReferencePoint().coordinates);
                break;
            }

            case Element::ElementType::ModelSpace:
                RT_VLIST_SET_MODEL_MAT(m_vlist);
        }

        ret = true;
    }
    else
        BU_UNSETJUMP;

    BU_UNSETJUMP;

    return ret;
}


void VectorList::Clear(void) {
    RT_FREE_VLIST(m_vlist);
}
