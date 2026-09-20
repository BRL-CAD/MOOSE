/*                      V E C T O R L I S T . C P P
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
/** @file vectorList.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implementation for VectorList opaque wrapper
 */

#include <cassert>

#include <brlcad/VectorList.h>
#include <brlcad/C/vectorList.h>

#include "casts.h"


using namespace BRLCAD;


BrlVectorList BrlNewVectorList(void) {
    return new VectorListData(new VectorList());
}


BrlVectorListElementElementType BrlVectorListElementType
(
    BrlVectorListElement element
) {
    BrlVectorListElementElementType ret = BrlVectorListElementElementTypeModelSpace;

    if (element != nullptr) {
        VectorList::Element* el = CastVectorListElement(element);
        assert(el != nullptr);

        if (el != nullptr) {
            switch (el->Type()) {
            case VectorList::Element::ElementType::PointDraw:
                ret = BrlVectorListElementElementTypePointDraw;
                break;
            case VectorList::Element::ElementType::PointSize:
                ret = BrlVectorListElementElementTypePointSize;
                break;
            case VectorList::Element::ElementType::LineMove:
                ret = BrlVectorListElementElementTypeLineMove;
                break;
            case VectorList::Element::ElementType::LineDraw:
                ret = BrlVectorListElementElementTypeLineDraw;
                break;
            case VectorList::Element::ElementType::LineWidth:
                ret = BrlVectorListElementElementTypeLineWidth;
                break;
            case VectorList::Element::ElementType::TriangleStart:
                ret = BrlVectorListElementElementTypeTriangleStart;
                break;
            case VectorList::Element::ElementType::TriangleMove:
                ret = BrlVectorListElementElementTypeTriangleMove;
                break;
            case VectorList::Element::ElementType::TriangleDraw:
                ret = BrlVectorListElementElementTypeTriangleDraw;
                break;
            case VectorList::Element::ElementType::TriangleEnd:
                ret = BrlVectorListElementElementTypeTriangleEnd;
                break;
            case VectorList::Element::ElementType::TriangleVertexNormal:
                ret = BrlVectorListElementElementTypeTriangleVertexNormal;
                break;
            case VectorList::Element::ElementType::PolygonStart:
                ret = BrlVectorListElementElementTypePolygonStart;
                break;
            case VectorList::Element::ElementType::PolygonMove:
                ret = BrlVectorListElementElementTypePolygonMove;
                break;
            case VectorList::Element::ElementType::PolygonDraw:
                ret = BrlVectorListElementElementTypePolygonDraw;
                break;
            case VectorList::Element::ElementType::PolygonEnd:
                ret = BrlVectorListElementElementTypePolygonEnd;
                break;
            case VectorList::Element::ElementType::PolygonVertexNormal:
                ret = BrlVectorListElementElementTypePolygonVertexNormal;
                break;
            case VectorList::Element::ElementType::DisplaySpace:
                ret = BrlVectorListElementElementTypeDisplaySpace;
                break;
            case VectorList::Element::ElementType::ModelSpace:
                ret = BrlVectorListElementElementTypeModelSpace;
                break;
            }
        }
    }

    return ret;
}


