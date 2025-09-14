/*                      A R B 8 . C P P
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
/** @file Arb8.cpp
 *
 *  BRL-CAD core C++ interface:
 *      arbitrary regular polyhedron with as many as 8 vertices (ID_ARB8) database object implementation
 */

#include <cassert>

#include "rt/geom.h"
#include "raytrace.h"
#include "bu/parallel.h"

#ifdef min
#   undef min
#endif

#ifdef max
#   undef max
#endif

#include <algorithm>

#include <brlcad/Database/Arb8.h>


using namespace BRLCAD;


Arb8::Arb8(void) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_arb_internal);
        m_internalp->magic = RT_ARB_INTERNAL_MAGIC;

        SetPoints(Vector3D(0., 0., 0.), Vector3D(1., 1., 1.));
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Arb8::Arb8
(
    const Vector3D& point1,
    const Vector3D& point2,
    const Vector3D& point3,
    const Vector3D& point4
) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_arb_internal);
        m_internalp->magic = RT_ARB_INTERNAL_MAGIC;

        SetPoints(point1, point2, point3, point4);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Arb8::Arb8
(
    const Vector3D& point1,
    const Vector3D& point2,
    const Vector3D& point3,
    const Vector3D& point4,
    const Vector3D& point5
) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_arb_internal);
        m_internalp->magic = RT_ARB_INTERNAL_MAGIC;

        SetPoints(point1, point2, point3, point4, point5);
    }
    else {
        BU_UNSETJUMP;

    }

    BU_UNSETJUMP;
}


Arb8::Arb8
(
    const Vector3D& point1,
    const Vector3D& point2,
    const Vector3D& point3,
    const Vector3D& point4,
    const Vector3D& point5,
    const Vector3D& point6
) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_arb_internal);
        m_internalp->magic = RT_ARB_INTERNAL_MAGIC;

        SetPoints(point1, point2, point3, point4, point5, point6);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Arb8::Arb8
(
    const Vector3D& point1,
    const Vector3D& point2,
    const Vector3D& point3,
    const Vector3D& point4,
    const Vector3D& point5,
    const Vector3D& point6,
    const Vector3D& point7
) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_arb_internal);
        m_internalp->magic = RT_ARB_INTERNAL_MAGIC;

        SetPoints(point1, point2, point3, point4, point5, point6, point7);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Arb8::Arb8
(
    const Vector3D& point1,
    const Vector3D& point2,
    const Vector3D& point3,
    const Vector3D& point4,
    const Vector3D& point5,
    const Vector3D& point6,
    const Vector3D& point7,
    const Vector3D& point8
) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_arb_internal);
        m_internalp->magic = RT_ARB_INTERNAL_MAGIC;

        SetPoints(point1, point2, point3, point4, point5, point6, point7, point8);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Arb8::Arb8
(
    const Vector3D& point1,
    const Vector3D& point2
) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_arb_internal);
        m_internalp->magic = RT_ARB_INTERNAL_MAGIC;

        SetPoints(point1, point2);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Arb8::Arb8
(
    const Arb8& original
) : Object(original) {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_arb_internal);
        memcpy(m_internalp, original.Internal(), sizeof(rt_arb_internal));
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Arb8::~Arb8(void) {
    if (m_internalp != 0)
        bu_free(m_internalp, "BRLCAD::Arb8::~Arb8::m_internalp");
}


const Arb8& Arb8::operator=
(
    const Arb8& original
) {
    if (&original != this) {
        Copy(original);
        memcpy(Internal()->pt, original.Internal()->pt, 8 * sizeof(point_t));
    }

    return *this;
}


size_t Arb8::NumberOfVertices(void) const {
    size_t ret = 0;

    rt_db_internal intern;
    intern.idb_magic = RT_DB_INTERNAL_MAGIC;
    intern.idb_type  = ID_ARB8;
    intern.idb_ptr   = const_cast<rt_arb_internal*>(Internal());

    // same procedure as in librt's arb8.c
    bn_tol tolerance;
    tolerance.magic   = BN_TOL_MAGIC;
    tolerance.dist    = 0.0001;
    tolerance.dist_sq = tolerance.dist * tolerance.dist;
    tolerance.perp    = 1e-5;
    tolerance.para    = 1 - tolerance.perp;

    if (!BU_SETJUMP)
        ret = rt_arb_std_type(&intern, &tolerance);

    BU_UNSETJUMP;

    return ret;
}


