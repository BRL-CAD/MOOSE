/*                      B A G O F T R I A N G L E S . C P P
 * BRL-CAD
 *
 * Copyright (c) 2014-2025 United States Government as represented by
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
/** @file BagOfTriangles.cpp
 *
 *  BRL-CAD core C++ interface:
 *      bag of triangles (ID_BOT) database object implementation
 */

#include <cstring>
#include <cassert>

#include "raytrace.h"
#include "rt/geom.h"
#include "bu/parallel.h"

#include "private.h"

#include <brlcad/Database/BagOfTriangles.h>


using namespace BRLCAD;


static int AddVertex
(
    const point_t&   point,
    rt_bot_internal& bot
) {
    int ret = 0; // index of the added vertex

    // vertex already there?
    for (; ret < bot.num_vertices; ++ret) {
        fastf_t tmp[3] = {bot.vertices[ret * 3], bot.vertices[ret * 3 + 1], bot.vertices[ret * 3 + 2]};

        if (VNEAR_EQUAL(point, tmp, VUNITIZE_TOL))
            break;
    }

    if (ret == bot.num_vertices) {
        // add a new vertex
        ++bot.num_vertices;
        bot.vertices = static_cast<fastf_t*>(bu_realloc(bot.vertices, bot.num_vertices * 3 * sizeof(fastf_t), "bot interface AddVertex()"));
        bot.vertices[ret * 3]     = point[0];
        bot.vertices[ret * 3 + 1] = point[1];
        bot.vertices[ret * 3 + 2] = point[2];
    }

    return ret;
}


static void RemoveVertex
(
    int              index,
    rt_bot_internal& bot
) {
    assert(index < bot.num_vertices);

    if (index < bot.num_vertices) {
        // is the vertex used elsewhere?
        size_t vertexUsage = 0;

        for (int i = 0; i < (3 * bot.num_faces); ++i) {
            if (bot.faces[i] == index)
                vertexUsage++;
        }

        if (vertexUsage <= 1) {
            // really remove it
            memcpy(bot.vertices + index * 3, bot.vertices + (index + 1) * 3, (bot.num_vertices - index - 1) * 3 * sizeof(fastf_t));

            --bot.num_vertices;
            bot.vertices = static_cast<fastf_t*>(bu_realloc(bot.vertices, bot.num_vertices * 3 * sizeof(fastf_t), "bot interface RemoveVertex()"));

            // update faces
            for (int i = 0; i < (3 * bot.num_faces); ++i) {
                if (bot.faces[i] > index)
                    --bot.faces[i];
            }
        }
    }
}


static int SwapVertex
(
    int              oldIndex,
    const point_t&   newPoint,
    rt_bot_internal& bot
) {
    int     ret; // index of the new vertex
    fastf_t tmp[3];
    tmp[0] = bot.vertices[oldIndex];
    tmp[1] = bot.vertices[oldIndex + 1];
    tmp[2] = bot.vertices[oldIndex + 2];

    if (VNEAR_EQUAL(newPoint, tmp, VUNITIZE_TOL))
        ret = oldIndex;
    else {
        RemoveVertex(oldIndex, bot);

        ret = AddVertex(newPoint, bot);
    }

    return ret;
}


static int AddNormal
(
    const fastf_t    normal[3],
    rt_bot_internal& bot
) {
    int     ret = 0; // index of the added normal
    fastf_t tmp[3];

    // normal already there?
    for (; ret < bot.num_normals; ++ret) {
        tmp[0] = bot.normals[ret];
        tmp[1] = bot.normals[ret + 1];
        tmp[2] = bot.normals[ret + 2];

        if (VNEAR_EQUAL(normal, tmp, VUNITIZE_TOL))
            break;
    }

    if (ret == bot.num_normals) {
        // add a new normal
        ++bot.num_normals;
        bot.normals = static_cast<fastf_t*>(bu_realloc(bot.normals, bot.num_normals * 3 * sizeof(fastf_t), "bot interface AddNormal()"));
        bot.normals[ret]     = normal[0];
        bot.normals[ret + 1] = normal[1];
        bot.normals[ret + 2] = normal[2];
    }

    return ret;
}