static BrlVectorListElement DowncastVectorListElement
(
    VectorList::Element* el,
    bool                 owned = true
) {
    if (el == nullptr)
        return nullptr;

    switch (el->Type()) {
    case VectorList::Element::ElementType::PointDraw:
        return new VectorListPointDrawData(static_cast<VectorList::PointDraw*>(el));
    case VectorList::Element::ElementType::PointSize:
        return new VectorListPointSizeData(static_cast<VectorList::PointSize*>(el));
    case VectorList::Element::ElementType::LineMove:
        return new VectorListLineMoveData(static_cast<VectorList::LineMove*>(el));
    case VectorList::Element::ElementType::LineDraw:
        return new VectorListLineDrawData(static_cast<VectorList::LineDraw*>(el));
    case VectorList::Element::ElementType::LineWidth:
        return new VectorListLineWidthData(static_cast<VectorList::LineWidth*>(el));
    case VectorList::Element::ElementType::TriangleStart:
        return new VectorListTriangleStartData(static_cast<VectorList::TriangleStart*>(el));
    case VectorList::Element::ElementType::TriangleMove:
        return new VectorListTriangleMoveData(static_cast<VectorList::TriangleMove*>(el));
    case VectorList::Element::ElementType::TriangleDraw:
        return new VectorListTriangleDrawData(static_cast<VectorList::TriangleDraw*>(el));
    case VectorList::Element::ElementType::TriangleEnd:
        return new VectorListTriangleEndData(static_cast<VectorList::TriangleEnd*>(el));
    case VectorList::Element::ElementType::TriangleVertexNormal:
        return new VectorListTriangleVertexNormalData(static_cast<VectorList::TriangleVertexNormal*>(el));
    case VectorList::Element::ElementType::PolygonStart:
        return new VectorListPolygonStartData(static_cast<VectorList::PolygonStart*>(el));
    case VectorList::Element::ElementType::PolygonMove:
        return new VectorListPolygonMoveData(static_cast<VectorList::PolygonMove*>(el));
    case VectorList::Element::ElementType::PolygonDraw:
        return new VectorListPolygonDrawData(static_cast<VectorList::PolygonDraw*>(el));
    case VectorList::Element::ElementType::PolygonEnd:
        return new VectorListPolygonEndData(static_cast<VectorList::PolygonEnd*>(el));
    case VectorList::Element::ElementType::PolygonVertexNormal:
        return new VectorListPolygonVertexNormalData(static_cast<VectorList::PolygonVertexNormal*>(el));
    case VectorList::Element::ElementType::DisplaySpace:
        return new VectorListDisplaySpaceData(static_cast<VectorList::DisplaySpace*>(el));
    case VectorList::Element::ElementType::ModelSpace:
        return new VectorListModelSpaceData(static_cast<VectorList::ModelSpace*>(el));
    default:
        return new VectorListElementData(el);
    }
}


BrlVectorListPointDraw BrlNewVectorListPointDraw(void) {
    return new VectorListPointDrawData(new VectorList::PointDraw());
}


BrlVectorListPointDraw BrlNewVectorListPointDrawAsPoint
(
    double x, double y, double z
) {
    return new VectorListPointDrawData(new VectorList::PointDraw(Vector3D(x, y, z)));
}


BrlVector3D BrlVectorListPointDrawPoint
(
    BrlVectorListPointDraw pointDraw
) {
    BrlVector3D ret = nullptr;

    if (pointDraw != nullptr) {
        VectorList::PointDraw* pd = CastVectorListPointDraw(pointDraw);
        assert(pd != nullptr);

        if (pd != nullptr)
            ret = new Vector3DData(pd->Point());
    }

    return ret;
}


void BrlVectorListPointDrawSetPoint
(
    BrlVectorListPointDraw pointDraw,
    double x, double y, double z
) {
    if (pointDraw != nullptr) {
        VectorList::PointDraw* pd = CastVectorListPointDraw(pointDraw);
        assert(pd != nullptr);

        if (pd != nullptr)
            pd->SetPoint(Vector3D(x, y, z));
    }
}


BrlVectorListPointSize BrlNewVectorListPointSize(void) {
    return new VectorListPointSizeData(new VectorList::PointSize());
}


BrlVectorListPointSize BrlNewVectorListPointSizeAsSize
(
    double size
) {
    return new VectorListPointSizeData(new VectorList::PointSize(size));
}


double BrlVectorListPointSizeSize
(
    BrlVectorListPointSize pointSize
) {
    double ret = 0.0;

    if (pointSize != nullptr) {
        VectorList::PointSize* ps = CastVectorListPointSize(pointSize);
        assert(ps != nullptr);

        if (ps != nullptr)
            ret = ps->Size();
    }

    return ret;
}


