/*            N O N M A N I F O L D G E O M E T R Y . C P P
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
/** @file NonManifoldGeometry.cpp
 *
 *  BRL-CAD core C++ interface:
 *      non-manifold geometry (ID_NMG) database object implementation
 */

#include <cassert>

#include "raytrace.h"
#include "bu/parallel.h"

#include <brlcad/Database/NonManifoldGeometry.h>


using namespace BRLCAD;


//
// class NonManifoldGeometry::Vetrex
//

Vector3D NonManifoldGeometry::Vertex::Point(void) const {
    Vector3D ret;

    if (m_vertex != 0) {
        NMG_CK_VERTEXUSE(m_vertex);

        if (m_vertex->v_p != 0) {
            NMG_CK_VERTEX(m_vertex->v_p);

            if (m_vertex->v_p->vg_p != 0) {
                NMG_CK_VERTEX_G(m_vertex->v_p->vg_p);

                ret = Vector3D(m_vertex->v_p->vg_p->coord);
            }
        }
    }

    return ret;
}


//
// class NonManifoldGeometry::Edge
//

NonManifoldGeometry::Vertex NonManifoldGeometry::Edge::ForwardVertex(void) const {
    Vertex ret;

    if (m_edge != 0) {
        NMG_CK_EDGEUSE(m_edge);

        if (m_edge->vu_p != 0) {
            NMG_CK_VERTEXUSE(m_edge->vu_p);

            ret.m_vertex = m_edge->vu_p;
        }
    }

    return ret;
}


NonManifoldGeometry::Vertex NonManifoldGeometry::Edge::BackwardVertex(void) const {
    Vertex ret;

    if (m_edge != 0) {
        NMG_CK_EDGEUSE(m_edge);

        if (m_edge->eumate_p != 0) {
            NMG_CK_EDGEUSE(m_edge->eumate_p);

            if (m_edge->eumate_p->vu_p != 0) {
                NMG_CK_VERTEXUSE(m_edge->eumate_p->vu_p);

                ret.m_vertex = m_edge->eumate_p->vu_p;
            }
        }
    }

    return ret;
}


//
// class NonManifoldGeometry::Loop
//

bool NonManifoldGeometry::Loop::IsHole(void) const {
    bool ret = false;

    if (m_loop != 0) {
        NMG_CK_LOOPUSE(m_loop);

        if (m_loop->orientation == OT_OPPOSITE)
            ret = true;
    }

    return ret;
}


void NonManifoldGeometry::Loop::GotoFirstEdge(void) {
    m_currentEdge = 0;

    if (m_loop != 0) {
        NMG_CK_LOOPUSE(m_loop);

        if (BU_LIST_FIRST_MAGIC(&m_loop->down_hd) == NMG_EDGEUSE_MAGIC) {
            m_currentEdge = BU_LIST_FIRST(edgeuse, &m_loop->down_hd);

            if ((m_currentEdge == 0) || BU_LIST_IS_HEAD(m_currentEdge, &m_loop->down_hd))
                m_currentEdge = 0;
        }
    }
}


const NonManifoldGeometry::Loop& NonManifoldGeometry::Loop::operator++(void) {
    if ((m_loop != 0) && (m_currentEdge != 0)) {
        NMG_CK_LOOPUSE(m_loop);

        m_currentEdge = BU_LIST_PNEXT(edgeuse, m_currentEdge);

        if ((m_currentEdge == 0) || BU_LIST_IS_HEAD(m_currentEdge, &m_loop->down_hd))
            m_currentEdge = 0;
    }

    return *this;
}


NonManifoldGeometry::Edge NonManifoldGeometry::Loop::CurrentEdge(void) const {
    Edge ret;

    if (m_currentEdge != 0) {
        NMG_CK_EDGEUSE(m_currentEdge);

        ret.m_edge = m_currentEdge;
    }

    return ret;
}


//
// class NonManifoldGeometry::Face
//

void NonManifoldGeometry::Face::GotoFirstLoop(void){
    m_currentLoop = 0;

    if (m_face != 0) {
        NMG_CK_FACEUSE(m_face);

        m_currentLoop = BU_LIST_FIRST(loopuse, &m_face->lu_hd);

        if ((m_currentLoop == 0) || BU_LIST_IS_HEAD(m_currentLoop, &m_face->lu_hd))
            m_currentLoop = 0;
    }
}


