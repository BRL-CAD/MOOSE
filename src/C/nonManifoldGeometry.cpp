/*                          N O N M A N I F O L D G E O M E T R Y . C P P
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
/** @file nonManifoldGeometry.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements a handle and functions for NonManifoldGeometry solid handling
 */

#include <cassert>

#include <brlcad/Database/NonManifoldGeometry.h>

#include <brlcad/C/nonManifoldGeometry.h>

#include "BrlData.h"

#include "casts.h"


using namespace BRLCAD;


BrlNonManifoldGeometry BrlNewNonManifoldGeometry(void) {
    return new NonManifoldGeometryData(new NonManifoldGeometry());
}


void BrlNonManifoldGeometryTriangulate
(
    BrlNonManifoldGeometry nonManifoldGeometry
) {
    if (nonManifoldGeometry != nullptr) {
        NonManifoldGeometry* nmg = CastNonManifoldGeometry(nonManifoldGeometry);

        assert(nmg != nullptr);

        if (nmg != nullptr)
            nmg->Triangulate();
    }
}


const char* BrlNonManifoldGeometryClassName(void) {
    return NonManifoldGeometry::ClassName();
}


BrlNonManifoldGeometryRegionIterator BrlNonManifoldGeometryRegions
(
    BrlNonManifoldGeometry nonManifoldGeometry
) {
    BrlNonManifoldGeometryRegionIterator ret = nullptr;

    if (nonManifoldGeometry != nullptr) {
        NonManifoldGeometry* nmg = CastNonManifoldGeometry(nonManifoldGeometry);
        assert(nmg != nullptr);
        if (nmg != nullptr)
            ret = new NonManifoldGeometryRegionIteratorData(nmg->Regions());
    }

    return ret;
}


void BrlNonManifoldGeometryTriangulateShell
(
    BrlNonManifoldGeometry nonManifoldGeometry,
    BrlNonManifoldGeometryShell shell
) {
    if (nonManifoldGeometry != nullptr && shell != nullptr) {
        NonManifoldGeometry* nmg = CastNonManifoldGeometry(nonManifoldGeometry);
        NonManifoldGeometry::Shell* s = CastNonManifoldGeometryShell(shell);
        assert(nmg != nullptr);
        assert(s != nullptr);
        if (nmg != nullptr && s != nullptr)
            nmg->Triangulate(*s);
    }
}


void BrlNonManifoldGeometryTriangulateFace
(
    BrlNonManifoldGeometry nonManifoldGeometry,
    BrlNonManifoldGeometryFace face
) {
    if (nonManifoldGeometry != nullptr && face != nullptr) {
        NonManifoldGeometry* nmg = CastNonManifoldGeometry(nonManifoldGeometry);
        NonManifoldGeometry::Face* f = CastNonManifoldGeometryFace(face);
        assert(nmg != nullptr);
        assert(f != nullptr);
        if (nmg != nullptr && f != nullptr)
            nmg->Triangulate(*f);
    }
}


void BrlNonManifoldGeometryRegionIteratorGotoFirstRegion
(
    BrlNonManifoldGeometryRegionIterator iterator
) {
    if (iterator != nullptr) {
        NonManifoldGeometry::RegionIterator* ri = CastNonManifoldGeometryRegionIterator(iterator);
        assert(ri != nullptr);
        if (ri != nullptr)
            ri->GotoFirstRegion();
    }
}


BrlNonManifoldGeometryRegionIterator BrlNonManifoldGeometryRegionIteratorNextRegion
(
    BrlNonManifoldGeometryRegionIterator iterator
) {
    BrlNonManifoldGeometryRegionIterator ret = nullptr;
    if (iterator != nullptr) {
        NonManifoldGeometry::RegionIterator* ri = CastNonManifoldGeometryRegionIterator(iterator);
        assert(ri != nullptr);
        if (ri != nullptr) {
            ri->operator++();
            ret = iterator;
        }
    }
    return ret;
}


