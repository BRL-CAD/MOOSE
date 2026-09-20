/*                      S K E T C H . C P P
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
/** @file sketch.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements a handle and functions for Sketch solid handling
 */

#include <cassert>

#include <brlcad/Database/Sketch.h>

#include <brlcad/C/sketch.h>

#include "casts.h"


using namespace BRLCAD;


static BrlSketchSegment DowncastSketchSegment
(
    BRLCAD::Sketch::Segment* segment
) {
    BrlSketchSegment ret = nullptr;

    if (segment != nullptr) {
        switch (segment->Type()) {
        case Sketch::Segment::SegmentType::Null:
            ret = new SketchSegmentData(segment);
            break;

        case Sketch::Segment::SegmentType::Line:
            ret = new SketchLineData(static_cast<Sketch::Line*>(segment));
            break;

        case Sketch::Segment::SegmentType::CircularArc:
            ret = new SketchCircularArcData(static_cast<Sketch::CircularArc*>(segment));
            break;

        case Sketch::Segment::SegmentType::Nurb:
            ret = new SketchNurbData(static_cast<Sketch::Nurb*>(segment));
            break;

        case Sketch::Segment::SegmentType::Bezier:
            ret = new SketchBezierData(static_cast<Sketch::Bezier*>(segment));
            break;

        default:
            ret = new SketchSegmentData(segment);
        }
    }

    return ret;
}


BrlSketch BrlNewSketch(void) {
    return DowncastObject(new Sketch());
}


BrlSketchSegmentSegmentType BrlSketchSegmentType
(
    BrlSketchSegment segment
) {
    BrlSketchSegmentSegmentType ret = BrlSketchSegmentSegmentTypeNull;

    if (segment != nullptr) {
        Sketch::Segment* segIntern = CastSketchSegment(segment);
        assert(segIntern != nullptr);

        if (segIntern != nullptr) {
            switch (segIntern->Type()) {
            case Sketch::Segment::SegmentType::Null:
                ret = BrlSketchSegmentSegmentTypeNull;
                break;

            case Sketch::Segment::SegmentType::Line:
                ret = BrlSketchSegmentSegmentTypeLine;
                break;

            case Sketch::Segment::SegmentType::CircularArc:
                ret = BrlSketchSegmentSegmentTypeCircularArc;
                break;

            case Sketch::Segment::SegmentType::Nurb:
                ret = BrlSketchSegmentSegmentTypeNurb;
                break;

            case Sketch::Segment::SegmentType::Bezier:
                ret = BrlSketchSegmentSegmentTypeBezier;
                break;

            default:
                ret = BrlSketchSegmentSegmentTypeNull;
            }
        }
    }

    return ret;
}


BrlSketchSegment BrlSketchSegmentClone
(
    BrlSketchSegment segment
) {
    BrlSketchSegment ret = nullptr;

    if (segment != nullptr) {
        Sketch::Segment* segIntern = CastSketchSegment(segment);
        assert(segIntern != nullptr);

        if (segIntern != nullptr)
            ret = DowncastSketchSegment(segIntern->Clone());
    }

    return ret;
}


BrlVector2D BrlSketchSegmentStartPoint
(
    BrlSketchSegment segment
) {
    BrlVector2D ret = nullptr;

    if (segment != nullptr) {
        Sketch::Segment* segIntern = CastSketchSegment(segment);
        assert(segIntern != nullptr);

        if (segIntern != nullptr)
            ret = new Vector2DData(segIntern->StartPoint());
    }

    return ret;
}


void BrlSketchSegmentSetStartPoint
(
    BrlSketchSegment segment,
    double           x, double y
) {
    if (segment != nullptr) {
        Sketch::Segment* segIntern = CastSketchSegment(segment);
        assert(segIntern != nullptr);

        if (segIntern != nullptr)
            segIntern->SetStartPoint(Vector2D(x, y));
    }
}


BrlVector2D BrlSketchSegmentEndPoint
(
    BrlSketchSegment segment
) {
    BrlVector2D ret = nullptr;

    if (segment != nullptr) {
        Sketch::Segment* segIntern = CastSketchSegment(segment);
        assert(segIntern != nullptr);

        if (segIntern != nullptr)
            ret = new Vector2DData(segIntern->EndPoint());
    }

    return ret;
}