static void RemoveNormal
(
    int              index,
    rt_bot_internal& bot
) {
    assert(index < bot.num_normals);

    if (index < bot.num_normals) {
        // is the normal used elsewhere?
        size_t normalUsage = 0;

        for (int i = 0; i < (3 * bot.num_face_normals); ++i) {
            if (bot.face_normals[i] == index)
                normalUsage++;
        }

        if (normalUsage <= 1) {
            // really remove it
            memcpy(bot.normals + index, bot.normals + index + 3, (bot.num_normals - index - 1) * 3 * sizeof(fastf_t));

            --bot.num_normals;
            bot.normals = static_cast<fastf_t*>(bu_realloc(bot.normals, bot.num_normals * 3 * sizeof(fastf_t), "bot interface RemoveNormal()"));

            // update face normals
            for (int i = 0; i < (3 * bot.num_face_normals); ++i) {
                if (bot.face_normals[i] > index)
                    --bot.face_normals[i];
            }
        }
    }
}


static int SwapNormal
(
    int              oldIndex,
    const fastf_t    newNormal[3],
    rt_bot_internal& bot
) {
    int     ret; // index of the new normal
    fastf_t tmp[3];
    tmp[0] = bot.normals[oldIndex];
    tmp[1] = bot.normals[oldIndex + 1];
    tmp[2] = bot.normals[oldIndex + 2];

    if (VNEAR_EQUAL(newNormal, tmp, VUNITIZE_TOL))
        ret = oldIndex;
    else {
        RemoveNormal(oldIndex, bot);

        ret = AddNormal(newNormal, bot);
    }

    return ret;
}


static void EnsureFaceNormals
(
    rt_bot_internal& bot
) {
    assert(bot.num_faces >= bot.num_face_normals);

    if (bot.num_faces > 0) {
        if (bot.face_normals == nullptr)
            bot.face_normals = static_cast<int*>(bu_calloc(3 * bot.num_faces, sizeof(int), "bot interface EnsureFaceNormals(): face_normals"));
        else if (bot.num_faces > bot.num_face_normals) {
            bot.face_normals = static_cast<int*>(bu_realloc(bot.face_normals, 3 * bot.num_faces * sizeof(int), "bot interface EnsureFaceNormals(): face_normals"));

            for (size_t i = bot.num_face_normals; i < bot.num_faces; ++i) {
                fastf_t defaultNormal[3] = {0};
                int     newIndex         = AddNormal(defaultNormal, bot);

                bot.face_normals[3 * i]     = newIndex;
                bot.face_normals[3 * i + 1] = newIndex;
                bot.face_normals[3 * i + 2] = newIndex;
            }
        }

        bot.num_face_normals = bot.num_faces;
    }
}


static void CleanBotInternal
(
    rt_bot_internal* bot
) {
    assert(bot != nullptr);

    RT_BOT_CK_MAGIC(bot);

    if (bot->tie != nullptr)
        bot->tie = nullptr;

    if (bot->vertices != nullptr) {
        bu_free(bot->vertices, "bot interface CleanBotInternal(): vertices");
        bot->vertices     = nullptr;
        bot->num_vertices = 0;
    }

    if (bot->faces != nullptr) {
        bu_free(bot->faces, "bot interface CleanBotInternal(): faces");
        bot->faces     = nullptr;
        bot->num_faces = 0;
    }

    if (bot->thickness != nullptr) {
        bu_free(bot->thickness, "bot interface CleanBotInternal(): thickness");
        bot->thickness = nullptr;
    }

    if (bot->face_mode != nullptr) {
        bu_free(bot->face_mode, "bot interface CleanBotInternal(): face_mode");
        bot->face_mode = nullptr;
    }

    if (bot->normals != nullptr) {
        bu_free(bot->normals, "bot interface CleanBotInternal(): normals");
        bot->normals     = nullptr;
        bot->num_normals = 0;
    }

    if (bot->face_normals != nullptr) {
        bu_free(bot->face_normals, "bot interface CleanBotInternal(): face_normals");
        bot->face_normals     = nullptr;
        bot->num_face_normals = 0;
    }
}