void BrlVectorListPointSizeSetSize
(
    BrlVectorListPointSize pointSize,
    double size
) {
    if (pointSize != nullptr) {
        VectorList::PointSize* ps = CastVectorListPointSize(pointSize);
        assert(ps != nullptr);

        if (ps != nullptr)
            ps->SetSize(size);
    }
}


BrlVectorListLineMove BrlNewVectorListLineMove(void) {
    return new VectorListLineMoveData(new VectorList::LineMove());
}


BrlVectorListLineMove BrlNewVectorListLineMoveAsPoint
(
    double x, double y, double z
) {
    return new VectorListLineMoveData(new VectorList::LineMove(Vector3D(x, y, z)));
}


BrlVector3D BrlVectorListLineMovePoint
(
    BrlVectorListLineMove lineMove
) {
    BrlVector3D ret = nullptr;

    if (lineMove != nullptr) {
        VectorList::LineMove* lm = CastVectorListLineMove(lineMove);
        assert(lm != nullptr);

        if (lm != nullptr)
            ret = new Vector3DData(lm->Point());
    }

    return ret;
}


void BrlVectorListLineMoveSetPoint
(
    BrlVectorListLineMove lineMove,
    double x, double y, double z
) {
    if (lineMove != nullptr) {
        VectorList::LineMove* lm = CastVectorListLineMove(lineMove);
        assert(lm != nullptr);

        if (lm != nullptr)
            lm->SetPoint(Vector3D(x, y, z));
    }
}


BrlVectorListLineDraw BrlNewVectorListLineDraw(void) {
    return new VectorListLineDrawData(new VectorList::LineDraw());
}


BrlVectorListLineDraw BrlNewVectorListLineDrawAsPoint
(
    double x, double y, double z
) {
    return new VectorListLineDrawData(new VectorList::LineDraw(Vector3D(x, y, z)));
}


BrlVector3D BrlVectorListLineDrawPoint
(
    BrlVectorListLineDraw lineDraw
) {
    BrlVector3D ret = nullptr;

    if (lineDraw != nullptr) {
        VectorList::LineDraw* ld = CastVectorListLineDraw(lineDraw);
        assert(ld != nullptr);

        if (ld != nullptr)
            ret = new Vector3DData(ld->Point());
    }

    return ret;
}


void BrlVectorListLineDrawSetPoint
(
    BrlVectorListLineDraw lineDraw,
    double x, double y, double z
) {
    if (lineDraw != nullptr) {
        VectorList::LineDraw* ld = CastVectorListLineDraw(lineDraw);
        assert(ld != nullptr);

        if (ld != nullptr)
            ld->SetPoint(Vector3D(x, y, z));
    }
}


BrlVectorListLineWidth BrlNewVectorListLineWidth(void) {
    return new VectorListLineWidthData(new VectorList::LineWidth());
}


BrlVectorListLineWidth BrlNewVectorListLineWidthAsWidth
(
    double width
) {
    return new VectorListLineWidthData(new VectorList::LineWidth(width));
}


double BrlVectorListLineWidthWidth
(
    BrlVectorListLineWidth lineWidth
) {
    double ret = 0.0;

    if (lineWidth != nullptr) {
        VectorList::LineWidth* lw = CastVectorListLineWidth(lineWidth);
        assert(lw != nullptr);

        if (lw != nullptr)
            ret = lw->Width();
    }

    return ret;
}


void BrlVectorListLineWidthSetWidth
(
    BrlVectorListLineWidth lineWidth,
    double width
) {
    if (lineWidth != nullptr) {
        VectorList::LineWidth* lw = CastVectorListLineWidth(lineWidth);
        assert(lw != nullptr);

        if (lw != nullptr)
            lw->SetWidth(width);
    }
}


BrlVectorListTriangleStart BrlNewVectorListTriangleStart(void) {
    return new VectorListTriangleStartData(new VectorList::TriangleStart());
}


