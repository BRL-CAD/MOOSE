/*                      H A L F S P A C E . C P P
 * BRL-CAD
 *
 * Copyright (c) 2011-2020 United States Government as represented by
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
/** @file Halfspace.cpp
 *
 *  BRL-CAD core C++ interface:
 *      half-space (ID_HALF) database object implementation
 */

#include <cassert>

#include "raytrace.h"
#include "rt/geom.h"
#include "bu/parallel.h"

#include <brlcad/Database/Halfspace.h>


using namespace BRLCAD;


Halfspace::Halfspace(void) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_half_internal);
        m_internalp->magic = RT_HALF_INTERNAL_MAGIC;
        m_internalp->eqn[X] = 0.;
        m_internalp->eqn[Y] = 0.;
        m_internalp->eqn[Z] = 1.;
        m_internalp->eqn[3] = 0.;
    }
    else
        BU_UNSETJUMP;

    BU_UNSETJUMP;
}


Halfspace::Halfspace
(
    const  Vector3D& normal,
    double           distanceFromOrigin
) {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_half_internal);
        m_internalp->magic = RT_HALF_INTERNAL_MAGIC;
        Set(normal, distanceFromOrigin);
    }
    else
        BU_UNSETJUMP;

    BU_UNSETJUMP;
}


Halfspace::Halfspace
(
    const Halfspace& original
) : Object(original) {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_half_internal);
        memcpy(m_internalp, original.Internal(), sizeof(rt_half_internal));
    }
    else
        BU_UNSETJUMP;

    BU_UNSETJUMP;
}


Halfspace::~Halfspace(void) {
    if (m_internalp != 0)
        bu_free(m_internalp, "BRLCAD::Halfspace::~Halfspace::m_internalp");
}


const Halfspace& Halfspace::operator=
(
    const Halfspace& original
) {
    if (&original != this) {
        Copy(original);
        memcpy(Internal()->eqn, original.Internal()->eqn, sizeof(plane_t));
    }

    return *this;
}


Vector3D Halfspace::Normal(void) const {
    return Vector3D(Internal()->eqn);
}


void Halfspace::SetNormal
(
    const Vector3D& normal
) {
    double length = MAGNITUDE(normal.coordinates);

    if (length >= VDIVIDE_TOL) {
        vect_t guaranteedNormal;
        VSCALE(guaranteedNormal, normal.coordinates, 1. / length);

        VMOVE(Internal()->eqn, guaranteedNormal);
    }
}


double Halfspace::DistanceFromOrigin(void) const {
    return Internal()->eqn[3];
}


void Halfspace::SetDistanceFromOrigin
(
    double distance
) {
    Internal()->eqn[3] = distance;
}


void Halfspace::Set
(
    const Vector3D& normal,
    double          distanceFromOrigin
) {
    SetNormal(normal);
    SetDistanceFromOrigin(distanceFromOrigin);
}


const Object& Halfspace::operator=
(
    const Object& original
) {
    const Halfspace* half = dynamic_cast<const Halfspace*>(&original);
    assert(half != 0);

    if (half != 0)
        *this = *half;

    return *this;
}


Object* Halfspace::Clone(void) const {
    return new Halfspace(*this);
}


const char* Halfspace::ClassName(void) {
    return "Halfspace";
}


const char* Halfspace::Type(void) const {
    return ClassName();
}


bool Halfspace::IsValid(void) const {
    bool ret = Validate();

    if (ret) {
        double length = MAGNITUDE(Internal()->eqn);

        if (length <= VDIVIDE_TOL) // or has it to be 1?
            ret = false;
    }

    return ret;
}


Halfspace::Halfspace
(
    resource*       resp,
    directory*      pDir,
    rt_db_internal* ip,
    db_i*           dbip
) : Object(resp, pDir, ip, dbip), m_internalp(0) {}


const rt_half_internal* Halfspace::Internal(void) const {
    const rt_half_internal* ret;

    if (m_ip != 0)
        ret = static_cast<const rt_half_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_HALF_CK_MAGIC(ret);

    return ret;
}


rt_half_internal* Halfspace::Internal(void) {
    rt_half_internal* ret;

    if (m_ip != 0)
        ret = static_cast<rt_half_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_HALF_CK_MAGIC(ret);

    return ret;
}
