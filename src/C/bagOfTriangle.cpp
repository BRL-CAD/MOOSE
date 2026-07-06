/*                      B A G O F T R I A N G L E . C P P
 * BRL-CAD
 *
 * Copyright (c) 2026 United States Government as represented by
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
/** @file bagOfTriangle.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      Implements a handle and functions for Bag of Triangle solid handling
 */

/* B A G O F T R I A N G L E S . C P P
 * BRL-CAD
 */

#include <cassert>

#include "bu/log.h"

#include <brlcad/Database/BagOfTriangles.h>

#include <brlcad/C/bagOfTriangles.h>

#include "casts.h"


using namespace BRLCAD;


BrlBagOfTriangles BrlNewBagOfTriangles
(
    void
) {
    return new BagOfTrianglesData(new BagOfTriangles());
}


BrlBotMode BrlBagOfTrianglesMode
(
    BrlBagOfTriangles bot
) {
    BrlBotMode ret = BrlBotModeSurface;

    if (bot != nullptr) {
        BagOfTriangles* b = CastBagOfTriangles(bot);

        assert(b != nullptr);

        if (b != nullptr) {
            switch (b->Mode()) {
            case BagOfTriangles::BotMode::Surface:
                ret = BrlBotModeSurface;
                break;
            case BagOfTriangles::BotMode::Solid:
                ret = BrlBotModeSolid;
                break;
            case BagOfTriangles::BotMode::Plate:
                ret = BrlBotModePlate;
                break;
            case BagOfTriangles::BotMode::EqualLineOfSightPlate:
                ret = BrlBotModeEqualLineOfSightPlate;
                break;
            default:
                assert(0);
            }
        }
    }

    return ret;
}


void BrlBagOfTrianglesSetMode
(
    BrlBagOfTriangles bot,
    BrlBotMode        mode
) {
    if (bot != nullptr) {
        BagOfTriangles* b = CastBagOfTriangles(bot);

        assert(b != nullptr);

        if (b != nullptr) {
            switch (mode) {
            case BrlBotModeSurface:
                b->SetMode(BagOfTriangles::BotMode::Surface);
                break;
            case BrlBotModeSolid:
                b->SetMode(BagOfTriangles::BotMode::Solid);
                break;
            case BrlBotModePlate:
                b->SetMode(BagOfTriangles::BotMode::Plate);
                break;
            case BrlBotModeEqualLineOfSightPlate:
                b->SetMode(BagOfTriangles::BotMode::EqualLineOfSightPlate);
                break;
            default:
                assert(0);
            }
        }
    }
}


BrlBotOrientation BrlBagOfTrianglesOrientation
(
    BrlBagOfTriangles bot
) {
    BrlBotOrientation ret = BrlBotOrientationUnoriented;

    if (bot != nullptr) {
        BagOfTriangles* b = CastBagOfTriangles(bot);

        assert(b != nullptr);

        if (b != nullptr) {
            switch (b->Orientation()) {
            case BagOfTriangles::BotOrientation::Unoriented:
                ret = BrlBotOrientationUnoriented;
                break;
            case BagOfTriangles::BotOrientation::ClockWise:
                ret = BrlBotOrientationClockWise;
                break;
            case BagOfTriangles::BotOrientation::CounterClockWise:
                ret = BrlBotOrientationCounterClockWise;
                break;
            default:
                assert(0);
            }
        }
    }

    return ret;
}


void BrlBagOfTrianglesSetOrientation
(
    BrlBagOfTriangles bot,
    BrlBotOrientation orientation
) {
    if (bot != nullptr) {
        BagOfTriangles* b = CastBagOfTriangles(bot);

        assert(b != nullptr);

        if (b != nullptr) {
            switch (orientation) {
            case BrlBotOrientationUnoriented:
                b->SetOrientation(BagOfTriangles::BotOrientation::Unoriented);
                break;
            case BrlBotOrientationClockWise:
                b->SetOrientation(BagOfTriangles::BotOrientation::ClockWise);
                break;
            case BrlBotOrientationCounterClockWise:
                b->SetOrientation(BagOfTriangles::BotOrientation::CounterClockWise);
                break;
            default:
                assert(0);
            }
        }
    }
}


int BrlBagOfTrianglesFacesHaveNormals
(
    BrlBagOfTriangles bot
) {
    int ret = 0;

    if (bot != nullptr) {
        BagOfTriangles* b = CastBagOfTriangles(bot);

        assert(b != nullptr);

        if (b != nullptr)
            ret = b->FacesHaveNormals() ? 1 : 0;
    }

    return ret;
}