const NonManifoldGeometry::Face& NonManifoldGeometry::Face::operator++(void) {
    if ((m_face != 0) && (m_currentLoop != 0)) {
        NMG_CK_FACEUSE(m_face);

        m_currentLoop = BU_LIST_PNEXT(loopuse, m_currentLoop);

        if ((m_currentLoop == 0) || BU_LIST_IS_HEAD(m_currentLoop, &m_face->lu_hd))
            m_currentLoop = 0;
    }

    return *this;
}


NonManifoldGeometry::Loop NonManifoldGeometry::Face::CurrentLoop(void) const {
    Loop ret;

    if (m_currentLoop != 0) {
        NMG_CK_LOOPUSE(m_currentLoop);

        ret.m_loop = m_currentLoop;
    }

    return ret;
}


//
// class NonManifoldGeometry::Shell
//

void NonManifoldGeometry::Shell::GotoFirstFace(void) {
    m_currentFace = 0;

    if (m_shell != 0) {
        NMG_CK_SHELL(m_shell);

        m_currentFace = BU_LIST_FIRST(faceuse, &m_shell->fu_hd);

        if ((m_currentFace == 0) || BU_LIST_IS_HEAD(m_currentFace, &m_shell->fu_hd))
            m_currentFace = 0;
        else {
            while ((m_currentFace != 0) && (m_currentFace->orientation != OT_SAME)) {
                m_currentFace = BU_LIST_PNEXT(faceuse, m_currentFace);

                if ((m_currentFace == 0) || BU_LIST_IS_HEAD(m_currentFace, &m_shell->fu_hd))
                    m_currentFace = 0;
            }
        }
    }
}


const NonManifoldGeometry::Shell& NonManifoldGeometry::Shell::GotoNextFace(void) {
    if ((m_shell != 0) && (m_currentFace != 0)) {
        NMG_CK_SHELL(m_shell);

        m_currentFace = BU_LIST_PNEXT(faceuse, m_currentFace);

        if ((m_currentFace == 0) || BU_LIST_IS_HEAD(m_currentFace, &m_shell->fu_hd))
            m_currentFace = 0;
        else {
            while ((m_currentFace != 0) && (m_currentFace->orientation != OT_SAME)) {
                m_currentFace = BU_LIST_PNEXT(faceuse, m_currentFace);

                if ((m_currentFace == 0) || BU_LIST_IS_HEAD(m_currentFace, &m_shell->fu_hd))
                    m_currentFace = 0;
            }
        }
    }

    return *this;
}


NonManifoldGeometry::Face NonManifoldGeometry::Shell::CurrentFace(void) const {
    Face ret;

    if (m_currentFace != 0) {
        NMG_CK_FACEUSE(m_currentFace);

        ret.m_face = m_currentFace;
    }

    return ret;
}


void NonManifoldGeometry::Shell::GotoFirstLoop(void) {
    m_currentLoop = 0;

    if (m_shell != 0) {
        NMG_CK_SHELL(m_shell);

        m_currentLoop = BU_LIST_FIRST(loopuse, &m_shell->lu_hd);

        if ((m_currentLoop == 0) || BU_LIST_IS_HEAD(m_currentLoop, &m_shell->lu_hd))
            m_currentLoop = 0;
    }
}


const NonManifoldGeometry::Shell& NonManifoldGeometry::Shell::GotoNextLoop(void) {
    if ((m_shell != 0) && (m_currentLoop != 0)) {
        NMG_CK_SHELL(m_shell);

        m_currentLoop = BU_LIST_PNEXT(loopuse, m_currentLoop);

        if ((m_currentLoop == 0) || BU_LIST_IS_HEAD(m_currentLoop, &m_shell->lu_hd))
            m_currentLoop = 0;
    }

    return *this;
}


NonManifoldGeometry::Loop NonManifoldGeometry::Shell::CurrentLoop(void) const {
    Loop ret;

    if (m_currentLoop != 0) {
        NMG_CK_LOOPUSE(m_currentLoop);

        ret.m_loop = m_currentLoop;
    }

    return ret;
}


void NonManifoldGeometry::Shell::GotoFirstEdge(void) {
    m_currentEdge = 0;

    if (m_shell != 0) {
        NMG_CK_SHELL(m_shell);

        m_currentEdge = BU_LIST_FIRST(edgeuse, &m_shell->eu_hd);

        if ((m_currentEdge == 0) || BU_LIST_IS_HEAD(m_currentEdge, &m_shell->eu_hd))
            m_currentEdge = 0;
    }
}


