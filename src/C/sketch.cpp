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

#include "rt/geom.h"

#include <brlcad/Database/Sketch.h>

#include <brlcad/C/sketch.h>

#include "casts.h"


using namespace BRLCAD;


BrlSketch BrlNewSketch(void) {
    return DowncastObject(new Sketch());
}


BrlVector3D BrlSketchEmbeddingPlaneX
(
    BrlSketch              sketch
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


void BrlSketchSetEmbeddingPlaneX
(
    BrlSketch              sketch,
    double                 x,
    double                 y,
    double                 z
) {
    if (sketch != nullptr) {
        Sketch* sIntern = CastSketch(sketch);
        assert(sIntern != nullptr);
        if (sIntern != nullptr) {
            Vector3D u(x, y, z);
            sIntern->SetEmbeddingPlaneX(u);
        }
    }
}


BrlVector3D BrlSketchEmbeddingPlaneY
(
    BrlSketch              sketch
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


void BrlSketchSetEmbeddingPlaneY
(
    BrlSketch              sketch,
    double                 x,
    double                 y,
    double                 z
) {
    if (sketch != nullptr) {
        Sketch* sIntern = CastSketch(sketch);
        assert(sIntern != nullptr);
        if (sIntern != nullptr) {
            Vector3D v(x, y, z);
            sIntern->SetEmbeddingPlaneY(v);
        }
    }
}


BrlVector3D BrlSketchEmbeddingPlaneOrigin
(
    BrlSketch              sketch
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
    BrlSketch              sketch,
    double                 x,
    double                 y,
    double                 z
) {
    if (sketch != nullptr) {
        Sketch* sIntern = CastSketch(sketch);
        assert(sIntern != nullptr);
        if (sIntern != nullptr) {
            Vector3D pt(x, y, z);
            sIntern->SetEmbeddingPlaneOrigin(pt);
        }
    }
}


int BrlSketchNumberOfSegments
(
    BrlSketch              sketch
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
    BrlSketch              sketch,
    int index
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
    BrlSketch              sketch
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
    BrlSketch              sketch,
    int index
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
    BrlSketch              sketch
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
    BrlSketch              sketch,
    int index
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
    BrlSketch              sketch
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
    BrlSketch              sketch,
    int index
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
    BrlSketch              sketch
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
    BrlSketch              sketch,
    int index
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
    BrlSketch              sketch,
    int index
) {
    if (sketch != nullptr) {
        Sketch* sIntern = CastSketch(sketch);
        assert(sIntern != nullptr);
        if (sIntern != nullptr)
            sIntern->DeleteSegment(index);
    }
}


const char* BrlSketchClassName(void) {
    return Sketch::ClassName();
}


int BrlSketchSegmentType
(
    BrlSketchSegment       segment
) {
    int ret = 0; // Null
    if (segment != nullptr) {
        Sketch::Segment* segIntern = CastSketchSegment(segment);
        assert(segIntern != nullptr);
        if (segIntern != nullptr)
            ret = static_cast<int>(segIntern->Type());
    }
    return ret;
}


BrlVector3D BrlSketchSegmentStartPoint
(
    BrlSketchSegment       segment
) {
    BrlVector3D ret = nullptr;
    if (segment != nullptr) {
        Sketch::Segment* segIntern = CastSketchSegment(segment);
        assert(segIntern != nullptr);
        if (segIntern != nullptr) {
            Vector2D pt = segIntern->StartPoint();
            ret = new Vector3DData(Vector3D(pt.coordinates[0], pt.coordinates[1], 0.));
        }
    }
    return ret;
}


BrlVector3D BrlSketchSegmentEndPoint
(
    BrlSketchSegment       segment
) {
    BrlVector3D ret = nullptr;
    if (segment != nullptr) {
        Sketch::Segment* segIntern = CastSketchSegment(segment);
        assert(segIntern != nullptr);
        if (segIntern != nullptr) {
            Vector2D pt = segIntern->EndPoint();
            ret = new Vector3DData(Vector3D(pt.coordinates[0], pt.coordinates[1], 0.));
        }
    }
    return ret;
}


// Helper to access private members of Sketch::Segment derived classes
struct SegmentMemoryLayout {
    void* vptr;
    struct rt_sketch_internal* m_sketch;
    void* m_segment;
};

static void* GetSpecificSegment(BRLCAD::Sketch::Segment* seg, struct rt_sketch_internal** sketch_out) {
    if (!seg) return nullptr;
    SegmentMemoryLayout* layout = reinterpret_cast<SegmentMemoryLayout*>(seg);
    if (sketch_out) *sketch_out = layout->m_sketch;
    return layout->m_segment;
}

bool BrlSketchSegmentReverse
(
    BrlSketchSegment       segment
) {
    bool ret = false;
    if (segment != nullptr) {
        Sketch::Segment* segIntern = CastSketchSegment(segment);
        assert(segIntern != nullptr);
        if (segIntern != nullptr) {
            struct rt_sketch_internal* sketch = nullptr;
            void* internal_seg = GetSpecificSegment(segIntern, &sketch);
            if (sketch && internal_seg) {
                for (int i = 0; i < sketch->curve.count; ++i) {
                    if (sketch->curve.segment[i] == internal_seg) {
                        ret = (sketch->curve.reverse[i] != 0);
                        break;
                    }
                }
            }
        }
    }
    return ret;
}


void BrlSketchSegmentSetReverse
(
    BrlSketchSegment       segment,
    bool                   reverse
) {
    if (segment != nullptr) {
        Sketch::Segment* segIntern = CastSketchSegment(segment);
        assert(segIntern != nullptr);
        if (segIntern != nullptr) {
            struct rt_sketch_internal* sketch = nullptr;
            void* internal_seg = GetSpecificSegment(segIntern, &sketch);
            if (sketch && internal_seg) {
                for (int i = 0; i < sketch->curve.count; ++i) {
                    if (sketch->curve.segment[i] == internal_seg) {
                        sketch->curve.reverse[i] = reverse ? 1 : 0;
                        break;
                    }
                }
            }
        }
    }
}


BrlSketchLine BrlCastToSketchLine
(
    BrlSketchSegment       segment
) {
    BrlSketchLine ret = nullptr;
    if (segment != nullptr) {
        Sketch::Segment* segIntern = CastSketchSegment(segment);
        assert(segIntern != nullptr);
        if (segIntern != nullptr && segIntern->Type() == Sketch::Segment::SegmentType::Line)
            ret = new SketchLineData(dynamic_cast<Sketch::Line*>(segIntern));
    }
    return ret;
}


BrlSketchCircularArc BrlCastToSketchCircularArc
(
    BrlSketchSegment       segment
) {
    BrlSketchCircularArc ret = nullptr;
    if (segment != nullptr) {
        Sketch::Segment* segIntern = CastSketchSegment(segment);
        assert(segIntern != nullptr);
        if (segIntern != nullptr && segIntern->Type() == Sketch::Segment::SegmentType::CircularArc)
            ret = new SketchCircularArcData(dynamic_cast<Sketch::CircularArc*>(segIntern));
    }
    return ret;
}


BrlSketchNurb BrlCastToSketchNurb
(
    BrlSketchSegment       segment
) {
    BrlSketchNurb ret = nullptr;
    if (segment != nullptr) {
        Sketch::Segment* segIntern = CastSketchSegment(segment);
        assert(segIntern != nullptr);
        if (segIntern != nullptr && segIntern->Type() == Sketch::Segment::SegmentType::Nurb)
            ret = new SketchNurbData(dynamic_cast<Sketch::Nurb*>(segIntern));
    }
    return ret;
}


BrlSketchBezier BrlCastToSketchBezier
(
    BrlSketchSegment       segment
) {
    BrlSketchBezier ret = nullptr;
    if (segment != nullptr) {
        Sketch::Segment* segIntern = CastSketchSegment(segment);
        assert(segIntern != nullptr);
        if (segIntern != nullptr && segIntern->Type() == Sketch::Segment::SegmentType::Bezier)
            ret = new SketchBezierData(dynamic_cast<Sketch::Bezier*>(segIntern));
    }
    return ret;
}


void BrlSketchLineSetStartPoint
(
    BrlSketchLine          line,
    double                 x,
    double                 y
) {
    if (line != nullptr) {
        Sketch::Line* lineIntern = CastSketchLine(line);
        assert(lineIntern != nullptr);
        if (lineIntern != nullptr) {
            Vector2D pt(x, y);
            lineIntern->SetStartPoint(pt);
        }
    }
}


void BrlSketchLineSetEndPoint
(
    BrlSketchLine          line,
    double                 x,
    double                 y
) {
    if (line != nullptr) {
        Sketch::Line* lineIntern = CastSketchLine(line);
        assert(lineIntern != nullptr);
        if (lineIntern != nullptr) {
            Vector2D pt(x, y);
            lineIntern->SetEndPoint(pt);
        }
    }
}


void BrlSketchCircularArcSetStartPoint
(
    BrlSketchCircularArc   arc,
    double                 x,
    double                 y
) {
    if (arc != nullptr) {
        Sketch::CircularArc* arcIntern = CastSketchCircularArc(arc);
        assert(arcIntern != nullptr);
        if (arcIntern != nullptr) {
            Vector2D pt(x, y);
            arcIntern->SetStartPoint(pt);
        }
    }
}


void BrlSketchCircularArcSetEndPoint
(
    BrlSketchCircularArc   arc,
    double                 x,
    double                 y
) {
    if (arc != nullptr) {
        Sketch::CircularArc* arcIntern = CastSketchCircularArc(arc);
        assert(arcIntern != nullptr);
        if (arcIntern != nullptr) {
            Vector2D pt(x, y);
            arcIntern->SetEndPoint(pt);
        }
    }
}


BrlVector3D BrlSketchCircularArcCenter
(
    BrlSketchCircularArc   arc
) {
    BrlVector3D ret = nullptr;
    if (arc != nullptr) {
        Sketch::CircularArc* arcIntern = CastSketchCircularArc(arc);
        assert(arcIntern != nullptr);
        if (arcIntern != nullptr)
            ret = new Vector3DData(arcIntern->Center());
    }
    return ret;
}


void BrlSketchCircularArcSetCenter
(
    BrlSketchCircularArc   arc,
    double                 x,
    double                 y
) {
    if (arc != nullptr) {
        Sketch::CircularArc* arcIntern = CastSketchCircularArc(arc);
        assert(arcIntern != nullptr);
        if (arcIntern != nullptr) {
            Vector2D pt(x, y);
            arcIntern->SetCenter(pt);
        }
    }
}


double BrlSketchCircularArcRadius
(
    BrlSketchCircularArc   arc
) {
    double ret = 0.0;
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
    BrlSketchCircularArc   arc,
    double                 radius
) {
    if (arc != nullptr) {
        Sketch::CircularArc* arcIntern = CastSketchCircularArc(arc);
        assert(arcIntern != nullptr);
        if (arcIntern != nullptr)
            arcIntern->SetRadius(radius);
    }
}


bool BrlSketchCircularArcCenterIsLeft
(
    BrlSketchCircularArc   arc
) {
    bool ret = false;
    if (arc != nullptr) {
        Sketch::CircularArc* arcIntern = CastSketchCircularArc(arc);
        assert(arcIntern != nullptr);
        if (arcIntern != nullptr)
            ret = arcIntern->CenterIsLeft();
    }
    return ret;
}


void BrlSketchCircularArcSetCenterIsLeft
(
    BrlSketchCircularArc   arc,
    bool                   isLeft
) {
    if (arc != nullptr) {
        Sketch::CircularArc* arcIntern = CastSketchCircularArc(arc);
        assert(arcIntern != nullptr);
        if (arcIntern != nullptr)
            arcIntern->SetCenterIsLeft(isLeft);
    }
}


bool BrlSketchCircularArcClockwiseOriented
(
    BrlSketchCircularArc   arc
) {
    bool ret = false;
    if (arc != nullptr) {
        Sketch::CircularArc* arcIntern = CastSketchCircularArc(arc);
        assert(arcIntern != nullptr);
        if (arcIntern != nullptr)
            ret = arcIntern->ClockwiseOriented();
    }
    return ret;
}


void BrlSketchCircularArcSetClockwiseOriented
(
    BrlSketchCircularArc   arc,
    bool                   clockwise
) {
    if (arc != nullptr) {
        Sketch::CircularArc* arcIntern = CastSketchCircularArc(arc);
        assert(arcIntern != nullptr);
        if (arcIntern != nullptr)
            arcIntern->SetClockwiseOriented(clockwise);
    }
}


void BrlSketchNurbSetStartPoint
(
    BrlSketchNurb          nurb,
    double                 x,
    double                 y
) {
    if (nurb != nullptr) {
        Sketch::Nurb* nurbIntern = CastSketchNurb(nurb);
        assert(nurbIntern != nullptr);
        if (nurbIntern != nullptr) {
            Vector2D pt(x, y);
            nurbIntern->SetStartPoint(pt);
        }
    }
}


void BrlSketchNurbSetEndPoint
(
    BrlSketchNurb          nurb,
    double                 x,
    double                 y
) {
    if (nurb != nullptr) {
        Sketch::Nurb* nurbIntern = CastSketchNurb(nurb);
        assert(nurbIntern != nullptr);
        if (nurbIntern != nullptr) {
            Vector2D pt(x, y);
            nurbIntern->SetEndPoint(pt);
        }
    }
}


int BrlSketchNurbOrder
(
    BrlSketchNurb          nurb
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


void BrlSketchNurbSetOrder
(
    BrlSketchNurb          nurb,
    int order
) {
    if (nurb != nullptr) {
        Sketch::Nurb* nurbIntern = CastSketchNurb(nurb);
        assert(nurbIntern != nullptr);
        if (nurbIntern != nullptr)
            nurbIntern->SetOrder(order);
    }
}


bool BrlSketchNurbIsRational
(
    BrlSketchNurb          nurb
) {
    bool ret = false;
    if (nurb != nullptr) {
        Sketch::Nurb* nurbIntern = CastSketchNurb(nurb);
        assert(nurbIntern != nullptr);
        if (nurbIntern != nullptr)
            ret = nurbIntern->IsRational();
    }
    return ret;
}


int BrlSketchNurbNumberOfKnots
(
    BrlSketchNurb          nurb
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
    BrlSketchNurb          nurb,
    int index
) {
    double ret = 0.0;
    if (nurb != nullptr) {
        Sketch::Nurb* nurbIntern = CastSketchNurb(nurb);
        assert(nurbIntern != nullptr);
        if (nurbIntern != nullptr)
            ret = nurbIntern->Knot(index);
    }
    return ret;
}


void BrlSketchNurbAddKnot
(
    BrlSketchNurb          nurb,
    double                 knot
) {
    if (nurb != nullptr) {
        Sketch::Nurb* nurbIntern = CastSketchNurb(nurb);
        assert(nurbIntern != nullptr);
        if (nurbIntern != nullptr)
            nurbIntern->AddKnot(knot);
    }
}


int BrlSketchNurbNumberOfControlPoints
(
    BrlSketchNurb          nurb
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


BrlVector3D BrlSketchNurbControlPoint
(
    BrlSketchNurb          nurb,
    int index
) {
    BrlVector3D ret = nullptr;
    if (nurb != nullptr) {
        Sketch::Nurb* nurbIntern = CastSketchNurb(nurb);
        assert(nurbIntern != nullptr);
        if (nurbIntern != nullptr) {
            Vector2D pt = nurbIntern->ControlPoint(index);
            ret = new Vector3DData(Vector3D(pt.coordinates[0], pt.coordinates[1], 0.));
        }
    }
    return ret;
}


double BrlSketchNurbControlPointWeight
(
    BrlSketchNurb          nurb,
    int index
) {
    double ret = 0.0;
    if (nurb != nullptr) {
        Sketch::Nurb* nurbIntern = CastSketchNurb(nurb);
        assert(nurbIntern != nullptr);
        if (nurbIntern != nullptr)
            ret = nurbIntern->ControlPointWeight(index);
    }
    return ret;
}


void BrlSketchNurbAddControlPoint
(
    BrlSketchNurb          nurb,
    double                 x,
    double                 y
) {
    if (nurb != nullptr) {
        Sketch::Nurb* nurbIntern = CastSketchNurb(nurb);
        assert(nurbIntern != nullptr);
        if (nurbIntern != nullptr) {
            Vector2D pt(x, y);
            nurbIntern->AddControlPoint(pt);
        }
    }
}


void BrlSketchNurbAddControlPointWeight
(
    BrlSketchNurb          nurb,
    double                 x,
    double                 y,
    double                 weight
) {
    if (nurb != nullptr) {
        Sketch::Nurb* nurbIntern = CastSketchNurb(nurb);
        assert(nurbIntern != nullptr);
        if (nurbIntern != nullptr) {
            Vector2D pt(x, y);
            nurbIntern->AddControlPointWeight(pt, weight);
        }
    }
}


void BrlSketchBezierSetStartPoint
(
    BrlSketchBezier        bezier,
    double                 x,
    double                 y
) {
    if (bezier != nullptr) {
        Sketch::Bezier* bezierIntern = CastSketchBezier(bezier);
        assert(bezierIntern != nullptr);
        if (bezierIntern != nullptr) {
            Vector2D pt(x, y);
            bezierIntern->SetStartPoint(pt);
        }
    }
}


void BrlSketchBezierSetEndPoint
(
    BrlSketchBezier        bezier,
    double                 x,
    double                 y
) {
    if (bezier != nullptr) {
        Sketch::Bezier* bezierIntern = CastSketchBezier(bezier);
        assert(bezierIntern != nullptr);
        if (bezierIntern != nullptr) {
            Vector2D pt(x, y);
            bezierIntern->SetEndPoint(pt);
        }
    }
}


int BrlSketchBezierDegree
(
    BrlSketchBezier        bezier
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


BrlVector3D BrlSketchBezierControlPoint
(
    BrlSketchBezier        bezier,
    int index
) {
    BrlVector3D ret = nullptr;
    if (bezier != nullptr) {
        Sketch::Bezier* bezierIntern = CastSketchBezier(bezier);
        assert(bezierIntern != nullptr);
        if (bezierIntern != nullptr) {
            Vector2D pt = bezierIntern->ControlPoint(index);
            ret = new Vector3DData(Vector3D(pt.coordinates[0], pt.coordinates[1], 0.));
        }
    }
    return ret;
}


void BrlSketchBezierAddControlPoint
(
    BrlSketchBezier        bezier,
    double                 x,
    double                 y
) {
    if (bezier != nullptr) {
        Sketch::Bezier* bezierIntern = CastSketchBezier(bezier);
        assert(bezierIntern != nullptr);
        if (bezierIntern != nullptr) {
            Vector2D pt(x, y);
            bezierIntern->AddControlPoint(pt);
        }
    }
}