BrlVectorListTriangleStart BrlNewVectorListTriangleStartAsNormal
(
    double x, double y, double z
) {
    return new VectorListTriangleStartData(new VectorList::TriangleStart(Vector3D(x, y, z)));
}


BrlVector3D BrlVectorListTriangleStartNormal
(
    BrlVectorListTriangleStart triangleStart
) {
    BrlVector3D ret = nullptr;

    if (triangleStart != nullptr) {
        VectorList::TriangleStart* ts = CastVectorListTriangleStart(triangleStart);
        assert(ts != nullptr);

        if (ts != nullptr)
            ret = new Vector3DData(ts->Normal());
    }

    return ret;
}


void BrlVectorListTriangleStartSetNormal
(
    BrlVectorListTriangleStart triangleStart,
    double x, double y, double z
) {
    if (triangleStart != nullptr) {
        VectorList::TriangleStart* ts = CastVectorListTriangleStart(triangleStart);
        assert(ts != nullptr);

        if (ts != nullptr)
            ts->SetNormal(Vector3D(x, y, z));
    }
}


BrlVectorListTriangleMove BrlNewVectorListTriangleMove(void) {
    return new VectorListTriangleMoveData(new VectorList::TriangleMove());
}


BrlVectorListTriangleMove BrlNewVectorListTriangleMoveAsPoint
(
    double x, double y, double z
) {
    return new VectorListTriangleMoveData(new VectorList::TriangleMove(Vector3D(x, y, z)));
}


BrlVector3D BrlVectorListTriangleMovePoint
(
    BrlVectorListTriangleMove triangleMove
) {
    BrlVector3D ret = nullptr;

    if (triangleMove != nullptr) {
        VectorList::TriangleMove* tm = CastVectorListTriangleMove(triangleMove);
        assert(tm != nullptr);

        if (tm != nullptr)
            ret = new Vector3DData(tm->Point());
    }

    return ret;
}


void BrlVectorListTriangleMoveSetPoint
(
    BrlVectorListTriangleMove triangleMove,
    double x, double y, double z
) {
    if (triangleMove != nullptr) {
        VectorList::TriangleMove* tm = CastVectorListTriangleMove(triangleMove);
        assert(tm != nullptr);

        if (tm != nullptr)
            tm->SetPoint(Vector3D(x, y, z));
    }
}


BrlVectorListTriangleDraw BrlNewVectorListTriangleDraw(void) {
    return new VectorListTriangleDrawData(new VectorList::TriangleDraw());
}


BrlVectorListTriangleDraw BrlNewVectorListTriangleDrawAsPoint
(
    double x, double y, double z
) {
    return new VectorListTriangleDrawData(new VectorList::TriangleDraw(Vector3D(x, y, z)));
}


BrlVector3D BrlVectorListTriangleDrawPoint
(
    BrlVectorListTriangleDraw triangleDraw
) {
    BrlVector3D ret = nullptr;

    if (triangleDraw != nullptr) {
        VectorList::TriangleDraw* td = CastVectorListTriangleDraw(triangleDraw);
        assert(td != nullptr);

        if (td != nullptr)
            ret = new Vector3DData(td->Point());
    }

    return ret;
}


void BrlVectorListTriangleDrawSetPoint
(
    BrlVectorListTriangleDraw triangleDraw,
    double x, double y, double z
) {
    if (triangleDraw != nullptr) {
        VectorList::TriangleDraw* td = CastVectorListTriangleDraw(triangleDraw);
        assert(td != nullptr);

        if (td != nullptr)
            td->SetPoint(Vector3D(x, y, z));
    }
}


BrlVectorListTriangleEnd BrlNewVectorListTriangleEnd(void) {
    return new VectorListTriangleEndData(new VectorList::TriangleEnd());
}


BrlVectorListTriangleEnd BrlNewVectorListTriangleEndAsPoint
(
    double x, double y, double z
) {
    return new VectorListTriangleEndData(new VectorList::TriangleEnd(Vector3D(x, y, z)));
}