const NonManifoldGeometry::Shell& NonManifoldGeometry::Shell::GotoNextEdge(void) {
    if ((m_shell != 0) && (m_currentEdge != 0)) {
        NMG_CK_SHELL(m_shell);

        m_currentEdge = BU_LIST_PNEXT(edgeuse, m_currentEdge);

        if ((m_currentEdge == 0) || BU_LIST_IS_HEAD(m_currentEdge, &m_shell->eu_hd))
            m_currentEdge = 0;
    }

    return *this;
}


NonManifoldGeometry::Edge NonManifoldGeometry::Shell::CurrentEdge(void) const {
    Edge ret;

    if (m_currentEdge != 0) {
        NMG_CK_EDGEUSE(m_currentEdge);

        ret.m_edge = m_currentEdge;
    }

    return ret;
}


void NonManifoldGeometry::Shell::GotoFirstVertex(void) {
    m_currentVertex = 0;

    if (m_shell != 0) {
        NMG_CK_SHELL(m_shell);

        m_currentVertex = m_shell->vu_p;
    }
}


const NonManifoldGeometry::Shell& NonManifoldGeometry::Shell::GotoNextVertex(void) {
    m_currentVertex = 0;

    return *this;
}


NonManifoldGeometry::Vertex NonManifoldGeometry::Shell::CurrentVertex(void) const {
    Vertex ret;

    if (m_currentVertex != 0) {
        NMG_CK_VERTEXUSE(m_currentVertex);

        ret.m_vertex = m_currentVertex;
    }

    return ret;
}


//
// class NonManifoldGeometry::Region
//

void NonManifoldGeometry::Region::GotoFirstShell(void) {
    m_currentShell = 0;

    if (m_region != 0) {
        NMG_CK_REGION(m_region);

        m_currentShell = BU_LIST_FIRST(shell, &m_region->s_hd);

        if ((m_currentShell == 0) || BU_LIST_IS_HEAD(m_currentShell, &m_region->s_hd))
            m_currentShell = 0;
    }
}


const NonManifoldGeometry::Region& NonManifoldGeometry::Region::operator++(void) {
    if ((m_region != 0) && (m_currentShell != 0)) {
        NMG_CK_REGION(m_region);

        m_currentShell = BU_LIST_PNEXT(shell, m_currentShell);

        if ((m_currentShell == 0) || BU_LIST_IS_HEAD(m_currentShell, &m_region->s_hd))
            m_currentShell = 0;
    }

    return *this;
}


NonManifoldGeometry::Shell NonManifoldGeometry::Region::CurrentShell(void) const {
    Shell ret;

    if (m_currentShell != 0) {
        NMG_CK_SHELL(m_currentShell);

        ret.m_shell = m_currentShell;
    }

    return ret;
}


//
// class NonManifoldGeometry::RegionIterator
//

void NonManifoldGeometry::RegionIterator::GotoFirstRegion(void) {
    m_currentRegion = 0;

    if (m_model != 0) {
        NMG_CK_MODEL(m_model);

        m_currentRegion = BU_LIST_FIRST(nmgregion, &m_model->r_hd);

        if ((m_currentRegion == 0) || BU_LIST_IS_HEAD(m_currentRegion, &m_model->r_hd))
            m_currentRegion = 0;
    }
}


const NonManifoldGeometry::RegionIterator& NonManifoldGeometry::RegionIterator::operator++(void) {
    if ((m_model != 0) && (m_currentRegion != 0)) {
        NMG_CK_MODEL(m_model);

        m_currentRegion = BU_LIST_PNEXT(nmgregion, m_currentRegion);

        if ((m_currentRegion == 0) || BU_LIST_IS_HEAD(m_currentRegion, &m_model->r_hd))
            m_currentRegion = 0;
    }

    return *this;
}


NonManifoldGeometry::Region NonManifoldGeometry::RegionIterator::CurrentRegion(void) const {
    Region ret;

    if (m_currentRegion != 0) {
        NMG_CK_REGION(m_currentRegion);

        ret.m_region = m_currentRegion;
    }

    return ret;
}


//
// class NonManifoldGeometry
//

