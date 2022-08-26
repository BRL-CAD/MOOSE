/*                      S P H E R E . C P P
 * BRL-CAD
 *
 * Copyright (c) 2014-2020 United States Government as represented by
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
/** @file Sphere.cpp
 *
 *  BRL-CAD core C++ interface:
 *      SPHERE (ID_SPH) database object implementation
 */

#include <cassert>

#include "raytrace.h"
#include "rt/geom.h"
#include "bu/parallel.h"

#include <brlcad/Database/Sphere.h>


using namespace BRLCAD;


Sphere::Sphere(void) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_ell_internal);
        m_internalp->magic = RT_ELL_INTERNAL_MAGIC;
        Set(Vector3D(), 1.);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Sphere::Sphere
(
    const Vector3D& center,
    double          radius
) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_ell_internal);
        m_internalp->magic = RT_ELL_INTERNAL_MAGIC;
        Set(center, radius);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Sphere::Sphere
(
    const Sphere& original
) : Object(original) {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_ell_internal);
        memcpy(m_internalp, original.Internal(), sizeof(rt_ell_internal));
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;

}


Sphere::~Sphere
(
    void
) {
    if (m_internalp != 0)
        bu_free(m_internalp, "BRLCAD::Sphere::~Sphere::m_internalp");
}


const Sphere& Sphere::operator=(const Sphere& original) {
    if (&original != this) {
        Copy(original);
        memcpy(Internal(), original.Internal(), sizeof(rt_ell_internal));
    }

    return *this;
}


const Object& Sphere::operator=
(
    const Object& original
) {
    const Sphere* sph = dynamic_cast<const Sphere*>(&original);
    assert(sph != 0);

    if (sph != 0)
        *this = *sph;

    return *this;
}


Vector3D Sphere::Center(void) const {
    return Vector3D(Internal()->v);
}


void Sphere::SetCenter(const Vector3D& center){
    VMOVE(Internal()->v, center.coordinates);
}


double Sphere::Radius(void) const {
    return MAGNITUDE(Internal()->a);;
}


void Sphere::SetRadius(double radius) {
    assert(radius > SMALL_FASTF);

    if (!NEAR_ZERO(radius, SMALL_FASTF)) {
        rt_ell_internal* internalp = Internal();

        VSET(internalp->a, radius, 0., 0.);
        VSET(internalp->b, 0., radius, 0.);
        VSET(internalp->c, 0., 0., radius);
    }
}


void Sphere::Set
(
    const Vector3D& center,
    double          radius
) {
    assert(radius > SMALL_FASTF);

    if (!NEAR_ZERO(radius, SMALL_FASTF)) {
        rt_ell_internal* internalp = Internal();

        VMOVE(internalp->v, center.coordinates);
        VSET(internalp->a, radius, 0., 0.);
        VSET(internalp->b, 0., radius, 0.);
        VSET(internalp->c, 0., 0., radius);
    }
}


Object* Sphere::Clone(void) const {
    return new Sphere(*this);
}


const char* Sphere::ClassName(void) {
    return "Sphere";
}


const char* Sphere::Type(void) const {
    return ClassName();
}


bool Sphere::IsValid(void) const {
    bool   ret                        = false;
    const  rt_ell_internal* internalp = Internal();
    double dist                       = 0.0005 * 0.0005;

    if (Validate() &&
        !VNEAR_ZERO(internalp->a, SMALL_FASTF) &&
        !VNEAR_ZERO(internalp->b, SMALL_FASTF) &&
        !VNEAR_ZERO(internalp->c, SMALL_FASTF) &&
        NEAR_ZERO(VDOT(internalp->b, Internal()->a ), RT_DOT_TOL)   &&
        NEAR_ZERO(VDOT(internalp->c, Internal()->a ), RT_DOT_TOL)   &&
        NEAR_ZERO(VDOT(internalp->b, Internal()->c ), RT_DOT_TOL)   &&
        NEAR_EQUAL(MAGNITUDE(internalp->a),MAGNITUDE(internalp->b), dist) &&
        NEAR_EQUAL(MAGNITUDE(internalp->b),MAGNITUDE(internalp->c), dist))
        ret = true;

    return ret;
}


Sphere::Sphere
(
    resource*       resp,
    directory*      pDir,
    rt_db_internal* ip,
    db_i*           dbip
) : Object(resp, pDir, ip, dbip), m_internalp(0) {}


const rt_ell_internal* Sphere::Internal(void) const {
    const rt_ell_internal* ret;

    if (m_ip != 0)
        ret = static_cast<const rt_ell_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_ELL_CK_MAGIC(ret);

    return ret;
}


rt_ell_internal* Sphere::Internal(void) {
    rt_ell_internal* ret;

    if (m_ip != 0)
        ret = static_cast<rt_ell_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_ELL_CK_MAGIC(ret);

    return ret;
}