BrlNonManifoldGeometryRegion BrlNonManifoldGeometryRegionIteratorCurrentRegion
(
    BrlNonManifoldGeometryRegionIterator iterator
) {
    BrlNonManifoldGeometryRegion ret = nullptr;
    if (iterator != nullptr) {
        NonManifoldGeometry::RegionIterator* ri = CastNonManifoldGeometryRegionIterator(iterator);
        assert(ri != nullptr);
        if (ri != nullptr)
            ret = new NonManifoldGeometryRegionData(ri->CurrentRegion());
    }
    return ret;
}


void BrlNonManifoldGeometryRegionGotoFirstShell
(
    BrlNonManifoldGeometryRegion region
) {
    if (region != nullptr) {
        NonManifoldGeometry::Region* r = CastNonManifoldGeometryRegion(region);
        assert(r != nullptr);
        if (r != nullptr)
            r->GotoFirstShell();
    }
}


BrlNonManifoldGeometryRegion BrlNonManifoldGeometryRegionNextShell
(
    BrlNonManifoldGeometryRegion region
) {
    BrlNonManifoldGeometryRegion ret = nullptr;
    if (region != nullptr) {
        NonManifoldGeometry::Region* r = CastNonManifoldGeometryRegion(region);
        assert(r != nullptr);
        if (r != nullptr) {
            r->operator++();
            ret = region;
        }
    }
    return ret;
}


BrlNonManifoldGeometryShell BrlNonManifoldGeometryRegionCurrentShell
(
    BrlNonManifoldGeometryRegion region
) {
    BrlNonManifoldGeometryShell ret = nullptr;
    if (region != nullptr) {
        NonManifoldGeometry::Region* r = CastNonManifoldGeometryRegion(region);
        assert(r != nullptr);
        if (r != nullptr)
            ret = new NonManifoldGeometryShellData(r->CurrentShell());
    }
    return ret;
}


void BrlNonManifoldGeometryShellGotoFirstFace
(
    BrlNonManifoldGeometryShell shell
) {
    if (shell != nullptr) {
        NonManifoldGeometry::Shell* s = CastNonManifoldGeometryShell(shell);
        assert(s != nullptr);
        if (s != nullptr)
            s->GotoFirstFace();
    }
}


BrlNonManifoldGeometryShell BrlNonManifoldGeometryShellNextFace
(
    BrlNonManifoldGeometryShell shell
) {
    BrlNonManifoldGeometryShell ret = nullptr;
    if (shell != nullptr) {
        NonManifoldGeometry::Shell* s = CastNonManifoldGeometryShell(shell);
        assert(s != nullptr);
        if (s != nullptr) {
            s->GotoNextFace();
            ret = shell;
        }
    }
    return ret;
}


BrlNonManifoldGeometryFace BrlNonManifoldGeometryShellCurrentFace
(
    BrlNonManifoldGeometryShell shell
) {
    BrlNonManifoldGeometryFace ret = nullptr;
    if (shell != nullptr) {
        NonManifoldGeometry::Shell* s = CastNonManifoldGeometryShell(shell);
        assert(s != nullptr);
        if (s != nullptr)
            ret = new NonManifoldGeometryFaceData(s->CurrentFace());
    }
    return ret;
}


void BrlNonManifoldGeometryShellGotoFirstLoop
(
    BrlNonManifoldGeometryShell shell
) {
    if (shell != nullptr) {
        NonManifoldGeometry::Shell* s = CastNonManifoldGeometryShell(shell);
        assert(s != nullptr);
        if (s != nullptr)
            s->GotoFirstLoop();
    }
}


BrlNonManifoldGeometryShell BrlNonManifoldGeometryShellNextLoop
(
    BrlNonManifoldGeometryShell shell
) {
    BrlNonManifoldGeometryShell ret = nullptr;
    if (shell != nullptr) {
        NonManifoldGeometry::Shell* s = CastNonManifoldGeometryShell(shell);
        assert(s != nullptr);
        if (s != nullptr) {
            s->GotoNextLoop();
            ret = shell;
        }
    }
    return ret;
}


