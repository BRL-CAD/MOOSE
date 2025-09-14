/*                P A R A B O L O I D . C P P
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
/** @file Paraboloid.cpp
 *
 *  BRL-CAD core C++ interface:
 *      elliptical paraboloid (ID_EPA) database object implementation
 */

#include <cassert>

#include "rt/geom.h"
#include "raytrace.h"
#include "bu/parallel.h"

#include <brlcad/Database/Paraboloid.h>


using namespace BRLCAD;


Paraboloid::Paraboloid(void) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_epa_internal);
        m_internalp->epa_magic = RT_EPA_INTERNAL_MAGIC;

        Set(Vector3D(),Vector3D(0,0,1),Vector3D(0,1,0),1);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Paraboloid::Paraboloid
(
const Vector3D& basePoint,
const Vector3D& height,
const Vector3D& semiMajorAxis,
double          semiMinorAxisLength
) {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_epa_internal);
        m_internalp->epa_magic = RT_EPA_INTERNAL_MAGIC;

        Set(basePoint, height, semiMajorAxis, semiMinorAxisLength);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Paraboloid::Paraboloid
(
const Vector3D& basePoint,
const Vector3D& height,
const Vector3D& semiMajorAxisDirection,
double          semiMajorAxisLength,
double          semiMinorAxisLength
) {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_epa_internal);
        m_internalp->epa_magic = RT_EPA_INTERNAL_MAGIC;

        Set(basePoint, height, semiMajorAxisDirection, semiMajorAxisLength, semiMinorAxisLength);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Paraboloid::Paraboloid
(
    const Paraboloid& original
) : Object(original) {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_epa_internal);
        memcpy(m_internalp, original.Internal(), sizeof(rt_epa_internal));
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Paraboloid::~Paraboloid(void) {
    if (m_internalp != 0)
        bu_free(m_internalp, "BRLCAD::Paraboloid::~Paraboloid::m_internalp");
}


const Paraboloid& Paraboloid::operator=
(
    const Paraboloid& original
) {
    if(&original != this) {
        Copy(original);
        memcpy(Internal(), original.Internal(), sizeof(rt_epa_internal));
    }

    return *this;
}


Vector3D Paraboloid::BasePoint(void) const {
    return Vector3D(Internal()->epa_V);
}


void Paraboloid::SetBasePoint
(
    const Vector3D& point
) {
    VMOVE(Internal()->epa_V, point.coordinates);
}


Vector3D Paraboloid::Height(void) const {
    return Vector3D(Internal()->epa_H);
}


void Paraboloid::SetHeight
(
    const Vector3D& height
) {
    VMOVE(Internal()->epa_H, height.coordinates);
}


Vector3D Paraboloid::SemiMajorAxis(void) const {
    Vector3D               ret;
    const rt_epa_internal* internalp = Internal();

    VSCALE(ret.coordinates, internalp->epa_Au, internalp->epa_r1);

    return ret;
}


void Paraboloid::SetSemiMajorAxis
(
    const Vector3D& axis
) {
    rt_epa_internal* internalp = Internal();

    VMOVE(internalp->epa_Au, axis.coordinates);
    internalp->epa_r1 = MAGNITUDE(internalp->epa_Au);
    VUNITIZE(internalp->epa_Au);
}


void Paraboloid::SetSemiMajorAxis
(
    const Vector3D& direction,
    double          length
) {
    rt_epa_internal* internalp = Internal();

    VMOVE(internalp->epa_Au, direction.coordinates);
    VUNITIZE(internalp->epa_Au);
    internalp->epa_r1 = length;
}


Vector3D Paraboloid::SemiMajorAxisDirection(void) const {
    return Vector3D(Internal()->epa_Au);
}


void Paraboloid::SetSemiMajorAxisDirection
(
    const Vector3D& direction
) {
    rt_epa_internal* internalp = Internal();

    VMOVE(internalp->epa_Au, direction.coordinates);
    VUNITIZE(internalp->epa_Au);
}


double Paraboloid::SemiMajorAxisLength(void) const {
    return Internal()->epa_r1;
}


void Paraboloid::SetSemiMajorAxisLength
(
double length
) {
    Internal()->epa_r1 = length;
}


double Paraboloid::SemiMinorAxisLength(void) const {
    return Internal()->epa_r2;
}


void Paraboloid::SetSemiMinorAxisLength
(
double length
) {
    Internal()->epa_r2 = length;
}


void Paraboloid::Set
(
const Vector3D& basePoint,
const Vector3D& height,
const Vector3D& semiMajorAxis,
double          semiMinorAxisLength
) {
    rt_epa_internal* internalp = Internal();

    VMOVE(internalp->epa_V, basePoint.coordinates);
    VMOVE(internalp->epa_H, height.coordinates);
    VMOVE(internalp->epa_Au, semiMajorAxis.coordinates);
    internalp->epa_r1 = MAGNITUDE(internalp->epa_Au);
    VUNITIZE(internalp->epa_Au);
    internalp->epa_r2 = semiMinorAxisLength;
}


void Paraboloid::Set
(
const Vector3D& basePoint,
const Vector3D& height,
const Vector3D& semiMajorAxisDirection,
double          semiMajorAxisLength,
double          semiMinorAxisLength
) {
    rt_epa_internal* internalp = Internal();

    VMOVE(internalp->epa_V, basePoint.coordinates);
    VMOVE(internalp->epa_H, height.coordinates);
    VMOVE(internalp->epa_Au, semiMajorAxisDirection.coordinates);
    VUNITIZE(internalp->epa_Au);
    internalp->epa_r1 = semiMajorAxisLength;
    internalp->epa_r2 = semiMinorAxisLength;
}


const Object& Paraboloid::operator=
(
    const Object& original
) {
    const Paraboloid* epa = dynamic_cast<const Paraboloid*>(&original);
    assert(epa != 0);

    if (epa != 0)
        *this = *epa;

    return *this;
}


Object* Paraboloid::Clone(void) const {
    return new Paraboloid(*this);
}


const char* Paraboloid::ClassName(void) {
    return "Paraboloid";
}


const char* Paraboloid::Type(void) const {
    return ClassName();
}


bool Paraboloid::IsValid(void) const {
    bool                   ret       = false;
    const rt_epa_internal* internalp = Internal();

    if (Validate() &&
        !VNEAR_ZERO(internalp->epa_H, SMALL_FASTF) &&
        NEAR_EQUAL(MAGNITUDE(internalp->epa_Au), 1., RT_LEN_TOL) &&
        (internalp->epa_r1 > SMALL_FASTF) &&
        (internalp->epa_r1 >= internalp->epa_r2) &&
        NEAR_ZERO(VDOT(internalp->epa_H, internalp->epa_Au ), RT_DOT_TOL))
        ret = true;

    return ret;
}


Paraboloid::Paraboloid
(
    resource*       resp,
    directory*      pDir,
    rt_db_internal* ip,
    db_i*           dbip
) : Object(resp, pDir, ip, dbip), m_internalp(0) {}


rt_epa_internal* Paraboloid::Internal(void) {
    rt_epa_internal* ret;

    if(m_ip != 0)
        ret = static_cast<rt_epa_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_EPA_CK_MAGIC(ret);

    return ret;
}


const rt_epa_internal* Paraboloid::Internal(void) const {
    const rt_epa_internal* ret;

    if (m_ip != 0)
        ret = static_cast<const rt_epa_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_EPA_CK_MAGIC(ret);

    return ret;
}
