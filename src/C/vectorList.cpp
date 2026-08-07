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


bool BrlVectorListAppend
(
    BrlVectorList          vlist,
    BrlVectorListElement   element
) {
    bool ret = false;
    if (vlist != nullptr && element != nullptr) {
        VectorList* vl = CastVectorList(vlist);
        VectorList::Element* el = CastVectorListElement(element);
        
        assert(vl != nullptr && el != nullptr);
        
        if (vl != nullptr && el != nullptr)
            ret = vl->Append(*el);
    }
    return ret;
}


void BrlVectorListClear
(
    BrlVectorList          vlist
) {
    if (vlist != nullptr) {
        VectorList* vl = CastVectorList(vlist);

        assert(vl != nullptr);

        if (vl != nullptr)
            vl->Clear();
    }
}


int BrlVectorListElementType
(
    BrlVectorListElement   element
) {
    int ret = 0;
    if (element != nullptr) {
        VectorList::Element* el = CastVectorListElement(element);
        assert(el != nullptr);
        if (el != nullptr)
            ret = static_cast<int>(el->Type());
    }
    return ret;
}


BrlVectorListElement BrlNewVectorListPointDraw
(
    double                 x,
    double                 y,
    double                 z
) {
    Vector3D pt(x, y, z);
    return new VectorListElementData(new VectorList::PointDraw(pt));
}


BrlVectorListElement BrlNewVectorListPointSize
(
    double                 size
) {
    return new VectorListElementData(new VectorList::PointSize(size));
}


BrlVectorListElement BrlNewVectorListLineMove
(
    double                 x,
    double                 y,
    double                 z
) {
    Vector3D pt(x, y, z);
    return new VectorListElementData(new VectorList::LineMove(pt));
}


BrlVectorListElement BrlNewVectorListLineDraw
(
    double                 x,
    double                 y,
    double                 z
) {
    Vector3D pt(x, y, z);
    return new VectorListElementData(new VectorList::LineDraw(pt));
}


BrlVectorListElement BrlNewVectorListLineWidth
(
    double                 width
) {
    return new VectorListElementData(new VectorList::LineWidth(width));
}


BrlVectorListElement BrlNewVectorListTriangleStart
(
    double                 nx,
    double                 ny,
    double                 nz
) {
    Vector3D norm(nx, ny, nz);
    return new VectorListElementData(new VectorList::TriangleStart(norm));
}


BrlVectorListElement BrlNewVectorListTriangleMove
(
    double                 x,
    double                 y,
    double                 z
) {
    Vector3D pt(x, y, z);
    return new VectorListElementData(new VectorList::TriangleMove(pt));
}


BrlVectorListElement BrlNewVectorListTriangleDraw
(
    double                 x,
    double                 y,
    double                 z
) {
    Vector3D pt(x, y, z);
    return new VectorListElementData(new VectorList::TriangleDraw(pt));
}


BrlVectorListElement BrlNewVectorListTriangleEnd
(
    double                 x,
    double                 y,
    double                 z
) {
    Vector3D pt(x, y, z);
    return new VectorListElementData(new VectorList::TriangleEnd(pt));
}


BrlVectorListElement BrlNewVectorListTriangleVertexNormal
(
    double                 nx,
    double                 ny,
    double                 nz
) {
    Vector3D norm(nx, ny, nz);
    return new VectorListElementData(new VectorList::TriangleVertexNormal(norm));
}


BrlVectorListElement BrlNewVectorListPolygonStart
(
    double                 nx,
    double                 ny,
    double                 nz
) {
    Vector3D norm(nx, ny, nz);
    return new VectorListElementData(new VectorList::PolygonStart(norm));
}


BrlVectorListElement BrlNewVectorListPolygonMove
(
    double                 x,
    double                 y,
    double                 z
) {
    Vector3D pt(x, y, z);
    return new VectorListElementData(new VectorList::PolygonMove(pt));
}


BrlVectorListElement BrlNewVectorListPolygonDraw
(
    double                 x,
    double                 y,
    double                 z
) {
    Vector3D pt(x, y, z);
    return new VectorListElementData(new VectorList::PolygonDraw(pt));
}


BrlVectorListElement BrlNewVectorListPolygonEnd
(
    double                 x,
    double                 y,
    double                 z
) {
    Vector3D pt(x, y, z);
    return new VectorListElementData(new VectorList::PolygonEnd(pt));
}


BrlVectorListElement BrlNewVectorListPolygonVertexNormal
(
    double                 nx,
    double                 ny,
    double                 nz
) {
    Vector3D norm(nx, ny, nz);
    return new VectorListElementData(new VectorList::PolygonVertexNormal(norm));
}


BrlVectorListElement BrlNewVectorListDisplaySpace
(
    double                 x,
    double                 y,
    double                 z
) {
    Vector3D pt(x, y, z);
    return new VectorListElementData(new VectorList::DisplaySpace(pt));
}


BrlVectorListElement BrlNewVectorListModelSpace(void) {
    return new VectorListElementData(new VectorList::ModelSpace());
}
