/*                      C O N E . C P P
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
/** @file Cone.cpp
 *
 *  BRL-CAD core C++ interface:
 *      truncated general cone (ID_TGC) database object implementation
 */

#include <cassert>

#include "rt/geom.h"
#include "raytrace.h"
#include "bu/parallel.h"

#include <brlcad/Database/Cone.h>


using namespace BRLCAD;


Cone::Cone(void) : Object () {
    if(!BU_SETJUMP){
        BU_GET(m_internalp, rt_tgc_internal);
        m_internalp->magic = RT_TGC_INTERNAL_MAGIC;

        Set(Vector3D(), Vector3D(0., 0., 1.), 1., 0.);
    }
    else{
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Cone::Cone
(
    const Vector3D& basePoint,
    const Vector3D& height,
    const Vector3D& semiPrincipalAxisA,
    const Vector3D& semiPrincipalAxisB,
    double          ratioCtoA,
    double          ratioDtoB
) {
    if(!BU_SETJUMP){
        BU_GET(m_internalp, rt_tgc_internal);
        m_internalp->magic = RT_TGC_INTERNAL_MAGIC;

        Set(basePoint, height, semiPrincipalAxisA, semiPrincipalAxisB, ratioCtoA, ratioDtoB);
    }
    else{
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;

}


Cone::Cone
(
    const Vector3D& basePoint,
    const Vector3D& height,
    const Vector3D& semiPrincipalAxisA,
    const Vector3D& semiPrincipalAxisB,
    double          scale
) {
    if(!BU_SETJUMP){
        BU_GET(m_internalp, rt_tgc_internal);
        m_internalp->magic = RT_TGC_INTERNAL_MAGIC;

        Set(basePoint, height, semiPrincipalAxisA, semiPrincipalAxisB, scale);
    }
    else{
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;

}


Cone::Cone
(
    const Vector3D& basePoint,
    const Vector3D& height,
    const Vector3D& semiPrincipalAxisA,
    const Vector3D& semiPrincipalAxisB
) {
    if(!BU_SETJUMP){
        BU_GET(m_internalp, rt_tgc_internal);
        m_internalp->magic = RT_TGC_INTERNAL_MAGIC;

        Set(basePoint, height, semiPrincipalAxisA, semiPrincipalAxisB);
    }
    else{
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;

}


Cone::Cone
(
    const Vector3D& basePoint,
    const Vector3D& height,
    double          radiusBase,
    double          radiusTop
) {
    if(!BU_SETJUMP){
        BU_GET(m_internalp, rt_tgc_internal);
        m_internalp->magic = RT_TGC_INTERNAL_MAGIC;

        Set(basePoint, height, radiusBase, radiusTop);
    }
    else{
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;

}


Cone::Cone
(
    const Vector3D& basePoint,
    const Vector3D& height,
    double          radius
) {
    if(!BU_SETJUMP){
        BU_GET(m_internalp, rt_tgc_internal);
        m_internalp->magic = RT_TGC_INTERNAL_MAGIC;

        Set(basePoint, height, radius);
    }
    else{
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;

}


Cone::Cone
(
    const Cone& original
) : Object(original) {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_tgc_internal);
        memcpy(m_internalp, original.Internal(), sizeof(rt_tgc_internal));
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Cone::~Cone(void) {
    if (m_internalp != 0)
        bu_free(m_internalp, "BRLCAD::Cone::~Cone::m_internalp");
}


const Cone& Cone::operator=
(
    const Cone& original
) {
    if(&original != this) {
        Copy(original);
        memcpy(Internal(), original.Internal(), sizeof(rt_tgc_internal));
    }

    return *this;
}


Vector3D Cone::BasePoint(void) const {
    return Vector3D(Internal()->v);
}


void Cone::SetBasePoint
(
    const Vector3D& basePoint
) {
    VMOVE(Internal()->v, basePoint.coordinates);
}


Vector3D Cone::Height(void) const {
    return Vector3D(Internal()->h);
}


void Cone::SetHeight
(
    const Vector3D& height
) {
    VMOVE(Internal()->h, height.coordinates);
}


Vector3D Cone::SemiPrincipalAxis
(
    size_t index
) const {
    Vector3D ret;

    assert(index < 4);

    switch (index) {
        case 0:
            VMOVE(ret.coordinates, Internal()->a);
            break;

        case 1:
            VMOVE(ret.coordinates, Internal()->b);
            break;

        case 2:
            VMOVE(ret.coordinates, Internal()->c);
            break;

        case 3:
            VMOVE(ret.coordinates, Internal()->d);
    }

    return ret;
}


void Cone::SetSemiPrincipalAxis
(
    size_t          index,
    const Vector3D& semiPrincipalAxis
) {
    assert(index < 4);

    switch (index) {
        case 0:
            VMOVE(Internal()->a, semiPrincipalAxis.coordinates);
            break;

        case 1:
            VMOVE(Internal()->b, semiPrincipalAxis.coordinates);
            break;

        case 2:
            VMOVE(Internal()->c, semiPrincipalAxis.coordinates);
            break;

        case 3:
            VMOVE(Internal()->d, semiPrincipalAxis.coordinates);
    }
}


void Cone::Set
(
    const Vector3D& basePoint,
    const Vector3D& height,
    const Vector3D& semiPrincipalAxisA,
    const Vector3D& semiPrincipalAxisB,
    double          ratioCtoA,
    double          ratioDtoB
) {
    rt_tgc_internal* internalp = Internal();

    VMOVE(internalp->v, basePoint.coordinates);
    VMOVE(internalp->h, height.coordinates);
    VMOVE(internalp->a, semiPrincipalAxisA.coordinates);
    VMOVE(internalp->b, semiPrincipalAxisB.coordinates);
    VSCALE(internalp->c, internalp->a, ratioCtoA);
    VSCALE(internalp->d, internalp->b, ratioDtoB);

}


void Cone::Set
(
    const Vector3D& basePoint,
    const Vector3D& height,
    const Vector3D& semiPrincipalAxisA,
    const Vector3D& semiPrincipalAxisB,
    double          scale
) {
    rt_tgc_internal* internalp = Internal();

    VMOVE(internalp->v, basePoint.coordinates);
    VMOVE(internalp->h, height.coordinates);
    VMOVE(internalp->a, semiPrincipalAxisA.coordinates);
    VMOVE(internalp->b, semiPrincipalAxisB.coordinates);
    VSCALE(internalp->c, internalp->a, scale);
    VSCALE(internalp->d, internalp->b, scale);

}


void Cone::Set
(
    const Vector3D& basePoint,
    const Vector3D& height,
    const Vector3D& semiPrincipalAxisA,
    const Vector3D& semiPrincipalAxisB
) {
    rt_tgc_internal* internalp = Internal();

    VMOVE(internalp->v, basePoint.coordinates);
    VMOVE(internalp->h, height.coordinates);
    VMOVE(internalp->a, semiPrincipalAxisA.coordinates);
    VMOVE(internalp->b, semiPrincipalAxisB.coordinates);
    VMOVE(internalp->c, internalp->a);
    VMOVE(internalp->d, internalp->b);

}


void Cone::Set
(
    const Vector3D& basePoint,
    const Vector3D& height,
    double          radiusBase,
    double          radiusTop
) {
    rt_tgc_internal* internalp = Internal();
    vect_t           semiPrincipalAxisA = {0.};
    vect_t           semiPrincipalAxisB = {0.};

    VMOVE(internalp->v, basePoint.coordinates);
    VMOVE(internalp->h, height.coordinates);

    bn_vec_ortho(semiPrincipalAxisA, internalp->h);
    VCROSS(semiPrincipalAxisB, semiPrincipalAxisA, internalp->h);
    VUNITIZE(semiPrincipalAxisB);

    VSCALE(internalp->a, semiPrincipalAxisA, radiusBase);
    VSCALE(internalp->b, semiPrincipalAxisB, radiusBase);
    VSCALE(internalp->c, semiPrincipalAxisA, radiusTop);
    VSCALE(internalp->d, semiPrincipalAxisB, radiusTop);
}


void Cone::Set
(
    const Vector3D& basePoint,
    const Vector3D& height,
    double          radius
) {
    rt_tgc_internal* internalp = Internal();
    vect_t           semiPrincipalAxisA = {0.};
    vect_t           semiPrincipalAxisB = {0.};

    VMOVE(internalp->v, basePoint.coordinates);
    VMOVE(internalp->h, height.coordinates);

    bn_vec_ortho(semiPrincipalAxisA, internalp->h);
    VCROSS(semiPrincipalAxisB, semiPrincipalAxisA, internalp->h);
    VUNITIZE(semiPrincipalAxisB);

    VSCALE(internalp->a, semiPrincipalAxisA, radius);
    VSCALE(internalp->b, semiPrincipalAxisB, radius);
    VMOVE(internalp->c, internalp->a);
    VMOVE(internalp->d, internalp->b);
}


const Object& Cone::operator=
(
    const Object& original
) {
    const Cone* tgc = dynamic_cast<const Cone*>(&original);
    assert(tgc != 0);

    if (tgc != 0)
        *this = *tgc;

    return *this;
}


Object* Cone::Clone(void) const {
    return new Cone(*this);
}


const char* Cone::ClassName(void) {
    return "Cone";
}


const char* Cone::Type(void) const {
    return ClassName();
}


bool Cone::IsValid(void) const {
    bool                   ret       = false;
    const rt_tgc_internal* internalp = Internal();
    double                 magA      = MAGNITUDE(internalp->a);
    double                 magB      = MAGNITUDE(internalp->b);
    double                 magH      = MAGNITUDE(internalp->h);

    if (Validate() &&
        !NEAR_ZERO(magA, RT_LEN_TOL) &&
        !NEAR_ZERO(magB, RT_LEN_TOL) &&
        !NEAR_ZERO(magH, RT_LEN_TOL) &&
        NEAR_ZERO(VDOT(internalp->a, internalp->b) / magA * magB, RT_DOT_TOL)) {
        double magC = MAGNITUDE(internalp->c);
        double magD = MAGNITUDE(internalp->d);

        if ((((magC * magD) <= SMALL) || NEAR_ZERO(VDOT(internalp->c, internalp->d), RT_DOT_TOL)) &&
            ((magC <= SMALL) || NEAR_ZERO(1. - VDOT(internalp->a, internalp->c) / (magA * magC), RT_DOT_TOL)) &&
            ((magD <= SMALL) || NEAR_ZERO(1. - VDOT(internalp->b, internalp->d) / (magB * magD), RT_DOT_TOL))) {
            vect_t aCrossB;
            VCROSS(aCrossB, internalp->a, internalp->b );

            ret = !NEAR_ZERO(VDOT(internalp->h, aCrossB ) / ( magA * magB * magH), RT_DOT_TOL);
        }
    }

    return ret;
}


Cone::Cone
(
    resource*       resp,
    directory*      pDir,
    rt_db_internal* ip,
    db_i*           dbip
) : Object(resp, pDir, ip, dbip), m_internalp(0) {}


rt_tgc_internal* Cone::Internal(void) {
    rt_tgc_internal* ret;

    if(m_ip != 0)
        ret = static_cast<rt_tgc_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_TGC_CK_MAGIC(ret);

    return ret;
}


const rt_tgc_internal* Cone::Internal(void) const {
    const rt_tgc_internal* ret;

    if (m_ip != 0)
        ret = static_cast<const rt_tgc_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_TGC_CK_MAGIC(ret);

    return ret;
}
