/*                P A R T I C L E . C P P
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
/** @file Particle.cpp
 *
 *  BRL-CAD core C++ interface:
 *      particle (ID_PARTICLE) database object implementation
 */

#include <cassert>

#include "rt/geom.h"
#include "raytrace.h"
#include "bu/parallel.h"

#include <brlcad/Database/Particle.h>


using namespace BRLCAD;


Particle::Particle(void) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_part_internal);
        m_internalp->part_magic = RT_PART_INTERNAL_MAGIC;

        Set(Vector3D(), Vector3D(0., 0., 1.), 1., 1.);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Particle::Particle
(
    const Vector3D& basePoint,
    const Vector3D& height,
    double          baseRadius,
    double          topRadius
) {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_part_internal);
        m_internalp->part_magic = RT_PART_INTERNAL_MAGIC;

        Set(basePoint, height, baseRadius, topRadius);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Particle::Particle
(
    const Particle& original
) : Object(original) {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_part_internal);
        memcpy(m_internalp, original.Internal(), sizeof(rt_part_internal));
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Particle::~Particle(void) {
    if (m_internalp != 0)
        bu_free(m_internalp, "BRLCAD::Particle::~Particle::m_internalp");
}


const Particle& Particle::operator =
(
    const Particle& original
) {
    if(&original != this) {
        Copy(original);
        memcpy(Internal(), original.Internal(), sizeof(rt_part_internal));
    }

    return *this;
}


Vector3D Particle::BasePoint(void) const {
    return Vector3D(Internal()->part_V);
}


void Particle::SetBasePoint
(
    const Vector3D& basePoint
) {
    VMOVE(Internal()->part_V, basePoint.coordinates);

    SetType();
}


Vector3D Particle::Height(void) const {
    return Vector3D(Internal()->part_H);
}


void Particle::SetHeight
(
    const Vector3D& height
){
    VMOVE(Internal()->part_H, height.coordinates);

    SetType();
}


double Particle::BaseRadius(void) const {
    return Internal()->part_vrad;
}


void Particle::SetBaseRadius
(
    double baseRadius
) {
    Internal()->part_vrad = baseRadius;

    SetType();
}


double Particle::TopRadius(void) const{
    return Internal()->part_hrad;
}


void Particle::SetTopRadius
(
    double topRadius
) {
    Internal()->part_hrad = topRadius;

    SetType();
}


void Particle::Set
(
    const Vector3D& basePoint,
    const Vector3D& height,
    double          baseRadius,
    double          topRadius
) {
    rt_part_internal* internalp = Internal();

    VMOVE(internalp->part_V, basePoint.coordinates);
    VMOVE(internalp->part_H, height.coordinates);

    internalp->part_vrad = baseRadius;
    internalp->part_hrad = topRadius;

    SetType();
}


const Object& Particle::operator=
(
    const Object& original
) {
    const Particle* part = dynamic_cast<const Particle*>(&original);
    assert(part != 0);

    if (part != 0)
        *this = *part;

    return *this;
}


Object* Particle::Clone(void) const {
    return new Particle(*this);
}


const char* Particle::ClassName(void) {
    return "Particle";
}


const char* Particle::Type(void) const {
    return ClassName();
}


bool Particle::IsValid(void) const {
    bool                    ret       = false;
    const rt_part_internal* internalp = Internal();
    double                  maxRadius;
    double                  minRadius;

    if (internalp->part_vrad > internalp->part_hrad)  {
	maxRadius = internalp->part_vrad;
	minRadius = internalp->part_hrad;
    }
    else {
	maxRadius = internalp->part_hrad;
	minRadius = internalp->part_vrad;
    }

    if (Validate() && (maxRadius > 0.) && (minRadius >= 0.)) {
        if (internalp->part_type == RT_PARTICLE_TYPE_SPHERE) {
            if (((maxRadius - minRadius) / maxRadius) < SMALL_FASTF) // radii are nearly equal
                ret = true;
        }
        else
            ret = true;
    }

    return ret;
}


Particle::Particle
(
    resource*       resp,
    directory*      pDir,
    rt_db_internal* ip,
    db_i*           dbip
) : Object(resp, pDir, ip, dbip), m_internalp(0) {}


void Particle::SetType(void) {
    rt_part_internal* internalp = Internal();
    double            maxRadius;
    double            minRadius;

    if (internalp->part_vrad > internalp->part_hrad)  {
	maxRadius = internalp->part_vrad;
	minRadius = internalp->part_hrad;
    }
    else {
	maxRadius = internalp->part_hrad;
	minRadius = internalp->part_vrad;
    }

    if ((MAGSQ(internalp->part_H) * 1000000.) < (maxRadius * maxRadius)) // Height vector is insignificant, particle is a sphere
	internalp->part_type = RT_PARTICLE_TYPE_SPHERE;
    else if (((maxRadius - minRadius) / maxRadius) < 0.001 )             // radii are nearly equal, particle is a cylinder
	internalp->part_type = RT_PARTICLE_TYPE_CYLINDER;
    else
        internalp->part_type = RT_PARTICLE_TYPE_CONE;
}


rt_part_internal* Particle::Internal(void) {
    rt_part_internal* ret;

    if(m_ip != 0)
        ret = static_cast<rt_part_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_PART_CK_MAGIC(ret);

    return ret;
}


const rt_part_internal* Particle::Internal(void) const {
    const rt_part_internal* ret;

    if (m_ip != 0)
        ret = static_cast<const rt_part_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_PART_CK_MAGIC(ret);

    return ret;
}