BrlVector3D BrlVectorListTriangleEndPoint
(
    BrlVectorListTriangleEnd triangleEnd
) {
    BrlVector3D ret = nullptr;

    if (triangleEnd != nullptr) {
        VectorList::TriangleEnd* te = CastVectorListTriangleEnd(triangleEnd);
        assert(te != nullptr);

        if (te != nullptr)
            ret = new Vector3DData(te->Point());
    }

    return ret;
}


void BrlVectorListTriangleEndSetPoint
(
    BrlVectorListTriangleEnd triangleEnd,
    double x, double y, double z
) {
    if (triangleEnd != nullptr) {
        VectorList::TriangleEnd* te = CastVectorListTriangleEnd(triangleEnd);
        assert(te != nullptr);

        if (te != nullptr)
            te->SetPoint(Vector3D(x, y, z));
    }
}


BrlVectorListTriangleVertexNormal BrlNewVectorListTriangleVertexNormal(void) {
    return new VectorListTriangleVertexNormalData(new VectorList::TriangleVertexNormal());
}


BrlVectorListTriangleVertexNormal BrlNewVectorListTriangleVertexNormalAsNormal
(
    double x, double y, double z
) {
    return new VectorListTriangleVertexNormalData(new VectorList::TriangleVertexNormal(Vector3D(x, y, z)));
}


BrlVector3D BrlVectorListTriangleVertexNormalNormal
(
    BrlVectorListTriangleVertexNormal triangleVertexNormal
) {
    BrlVector3D ret = nullptr;

    if (triangleVertexNormal != nullptr) {
        VectorList::TriangleVertexNormal* tvn = CastVectorListTriangleVertexNormal(triangleVertexNormal);
        assert(tvn != nullptr);

        if (tvn != nullptr)
            ret = new Vector3DData(tvn->Normal());
    }

    return ret;
}


void BrlVectorListTriangleVertexNormalSetNormal
(
    BrlVectorListTriangleVertexNormal triangleVertexNormal,
    double x, double y, double z
) {
    if (triangleVertexNormal != nullptr) {
        VectorList::TriangleVertexNormal* tvn = CastVectorListTriangleVertexNormal(triangleVertexNormal);
        assert(tvn != nullptr);

        if (tvn != nullptr)
            tvn->SetNormal(Vector3D(x, y, z));
    }
}


BrlVectorListPolygonStart BrlNewVectorListPolygonStart(void) {
    return new VectorListPolygonStartData(new VectorList::PolygonStart());
}


BrlVectorListPolygonStart BrlNewVectorListPolygonStartAsNormal
(
    double x, double y, double z
) {
    return new VectorListPolygonStartData(new VectorList::PolygonStart(Vector3D(x, y, z)));
}


BrlVector3D BrlVectorListPolygonStartNormal
(
    BrlVectorListPolygonStart polygonStart
) {
    BrlVector3D ret = nullptr;

    if (polygonStart != nullptr) {
        VectorList::PolygonStart* ps = CastVectorListPolygonStart(polygonStart);
        assert(ps != nullptr);

        if (ps != nullptr)
            ret = new Vector3DData(ps->Normal());
    }

    return ret;
}


void BrlVectorListPolygonStartSetNormal
(
    BrlVectorListPolygonStart polygonStart,
    double x, double y, double z
) {
    if (polygonStart != nullptr) {
        VectorList::PolygonStart* ps = CastVectorListPolygonStart(polygonStart);
        assert(ps != nullptr);

        if (ps != nullptr)
            ps->SetNormal(Vector3D(x, y, z));
    }
}


BrlVectorListPolygonMove BrlNewVectorListPolygonMove(void) {
    return new VectorListPolygonMoveData(new VectorList::PolygonMove());
}


BrlVectorListPolygonMove BrlNewVectorListPolygonMoveAsPoint
(
    double x, double y, double z
) {
    return new VectorListPolygonMoveData(new VectorList::PolygonMove(Vector3D(x, y, z)));
}


