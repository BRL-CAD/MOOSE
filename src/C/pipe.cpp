/*                      P I P E . C P P
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
/** @file pipe.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements a handle and functions for Pipe solid handling
 */

#include <cassert>

#include <brlcad/Database/Pipe.h>

#include <brlcad/C/pipe.h>

#include "casts.h"


using namespace BRLCAD;


BrlPipe BrlNewPipe(void) {
    return DowncastObject(new Pipe());
}


int BrlPipeNumberOfControlPoints
(
    BrlPipe pipe
) {
    int ret = 0;

    if (pipe != nullptr) {
        Pipe* pIntern = CastPipe(pipe);

        assert(pIntern != nullptr);

        if (pIntern != nullptr)
            ret = pIntern->NumberOfControlPoints();
    }

    return ret;
}


BrlPipeControlPoint BrlPipeGetControlPoint
(
    BrlPipe pipe,
    int index
) {
    BrlPipeControlPoint ret = nullptr;

    if (pipe != nullptr) {
        Pipe* pIntern = CastPipe(pipe);

        assert(pIntern != nullptr);

        if (pIntern != nullptr)
            ret = new PipeControlPointData(pIntern->GetControlPoint(index));
    }

    return ret;
}


BrlPipeControlPoint BrlPipeAppendControlPoint
(
    BrlPipe pipe,
    double  pointX, double pointY, double pointZ,
    double  innerDiameter,
    double  outerDiameter,
    double  bendRadius
) {
    BrlPipeControlPoint ret = nullptr;

    if (pipe != nullptr) {
        Pipe* pIntern = CastPipe(pipe);

        assert(pIntern != nullptr);

        if (pIntern != nullptr) {
            Vector3D pt(pointX, pointY, pointZ);

            ret = new PipeControlPointData(pIntern->AppendControlPoint(pt, innerDiameter, outerDiameter, bendRadius));
        }
    }

    return ret;
}


BrlPipeControlPoint BrlPipeInsertControlPoint
(
    BrlPipe pipe,
    int index,
    double  pointX, double pointY, double pointZ,
    double  innerDiameter,
    double  outerDiameter,
    double  bendRadius
) {
    BrlPipeControlPoint ret = nullptr;

    if (pipe != nullptr) {
        Pipe* pIntern = CastPipe(pipe);

        assert(pIntern != nullptr);

        if (pIntern != nullptr) {
            Vector3D pt(pointX, pointY, pointZ);

            ret = new PipeControlPointData(pIntern->InsertControlPoint(index, pt, innerDiameter, outerDiameter, bendRadius));
        }
    }

    return ret;
}


void BrlPipeDeleteControlPoint
(
    BrlPipe pipe,
    int index
) {
    if (pipe != nullptr) {
        Pipe* pIntern = CastPipe(pipe);

        assert(pIntern != nullptr);

        if (pIntern != nullptr)
            pIntern->DeleteControlPoint(index);
    }
}


BrlVector3D BrlPipeControlPointPoint
(
    BrlPipeControlPoint controlPoint
) {
    BrlVector3D ret = nullptr;

    if (controlPoint != nullptr) {
        Pipe::ControlPoint* cpIntern = CastPipeControlPoint(controlPoint);

        assert(cpIntern != nullptr);

        if (cpIntern != nullptr)
            ret = new Vector3DData(cpIntern->Point());
    }

    return ret;
}


void BrlPipeControlPointSetPoint
(
    BrlPipeControlPoint controlPoint,
    double              pointX, double pointY, double pointZ
) {
    if (controlPoint != nullptr) {
        Pipe::ControlPoint* cpIntern = CastPipeControlPoint(controlPoint);

        assert(cpIntern != nullptr);

        if (cpIntern != nullptr) {
            Vector3D pt(pointX, pointY, pointZ);

            cpIntern->SetPoint(pt);
        }
    }
}


double BrlPipeControlPointInnerDiameter
(
    BrlPipeControlPoint controlPoint
) {
    double ret = 0.0;

    if (controlPoint != nullptr) {
        Pipe::ControlPoint* cpIntern = CastPipeControlPoint(controlPoint);

        assert(cpIntern != nullptr);

        if (cpIntern != nullptr)
            ret = cpIntern->InnerDiameter();
    }

    return ret;
}


void BrlPipeControlPointSetInnerDiameter
(
    BrlPipeControlPoint controlPoint,
    double              id
) {
    if (controlPoint != nullptr) {
        Pipe::ControlPoint* cpIntern = CastPipeControlPoint(controlPoint);

        assert(cpIntern != nullptr);

        if (cpIntern != nullptr)
            cpIntern->SetInnerDiameter(id);
    }
}


double BrlPipeControlPointOuterDiameter
(
    BrlPipeControlPoint controlPoint
) {
    double ret = 0.0;

    if (controlPoint != nullptr) {
        Pipe::ControlPoint* cpIntern = CastPipeControlPoint(controlPoint);

        assert(cpIntern != nullptr);

        if (cpIntern != nullptr)
            ret = cpIntern->OuterDiameter();
    }

    return ret;
}


void BrlPipeControlPointSetOuterDiameter
(
    BrlPipeControlPoint controlPoint,
    double              od
) {
    if (controlPoint != nullptr) {
        Pipe::ControlPoint* cpIntern = CastPipeControlPoint(controlPoint);

        assert(cpIntern != nullptr);

        if (cpIntern != nullptr)
            cpIntern->SetOuterDiameter(od);
    }
}


double BrlPipeControlPointBendRadius
(
    BrlPipeControlPoint controlPoint
) {
    double ret = 0.0;

    if (controlPoint != nullptr) {
        Pipe::ControlPoint* cpIntern = CastPipeControlPoint(controlPoint);

        assert(cpIntern != nullptr);

        if (cpIntern != nullptr)
            ret = cpIntern->BendRadius();
    }

    return ret;
}


void BrlPipeControlPointSetBendRadius
(
    BrlPipeControlPoint controlPoint,
    double              br
) {
    if (controlPoint != nullptr) {
        Pipe::ControlPoint* cpIntern = CastPipeControlPoint(controlPoint);

        assert(cpIntern != nullptr);

        if (cpIntern != nullptr)
            cpIntern->SetBendRadius(br);
    }
}


const char* BrlPipeClassName(void) {
    return Pipe::ClassName();
}