void BrlBagOfTrianglesSetFacesHaveNormals
(
    BrlBagOfTriangles bot,
    int               facesHaveNormals
) {
    if (bot != nullptr) {
        BagOfTriangles* b = CastBagOfTriangles(bot);

        assert(b != nullptr);

        if (b != nullptr)
            b->SetFacesHaveNormals(facesHaveNormals != 0);
    }
}


int BrlBagOfTrianglesUseFaceNormals
(
    BrlBagOfTriangles bot
) {
    int ret = 0;

    if (bot != nullptr) {
        BagOfTriangles* b = CastBagOfTriangles(bot);

        assert(b != nullptr);

        if (b != nullptr)
            ret = b->UseFaceNormals() ? 1 : 0;
    }

    return ret;
}


void BrlBagOfTrianglesSetUseFaceNormals
(
    BrlBagOfTriangles bot,
    int               useFaceNormals
) {
    if (bot != nullptr) {
        BagOfTriangles* b = CastBagOfTriangles(bot);

        assert(b != nullptr);

        if (b != nullptr)
            b->SetUseFaceNormals(useFaceNormals != 0);
    }
}


int BrlBagOfTrianglesUseFloats
(
    BrlBagOfTriangles bot
) {
    int ret = 0;

    if (bot != nullptr) {
        BagOfTriangles* b = CastBagOfTriangles(bot);

        assert(b != nullptr);

        if (b != nullptr)
            ret = b->UseFloats() ? 1 : 0;
    }

    return ret;
}


void BrlBagOfTrianglesSetUseFloats
(
    BrlBagOfTriangles bot,
    int               useFloats
) {
    if (bot != nullptr) {
        BagOfTriangles* b = CastBagOfTriangles(bot);

        assert(b != nullptr);

        if (b != nullptr)
            b->SetUseFloats(useFloats != 0);
    }
}


int BrlBagOfTrianglesNumberOfFaces
(
    BrlBagOfTriangles bot
) {
    int ret = 0;

    if (bot != nullptr) {
        BagOfTriangles* b = CastBagOfTriangles(bot);

        assert(b != nullptr);

        if (b != nullptr)
            ret = b->NumberOfFaces();
    }

    return ret;
}


BrlBagOfTrianglesFace BrlBagOfTrianglesGetFace
(
    BrlBagOfTriangles bot,
    int               index
) {
    BrlBagOfTrianglesFace ret = nullptr;

    if (bot != nullptr) {
        BagOfTriangles* b = CastBagOfTriangles(bot);

        assert(b != nullptr);

        if (b != nullptr)
            ret = new BagOfTrianglesFaceData(b->GetFace(index));
    }

    return ret;
}


BrlBagOfTrianglesFace BrlBagOfTrianglesAddFace
(
    BrlBagOfTriangles bot,
    const double*     pt1,
    const double*     pt2,
    const double*     pt3
) {
    BrlBagOfTrianglesFace ret = nullptr;

    if ((bot != nullptr) && (pt1 != nullptr) && (pt2 != nullptr) && (pt3 != nullptr)) {
        BagOfTriangles* b  = CastBagOfTriangles(bot);

        assert(b != nullptr);

        if (b != nullptr) {
            Vector3D v1(pt1[0], pt1[1], pt1[2]);
            Vector3D v2(pt2[0], pt2[1], pt2[2]);
            Vector3D v3(pt3[0], pt3[1], pt3[2]);
            ret = new BagOfTrianglesFaceData(b->AddFace(v1, v2, v3));
        }
    }

    return ret;
}


void BrlBagOfTrianglesDeleteFace
(
    BrlBagOfTriangles bot,
    int               index
) {
    if (bot != nullptr) {
        BagOfTriangles* b = CastBagOfTriangles(bot);

        assert(b != nullptr);

        if (b != nullptr)
            b->DeleteFace(index);
    }
}


const char* BrlBagOfTrianglesClassName
(
    void
) {
    return BagOfTriangles::ClassName();
}


void BrlBagOfTrianglesFacePoint
(
    BrlBagOfTrianglesFace face,
    int                   index,
    double*               out_pt
) {
    if ((face != nullptr) && (out_pt != nullptr)) {
        BagOfTriangles::Face* f = CastBagOfTrianglesFace(face);

        assert(f != nullptr);

        if (f != nullptr) {
            Vector3D v = f->Point(index);
            out_pt[0] = v.coordinates[0];
            out_pt[1] = v.coordinates[1];
            out_pt[2] = v.coordinates[2];
        }
    }
}