void BrlSketchSegmentSetEndPoint
(
    BrlSketchSegment segment,
    double           x, double y
) {
    if (segment != nullptr) {
        Sketch::Segment* segIntern = CastSketchSegment(segment);
        assert(segIntern != nullptr);

        if (segIntern != nullptr)
            segIntern->SetEndPoint(Vector2D(x, y));
    }
}


int BrlSketchSegmentReverse
(
    BrlSketchSegment segment
) {
    int ret = 0;

    if (segment != nullptr) {
        Sketch::Segment* segIntern = CastSketchSegment(segment);
        assert(segIntern != nullptr);

        if (segIntern != nullptr)
            ret = segIntern->Reverse() ? 1 : 0;
    }

    return ret;
}


void BrlSketchSegmentSetReverse
(
    BrlSketchSegment segment,
    int              reverse
) {
    if (segment != nullptr) {
        Sketch::Segment* segIntern = CastSketchSegment(segment);
        assert(segIntern != nullptr);

        if (segIntern != nullptr)
            segIntern->SetReverse(reverse != 0);
    }
}


BrlVector2D BrlSketchCircularArcCenter
(
    BrlSketchCircularArc arc
) {
    BrlVector2D ret = nullptr;

    if (arc != nullptr) {
        Sketch::CircularArc* arcIntern = CastSketchCircularArc(arc);
        assert(arcIntern != nullptr);

        if (arcIntern != nullptr)
            ret = new Vector2DData(arcIntern->Center());
    }

    return ret;
}


void BrlSketchCircularArcSetCenter
(
    BrlSketchCircularArc arc,
    double                 x, double y
) {
    if (arc != nullptr) {
        Sketch::CircularArc* arcIntern = CastSketchCircularArc(arc);
        assert(arcIntern != nullptr);

        if (arcIntern != nullptr)
            arcIntern->SetCenter(Vector2D(x, y));
    }
}


double BrlSketchCircularArcRadius
(
    BrlSketchCircularArc arc
) {
    double ret = 0.;

    if (arc != nullptr) {
        Sketch::CircularArc* arcIntern = CastSketchCircularArc(arc);
        assert(arcIntern != nullptr);

        if (arcIntern != nullptr)
            ret = arcIntern->Radius();
    }

    return ret;
}


void BrlSketchCircularArcSetRadius
(
    BrlSketchCircularArc arc,
    double               radius
) {
    if (arc != nullptr) {
        Sketch::CircularArc* arcIntern = CastSketchCircularArc(arc);
        assert(arcIntern != nullptr);

        if (arcIntern != nullptr)
            arcIntern->SetRadius(radius);
    }
}


int BrlSketchCircularArcCenterIsLeft
(
    BrlSketchCircularArc arc
) {
    int ret = 0;

    if (arc != nullptr) {
        Sketch::CircularArc* arcIntern = CastSketchCircularArc(arc);
        assert(arcIntern != nullptr);

        if (arcIntern != nullptr)
            ret = arcIntern->CenterIsLeft() ? 1 : 0;
    }

    return ret;
}


void BrlSketchCircularArcSetCenterIsLeft
(
    BrlSketchCircularArc arc,
    int                  isLeft
) {
    if (arc != nullptr) {
        Sketch::CircularArc* arcIntern = CastSketchCircularArc(arc);
        assert(arcIntern != nullptr);

        if (arcIntern != nullptr)
            arcIntern->SetCenterIsLeft(isLeft != 0);
    }
}


int BrlSketchCircularArcClockwiseOriented
(
    BrlSketchCircularArc arc
) {
    int ret = 0;

    if (arc != nullptr) {
        Sketch::CircularArc* arcIntern = CastSketchCircularArc(arc);
        assert(arcIntern != nullptr);

        if (arcIntern != nullptr)
            ret = arcIntern->ClockwiseOriented() ? 1 : 0;
    }

    return ret;
}


void BrlSketchCircularArcSetClockwiseOriented
(
    BrlSketchCircularArc arc,
    int                  clockwise
) {
    if (arc != nullptr) {
        Sketch::CircularArc* arcIntern = CastSketchCircularArc(arc);
        assert(arcIntern != nullptr);

        if (arcIntern != nullptr)
            arcIntern->SetClockwiseOriented(clockwise != 0);
    }
}


