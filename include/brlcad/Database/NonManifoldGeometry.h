/*            N O N M A N I F O L D G E O M E T R Y . H
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
/** @file NonManifoldGeometry.h
 *
 *  BRL-CAD core C++ interface:
 *      non-manifold geometry (ID_NMG) database object declaration
 */

#ifndef BRLCAD_NONMANIFOLDGEOMETRY_INCLUDED
#define BRLCAD_NONMANIFOLDGEOMETRY_INCLUDED

#include <brlcad/vector.h>
#include <brlcad/Database/Object.h>


struct vertexuse;
struct edgeuse;
struct loopuse;
struct faceuse;
struct shell;
struct nmgregion;
struct model;


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT NonManifoldGeometry : public Object {
    public:
        NonManifoldGeometry(void);
        NonManifoldGeometry(const NonManifoldGeometry& original);
        virtual ~NonManifoldGeometry(void);

        const NonManifoldGeometry& operator=(const NonManifoldGeometry& original);

        // the classes for the subobjects are all non-changing
        // otherwise we would need every subclass in two kinds: constant and mutable
        // the manipulation routines are all in the main class NonManifoldGeometry
        class Edge;
        class Loop;
        class Face;
        class Shell;
        class Region;
        class RegionIterator;

        class BRLCAD_MOOSE_EXPORT Vertex {
        public:
            Vertex(const Vertex& original) : m_vertex(original.m_vertex) {}

            ~Vertex(void) {}

            const Vertex& operator=(const Vertex& original) {
                m_vertex = original.m_vertex;

                return *this;
            }

                          operator const void*(void) const {
                return m_vertex;
            }

            // here we go
            Vector3D      Point(void) const;

        private:
            const vertexuse* m_vertex;

            friend class Edge;
            friend class Shell;

            Vertex(void) : m_vertex(nullptr) {}
        };


        class BRLCAD_MOOSE_EXPORT Edge {
        public:
            Edge(const Edge& original) : m_edge(original.m_edge) {}

            ~Edge(void) {}

            const Edge& operator=(const Edge& original) {
                m_edge = original.m_edge;

                return *this;
            }

                        operator const void*(void) const {
                return m_edge;
            }

            // here we go
            Vertex      ForwardVertex(void) const;
            Vertex      BackwardVertex(void) const;

        private:
            const edgeuse* m_edge;

            friend class Loop;
            friend class Shell;

            Edge(void) : m_edge(nullptr) {}
        };


        class BRLCAD_MOOSE_EXPORT Loop {
        public:
            Loop(const Loop& original) : m_loop(original.m_loop), m_currentEdge(original.m_currentEdge) {}

            ~Loop(void) {}

            const Loop& operator=(const Loop& original) {
                m_loop        = original.m_loop;
                m_currentEdge = original.m_currentEdge;

                return *this;
            }

                        operator const void*(void) const {
                return m_loop;
            }

            // here we go
            bool        IsHole(void) const;

            // it's an iterator
            void        GotoFirstEdge(void);
            const Loop& operator++(void);
            Edge        CurrentEdge(void) const;

        private:
            const loopuse* m_loop;
            const edgeuse* m_currentEdge;

            friend class Face;
            friend class Shell;

            Loop(void) : m_loop(nullptr), m_currentEdge(nullptr) {}
        };


        class BRLCAD_MOOSE_EXPORT Face {
        public:
            Face(const Face& original) : m_face(original.m_face), m_currentLoop(original.m_currentLoop) {}

            ~Face(void) {}

            const Face& operator=(const Face& original) {
                m_face        = original.m_face;
                m_currentLoop = original.m_currentLoop;

                return *this;
            }

                        operator const void*(void) const {
                return m_face;
            }

            // it's an iterator
            void        GotoFirstLoop(void);
            const Face& operator++(void);
            Loop        CurrentLoop(void) const;

        private:
            const faceuse* m_face;
            const loopuse* m_currentLoop;

            friend class Shell;
            friend class NonManifoldGeometry;

            Face(void) : m_face(nullptr), m_currentLoop(nullptr) {}
        };


        class BRLCAD_MOOSE_EXPORT Shell {
        public:
            Shell(const Shell& original) : m_shell(original.m_shell),
                                                   m_currentFace(original.m_currentFace),
                                                   m_currentLoop(original.m_currentLoop),
                                                   m_currentEdge(original.m_currentEdge),
                                                   m_currentVertex(original.m_currentVertex) {}

            ~Shell(void) {}

            const Shell& operator=(const Shell& original) {
                m_shell         = original.m_shell;
                m_currentFace   = original.m_currentFace;
                m_currentLoop   = original.m_currentLoop;
                m_currentEdge   = original.m_currentEdge;
                m_currentVertex = original.m_currentVertex;

                return *this;
            }

                        operator const void*(void) const {
                return m_shell;
            }

            // in fact it's a multiple iterator
            void         GotoFirstFace(void);
            const Shell& GotoNextFace(void);
            Face         CurrentFace(void) const;

            void         GotoFirstLoop(void);
            const Shell& GotoNextLoop(void);
            Loop         CurrentLoop(void) const;

            void         GotoFirstEdge(void);
            const Shell& GotoNextEdge(void);
            Edge         CurrentEdge(void) const;

            void         GotoFirstVertex(void);
            const Shell& GotoNextVertex(void);
            Vertex       CurrentVertex(void) const;

        private:
            const shell*     m_shell;
            const faceuse*   m_currentFace;
            const loopuse*   m_currentLoop;
            const edgeuse*   m_currentEdge;
            const vertexuse* m_currentVertex;

            friend class Region;
            friend class NonManifoldGeometry;

            Shell(void) : m_shell(nullptr), m_currentFace(nullptr), m_currentLoop(nullptr), m_currentEdge(nullptr), m_currentVertex(nullptr) {}
        };


        class BRLCAD_MOOSE_EXPORT Region {
        public:
            Region(const Region& original) : m_region(original.m_region), m_currentShell(original.m_currentShell) {}

            ~Region(void) {}

            const Region& operator=(const Region& original) {
                m_region       = original.m_region;
                m_currentShell = original.m_currentShell;

                return *this;
            }

                        operator const void*(void) const {
                return m_region;
            }

            // it's an iterator
            void          GotoFirstShell(void);
            const Region& operator++(void);
            Shell         CurrentShell(void) const;

        private:
            const nmgregion* m_region;
            const shell*     m_currentShell;

            friend class RegionIterator;

            Region(void) : m_region(nullptr), m_currentShell(nullptr) {}
        };


        // decuples the iteration over the regions from NonManifoldGeometry
        // i.e. a const NonManifoldGeometry can be used to iterate over the structure
        class BRLCAD_MOOSE_EXPORT RegionIterator {
        public:
            RegionIterator(const RegionIterator& original) : m_model(original.m_model), m_currentRegion(original.m_currentRegion) {}

            ~RegionIterator(void) {}

            const RegionIterator& operator=(const RegionIterator& original) {
                m_model         = original.m_model;
                m_currentRegion = original.m_currentRegion;

                return *this;
            }

            // it's an iterator
            void                  GotoFirstRegion(void);
            const RegionIterator& operator++(void);
            Region                CurrentRegion(void) const;

        private:
            const model*     m_model;
            const nmgregion* m_currentRegion;

            friend class NonManifoldGeometry;

            RegionIterator(void) : m_model(nullptr), m_currentRegion(nullptr) {}
        };


        // Basic Operations
        /*
        Region       MakeRegion(void); // 0

        Shell        MakeShell(Region, Vector3D& firstVertex); // nmg_msv(region)

        /// creates a new edge by connecting an existing vertex and reusing onother one
        Edge         MakeEdgeVertex(Vetrex& vertexAlreadyInShell,
                                    Vetex&  vertexToAdd); // mmg_me(vertex, vertex, shell)
        /// creates a new edge by connecting an existing vertex with a new one
        Edge         MakeEdgeVertex(Vetrex& vertexAlreadyInShell,
                                    Vector3D&  vertexToAdd); // mmg_me(vertex, vertex, shell)

        /// creates a loop existing of one vertex by reusing one
        Loop         MakeVertexLoop(Vetex& vertexToAdd);
        /// creates a loop existing of one vertex by adding a new one
        Loop         MakeVertexLoop(Vector3D& vertexToAdd);

        /// creates a loop by connecting two vertices
        Edge         MakeEdgeLoop(Vetrex& firstVertexToConnect,
                                  Vertex& secondVertexToConnect);

        /// creates a face by using a loop as its boundary
        /// after this the loop isn't more a 1D subset of the manifold
        Face   MakeFaceKillLoop(Loop& loopToConvert);
        */

        // Extended Operations
        /*
        Vertex       SplitEdgeMakeVertex(EdgeUse&  edgeToSplit,
                                         Vetex&    vertexToInsert);
        Vertex       SplitEdgeMakeVertex(EdgeUse&  edgeToSplit,
                                         Vector3D& vertexToInsert);

        /// creates a new face from an existing one by dividing it with an additional edge
        Edge         MakeEdgeFace(Vetrex& firstVertexToConnect,
                              Vertex& secondVertexToConnect);
        /// connects two faces to form a new common one by removing a common edge
        Face         KillEdgeFace(Edge& edgeToRemove);

        /// creates a new loop from an existing one by removing a "double-edge"
        Loop         KillEdgeMakeLoop(Edge& edgeToRemove);
        /// joins two loops by creating an edge between a point of each loop
        Loop         MakeEdgeKillLoop(Vetrex& firstVertexToConnect,
                                      Vertex& secondVertexToConnect);
        */
        void         Triangulate(void);
        void         Triangulate(Shell& shellToTrinagulate);
        void         Triangulate(Face& faceToTrinagulate);

        // Destruction Operations
        /*
        void         KillRegion(Region& regionToRemove);
        void         KillShell(Shell& shellToRemove);

        /// if the vertex is unconnected: the objects (vertex, loop with itself, ...) are removed
        /// if the vertex is connected with one other by an edge: the edge well be removed too
        /// if the vertex is connected with two othe vertices by edges: these two other vertices will be connected by an edge
        Edge         KillVertex(Vetrex& vertexToRemove);

        /// in a loop: opens the loop
        /// if the edge is between two faces: the faces  wil be connected to form a new common one
        Face         KillEdge(Edge& edgeToRemove);

        void         KillLoop(Loop* loopToRemove);

        /// makes a loop from the face and removes the face
        Loop         KillFaceMakeLoop(Face& faceToConvert);
        */

        // iterate over the regions
        RegionIterator             Regions(void) const;

        // inherited from BRLCAD::Object
        virtual const Object&      operator=(const Object& original);
        virtual Object*            Clone(void) const;
        static const char*         ClassName(void);
        virtual const char*        Type(void) const;
        virtual bool               IsValid(void) const;

    protected:
        NonManifoldGeometry(resource*       resp,
                            directory*      pDir,
                            rt_db_internal* ip,
                            db_i*           dbip = nullptr);

        friend class ConstDatabase;

    private:
        // holds Objects's content if not connected to a database
        model* m_internalp;

        const model* Internal(void) const;
        model*       Internal(void);

        friend class Database;
    };
}


#endif // BRLCAD_NONMANIFOLDGEOMETRY_INCLUDED