static void FreeBotInternal
(
    rt_bot_internal* bot
) {
    assert(bot != nullptr);

    RT_BOT_CK_MAGIC(bot);

    CleanBotInternal(bot);
    bot->magic = 0; /* sanity */
    bu_free(bot, "bot interface FreeBotInternal(): rt_bot_internal");
}


static void CopyBotInternal
(
    rt_bot_internal*       copy,
    const rt_bot_internal* original
) {
    RT_BOT_CK_MAGIC(copy);
    RT_BOT_CK_MAGIC(original);

    CleanBotInternal(copy);
    *copy = *original;

    if (original->faces != nullptr) {
        copy->faces =  static_cast<int*>(bu_malloc(3 * original->num_faces * sizeof(int), "bot interface CopyBotInternal(): faces"));

        memcpy(copy->faces, original->faces, 3 * original->num_faces * sizeof(int));
    }

    if (original->vertices != nullptr) {
        copy->vertices = static_cast<fastf_t*>(bu_malloc(3 * original->num_vertices * sizeof(fastf_t), "bot interface CopyBotInternal(): vertices"));

        memcpy(copy->vertices, original->vertices, 3 * original->num_vertices * sizeof(fastf_t));
    }

    if (original->thickness != nullptr) {
        copy->thickness = static_cast<fastf_t*>(bu_malloc(original->num_faces * sizeof(fastf_t), "bot interface CopyBotInternal(): thickness"));

        memcpy(copy->thickness, original->thickness, original->num_faces * sizeof(fastf_t));
    }

    if (original->face_mode != nullptr)
        copy->face_mode = bu_bitv_dup(original->face_mode);

    if (original->normals != nullptr) {
        copy->normals = static_cast<fastf_t*>(bu_malloc(3 * original->num_normals * sizeof(fastf_t), "bot interface CopyBotInternal(): normals"));

        memcpy(copy->normals, original->normals, 3 * original->num_normals * sizeof(fastf_t));
    }

    if (original->face_normals != nullptr) {
        copy->face_normals = static_cast<int*>(bu_malloc(3 * original->num_face_normals * sizeof(int), "bot interface CopyBotInternal(): face_normals"));

        memcpy(copy->face_normals, original->face_normals, 3 * original->num_face_normals * sizeof(int));
    }
}


rt_bot_internal* CloneBotInternal
(
    const rt_bot_internal& bot
) {
    RT_BOT_CK_MAGIC(&bot);

    struct rt_bot_internal* ret;

    BU_GET(ret, rt_bot_internal);
    ret->magic = RT_BOT_INTERNAL_MAGIC;
    CopyBotInternal(ret, &bot);

    return ret;
}


void CleanUpBotInternal
(
    rt_bot_internal& bot
) {
    RT_BOT_CK_MAGIC(&bot);

    // remove unused vertices
    int vertexCount = 0;

    while (vertexCount < bot.num_vertices) {
        bool inUse = false;

        for (int i = 0; i < (3 * bot.num_faces); ++i) {
            if (bot.faces[i] == vertexCount) {
                inUse = true;
                break;
            }
        }

        if (!inUse)
            RemoveVertex(vertexCount, bot);
        else
            ++vertexCount;
    }

    // remove unused normals
    if ((bot.normals != nullptr) && (bot.face_normals != nullptr)) {
        int normalCount = 0;

        while (normalCount < bot.num_normals) {
            bool inUse = false;

            for (int i = 0; i < (3 * bot.num_face_normals); ++i) {
                if (bot.face_normals[i] == normalCount) {
                    inUse = true;
                    break;
                }
            }

            if (!inUse)
                RemoveNormal(normalCount, bot);
            else
                ++normalCount;
        }
    }

    if ((bot.mode == RT_BOT_SURFACE) || (bot.mode == RT_BOT_SOLID)) {
        if (bot.thickness != nullptr) {
            bu_free(bot.thickness, "bot interface CleanUpBotInternal(): thickness");
            bot.thickness = nullptr;
        }

        if (bot.face_mode != nullptr) {
            bu_free(bot.face_mode, "bot interface CleanUpBotInternal(): face_mode");
            bot.face_mode = nullptr;
        }
    }

    if (bot.bot_flags & RT_BOT_HAS_SURFACE_NORMALS)
        EnsureFaceNormals(bot);
    else {
        if (bot.normals != nullptr) {
            bu_free(bot.normals, "bot interface CleanUpBotInternal(): normals");

            bot.normals     = nullptr;
            bot.num_normals = 0;
        }

        if (bot.face_normals != nullptr) {
            bu_free(bot.face_normals, "bot interface CleanUpBotInternal(): face_normals");

            bot.face_normals     = nullptr;
            bot.num_face_normals = 0;
        }
    }
}