BrlVector3D BrlVectorListPolygonMovePoint
(
    BrlVectorListPolygonMove polygonMove
) {
    BrlVector3D ret = nullptr;

    if (polygonMove != nullptr) {
        VectorList::PolygonMove* pm = CastVectorListPolygonMove(polygonMove);
        assert(pm != nullptr);

        if (pm != nullptr)
            ret = new Vector3DData(pm->Point());
    }

    return ret;
}


void BrlVectorListPolygonMoveSetPoint
(
    BrlVectorListPolygonMove polygonMove,
    double x, double y, double z
) {
    if (polygonMove != nullptr) {
        VectorList::PolygonMove* pm = CastVectorListPolygonMove(polygonMove);
        assert(pm != nullptr);

        if (pm != nullptr)
            pm->SetPoint(Vector3D(x, y, z));
    }
}


BrlVectorListPolygonDraw BrlNewVectorListPolygonDraw(void) {
    return new VectorListPolygonDrawData(new VectorList::PolygonDraw());
}


BrlVectorListPolygonDraw BrlNewVectorListPolygonDrawAsPoint
(
    double x, double y, double z
) {
    return new VectorListPolygonDrawData(new VectorList::PolygonDraw(Vector3D(x, y, z)));
}


BrlVector3D BrlVectorListPolygonDrawPoint
(
    BrlVectorListPolygonDraw polygonDraw
) {
    BrlVector3D ret = nullptr;

    if (polygonDraw != nullptr) {
        VectorList::PolygonDraw* pd = CastVectorListPolygonDraw(polygonDraw);
        assert(pd != nullptr);

        if (pd != nullptr)
            ret = new Vector3DData(pd->Point());
    }

    return ret;
}


void BrlVectorListPolygonDrawSetPoint
(
    BrlVectorListPolygonDraw polygonDraw,
    double x, double y, double z
) {
    if (polygonDraw != nullptr) {
        VectorList::PolygonDraw* pd = CastVectorListPolygonDraw(polygonDraw);
        assert(pd != nullptr);

        if (pd != nullptr)
            pd->SetPoint(Vector3D(x, y, z));
    }
}


BrlVectorListPolygonEnd BrlNewVectorListPolygonEnd(void) {
    return new VectorListPolygonEndData(new VectorList::PolygonEnd());
}


BrlVectorListPolygonEnd BrlNewVectorListPolygonEndAsPoint
(
    double x, double y, double z
) {
    return new VectorListPolygonEndData(new VectorList::PolygonEnd(Vector3D(x, y, z)));
}


BrlVector3D BrlVectorListPolygonEndPoint
(
    BrlVectorListPolygonEnd polygonEnd
) {
    BrlVector3D ret = nullptr;

    if (polygonEnd != nullptr) {
        VectorList::PolygonEnd* pe = CastVectorListPolygonEnd(polygonEnd);
        assert(pe != nullptr);

        if (pe != nullptr)
            ret = new Vector3DData(pe->Point());
    }

    return ret;
}


void BrlVectorListPolygonEndSetPoint
(
    BrlVectorListPolygonEnd polygonEnd,
    double x, double y, double z
) {
    if (polygonEnd != nullptr) {
        VectorList::PolygonEnd* pe = CastVectorListPolygonEnd(polygonEnd);
        assert(pe != nullptr);

        if (pe != nullptr)
            pe->SetPoint(Vector3D(x, y, z));
    }
}


BrlVectorListPolygonVertexNormal BrlNewVectorListPolygonVertexNormal(void) {
    return new VectorListPolygonVertexNormalData(new VectorList::PolygonVertexNormal());
}


BrlVectorListPolygonVertexNormal BrlNewVectorListPolygonVertexNormalAsNormal
(
    double x, double y, double z
) {
    return new VectorListPolygonVertexNormalData(new VectorList::PolygonVertexNormal(Vector3D(x, y, z)));
}


