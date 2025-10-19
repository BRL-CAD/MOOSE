/*                      T O R U S . C P P
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
/** @file Torus.cpp
 *
 *  BRL-CAD core C++ interface:
 *      torus (ID_TOR) database object implementation
 */

#include <cassert>

#include "rt/geom.h"
#include "raytrace.h"
#include "bu/parallel.h"

#include <brlcad/Database/Torus.h>


using namespace BRLCAD;


Torus::Torus(void) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_tor_internal);
        m_internalp->magic = RT_TOR_INTERNAL_MAGIC;

        Set(Vector3D(), Vector3D(0., 0., 1.), 2., 1.);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Torus::Torus
(
    const Vector3D& center,
    const Vector3D& normalToTubeCenterLinePlane,
    double          tubeCenterLineRadius,
    double          tubeRadius
) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_tor_internal);
        m_internalp->magic = RT_TOR_INTERNAL_MAGIC;

        Set(center, normalToTubeCenterLinePlane, tubeCenterLineRadius, tubeRadius);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Torus::Torus
(
    const Torus& original
) : Object(original) {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_tor_internal);
        memcpy(m_internalp, original.Internal(), sizeof(rt_tor_internal));
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Torus::~Torus(void) {
    if (m_internalp != nullptr)
        bu_free(m_internalp, "BRLCAD::Torus::~Torus::m_internalp");
}


const Torus& Torus::operator =
(
    const Torus& original
) {
    if (&original != this) {
        Copy(original);
        memcpy(Internal(), original.Internal(), sizeof(rt_tor_internal));
    }

    return *this;
}


Vector3D Torus::Center(void) const {
    return Vector3D(Internal()->v);
}


void Torus::SetCenter
(
    const Vector3D& center
) {
    VMOVE(Internal()->v, center.coordinates);
}


Vector3D Torus::Normal(void) const{
    return Vector3D(Internal()->h);
}


void Torus::SetNormal
(
    const Vector3D& normal
) {
    assert(!VNEAR_ZERO(normal.coordinates, SMALL_FASTF));

    VMOVE(Internal()->h, normal.coordinates);
    VUNITIZE(Internal()->h);
}


double Torus::TubeCenterLineRadius(void) const {
    return Internal()->r_a;
}


void Torus::SetTubeCenterLineRadius
(
    double radius
){
    Internal()->r_a = radius;
}


double Torus::TubeRadius(void) const{
    return Internal()->r_h;
}


void Torus::SetTubeRadius
(
    double radius
) {
    Internal()->r_h = radius;
}


void Torus::Set
(
    const Vector3D& center,
    const Vector3D& normalToTubeCenterLinePlane,
    double          tubeCenterLineRadius,
    double          tubeRadius
) {
        rt_tor_internal* internalp = Internal();

        VMOVE(internalp->v, center.coordinates);

        assert(!VNEAR_ZERO(normalToTubeCenterLinePlane.coordinates, SMALL_FASTF));
        VMOVE(internalp->h, normalToTubeCenterLinePlane.coordinates);
        VUNITIZE(internalp->h);

        internalp->r_a = tubeCenterLineRadius;
        internalp->r_h = tubeRadius;
}


const Object& Torus::operator=
(
    const Object& original
) {
    const Torus* tor = dynamic_cast<const Torus*>(&original);
    assert(tor != nullptr);

    if (tor != nullptr)
        *this = *tor;

    return *this;
}


Object* Torus::Clone(void) const {
    return new Torus(*this);
}


const char* Torus::ClassName(void) {
    return "Torus";
}


const char* Torus::Type(void) const {
    return ClassName();
}


bool Torus::IsValid(void) const {
    bool                   ret       = false;
    const rt_tor_internal* internalp = Internal();

    if (Validate() &&
        !NEAR_ZERO(internalp->r_a, SMALL_FASTF) &&
        !NEAR_ZERO(internalp->r_h, SMALL_FASTF) &&
        NEAR_EQUAL(MAGNITUDE(internalp->h), 1., RT_LEN_TOL) &&
        (internalp->r_a >= internalp->r_h))
        ret = true;

    return ret;
}


Torus::Torus
(
    resource*       resp,
    directory*      pDir,
    rt_db_internal* ip,
    db_i*           dbip
) : Object(resp, pDir, ip, dbip), m_internalp(nullptr) {}


const rt_tor_internal* Torus::Internal(void) const {
    const rt_tor_internal* ret;

    if (m_ip != nullptr)
        ret = static_cast<const rt_tor_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_TOR_CK_MAGIC(ret);

    return ret;
}


rt_tor_internal* Torus::Internal(void) {
    rt_tor_internal* ret;

    if(m_ip != nullptr)
        ret = static_cast<rt_tor_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_TOR_CK_MAGIC(ret);

    return ret;
}
