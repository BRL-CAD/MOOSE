/*                H Y P E R B O L O I D . C P P
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
/** @file Hyperboloid.cpp
 *
 *  BRL-CAD core C++ interface:
 *      elliptical hyperboloid (ID_EHY) database object implementation
 */

#include <cassert>

#include "rt/geom.h"
#include "raytrace.h"
#include "bu/parallel.h"

#include <brlcad/Database/Hyperboloid.h>


using namespace BRLCAD;


Hyperboloid::Hyperboloid(void) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_ehy_internal);
        m_internalp->ehy_magic = RT_EHY_INTERNAL_MAGIC;

        Set(Vector3D(), Vector3D(0, 0, 1), Vector3D(0, 1, 0), 1, 1);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Hyperboloid::Hyperboloid
(
    const Vector3D& basePoint,
    const Vector3D& height,
    const Vector3D& semiMajorAxis,
    double          semiMinorAxisLength,
    double          apexAsymptoteDistance
) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_ehy_internal);
        m_internalp->ehy_magic = RT_EHY_INTERNAL_MAGIC;

        Set(basePoint, height, semiMajorAxis, semiMinorAxisLength, apexAsymptoteDistance);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Hyperboloid::Hyperboloid
(
    const Vector3D& basePoint,
    const Vector3D& height,
    const Vector3D& semiMajorAxisDirection,
    double          semiMajorAxisLength,
    double          semiMinorAxisLength,
    double          apexAsymptoteDistance
) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_ehy_internal);
        m_internalp->ehy_magic = RT_EHY_INTERNAL_MAGIC;

        Set(basePoint, height, semiMajorAxisDirection, semiMajorAxisLength, semiMinorAxisLength, apexAsymptoteDistance);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Hyperboloid::Hyperboloid
(
    const Hyperboloid& original
) : Object(original) {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_ehy_internal);
        memcpy(m_internalp, original.Internal(), sizeof(rt_ehy_internal));
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Hyperboloid::~Hyperboloid(void) {
    if (m_internalp != 0)
        bu_free(m_internalp, "BRLCAD::Hyperboloid::~Hyperboloid::m_internalp");
}


const Hyperboloid& Hyperboloid::operator=
(
    const Hyperboloid& original
) {
    if(&original != this) {
        Copy(original);
        memcpy(Internal(), original.Internal(), sizeof(rt_ehy_internal));
    }

    return *this;
}


Vector3D Hyperboloid::BasePoint(void) const {
    return Vector3D(Internal()->ehy_V);
}


void Hyperboloid::SetBasePoint
(
    const Vector3D& point
) {
    VMOVE(Internal()->ehy_V, point.coordinates);
}


Vector3D Hyperboloid::Height(void) const {
    return Vector3D(Internal()->ehy_H);
}


void Hyperboloid::SetHeight
(
    const Vector3D& height
) {
    VMOVE(Internal()->ehy_H, height.coordinates);
}


Vector3D Hyperboloid::SemiMajorAxis(void) const {
    Vector3D               ret;
    const rt_ehy_internal* internalp = Internal();

    VSCALE(ret.coordinates, internalp->ehy_Au, internalp->ehy_r1);

    return ret;
}


void Hyperboloid::SetSemiMajorAxis
(
    const Vector3D& axis
) {
    rt_ehy_internal* internalp = Internal();

    VMOVE(internalp->ehy_Au, axis.coordinates);
    internalp->ehy_r1 = MAGNITUDE(internalp->ehy_Au);
    VUNITIZE(internalp->ehy_Au);
}


void Hyperboloid::SetSemiMajorAxis
(
    const Vector3D& direction,
    double          length
) {
    rt_ehy_internal* internalp = Internal();

    VMOVE(internalp->ehy_Au, direction.coordinates);
    VUNITIZE(internalp->ehy_Au);
    internalp->ehy_r1 = length;
}


Vector3D Hyperboloid::SemiMajorAxisDirection(void) const {
    return Vector3D(Internal()->ehy_Au);
}


void Hyperboloid::SetSemiMajorAxisDirection
(
    const Vector3D& direction
) {
    rt_ehy_internal* internalp = Internal();

    VMOVE(internalp->ehy_Au, direction.coordinates);
    VUNITIZE(internalp->ehy_Au);
}