int BrlSketchNurbOrder
(
    BrlSketchNurb nurb
) {
    int ret = 0;

    if (nurb != nullptr) {
        Sketch::Nurb* nurbIntern = CastSketchNurb(nurb);
        assert(nurbIntern != nullptr);

        if (nurbIntern != nullptr)
            ret = nurbIntern->Order();
    }

    return ret;
}


int BrlSketchNurbIsRational
(
    BrlSketchNurb nurb
) {
    int ret = false;

    if (nurb != nullptr) {
        Sketch::Nurb* nurbIntern = CastSketchNurb(nurb);
        assert(nurbIntern != nullptr);

        if (nurbIntern != nullptr)
            ret = nurbIntern->IsRational() ? 1 : 0;
    }

    return ret;
}


int BrlSketchNurbNumberOfKnots
(
    BrlSketchNurb nurb
) {
    int ret = 0;

    if (nurb != nullptr) {
        Sketch::Nurb* nurbIntern = CastSketchNurb(nurb);
        assert(nurbIntern != nullptr);

        if (nurbIntern != nullptr)
            ret = nurbIntern->NumberOfKnots();
    }

    return ret;
}


double BrlSketchNurbKnot
(
    BrlSketchNurb nurb,
    int           index
) {
    double ret = 0.;

    if (nurb != nullptr) {
        Sketch::Nurb* nurbIntern = CastSketchNurb(nurb);
        assert(nurbIntern != nullptr);

        if (nurbIntern != nullptr)
            ret = nurbIntern->Knot(index);
    }

    return ret;
}


int BrlSketchNurbNumberOfControlPoints
(
    BrlSketchNurb nurb
) {
    int ret = 0;

    if (nurb != nullptr) {
        Sketch::Nurb* nurbIntern = CastSketchNurb(nurb);
        assert(nurbIntern != nullptr);

        if (nurbIntern != nullptr)
            ret = nurbIntern->NumberOfControlPoints();
    }

    return ret;
}


BrlVector2D BrlSketchNurbControlPoint
(
    BrlSketchNurb nurb,
    int           index
) {
    BrlVector2D ret = nullptr;

    if (nurb != nullptr) {
        Sketch::Nurb* nurbIntern = CastSketchNurb(nurb);
        assert(nurbIntern != nullptr);

        if (nurbIntern != nullptr)
            ret = new Vector2DData(nurbIntern->ControlPoint(index));
    }

    return ret;
}


double BrlSketchNurbControlPointWeight
(
    BrlSketchNurb nurb,
    int           index
) {
    double ret = 0.;

    if (nurb != nullptr) {
        Sketch::Nurb* nurbIntern = CastSketchNurb(nurb);
        assert(nurbIntern != nullptr);

        if (nurbIntern != nullptr)
            ret = nurbIntern->ControlPointWeight(index);
    }

    return ret;
}


void BrlSketchNurbSetOrder
(
    BrlSketchNurb nurb,
    int           order
) {
    if (nurb != nullptr) {
        Sketch::Nurb* nurbIntern = CastSketchNurb(nurb);
        assert(nurbIntern != nullptr);

        if (nurbIntern != nullptr)
            nurbIntern->SetOrder(order);
    }
}


void BrlSketchNurbAddKnot
(
    BrlSketchNurb nurb,
    double        knot
) {
    if (nurb != nullptr) {
        Sketch::Nurb* nurbIntern = CastSketchNurb(nurb);
        assert(nurbIntern != nullptr);

        if (nurbIntern != nullptr)
            nurbIntern->AddKnot(knot);
    }
}


void BrlSketchNurbAddControlPoint
(
    BrlSketchNurb nurb,
    double        x, double y
) {
    if (nurb != nullptr) {
        Sketch::Nurb* nurbIntern = CastSketchNurb(nurb);
        assert(nurbIntern != nullptr);

        if (nurbIntern != nullptr)
            nurbIntern->AddControlPoint(Vector2D(x, y));
    }
}