static size_t VertexNumberToIndex
(
    size_t numberOfVertices,
    size_t number,
    size_t lastIndex = -1
) {
    static const size_t vertexOnIndex[5][8] ={{1, 2, 3, 1, 4, 4, 4, 4},
                                              {1, 2, 3, 4, 5, 5, 5, 5},
                                              {1, 2, 3, 4, 5, 5, 6, 6},
                                              {1, 2, 3, 4, 5, 6, 7, 5},
                                              {1, 2, 3, 4, 5, 6, 7, 8}};

    size_t              ret                 = -1;
    size_t              typeIndex           = numberOfVertices - 4;
    size_t              startIndex          = lastIndex + 1;

    for (size_t i = startIndex; i < 8; ++i) {
        if (vertexOnIndex[typeIndex][i] == number) {
            ret = i;
            break;
        }
    }

    return ret;
}


Vector3D Arb8::Point
(
    size_t number
) const {
    Vector3D ret;

    assert((number > 0) && (number < 9));

    if ((number > 0) && (number < 9)) {
        size_t numberOfVertices = NumberOfVertices();

        assert(numberOfVertices >= number);

        if (numberOfVertices >= number) {
            VMOVE(ret.coordinates, Internal()->pt[VertexNumberToIndex(numberOfVertices, number)]);
        }
    }

    return ret;
}


void Arb8::SetPoint
(
    size_t    number,
    Vector3D& point
) {
    assert((number > 0) && (number < 9));

    if ((number > 0) && (number < 9)) {
        size_t numberOfVertices = NumberOfVertices();

        assert(numberOfVertices >= number);

        if (numberOfVertices >= number) {
            if (number <= numberOfVertices) {
                rt_arb_internal* internalp    = Internal();
                bool             alreadyThere = false;

                for (size_t i = 0; i < 8; ++i) {
                    if (VNEAR_EQUAL(point.coordinates, internalp->pt[i], SQRT_SMALL_FASTF)) {
                        alreadyThere = true;
                        break;
                    }
                }

                assert(!alreadyThere);

                if (!alreadyThere) {
                    for (size_t i = VertexNumberToIndex(numberOfVertices, number);
                         i < 8;
                         i = VertexNumberToIndex(numberOfVertices, number, i)) {
                        VMOVE(internalp->pt[i], point.coordinates);
                    }
                }
            }
        }
    }
}


Vector3D Arb8::RawPoint
(
    size_t index
) const {
    Vector3D ret;

    assert(index < 8);

    if (index < 8) {
        VMOVE(ret.coordinates, Internal()->pt[index]);
    }

    return ret;
}


void Arb8::SetRawPoint
(
    size_t    index,
    Vector3D& point
) {
    assert(index < 8);

    if (index < 8) {
        VMOVE(Internal()->pt[index], point.coordinates);
    }
}


void Arb8::SetPoints
(
    const Vector3D& point1,
    const Vector3D& point2,
    const Vector3D& point3,
    const Vector3D& point4
) {
    rt_arb_internal* internalp = Internal();

    VMOVE(internalp->pt[0], point1.coordinates);
    VMOVE(internalp->pt[1], point2.coordinates);
    VMOVE(internalp->pt[2], point3.coordinates);
    VMOVE(internalp->pt[3], point1.coordinates);
    VMOVE(internalp->pt[4], point4.coordinates);
    VMOVE(internalp->pt[5], point4.coordinates);
    VMOVE(internalp->pt[6], point4.coordinates);
    VMOVE(internalp->pt[7], point4.coordinates);
}


void Arb8::SetPoints
(
    const Vector3D& point1,
    const Vector3D& point2,
    const Vector3D& point3,
    const Vector3D& point4,
    const Vector3D& point5
) {
    rt_arb_internal* internalp = Internal();

    VMOVE(internalp->pt[0], point1.coordinates);
    VMOVE(internalp->pt[1], point2.coordinates);
    VMOVE(internalp->pt[2], point3.coordinates);
    VMOVE(internalp->pt[3], point4.coordinates);
    VMOVE(internalp->pt[4], point5.coordinates);
    VMOVE(internalp->pt[5], point5.coordinates);
    VMOVE(internalp->pt[6], point5.coordinates);
    VMOVE(internalp->pt[7], point5.coordinates);
}


void Arb8::SetPoints
(
    const Vector3D& point1,
    const Vector3D& point2,
    const Vector3D& point3,
    const Vector3D& point4,
    const Vector3D& point5,
    const Vector3D& point6
) {
    rt_arb_internal* internalp = Internal();

    VMOVE(internalp->pt[0], point1.coordinates);
    VMOVE(internalp->pt[1], point2.coordinates);
    VMOVE(internalp->pt[2], point3.coordinates);
    VMOVE(internalp->pt[3], point4.coordinates);
    VMOVE(internalp->pt[4], point5.coordinates);
    VMOVE(internalp->pt[5], point5.coordinates);
    VMOVE(internalp->pt[6], point6.coordinates);
    VMOVE(internalp->pt[7], point6.coordinates);
}