NonManifoldGeometry::NonManifoldGeometry(void) : Object(), m_internalp(0) {
    assert(BU_LIST_IS_INITIALIZED(&rt_vlfree));

    if (!BU_SETJUMP)
        m_internalp = nmg_mm();
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


NonManifoldGeometry::NonManifoldGeometry
(
    const NonManifoldGeometry& original
) : Object(original), m_internalp(0) {
    Copy(original);

    if (!BU_SETJUMP)
        m_internalp = nmg_clone_model(original.Internal());
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


NonManifoldGeometry::~NonManifoldGeometry(void) {
    if (m_internalp != 0)
        nmg_km(m_internalp);
}


const NonManifoldGeometry& NonManifoldGeometry::operator=
(
    const NonManifoldGeometry& original
) {
    if (&original != this) {
        Copy(original);

        model* nmgModel = Internal();

        if (nmgModel != 0)
            nmg_km(nmgModel);

        if (!BU_SETJUMP)
            nmgModel = nmg_clone_model(original.Internal());
        else {
            BU_UNSETJUMP;
        }

        BU_UNSETJUMP;

        if (m_ip != 0)
            m_ip->idb_ptr = nmgModel;
        else
            m_internalp = nmgModel;
    }

    return *this;
}


void NonManifoldGeometry::Triangulate(void) {
    bn_tol tolerance;

    tolerance.magic   = BN_TOL_MAGIC;
    tolerance.dist    = 0.0005;
    tolerance.dist_sq = tolerance.dist * tolerance.dist;
    tolerance.perp    = 1e-6;
    tolerance.para    = 1 - tolerance.perp;

    if (!BU_SETJUMP)
        nmg_triangulate_model(Internal(), &rt_vlfree, &tolerance);
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


void NonManifoldGeometry::Triangulate
(
    Shell& shellToTrinagulate
) {
    bn_tol tolerance;

    tolerance.magic   = BN_TOL_MAGIC;
    tolerance.dist    = 0.0005;
    tolerance.dist_sq = tolerance.dist * tolerance.dist;
    tolerance.perp    = 1e-6;
    tolerance.para    = 1 - tolerance.perp;

    if (!BU_SETJUMP)
        nmg_triangulate_shell(const_cast<shell*>(shellToTrinagulate.m_shell), &rt_vlfree, &tolerance);
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


void NonManifoldGeometry::Triangulate
(
    Face& faceToTrinagulate
) {
    bn_tol tolerance;

    tolerance.magic   = BN_TOL_MAGIC;
    tolerance.dist    = 0.0005;
    tolerance.dist_sq = tolerance.dist * tolerance.dist;
    tolerance.perp    = 1e-6;
    tolerance.para    = 1 - tolerance.perp;

    if (!BU_SETJUMP)
        nmg_triangulate_fu(const_cast<faceuse*>(faceToTrinagulate.m_face), &rt_vlfree, &tolerance);
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


NonManifoldGeometry::RegionIterator NonManifoldGeometry::Regions(void) const {
    NonManifoldGeometry::RegionIterator ret;
    ret.m_model = Internal();

    return ret;
}


const Object& NonManifoldGeometry::operator=
(
    const Object& original
) {
    const NonManifoldGeometry* nmg = dynamic_cast<const NonManifoldGeometry*>(&original);
    assert(nmg != 0);

    if (nmg != 0)
        *this = *nmg;

    return *this;
}


Object* NonManifoldGeometry::Clone(void) const {
    return new NonManifoldGeometry(*this);
}


const char* NonManifoldGeometry::ClassName(void) {
    return "NonManifoldGeometry";
}


const char* NonManifoldGeometry::Type(void) const {
    return ClassName();
}


bool NonManifoldGeometry::IsValid(void) const {
    bool ret = Validate();

    if (ret) {
        if (!BU_SETJUMP) {
            NMG_CK_MODEL(Internal());
        }
        else
            ret = false;

        BU_UNSETJUMP;
    }

    return ret;
}


NonManifoldGeometry::NonManifoldGeometry
(
    resource*       resp,
    directory*      pDir,
    rt_db_internal* ip,
    db_i*           dbip
) : Object(resp, pDir, ip, dbip), m_internalp(0) {
    assert(BU_LIST_IS_INITIALIZED(&rt_vlfree));
}


const model* NonManifoldGeometry::Internal(void) const {
    const model* ret;

    if (m_ip != 0)
        ret = static_cast<const model*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    NMG_CK_MODEL(ret);

    return ret;
}


model* NonManifoldGeometry::Internal(void) {
    model* ret;

    if (m_ip != 0)
        ret = static_cast<model*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    NMG_CK_MODEL(ret);

    return ret;
}
