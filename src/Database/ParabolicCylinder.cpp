/*          P A R A B O L I C C Y L I N D E R . C P P
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
/** @file ParabolicCylinder.cpp
 *
 *  BRL-CAD core C++ interface:
 *      right parabolic cylinder (ID_RPC) database object implementation
 */

#include <cassert>

#include "rt/geom.h"
#include "raytrace.h"
#include "bu/parallel.h"

#include <brlcad/Database/ParabolicCylinder.h>


using namespace BRLCAD;


ParabolicCylinder::ParabolicCylinder(void) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_rpc_internal);
        m_internalp->rpc_magic = RT_RPC_INTERNAL_MAGIC;

        Set(Vector3D(), Vector3D(0., 0., 1.), Vector3D(1., 0., 0.), 1.);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


ParabolicCylinder::ParabolicCylinder
(
    const Vector3D& basePoint,
    const Vector3D& height,
    const Vector3D& depth,
    double          halfWidth
) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_rpc_internal);
        m_internalp->rpc_magic = RT_RPC_INTERNAL_MAGIC;

        Set(basePoint, height, depth, halfWidth);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


ParabolicCylinder::ParabolicCylinder
(
    const ParabolicCylinder& original
) : Object(original) {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_rpc_internal);
        memcpy(m_internalp, original.Internal(), sizeof(rt_rpc_internal));
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


ParabolicCylinder::~ParabolicCylinder(void) {
    if (m_internalp != nullptr)
        bu_free(m_internalp, "BRLCAD::ParabolicCylinder::~ParabolicCylinder::m_internalp");
}


const ParabolicCylinder& ParabolicCylinder::operator=
(
    const ParabolicCylinder& original
) {
    if(&original != this) {
        Copy(original);
        memcpy(Internal(), original.Internal(), sizeof(rt_rpc_internal));
    }

    return *this;
}


Vector3D ParabolicCylinder::BasePoint(void) const {
    return Vector3D(Internal()->rpc_V);
}


void ParabolicCylinder::SetBasePoint
(
    const Vector3D& basePoint
) {
    VMOVE(Internal()->rpc_V, basePoint.coordinates);
}


Vector3D ParabolicCylinder::Height(void) const {
    return Vector3D(Internal()->rpc_H);
}


void ParabolicCylinder::SetHeight
(
    const Vector3D& height
) {
    VMOVE(Internal()->rpc_H, height.coordinates);
}


Vector3D ParabolicCylinder::Depth(void) const {
    return Vector3D(Internal()->rpc_B);
}


void ParabolicCylinder::SetDepth
(
    const Vector3D& depth
) {
    VMOVE(Internal()->rpc_B, depth.coordinates);
}


double ParabolicCylinder::HalfWidth(void) const {
    return Internal()->rpc_r;
}


void ParabolicCylinder::SetHalfWidth
(
    double length
) {
    Internal()->rpc_r = length;
}


void ParabolicCylinder::Set
(
    const Vector3D& basePoint,
    const Vector3D& height,
    const Vector3D& depth,
    double          halfWidth
) {
    rt_rpc_internal* internalp = Internal();

    VMOVE(internalp->rpc_V, basePoint.coordinates);
    VMOVE(internalp->rpc_H, height.coordinates);
    VMOVE(internalp->rpc_B, depth.coordinates);
    internalp->rpc_r = halfWidth;
}


const Object& ParabolicCylinder::operator=
(
    const Object& original
) {
    const ParabolicCylinder* rpc = dynamic_cast<const ParabolicCylinder*>(&original);
    assert(rpc != nullptr);

    if (rpc != nullptr)
        *this = *rpc;

    return *this;
}


Object* ParabolicCylinder::Clone(void) const {
    return new ParabolicCylinder(*this);
}


const char* ParabolicCylinder::ClassName(void) {
    return "ParabolicCylinder";
}


const char* ParabolicCylinder::Type(void) const {
    return ClassName();
}


bool ParabolicCylinder::IsValid(void) const {
    bool                   ret       = false;
    const rt_rpc_internal* internalp = Internal();

    if (Validate() &&
        !VNEAR_ZERO(internalp->rpc_H, SMALL_FASTF) &&
        !VNEAR_ZERO(internalp->rpc_B, SMALL_FASTF) &&
        (internalp->rpc_r > SMALL_FASTF) &&
        NEAR_ZERO(VDOT(internalp->rpc_H, Internal()->rpc_B), RT_DOT_TOL))
        ret = true;

    return ret;
}


ParabolicCylinder::ParabolicCylinder
(
    resource*       resp,
    directory*      pDir,
    rt_db_internal* ip,
    db_i*           dbip
) : Object(resp, pDir, ip, dbip), m_internalp(nullptr) {}


rt_rpc_internal* ParabolicCylinder::Internal(void) {
    rt_rpc_internal* ret;

    if(m_ip != nullptr)
        ret = static_cast<rt_rpc_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_RPC_CK_MAGIC(ret);

    return ret;
}


const rt_rpc_internal* ParabolicCylinder::Internal(void) const {
    const rt_rpc_internal* ret;

    if (m_ip != nullptr)
        ret = static_cast<const rt_rpc_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_RPC_CK_MAGIC(ret);

    return ret;
}