void BrlSketchNurbAddControlPointWeight
(
    BrlSketchNurb nurb,
    double        x, double y,
    double        weight
) {
    if (nurb != nullptr) {
        Sketch::Nurb* nurbIntern = CastSketchNurb(nurb);
        assert(nurbIntern != nullptr);

        if (nurbIntern != nullptr)
            nurbIntern->AddControlPointWeight(Vector2D(x, y), weight);
    }
}


int BrlSketchBezierDegree
(
    BrlSketchBezier bezier
) {
    int ret = 0;

    if (bezier != nullptr) {
        Sketch::Bezier* bezierIntern = CastSketchBezier(bezier);
        assert(bezierIntern != nullptr);

        if (bezierIntern != nullptr)
            ret = bezierIntern->Degree();
    }

    return ret;
}


BrlVector2D BrlSketchBezierControlPoint
(
    BrlSketchBezier bezier,
    int             index
) {
    BrlVector2D ret = nullptr;

    if (bezier != nullptr) {
        Sketch::Bezier* bezierIntern = CastSketchBezier(bezier);
        assert(bezierIntern != nullptr);

        if (bezierIntern != nullptr)
            ret = new Vector2DData(bezierIntern->ControlPoint(index));
    }

    return ret;
}


void BrlSketchBezierAddControlPoint
(
    BrlSketchBezier bezier,
    double          x, double y
) {
    if (bezier != nullptr) {
        Sketch::Bezier* bezierIntern = CastSketchBezier(bezier);
        assert(bezierIntern != nullptr);

        if (bezierIntern != nullptr)
            bezierIntern->AddControlPoint(Vector2D(x, y));
    }
}


int BrlSketchNumberOfSegments
(
    BrlSketch sketch
) {
    int ret = 0;

    if (sketch != nullptr) {
        Sketch* sIntern = CastSketch(sketch);
        assert(sIntern != nullptr);

        if (sIntern != nullptr)
            ret = sIntern->NumberOfSegments();
    }

    return ret;
}


BrlSketchSegment BrlSketchGetSegment
(
    BrlSketch sketch,
    int       index
) {
    BrlSketchSegment ret = nullptr;

    if (sketch != nullptr) {
        Sketch* sIntern = CastSketch(sketch);
        assert(sIntern != nullptr);

        if (sIntern != nullptr)
            ret = new SketchSegmentData(sIntern->Get(index));
    }

    return ret;
}


BrlSketchLine BrlSketchAppendLine
(
    BrlSketch sketch
) {
    BrlSketchLine ret = nullptr;

    if (sketch != nullptr) {
        Sketch* sIntern = CastSketch(sketch);
        assert(sIntern != nullptr);

        if (sIntern != nullptr)
            ret = new SketchLineData(sIntern->AppendLine());
    }

    return ret;
}


BrlSketchLine BrlSketchInsertLine
(
    BrlSketch sketch,
    int       index
) {
    BrlSketchLine ret = nullptr;

    if (sketch != nullptr) {
        Sketch* sIntern = CastSketch(sketch);
        assert(sIntern != nullptr);

        if (sIntern != nullptr)
            ret = new SketchLineData(sIntern->InsertLine(index));
    }

    return ret;
}


BrlSketchCircularArc BrlSketchAppendArc
(
    BrlSketch sketch
) {
    BrlSketchCircularArc ret = nullptr;

    if (sketch != nullptr) {
        Sketch* sIntern = CastSketch(sketch);
        assert(sIntern != nullptr);

        if (sIntern != nullptr)
            ret = new SketchCircularArcData(sIntern->AppendArc());
    }

    return ret;
}


BrlSketchCircularArc BrlSketchInsertArc
(
    BrlSketch sketch,
    int       index
) {
    BrlSketchCircularArc ret = nullptr;

    if (sketch != nullptr) {
        Sketch* sIntern = CastSketch(sketch);
        assert(sIntern != nullptr);

        if (sIntern != nullptr)
            ret = new SketchCircularArcData(sIntern->InsertArc(index));
    }

    return ret;
}


BrlSketchNurb BrlSketchAppendNurb
(
    BrlSketch sketch
) {
    BrlSketchNurb ret = nullptr;

    if (sketch != nullptr) {
        Sketch* sIntern = CastSketch(sketch);
        assert(sIntern != nullptr);

        if (sIntern != nullptr)
            ret = new SketchNurbData(sIntern->AppendNurb());
    }

    return ret;
}