BrlNonManifoldGeometryLoop BrlNonManifoldGeometryShellCurrentLoop
(
    BrlNonManifoldGeometryShell shell
) {
    BrlNonManifoldGeometryLoop ret = nullptr;
    if (shell != nullptr) {
        NonManifoldGeometry::Shell* s = CastNonManifoldGeometryShell(shell);
        assert(s != nullptr);
        if (s != nullptr)
            ret = new NonManifoldGeometryLoopData(s->CurrentLoop());
    }
    return ret;
}


void BrlNonManifoldGeometryShellGotoFirstEdge
(
    BrlNonManifoldGeometryShell shell
) {
    if (shell != nullptr) {
        NonManifoldGeometry::Shell* s = CastNonManifoldGeometryShell(shell);
        assert(s != nullptr);
        if (s != nullptr)
            s->GotoFirstEdge();
    }
}


BrlNonManifoldGeometryShell BrlNonManifoldGeometryShellNextEdge
(
    BrlNonManifoldGeometryShell shell
) {
    BrlNonManifoldGeometryShell ret = nullptr;
    if (shell != nullptr) {
        NonManifoldGeometry::Shell* s = CastNonManifoldGeometryShell(shell);
        assert(s != nullptr);
        if (s != nullptr) {
            s->GotoNextEdge();
            ret = shell;
        }
    }
    return ret;
}


BrlNonManifoldGeometryEdge BrlNonManifoldGeometryShellCurrentEdge
(
    BrlNonManifoldGeometryShell shell
) {
    BrlNonManifoldGeometryEdge ret = nullptr;
    if (shell != nullptr) {
        NonManifoldGeometry::Shell* s = CastNonManifoldGeometryShell(shell);
        assert(s != nullptr);
        if (s != nullptr)
            ret = new NonManifoldGeometryEdgeData(s->CurrentEdge());
    }
    return ret;
}


void BrlNonManifoldGeometryShellGotoFirstVertex
(
    BrlNonManifoldGeometryShell shell
) {
    if (shell != nullptr) {
        NonManifoldGeometry::Shell* s = CastNonManifoldGeometryShell(shell);
        assert(s != nullptr);
        if (s != nullptr)
            s->GotoFirstVertex();
    }
}


BrlNonManifoldGeometryShell BrlNonManifoldGeometryShellNextVertex
(
    BrlNonManifoldGeometryShell shell
) {
    BrlNonManifoldGeometryShell ret = nullptr;
    if (shell != nullptr) {
        NonManifoldGeometry::Shell* s = CastNonManifoldGeometryShell(shell);
        assert(s != nullptr);
        if (s != nullptr) {
            s->GotoNextVertex();
            ret = shell;
        }
    }
    return ret;
}


BrlNonManifoldGeometryVertex BrlNonManifoldGeometryShellCurrentVertex
(
    BrlNonManifoldGeometryShell shell
) {
    BrlNonManifoldGeometryVertex ret = nullptr;
    if (shell != nullptr) {
        NonManifoldGeometry::Shell* s = CastNonManifoldGeometryShell(shell);
        assert(s != nullptr);
        if (s != nullptr)
            ret = new NonManifoldGeometryVertexData(s->CurrentVertex());
    }
    return ret;
}


void BrlNonManifoldGeometryFaceGotoFirstLoop
(
    BrlNonManifoldGeometryFace face
) {
    if (face != nullptr) {
        NonManifoldGeometry::Face* f = CastNonManifoldGeometryFace(face);
        assert(f != nullptr);
        if (f != nullptr)
            f->GotoFirstLoop();
    }
}


BrlNonManifoldGeometryFace BrlNonManifoldGeometryFaceNextLoop
(
    BrlNonManifoldGeometryFace face
) {
    BrlNonManifoldGeometryFace ret = nullptr;
    if (face != nullptr) {
        NonManifoldGeometry::Face* f = CastNonManifoldGeometryFace(face);
        assert(f != nullptr);
        if (f != nullptr) {
            f->operator++();
            ret = face;
        }
    }
    return ret;
}