void Arb8::SetPoints
(
    const Vector3D& point1,
    const Vector3D& point2,
    const Vector3D& point3,
    const Vector3D& point4,
    const Vector3D& point5,
    const Vector3D& point6,
    const Vector3D& point7
) {
    rt_arb_internal* internalp = Internal();

    VMOVE(internalp->pt[0], point1.coordinates);
    VMOVE(internalp->pt[1], point2.coordinates);
    VMOVE(internalp->pt[2], point3.coordinates);
    VMOVE(internalp->pt[3], point4.coordinates);
    VMOVE(internalp->pt[4], point5.coordinates);
    VMOVE(internalp->pt[5], point6.coordinates);
    VMOVE(internalp->pt[6], point7.coordinates);
    VMOVE(internalp->pt[7], point4.coordinates);
}


void Arb8::SetPoints
(
    const Vector3D& point1,
    const Vector3D& point2,
    const Vector3D& point3,
    const Vector3D& point4,
    const Vector3D& point5,
    const Vector3D& point6,
    const Vector3D& point7,
    const Vector3D& point8
) {
    rt_arb_internal* internalp = Internal();

    VMOVE(internalp->pt[0], point1.coordinates);
    VMOVE(internalp->pt[1], point2.coordinates);
    VMOVE(internalp->pt[2], point3.coordinates);
    VMOVE(internalp->pt[3], point4.coordinates);
    VMOVE(internalp->pt[4], point5.coordinates);
    VMOVE(internalp->pt[5], point6.coordinates);
    VMOVE(internalp->pt[6], point7.coordinates);
    VMOVE(internalp->pt[7], point8.coordinates);
}


void Arb8::SetPoints
(
    const Vector3D& point1,
    const Vector3D& point2
) {
    double           minX      = std::min(point1.coordinates[0], point2.coordinates[0]);
    double           minY      = std::min(point1.coordinates[1], point2.coordinates[1]);
    double           minZ      = std::min(point1.coordinates[2], point2.coordinates[2]);
    double           maxX      = std::max(point1.coordinates[0], point2.coordinates[0]);
    double           maxY      = std::max(point1.coordinates[1], point2.coordinates[1]);
    double           maxZ      = std::max(point1.coordinates[2], point2.coordinates[2]);
    rt_arb_internal* internalp = Internal();

    VSET(internalp->pt[0], maxX, minY, minZ);
    VSET(internalp->pt[1], maxX, maxY, minZ);
    VSET(internalp->pt[2], maxX, maxY, maxZ);
    VSET(internalp->pt[3], maxX, minY, maxZ);
    VSET(internalp->pt[4], minX, minY, minZ);
    VSET(internalp->pt[5], minX, maxY, minZ);
    VSET(internalp->pt[6], minX, maxY, maxZ);
    VSET(internalp->pt[7], minX, minY, maxZ);
}


const Object& Arb8::operator=
(
    const Object& original
) {
    const Arb8* arb8 = dynamic_cast<const Arb8*>(&original);
    assert(arb8 != 0);

    if (arb8 != 0)
        *this = *arb8;

    return *this;
}


Object* Arb8::Clone(void) const {
    return new Arb8(*this);
}


const char* Arb8::ClassName(void) {
    return "Arb8";
}


const char* Arb8::Type(void) const {
    return ClassName();
}


