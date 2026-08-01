/*                      B A G O F T R I A N G L E S . C P P
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
/** @file bagOfTriangles.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements a handle and functions for Bag of Triangle solid handling
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


BrlVector3D BrlBagOfTrianglesFacePoint
(
    BrlBagOfTrianglesFace face,
    int                   index
) {
    BrlVector3D ret = nullptr;

    if (face != nullptr) {
        BagOfTriangles::Face* f = CastBagOfTrianglesFace(face);
        assert(f != nullptr);

        if (f != nullptr)
            ret = new Vector3DData(f->Point(index));
    }

    return ret;
}


void BrlBagOfTrianglesFaceSetPoint
(
    BrlBagOfTrianglesFace face,
    int                   index,
    double                pointX, double pointY, double pointZ
) {
    if (face != nullptr) {
        BagOfTriangles::Face* f = CastBagOfTrianglesFace(face);

        assert(f != nullptr);

        if (f != nullptr) {
            Vector3D v(pointX, pointY, pointZ);
            f->SetPoint(index, v);
        }
    }
}


void BrlBagOfTrianglesFaceSetPoints
(
    BrlBagOfTrianglesFace face,
    double                point1X, double point1Y, double point1Z,
    double                point2X, double point2Y, double point2Z,
    double                point3X, double point3Y, double point3Z
) {
    if (face != nullptr) {
        BagOfTriangles::Face* f  = CastBagOfTrianglesFace(face);

        assert(f != nullptr);

        if (f != nullptr) {
            Vector3D v1(point1X, point1Y, point1Z);
            Vector3D v2(point2X, point2Y, point2Z);
            Vector3D v3(point3X, point3Y, point3Z);
            f->SetPoints(v1, v2, v3);
        }
    }
}


double BrlBagOfTrianglesFaceThickness
(
    BrlBagOfTrianglesFace face
) {
    double ret = 0.;

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


BrlVector3D BrlBagOfTrianglesFaceNormal
(
    BrlBagOfTrianglesFace face,
    int                   index
) {
    BrlVector3D ret = nullptr;

    if (face != nullptr) {
        BagOfTriangles::Face* f = CastBagOfTrianglesFace(face);
        assert(f != nullptr);

        if (f != nullptr)
            ret = new Vector3DData(f->Normal(index));
    }

    return ret;
}


void BrlBagOfTrianglesFaceSetNormal
(
    BrlBagOfTrianglesFace face,
    int                   index,
    double                normalX, double normalY, double normalZ
) {
    if (face != nullptr) {
        BagOfTriangles::Face* f = CastBagOfTrianglesFace(face);

        assert(f != nullptr);

        if (f != nullptr) {
            Vector3D n(normalX, normalY, normalZ);
            f->SetNormal(index, n);
        }
    }
}


void BrlBagOfTrianglesFaceSetNormals
(
    BrlBagOfTrianglesFace face,
    double                normal1X, double normal1Y, double normal1Z,
    double                normal2X, double normal2Y, double normal2Z,
    double                normal3X, double normal3Y, double normal3Z
) {
    if (face != nullptr) {
        BagOfTriangles::Face* f = CastBagOfTrianglesFace(face);

        assert(f != nullptr);

        if (f != nullptr) {
            Vector3D n1(normal1X, normal1Y, normal1Z);
            Vector3D n2(normal2X, normal2Y, normal2Z);
            Vector3D n3(normal3X, normal3Y, normal3Z);
            f->SetNormals(n1, n2, n3);
        }
    }
}


BrlBagOfTrianglesBotMode BrlBagOfTrianglesMode
(
    BrlBagOfTriangles bot
) {
    BrlBagOfTrianglesBotMode ret = BrlBagOfTrianglesBotModeSurface; 

    if (bot != nullptr) {
        BagOfTriangles* b = CastBagOfTriangles(bot);

        assert(b != nullptr);

        if (b != nullptr) {
            switch (b->Mode()) {
            case BagOfTriangles::BotMode::Surface:
                ret = BrlBagOfTrianglesBotModeSurface;
                break;
            case BagOfTriangles::BotMode::Solid:
                ret = BrlBagOfTrianglesBotModeSolid;
                break;
            case BagOfTriangles::BotMode::Plate:
                ret = BrlBagOfTrianglesBotModePlate;
                break;
            case BagOfTriangles::BotMode::EqualLineOfSightPlate:
                ret = BrlBagOfTrianglesBotModeEqualLineOfSightPlate;
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
    BrlBagOfTriangles        bot,
    BrlBagOfTrianglesBotMode mode
) {
    if (bot != nullptr) {
        BagOfTriangles* b = CastBagOfTriangles(bot);

        assert(b != nullptr);

        if (b != nullptr) {
            switch (mode) {
            case BrlBagOfTrianglesBotModeSurface:
                b->SetMode(BagOfTriangles::BotMode::Surface);
                break;
            case BrlBagOfTrianglesBotModeSolid:
                b->SetMode(BagOfTriangles::BotMode::Solid);
                break;
            case BrlBagOfTrianglesBotModePlate:
                b->SetMode(BagOfTriangles::BotMode::Plate);
                break;
            case BrlBagOfTrianglesBotModeEqualLineOfSightPlate:
                b->SetMode(BagOfTriangles::BotMode::EqualLineOfSightPlate);
                break;
            default:
                assert(0);
            }
        }
    }
}


BrlBagOfTrianglesBotOrientation BrlBagOfTrianglesOrientation
(
    BrlBagOfTriangles bot
) {
    BrlBagOfTrianglesBotOrientation ret = BrlBagOfTrianglesBotOrientationUnoriented; 

    if (bot != nullptr) {
        BagOfTriangles* b = CastBagOfTriangles(bot);

        assert(b != nullptr);

        if (b != nullptr) {
            switch (b->Orientation()) {
            case BagOfTriangles::BotOrientation::Unoriented:
                ret = BrlBagOfTrianglesBotOrientationUnoriented;
                break;
            case BagOfTriangles::BotOrientation::ClockWise:
                ret = BrlBagOfTrianglesBotOrientationClockWise;
                break;
            case BagOfTriangles::BotOrientation::CounterClockWise:
                ret = BrlBagOfTrianglesBotOrientationCounterClockWise;
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
    BrlBagOfTriangles               bot,
    BrlBagOfTrianglesBotOrientation orientation
) {
    if (bot != nullptr) {
        BagOfTriangles* b = CastBagOfTriangles(bot);

        assert(b != nullptr);

        if (b != nullptr) {
            switch (orientation) {
            case BrlBagOfTrianglesBotOrientationUnoriented:
                b->SetOrientation(BagOfTriangles::BotOrientation::Unoriented);
                break;
            case BrlBagOfTrianglesBotOrientationClockWise:
                b->SetOrientation(BagOfTriangles::BotOrientation::ClockWise);
                break;
            case BrlBagOfTrianglesBotOrientationCounterClockWise:
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
    double            point1X, double point1Y, double point1Z,
    double            point2X, double point2Y, double point2Z,
    double            point3X, double point3Y, double point3Z
) {
    BrlBagOfTrianglesFace ret = nullptr;

    if (bot != nullptr) {
        BagOfTriangles* b  = CastBagOfTriangles(bot);

        assert(b != nullptr);

        if (b != nullptr) {
            Vector3D v1(point1X, point1Y, point1Z);
            Vector3D v2(point2X, point2Y, point2Z);
            Vector3D v3(point3X, point3Y, point3Z);
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