BrlVector3D BrlVectorListPolygonVertexNormalNormal
(
    BrlVectorListPolygonVertexNormal polygonVertexNormal
) {
    BrlVector3D ret = nullptr;

    if (polygonVertexNormal != nullptr) {
        VectorList::PolygonVertexNormal* pvn = CastVectorListPolygonVertexNormal(polygonVertexNormal);
        assert(pvn != nullptr);

        if (pvn != nullptr)
            ret = new Vector3DData(pvn->Normal());
    }

    return ret;
}


void BrlVectorListPolygonVertexNormalSetNormal
(
    BrlVectorListPolygonVertexNormal polygonVertexNormal,
    double x, double y, double z
) {
    if (polygonVertexNormal != nullptr) {
        VectorList::PolygonVertexNormal* pvn = CastVectorListPolygonVertexNormal(polygonVertexNormal);
        assert(pvn != nullptr);

        if (pvn != nullptr)
            pvn->SetNormal(Vector3D(x, y, z));
    }
}


BrlVectorListDisplaySpace BrlNewVectorListDisplaySpace(void) {
    return new VectorListDisplaySpaceData(new VectorList::DisplaySpace());
}


BrlVectorListDisplaySpace BrlNewVectorListDisplaySpaceAsReferencePoint
(
    double x, double y, double z
) {
    return new VectorListDisplaySpaceData(new VectorList::DisplaySpace(Vector3D(x, y, z)));
}


BrlVector3D BrlVectorListDisplaySpaceReferencePoint
(
    BrlVectorListDisplaySpace displaySpace
) {
    BrlVector3D ret = nullptr;

    if (displaySpace != nullptr) {
        VectorList::DisplaySpace* ds = CastVectorListDisplaySpace(displaySpace);
        assert(ds != nullptr);

        if (ds != nullptr)
            ret = new Vector3DData(ds->ReferencePoint());
    }

    return ret;
}


void BrlVectorListDisplaySpaceSetReferencePoint
(
    BrlVectorListDisplaySpace displaySpace,
    double x, double y, double z
) {
    if (displaySpace != nullptr) {
        VectorList::DisplaySpace* ds = CastVectorListDisplaySpace(displaySpace);
        assert(ds != nullptr);

        if (ds != nullptr)
            ds->SetReferencePoint(Vector3D(x, y, z));
    }
}


BrlVectorListModelSpace BrlNewVectorListModelSpace(void) {
    return new VectorListModelSpaceData(new VectorList::ModelSpace());
}


void BrlVectorListIterate
(
    BrlVectorList         vlist,
    BrlVectorListCallback callback,
    void*                 userdata
) {
    if (vlist != nullptr) {
        VectorList* vl = CastVectorList(vlist);
        assert(vl != nullptr);

        if (vl != nullptr && callback != nullptr) {
            vl->Iterate([callback, userdata](VectorList::Element* el) -> bool {
                if (el != nullptr) {
                    BrlVectorListElement wrapped = DowncastVectorListElement(el);
                    int res = callback(wrapped, userdata);
                    if (res == 0)
                        return false;
                }
                return true;
            });
        }
    }
}


int BrlVectorListAppend
(
    BrlVectorList        vlist,
    BrlVectorListElement element
) {
    int ret = 0;

    if ((vlist != nullptr) && (element != nullptr)) {
        VectorList*          vl = CastVectorList(vlist);
        VectorList::Element* el = CastVectorListElement(element);
        assert(vl != nullptr);
        assert(el != nullptr);

        if ((vl != nullptr) && (el != nullptr)) {
            vl->Append(*el);
            ret = 1;
        }
    }

    return ret;
}


void BrlVectorListClear
(
    BrlVectorList vlist
) {
    if (vlist != nullptr) {
        VectorList* vl = CastVectorList(vlist);
        assert(vl != nullptr);

        if (vl != nullptr)
            vl->Clear();
    }
}