bool Arb8::IsValid(void) const {
    enum FaceType {FT_4Sided, FT_Triangle, FT_Degenerated};

    bool                   ret                = Validate();
    static const FaceType  faceTypes[5][6]    = {{FT_Triangle, FT_Degenerated, FT_Degenerated, FT_Triangle, FT_Triangle, FT_Triangle},
                                                 {FT_4Sided,   FT_Degenerated, FT_Triangle,    FT_Triangle, FT_Triangle, FT_Triangle},
                                                 {FT_4Sided,   FT_Degenerated, FT_4Sided,      FT_4Sided,   FT_Triangle, FT_Triangle},
                                                 {FT_4Sided,   FT_Triangle,    FT_Triangle,    FT_4Sided,   FT_4Sided,   FT_4Sided},
                                                 {FT_4Sided,   FT_4Sided,      FT_4Sided,      FT_4Sided,   FT_4Sided,   FT_4Sided}};
    static const size_t    faceVertices[6][8] = {{1, 2, 1, 0, 0, 1, 0, 3},
                                                 {5, 4, 5, 6, 4, 7, 4, 5},
                                                 {0, 3, 0, 4, 4, 0, 4, 7},
                                                 {1, 5, 1, 2, 5, 6, 5, 1},
                                                 {1, 0, 1, 5, 5, 1, 5, 4},
                                                 {2, 6, 2, 3, 6, 7, 6, 2}};
    size_t                 numberOfVertices   = NumberOfVertices();
    const rt_arb_internal* internalp          = Internal();
    point_t                innerPoint         = {0};

    VMOVE(innerPoint, internalp->pt[0]);
    VADD2(innerPoint, innerPoint, internalp->pt[1]);
    VADD2(innerPoint, innerPoint, internalp->pt[2]);
    VADD2(innerPoint, innerPoint, internalp->pt[3]);
    VADD2(innerPoint, innerPoint, internalp->pt[4]);
    VADD2(innerPoint, innerPoint, internalp->pt[5]);
    VADD2(innerPoint, innerPoint, internalp->pt[6]);
    VADD2(innerPoint, innerPoint, internalp->pt[7]);
    VSCALE(innerPoint, innerPoint, 0.125);

    for (size_t i = 0; (i < 6) && ret; ++i) {
        switch (faceTypes[numberOfVertices - 4][i]) {
        case FT_4Sided: {
                vect_t diff1, diff2, normal1, normal2;

                VSUB2(diff1, internalp->pt[faceVertices[i][1]], internalp->pt[faceVertices[i][0]]);
                VSUB2(diff2, internalp->pt[faceVertices[i][3]], internalp->pt[faceVertices[i][2]]);
                VCROSS(normal1, diff1, diff2);

                VSUB2(diff1, internalp->pt[faceVertices[i][5]], internalp->pt[faceVertices[i][4]]);
                VSUB2(diff2, internalp->pt[faceVertices[i][7]], internalp->pt[faceVertices[i][6]]);
                VCROSS(normal2, diff1, diff2);

                // check if the face normals have positive length, e.g. the three points are not colinear
                if (VNEAR_ZERO(normal1, SQRT_SMALL_FASTF) && !VNEAR_ZERO(normal2, SQRT_SMALL_FASTF)) {
                    ret = false;
                    break;
                }

                // check if the face normals are collinear and thus, if the face is planar
                vect_t temp;
                VCROSS(temp, normal1, normal2);

                if (!VNEAR_ZERO(temp, SQRT_SMALL_FASTF)) {
                    ret = false;
                    break;
                }

                // check if the two face normals point in the same direction
                if (!(VDOT(normal1, normal2) > 0)) {
                    ret = false;
                    break;
                }

                // check if the face normals point out of the solid
                VSUB2(temp, internalp->pt[faceVertices[i][0]], innerPoint);

                if (!(VDOT(temp, normal1) >= 0)){
                    ret = false;
                    break;
                }
            }
            break;

        case FT_Triangle: {
                vect_t diff1, diff2, normal;

                VSUB2(diff1, internalp->pt[faceVertices[i][1]], internalp->pt[faceVertices[i][0]]);
                VSUB2(diff2, internalp->pt[faceVertices[i][3]], internalp->pt[faceVertices[i][2]]);
                VCROSS(normal, diff1, diff2);

                // check if the face normal has positive length
                if(VNEAR_ZERO(normal, SQRT_SMALL_FASTF)) {
                    ret = false;
                    break;
                }

                // check if the face normals point out of the solid
                vect_t temp;
                VSUB2(temp, internalp->pt[faceVertices[i][0]], innerPoint);

                if(!(VDOT(temp, normal) >= 0)) {
                    ret = false;
                    break;
                }
            }
            break;

	default:;
            // case FT_Degenerated: nothing has to be checked
        }
    }

    return ret;
}


Arb8::Arb8
(
    resource*       resp,
    directory*      pDir,
    rt_db_internal* ip,
    db_i*           dbip
) : Object(resp, pDir, ip, dbip), m_internalp(0) {}


const rt_arb_internal* Arb8::Internal(void) const {
    const rt_arb_internal* ret;

    if (m_ip != 0)
        ret = static_cast<const rt_arb_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_ARB_CK_MAGIC(ret);

    return ret;
}


rt_arb_internal* Arb8::Internal(void) {
    rt_arb_internal* ret;

    if (m_ip != 0)
        ret = static_cast<rt_arb_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_ARB_CK_MAGIC(ret);

    return ret;
}