double Hyperboloid::SemiMajorAxisLength(void) const {
    return Internal()->ehy_r1;
}


void Hyperboloid::SetSemiMajorAxisLength
(
    double length
) {
    Internal()->ehy_r1 = length;
}


double Hyperboloid::SemiMinorAxisLength(void) const {
    return Internal()->ehy_r2;
}


void Hyperboloid::SetSemiMinorAxisLength
(
    double length
) {
    Internal()->ehy_r2 = length;
}


double Hyperboloid::ApexAsymptoteDistance(void) const {
    return Internal()->ehy_c;
}


void Hyperboloid::SetApexAsymptoteDistance
(
    double distance
) {
    Internal()->ehy_c = distance;
}


void Hyperboloid::Set
(
    const Vector3D& basePoint,
    const Vector3D& height,
    const Vector3D& semiMajorAxis,
    double          semiMinorAxisLength,
    double          apexAsymptoteDistance
) {
    rt_ehy_internal* internalp = Internal();

    VMOVE(internalp->ehy_V, basePoint.coordinates);
    VMOVE(internalp->ehy_H, height.coordinates);
    VMOVE(internalp->ehy_Au, semiMajorAxis.coordinates);
    internalp->ehy_r1 = MAGNITUDE(internalp->ehy_Au);
    VUNITIZE(internalp->ehy_Au);
    internalp->ehy_r2 = semiMinorAxisLength;
    internalp->ehy_c  = apexAsymptoteDistance;
}


void Hyperboloid::Set
(
    const Vector3D& basePoint,
    const Vector3D& height,
    const Vector3D& semiMajorAxisDirection,
    double          semiMajorAxisLength,
    double          semiMinorAxisLength,
    double          apexAsymptoteDistance
) {
    rt_ehy_internal* internalp = Internal();

    VMOVE(internalp->ehy_V, basePoint.coordinates);
    VMOVE(internalp->ehy_H, height.coordinates);
    VMOVE(internalp->ehy_Au, semiMajorAxisDirection.coordinates);
    VUNITIZE(internalp->ehy_Au);
    internalp->ehy_r1 = semiMajorAxisLength;
    internalp->ehy_r2 = semiMinorAxisLength;
    internalp->ehy_c  = apexAsymptoteDistance;
}


const Object& Hyperboloid::operator=
(
    const Object& original
) {
    const Hyperboloid* ehy = dynamic_cast<const Hyperboloid*>(&original);
    assert(ehy != 0);

    if (ehy != 0)
        *this = *ehy;

    return *this;
}


Object* Hyperboloid::Clone(void) const {
    return new Hyperboloid(*this);
}


const char* Hyperboloid::ClassName(void) {
    return "Hyperboloid";
}


const char* Hyperboloid::Type(void) const {
    return ClassName();
}


bool Hyperboloid::IsValid(void) const {
    bool                   ret       = false;
    const rt_ehy_internal* internalp = Internal();

    if (Validate() &&
        !VNEAR_ZERO(internalp->ehy_H, SMALL_FASTF) &&
        NEAR_EQUAL(MAGNITUDE(internalp->ehy_Au), 1., RT_LEN_TOL) &&
        (internalp->ehy_r1 > SMALL_FASTF) &&
        (internalp->ehy_r1 >= internalp->ehy_r2) &&
        (internalp->ehy_c > SMALL_FASTF) &&
        NEAR_ZERO(VDOT(internalp->ehy_H, internalp->ehy_Au ), RT_DOT_TOL))
        ret = true;

    return ret;
}


Hyperboloid::Hyperboloid
(
    resource*       resp,
    directory*      pDir,
    rt_db_internal* ip,
    db_i*           dbip
) : Object(resp, pDir, ip, dbip), m_internalp(0) {}


rt_ehy_internal* Hyperboloid::Internal(void) {
    rt_ehy_internal* ret;

    if(m_ip != 0)
        ret = static_cast<rt_ehy_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_EHY_CK_MAGIC(ret);

    return ret;
}


const rt_ehy_internal* Hyperboloid::Internal(void) const {
    const rt_ehy_internal* ret;

    if (m_ip != 0)
        ret = static_cast<const rt_ehy_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_EHY_CK_MAGIC(ret);

    return ret;
}