void RemoveFace
(
    size_t           index,
    rt_bot_internal& bot
) {
    if (bot.num_faces > (index + 1))
        memcpy(bot.faces + index * 3, bot.faces + index * 3 + 3, (bot.num_faces - index - 1) * 3 * sizeof(int));

    bot.faces = static_cast<int*>(bu_realloc(bot.faces, (bot.num_faces - 1) * 3 * sizeof(int), "bot interface RemoveFace(): faces"));

    if (bot.thickness != nullptr) {
        assert(bot.mode != RT_BOT_SURFACE);
        assert(bot.mode != RT_BOT_SOLID);

        memcpy(bot.thickness + index, bot.thickness + index + 1, (bot.num_faces - index - 1) * sizeof(fastf_t));
        bot.thickness = static_cast<fastf_t*>(bu_realloc(bot.thickness, (bot.num_faces - 1) * sizeof(fastf_t), "bot interface RemoveFace(): thickness"));
    }

    if (bot.face_mode != nullptr) {
        assert(bot.mode != RT_BOT_SURFACE);
        assert(bot.mode != RT_BOT_SOLID);

        bu_bitv* temp = bu_bitv_new(bot.num_faces - 1);

        for (size_t i = 0; i < index; ++i) {
            if (BU_BITTEST(bot.face_mode, i))
                BU_BITSET(temp, i);
            else
                BU_BITCLR(temp, i);
        }

        for (size_t i = (index + 1); i < bot.num_faces; ++i) {
            if (BU_BITTEST(bot.face_mode, i))
                BU_BITSET(temp, i - 1);
            else
                BU_BITCLR(temp, i - 1);
        }

        bu_bitv_free(bot.face_mode);
        bot.face_mode = temp;
    }

    if ((bot.face_normals != nullptr) && (bot.num_face_normals > index)) {
        if (bot.num_face_normals > (index + 1))
            memcpy(bot.face_normals + index * 3, bot.face_normals + index * 3 + 3, (bot.num_face_normals - index - 1) * 3 * sizeof(int));

        bot.face_normals = static_cast<int*>(bu_realloc(bot.face_normals, (bot.num_face_normals - 1) * 3 * sizeof(int), "bot interface RemoveFace(): face_normals"));
    }

    --bot.num_faces;
}


BagOfTriangles::BagOfTriangles
(
    void
) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_bot_internal);
        m_internalp->magic = RT_BOT_INTERNAL_MAGIC;
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