BrlNonManifoldGeometryLoop BrlNonManifoldGeometryFaceCurrentLoop
(
    BrlNonManifoldGeometryFace face
) {
    BrlNonManifoldGeometryLoop ret = nullptr;
    if (face != nullptr) {
        NonManifoldGeometry::Face* f = CastNonManifoldGeometryFace(face);
        assert(f != nullptr);
        if (f != nullptr)
            ret = new NonManifoldGeometryLoopData(f->CurrentLoop());
    }
    return ret;
}


int BrlNonManifoldGeometryLoopIsHole
(
    BrlNonManifoldGeometryLoop loop
) {
    int ret = 0;
    if (loop != nullptr) {
        NonManifoldGeometry::Loop* l = CastNonManifoldGeometryLoop(loop);
        assert(l != nullptr);
        if (l != nullptr)
            ret = l->IsHole() ? 1 : 0;
    }
    return ret;
}


void BrlNonManifoldGeometryLoopGotoFirstEdge
(
    BrlNonManifoldGeometryLoop loop
) {
    if (loop != nullptr) {
        NonManifoldGeometry::Loop* l = CastNonManifoldGeometryLoop(loop);
        assert(l != nullptr);
        if (l != nullptr)
            l->GotoFirstEdge();
    }
}


BrlNonManifoldGeometryLoop BrlNonManifoldGeometryLoopNextEdge
(
    BrlNonManifoldGeometryLoop loop
) {
    BrlNonManifoldGeometryLoop ret = nullptr;
    if (loop != nullptr) {
        NonManifoldGeometry::Loop* l = CastNonManifoldGeometryLoop(loop);
        assert(l != nullptr);
        if (l != nullptr) {
            l->operator++();
            ret = loop;
        }
    }
    return ret;
}


BrlNonManifoldGeometryEdge BrlNonManifoldGeometryLoopCurrentEdge
(
    BrlNonManifoldGeometryLoop loop
) {
    BrlNonManifoldGeometryEdge ret = nullptr;
    if (loop != nullptr) {
        NonManifoldGeometry::Loop* l = CastNonManifoldGeometryLoop(loop);
        assert(l != nullptr);
        if (l != nullptr)
            ret = new NonManifoldGeometryEdgeData(l->CurrentEdge());
    }
    return ret;
}


BrlNonManifoldGeometryVertex BrlNonManifoldGeometryEdgeForwardVertex
(
    BrlNonManifoldGeometryEdge edge
) {
    BrlNonManifoldGeometryVertex ret = nullptr;
    if (edge != nullptr) {
        NonManifoldGeometry::Edge* e = CastNonManifoldGeometryEdge(edge);
        assert(e != nullptr);
        if (e != nullptr)
            ret = new NonManifoldGeometryVertexData(e->ForwardVertex());
    }
    return ret;
}


BrlNonManifoldGeometryVertex BrlNonManifoldGeometryEdgeBackwardVertex
(
    BrlNonManifoldGeometryEdge edge
) {
    BrlNonManifoldGeometryVertex ret = nullptr;
    if (edge != nullptr) {
        NonManifoldGeometry::Edge* e = CastNonManifoldGeometryEdge(edge);
        assert(e != nullptr);
        if (e != nullptr)
            ret = new NonManifoldGeometryVertexData(e->BackwardVertex());
    }
    return ret;
}


BrlVector3D BrlNonManifoldGeometryVertexPoint
(
    BrlNonManifoldGeometryVertex vertex
) {
    BrlVector3D ret = nullptr;
    if (vertex != nullptr) {
        NonManifoldGeometry::Vertex* v = CastNonManifoldGeometryVertex(vertex);
        assert(v != nullptr);
        if (v != nullptr)
            ret = new Vector3DData(v->Point());
    }
    return ret;
}