BrlSketchNurb BrlSketchInsertNurb
(
    BrlSketch sketch,
    int       index
) {
    BrlSketchNurb ret = nullptr;

    if (sketch != nullptr) {
        Sketch* sIntern = CastSketch(sketch);
        assert(sIntern != nullptr);

        if (sIntern != nullptr)
            ret = new SketchNurbData(sIntern->InsertNurb(index));
    }

    return ret;
}


BrlSketchBezier BrlSketchAppendBezier
(
    BrlSketch sketch
) {
    BrlSketchBezier ret = nullptr;

    if (sketch != nullptr) {
        Sketch* sIntern = CastSketch(sketch);
        assert(sIntern != nullptr);

        if (sIntern != nullptr)
            ret = new SketchBezierData(sIntern->AppendBezier());
    }

    return ret;
}


BrlSketchBezier BrlSketchInsertBezier
(
    BrlSketch sketch,
    int       index
) {
    BrlSketchBezier ret = nullptr;

    if (sketch != nullptr) {
        Sketch* sIntern = CastSketch(sketch);
        assert(sIntern != nullptr);

        if (sIntern != nullptr)
            ret = new SketchBezierData(sIntern->InsertBezier(index));
    }

    return ret;
}


void BrlSketchDeleteSegment
(
    BrlSketch sketch,
    int       index
) {
    if (sketch != nullptr) {
        Sketch* sIntern = CastSketch(sketch);
        assert(sIntern != nullptr);

        if (sIntern != nullptr)
            sIntern->DeleteSegment(index);
    }
}


BrlVector3D BrlSketchEmbeddingPlaneX
(
    BrlSketch sketch
) {
    BrlVector3D ret = nullptr;

    if (sketch != nullptr) {
        Sketch* sIntern = CastSketch(sketch);
        assert(sIntern != nullptr);

        if (sIntern != nullptr)
            ret = new Vector3DData(sIntern->EmbeddingPlaneX());
    }

    return ret;
}


BrlVector3D BrlSketchEmbeddingPlaneY
(
    BrlSketch sketch
) {
    BrlVector3D ret = nullptr;

    if (sketch != nullptr) {
        Sketch* sIntern = CastSketch(sketch);
        assert(sIntern != nullptr);

        if (sIntern != nullptr)
            ret = new Vector3DData(sIntern->EmbeddingPlaneY());
    }

    return ret;
}


void BrlSketchSetEmbeddingPlaneX
(
    BrlSketch sketch,
    double    x, double y, double z
) {
    if (sketch != nullptr) {
        Sketch* sIntern = CastSketch(sketch);
        assert(sIntern != nullptr);

        if (sIntern != nullptr)
            sIntern->SetEmbeddingPlaneX(Vector3D(x, y, z));
    }
}


void BrlSketchSetEmbeddingPlaneY
(
    BrlSketch sketch,
    double    x, double y, double z
) {
    if (sketch != nullptr) {
        Sketch* sIntern = CastSketch(sketch);
        assert(sIntern != nullptr);

        if (sIntern != nullptr)
            sIntern->SetEmbeddingPlaneY(Vector3D(x, y, z));
    }
}


BrlVector3D BrlSketchEmbeddingPlaneOrigin
(
    BrlSketch sketch
) {
    BrlVector3D ret = nullptr;

    if (sketch != nullptr) {
        Sketch* sIntern = CastSketch(sketch);
        assert(sIntern != nullptr);

        if (sIntern != nullptr)
            ret = new Vector3DData(sIntern->EmbeddingPlaneOrigin());
    }

    return ret;
}


void BrlSketchSetEmbeddingPlaneOrigin
(
    BrlSketch sketch,
    double    x, double y, double z
) {
    if (sketch != nullptr) {
        Sketch* sIntern = CastSketch(sketch);
        assert(sIntern != nullptr);

        if (sIntern != nullptr)
            sIntern->SetEmbeddingPlaneOrigin(Vector3D(x, y, z));
    }
}


const char* BrlSketchClassName(void) {
    return Sketch::ClassName();
}