BagOfTriangles::BagOfTriangles
(
    const BagOfTriangles& original
) {
    if (!BU_SETJUMP)
        m_internalp = CloneBotInternal(*original.Internal());
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


BagOfTriangles::~BagOfTriangles
(
    void
) {
    if (m_internalp != nullptr)
        FreeBotInternal(m_internalp);
}


const BagOfTriangles& BagOfTriangles::operator=
(
    const BagOfTriangles& original
) {
    if (&original != this) {
        Copy(original);

        if (!BU_SETJUMP) {
            rt_bot_internal*       thisInternal     = Internal();
            const rt_bot_internal* originalInternal = original.Internal();

            CopyBotInternal(thisInternal, originalInternal);
        }
        else
            BU_UNSETJUMP;

        BU_UNSETJUMP;
    }

    return *this;
}


Vector3D BagOfTriangles::Face::Point
(
    size_t index
) const {
    assert(index < 3);
    assert(m_bot != nullptr);

    Vector3D ret;

    if ((m_bot != nullptr) && (index < 3)) {
        ret.coordinates[0] = m_bot->vertices[m_bot->faces[m_faceIndex * 3 + index] * 3];
        ret.coordinates[1] = m_bot->vertices[m_bot->faces[m_faceIndex * 3 + index] * 3 + 1];
        ret.coordinates[2] = m_bot->vertices[m_bot->faces[m_faceIndex * 3 + index] * 3 + 2];
    }

    return ret;
}


void BagOfTriangles::Face::SetPoint
(
    size_t          index,
    const Vector3D& point
) {
    assert(index < 3);
    assert(m_bot != nullptr);

    if ((m_bot != nullptr) && (index < 3)) {
        point_t newPoint = {point.coordinates[0], point.coordinates[1], point.coordinates[2]};

        m_bot->faces[m_faceIndex * 3 + index] = SwapVertex(m_bot->faces[m_faceIndex * 3 + index], newPoint, *m_bot);
    }
}


void BagOfTriangles::Face::SetPoints
(
    const Vector3D& point1,
    const Vector3D& point2,
    const Vector3D& point3
) {
    assert(m_bot != nullptr);

    if (m_bot != nullptr) {
        SetPoint(0, point1);
        SetPoint(1, point2);
        SetPoint(2, point3);
    }
}


double BagOfTriangles::Face::Thickness(void) const {
    assert(m_bot != nullptr);
    assert(m_bot->thickness != nullptr);
    assert(m_bot->mode != RT_BOT_SOLID);
    assert(m_bot->mode != RT_BOT_SURFACE);

    double ret = 0.;

    if ((m_bot != nullptr) && (m_bot->thickness != nullptr))
        ret = m_bot->thickness[m_faceIndex];

    return ret;
}


void BagOfTriangles::Face::SetThickness
(
    double value
) {
    assert(m_bot != nullptr);
    assert(m_bot->thickness != nullptr);
    assert(m_bot->mode != RT_BOT_SOLID);
    assert(m_bot->mode != RT_BOT_SURFACE);

    if (m_bot != nullptr) {
        if (m_bot->thickness == nullptr)
            m_bot->thickness = static_cast<fastf_t*>(bu_calloc(m_bot->num_faces, sizeof(fastf_t), "BRLAD::BagOfTriangles::Face::SetThickness(): thickness"));

        m_bot->thickness[m_faceIndex] = value;
    }
}


bool BagOfTriangles::Face::ApendThickness(void) const {
    assert(m_bot != nullptr);

    bool ret = false;

    if ((m_bot != nullptr) && (m_bot->face_mode != nullptr))
        ret = BU_BITTEST(m_bot->face_mode, m_faceIndex);

    return ret;
}


void BagOfTriangles::Face::SetApendThickness
(
    bool apendThickness
) {
    assert(m_bot != nullptr);

    if (m_bot != nullptr) {
        if (m_bot->face_mode == nullptr)
            m_bot->face_mode = bu_bitv_new(m_bot->num_faces);

        if (apendThickness)
            BU_BITSET(m_bot->face_mode, m_faceIndex);
        else
            BU_BITCLR(m_bot->face_mode, m_faceIndex);
    }
}


Vector3D BagOfTriangles::Face::Normal
(
    size_t index
) const {
    assert(m_bot != nullptr);

    Vector3D ret;

    if (m_bot != nullptr) {
        fastf_t tmp[3] = {m_bot->normals[m_bot->face_normals[m_faceIndex * 3 + index] * 3],
                          m_bot->normals[m_bot->face_normals[m_faceIndex * 3 + index] * 3 + 1],
                          m_bot->normals[m_bot->face_normals[m_faceIndex * 3 + index] * 3 + 2]};

        ret = Vector3D(tmp);
    }

    return ret;
}


void BagOfTriangles::Face::SetNormal
(
    size_t          index,
    const Vector3D& normal
) {
    assert(index < 3);
    assert(m_bot != nullptr);

    if ((m_bot != nullptr) && (index < 3)) {
        EnsureFaceNormals(*m_bot);

        point_t newNormal = {normal.coordinates[0], normal.coordinates[1], normal.coordinates[2]};

        m_bot->face_normals[m_faceIndex * 3 + index] = SwapNormal(m_bot->face_normals[m_faceIndex * 3 + index], newNormal, *m_bot);
    }
}


void BagOfTriangles::Face::SetNormals
(
    const Vector3D& normal1,
    const Vector3D& normal2,
    const Vector3D& normal3
) {
    assert(m_bot != nullptr);

    if (m_bot != nullptr) {
        SetNormal(0, normal1);
        SetNormal(1, normal2);
        SetNormal(2, normal3);
    }
}


BagOfTriangles::BotMode BagOfTriangles::Mode(void) const {
    BagOfTriangles::BotMode ret;

    switch (Internal()->mode) {
        case RT_BOT_SURFACE:
            ret = Surface;
            break;

        case RT_BOT_SOLID:
            ret = Solid;
            break;

        case RT_BOT_PLATE:
            ret = Plate;
            break;

        case RT_BOT_PLATE_NOCOS:
            ret = EqualLineOfSightPlate;
    }

    return ret;
}


void BagOfTriangles::SetMode
(
    BotMode mode
) {
    switch (mode) {
        case Surface:
            Internal()->mode = RT_BOT_SURFACE;
            break;

        case Solid:
            Internal()->mode = RT_BOT_SOLID;
            break;

        case Plate:
            Internal()->mode = RT_BOT_PLATE;
            break;

        case EqualLineOfSightPlate:
            Internal()->mode = RT_BOT_PLATE_NOCOS;
    }
}


BagOfTriangles::BotOrientation BagOfTriangles::Orientation(void) const {
    BagOfTriangles::BotOrientation ret = BagOfTriangles::Unoriented;

    switch (Internal()->orientation) {
        case RT_BOT_CW:
            ret = ClockWise;
            break;

        case RT_BOT_CCW:
            ret = CounterClockWise;
    }

    return ret;
}


void BagOfTriangles::SetOrientation
(
    BotOrientation orientation
) {
    switch (orientation) {
        case Unoriented:
            Internal()->orientation = RT_BOT_UNORIENTED;
            break;

        case ClockWise:
            Internal()->orientation = RT_BOT_CW;
            break;

        case CounterClockWise:
            Internal()->orientation = RT_BOT_CCW;
    }
}


bool BagOfTriangles::FacesHaveNormals(void) const {
    return Internal()->bot_flags & RT_BOT_HAS_SURFACE_NORMALS;
}


void BagOfTriangles::SetFacesHaveNormals
(
    bool facesHaveNormals
) {
    if (facesHaveNormals)
        Internal()->bot_flags |= RT_BOT_HAS_SURFACE_NORMALS;
    else
        Internal()->bot_flags &= RT_BOT_HAS_SURFACE_NORMALS;
}


bool BagOfTriangles::UseFaceNormals(void) const {
    return (Internal()->bot_flags & RT_BOT_USE_NORMALS) != 0;
}


void BagOfTriangles::SetUseFaceNormals
(
    bool useFaceNormals
) {
    if (useFaceNormals)
        Internal()->bot_flags |= RT_BOT_USE_NORMALS;
    else
        Internal()->bot_flags &= RT_BOT_USE_NORMALS;
}


bool BagOfTriangles::UseFloats(void) const {
    return (Internal()->bot_flags & RT_BOT_USE_FLOATS) != 0;
}


void BagOfTriangles::SetUseFloats
(
    bool useFloats
) {
    if (useFloats)
        Internal()->bot_flags |= RT_BOT_USE_FLOATS;
    else
        Internal()->bot_flags &= RT_BOT_USE_FLOATS;
}


size_t BagOfTriangles::NumberOfFaces(void) const {
    return Internal()->num_faces;
}


BagOfTriangles::Face BagOfTriangles::GetFace
(
    size_t index
) {
    assert(index < Internal()->num_faces);

    Face ret;

    if (index < Internal()->num_faces)
        ret = Face(Internal(), index);

    return ret;
}


BagOfTriangles::Face BagOfTriangles::AddFace
(
    const Vector3D& point1,
    const Vector3D& point2,
    const Vector3D& point3
) {
    BagOfTriangles::Face ret;

    if (!BU_SETJUMP) {
        rt_bot_internal* bot = Internal();

        bot->faces = static_cast<int*>(bu_realloc(bot->faces, (bot->num_faces + 1) * 3 * sizeof(int), "BagOfTriangles::AddFace(): faces"));

        point_t newPoint1 = {point1.coordinates[0], point1.coordinates[1], point1.coordinates[2]};
        point_t newPoint2 = {point2.coordinates[0], point2.coordinates[1], point2.coordinates[2]};
        point_t newPoint3 = {point3.coordinates[0], point3.coordinates[1], point3.coordinates[2]};

        bot->faces[bot->num_faces * 3]     = AddVertex(newPoint1, *bot);
        bot->faces[bot->num_faces * 3 + 1] = AddVertex(newPoint2, *bot);
        bot->faces[bot->num_faces * 3 + 2] = AddVertex(newPoint3, *bot);

        if(Internal()->thickness != nullptr) {
            bot->thickness                 = static_cast<fastf_t*>(bu_realloc(bot->thickness, (bot->num_faces + 1) * sizeof(fastf_t), "BagOfTriangles::InsertFace: thickness"));
            bot->thickness[bot->num_faces] = 1.;
        }

        if(Internal()->face_mode != nullptr) {
            assert(bot->mode != RT_BOT_SURFACE);
            assert(bot->mode != RT_BOT_SOLID);

            bu_bitv* temp = bu_bitv_new(bot->num_faces + 1);

            for (size_t i = 0; i < bot->num_faces; ++i) {
                if (BU_BITTEST(bot->face_mode, i))
                    BU_BITSET(temp, i);
                else
                    BU_BITCLR(temp, i);
            }

            if  (bot->num_faces > 0) {
                if (BU_BITTEST(bot->face_mode, bot->num_faces - 1))
                    BU_BITSET(temp, bot->num_faces);
                else
                    BU_BITCLR(temp, bot->num_faces);
            }

            bu_bitv_free(bot->face_mode);
            bot->face_mode = temp;
        }

        ++bot->num_faces;
        EnsureFaceNormals(*bot);

        ret = Face(bot, bot->num_faces - 1);
    }
    else
        BU_UNSETJUMP;

    BU_UNSETJUMP;

    return ret;
}


void BagOfTriangles::DeleteFace(
    size_t index
) {
    assert(index < Internal()->num_faces);

    if (!BU_SETJUMP) {
        for(int i = 0; i < 3; i++)
            RemoveVertex(Internal()->faces[index * 3 + i], *Internal());

        RemoveFace(index, *Internal());
    }
}


const Object& BagOfTriangles::operator=
(
    const Object& original
) {
    const BagOfTriangles* bot = dynamic_cast<const BagOfTriangles*>(&original);
    assert(bot != nullptr);

    if (bot != nullptr)
        *this = *bot;

    return *this;
}


Object* BagOfTriangles::Clone(void) const {
    return new BagOfTriangles(*this);
}


const char* BagOfTriangles::ClassName(void) {
    return "BagOfTriangles";
}


const char* BagOfTriangles::Type(void) const {
    return ClassName();
}


bool BagOfTriangles::IsValid(void) const {
    return Validate();
}


BagOfTriangles::BagOfTriangles
(
    resource*       resp,
    directory*      pDir,
    rt_db_internal* ip,
    db_i*           dbip
) : Object(resp, pDir, ip, dbip), m_internalp(nullptr) {}



rt_bot_internal* BagOfTriangles::Internal(void) {
    rt_bot_internal* ret;

    if (m_ip != nullptr)
        ret = static_cast<rt_bot_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_BOT_CK_MAGIC(ret);

    return ret;
}


const rt_bot_internal* BagOfTriangles::Internal(void) const {
    const rt_bot_internal* ret;

    if (m_ip != nullptr)
        ret = static_cast<const rt_bot_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_BOT_CK_MAGIC(ret);

    return ret;
}