void BrlBagOfTrianglesFaceSetPoint
(
    BrlBagOfTrianglesFace face,
    int                   index,
    const double*         point
) {
    if ((face != nullptr) && (point != nullptr)) {
        BagOfTriangles::Face* f = CastBagOfTrianglesFace(face);

        assert(f != nullptr);

        if (f != nullptr) {
            Vector3D v(point[0], point[1], point[2]);
            f->SetPoint(index, v);
        }
    }
}


void BrlBagOfTrianglesFaceSetPoints
(
    BrlBagOfTrianglesFace face,
    const double*         pt1,
    const double*         pt2,
    const double*         pt3
) {
    if ((face != nullptr) && (pt1 != nullptr) && (pt2 != nullptr) && (pt3 != nullptr)) {
        BagOfTriangles::Face* f  = CastBagOfTrianglesFace(face);

        assert(f != nullptr);

        if (f != nullptr) {
            Vector3D v1(pt1[0], pt1[1], pt1[2]);
            Vector3D v2(pt2[0], pt2[1], pt2[2]);
            Vector3D v3(pt3[0], pt3[1], pt3[2]);
            f->SetPoints(v1, v2, v3);
        }
    }
}


double BrlBagOfTrianglesFaceThickness
(
    BrlBagOfTrianglesFace face
) {
    double ret = 0.0;

    if (face != nullptr) {
        BagOfTriangles::Face* f = CastBagOfTrianglesFace(face);

        assert(f != nullptr);

        if (f != nullptr)
            ret = f->Thickness();
    }

    return ret;
}


void BrlBagOfTrianglesFaceSetThickness
(
    BrlBagOfTrianglesFace face,
    double                value
) {
    if (face != nullptr) {
        BagOfTriangles::Face* f = CastBagOfTrianglesFace(face);

        assert(f != nullptr);

        if (f != nullptr)
            f->SetThickness(value);
    }
}


int BrlBagOfTrianglesFaceApendThickness
(
    BrlBagOfTrianglesFace face
) {
    int ret = 0;

    if (face != nullptr) {
        BagOfTriangles::Face* f = CastBagOfTrianglesFace(face);

        assert(f != nullptr);

        if (f != nullptr)
            ret = f->ApendThickness() ? 1 : 0;
    }

    return ret;
}


void BrlBagOfTrianglesFaceSetApendThickness
(
    BrlBagOfTrianglesFace face,
    int                   apendThickness
) {
    if (face != nullptr) {
        BagOfTriangles::Face* f = CastBagOfTrianglesFace(face);

        assert(f != nullptr);

        if (f != nullptr)
            f->SetApendThickness(apendThickness != 0);
    }
}


void BrlBagOfTrianglesFaceNormal
(
    BrlBagOfTrianglesFace face,
    int                   index,
    double*               out_normal
) {
    if ((face != nullptr) && (out_normal != nullptr)) {
        BagOfTriangles::Face* f = CastBagOfTrianglesFace(face);

        assert(f != nullptr);

        if (f != nullptr) {
            Vector3D n = f->Normal(index);
            out_normal[0] = n.coordinates[0];
            out_normal[1] = n.coordinates[1];
            out_normal[2] = n.coordinates[2];
        }
    }
}


void BrlBagOfTrianglesFaceSetNormal
(
    BrlBagOfTrianglesFace face,
    int                   index,
    const double*         normal
) {
    if ((face != nullptr) && (normal != nullptr)) {
        BagOfTriangles::Face* f = CastBagOfTrianglesFace(face);

        assert(f != nullptr);

        if (f != nullptr) {
            Vector3D n(normal[0], normal[1], normal[2]);
            f->SetNormal(index, n);
        }
    }
}


void BrlBagOfTrianglesFaceSetNormals
(
    BrlBagOfTrianglesFace face,
    const double*         normal1,
    const double*         normal2,
    const double*         normal3
) {
    if ((face != nullptr) && (normal1 != nullptr) && (normal2 != nullptr) && (normal3 != nullptr)) {
        BagOfTriangles::Face* f  = CastBagOfTrianglesFace(face);

        assert(f != nullptr);

        if (f != nullptr) {
            Vector3D n1(normal1[0], normal1[1], normal1[2]);
            Vector3D n2(normal2[0], normal2[1], normal2[2]);
            Vector3D n3(normal3[0], normal3[1], normal3[2]);
            f->SetNormals(n1, n2, n3);
        }
    }
}


void BrlBagOfTrianglesFaceDelete
(
    BrlBagOfTrianglesFace face
) {
    if (face != nullptr) {
        BagOfTrianglesFaceData* data = static_cast<BagOfTrianglesFaceData*>(face);
        
        assert(data != nullptr);
        
        if (data != nullptr)
            delete data;
    }
}
