/*             E L L I P T I C A L T O R U S . C P P
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
/** @file EllipticalTorus.h
 *
 *  BRL-CAD core C++ interface:
 *       elliptical torus (ID_ETO) database object implementation
 */

#include <cassert>

#include "rt/geom.h"
#include "raytrace.h"
#include "bu/parallel.h"

#include <brlcad/Database/EllipticalTorus.h>


using namespace BRLCAD;


EllipticalTorus::EllipticalTorus(void) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_eto_internal);
        m_internalp->eto_magic = RT_ETO_INTERNAL_MAGIC;

        Set(Vector3D(), Vector3D(0., 0., 1.), 2., Vector3D(1., 0., 0.), 1.);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


EllipticalTorus::EllipticalTorus
(
    const Vector3D& center,
    const Vector3D& normalToTubeCenterLinePlane,
    double          tubeCenterLineRadius,
    const Vector3D& tubeSemiMajorAxis,
    double          tubeSemiMinorAxisLength
) {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_eto_internal);
        m_internalp->eto_magic = RT_ETO_INTERNAL_MAGIC;

        Set(center, normalToTubeCenterLinePlane, tubeCenterLineRadius, tubeSemiMajorAxis, tubeSemiMinorAxisLength);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


EllipticalTorus::EllipticalTorus
(
    const EllipticalTorus& original
) : Object(original) {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_eto_internal);
        memcpy(m_internalp, original.Internal(), sizeof(rt_eto_internal));
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


EllipticalTorus::~EllipticalTorus(void) {
    if (m_internalp != nullptr)
        bu_free(m_internalp, "BRLCAD::EllipticalTorus::~EllipticalTorus::m_internalp");
}


const EllipticalTorus& EllipticalTorus::operator =
(
    const EllipticalTorus& original
) {
    if(&original != this) {
        Copy(original);
        memcpy(Internal(), original.Internal(), sizeof(rt_eto_internal));
    }

    return *this;
}


Vector3D EllipticalTorus::Center(void) const {
    return Vector3D(Internal()->eto_V);
}


void EllipticalTorus::SetCenter
(
    const Vector3D& center
) {
    VMOVE(Internal()->eto_V, center.coordinates);
}


Vector3D EllipticalTorus::Normal(void) const {
    return Vector3D(Internal()->eto_N);
}


void EllipticalTorus::SetNormal
(
    const Vector3D& normal
) {
    assert(!VNEAR_ZERO(normal.coordinates, SMALL_FASTF));

    VMOVE(Internal()->eto_N, normal.coordinates);
    VUNITIZE(Internal()->eto_N);
}


double EllipticalTorus::TubeCenterLineRadius(void) const {
    return Internal()->eto_r;
}


void EllipticalTorus::SetTubeCenterLineRadius
(
    double radius
) {
    Internal()->eto_r = radius;
}


Vector3D EllipticalTorus::TubeSemiMajorAxis(void) const {
    return Vector3D(Internal()->eto_C);
}


void EllipticalTorus::SetTubeSemiMajorAxis
(
    const Vector3D& axis
) {
    VMOVE(Internal()->eto_C, axis.coordinates);
}


double EllipticalTorus::TubeSemiMinorAxis(void) const {
    return Internal()->eto_rd;
}


void EllipticalTorus::SetTubeSemiMinorAxis
(
    double length
) {
    Internal()->eto_rd = length;
}


void EllipticalTorus::Set
(
    const Vector3D& center,
    const Vector3D& normalToTubeCenterLinePlane,
    double          tubeCenterLineRadius,
    const Vector3D& tubeSemiMajorAxis,
    double          tubeSemiMinorAxisLength
) {
     rt_eto_internal* internalp = Internal();

    VMOVE(internalp->eto_V, center.coordinates);

    assert(!VNEAR_ZERO(normalToTubeCenterLinePlane.coordinates, SMALL_FASTF));
    VMOVE(internalp->eto_N, normalToTubeCenterLinePlane.coordinates);
    VUNITIZE(internalp->eto_N);

    internalp->eto_r = tubeCenterLineRadius;
    VMOVE(internalp->eto_C,tubeSemiMajorAxis.coordinates);
    internalp->eto_rd = tubeSemiMinorAxisLength;
}


const Object& EllipticalTorus::operator=
(
    const Object& original
) {
    const EllipticalTorus* eto = dynamic_cast<const EllipticalTorus*>(&original);
    assert(eto != nullptr);

    if (eto != nullptr)
        *this = *eto;

    return *this;
}


Object* EllipticalTorus::Clone(void) const {
    return new EllipticalTorus(*this);
}


const char* EllipticalTorus::ClassName(void) {
    return "EllipticalTorus";
}


const char* EllipticalTorus::Type(void) const {
    return ClassName();
}


bool EllipticalTorus::IsValid(void) const {
    bool                   ret       = false;
    const rt_eto_internal* internalp = Internal();
    double                 rc        = MAGNITUDE(internalp->eto_C);

    ret = (Validate() &&
           !VNEAR_ZERO(internalp->eto_N, SMALL_FASTF) &&
           !NEAR_ZERO(rc, 0.0001) &&
           !NEAR_ZERO(internalp->eto_r, 0.0001) &&
           !NEAR_ZERO(internalp->eto_rd, 0.0001));

    if (ret == true) { // ellipse may not overlap itself when revolved
        Vector3D unitizedNormal;

        VMOVE(unitizedNormal.coordinates, internalp->eto_N);
        VUNITIZE(unitizedNormal.coordinates);

        // get horizontal and vertical components of semi-major and semi-minor axes
        double cv = VDOT(internalp->eto_C, unitizedNormal.coordinates);
        double ch = sqrt(MAGSQ(internalp->eto_C ) - cv * cv);

        // angle between semi-major axis and unitizedNormal
        double phi = acos(cv / rc);
        double dh  = internalp->eto_rd * cos(phi);

        if (ch > internalp->eto_r || dh > internalp->eto_r)
            ret = false;
    }

    return ret;
}


EllipticalTorus::EllipticalTorus
(
    resource*       resp,
    directory*      pDir,
    rt_db_internal* ip,
    db_i*           dbip
) : Object(resp, pDir, ip, dbip), m_internalp(nullptr) {}


const rt_eto_internal* EllipticalTorus::Internal(void) const {
    const rt_eto_internal* ret;

    if (m_ip != nullptr)
        ret = static_cast<const rt_eto_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_ETO_CK_MAGIC(ret);

    return ret;
}


rt_eto_internal* EllipticalTorus::Internal(void) {
    rt_eto_internal* ret;

    if(m_ip != nullptr)
        ret = static_cast<rt_eto_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_ETO_CK_MAGIC(ret);

    return ret;
}
