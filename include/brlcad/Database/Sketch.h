/*                      S K E T C H. H
 * BRL-CAD
 *
 * Copyright (c) 2014-2020 United States Government as represented by
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
/** @file Sketch.h
 *
 *  BRL-CAD core C++ interface:
 *      sketch (ID_SKETCH) database object declaration
 */

#ifndef BRLCAD_SKETCH_INCLUDED
#define BRLCAD_SKETCH_INCLUDED

#include <functional>

#include <brlcad/vector.h>
#include <brlcad/Database/Object.h>


struct rt_sketch_internal;
struct line_seg;
struct carc_seg;
struct nurb_seg;
struct bezier_seg;


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT Sketch : public Object {
    public:
        Sketch(void);
        Sketch(const Sketch& original);
        virtual ~Sketch(void);

        const Sketch&           operator=(const Sketch& original);

        class BRLCAD_MOOSE_EXPORT Segment {
        public:
            enum SegmentType {
                Null,
                Line,
                CircularArc,
                Nurb,
                Bezier
            };

            virtual ~Segment(void) {}

            void                Destroy(void);
            virtual Segment*    Clone(void) const      = 0;
            virtual SegmentType Type(void) const       = 0;

            virtual Vector2D    StartPoint(void) const = 0;
            virtual Vector2D    EndPoint(void) const   = 0;

            bool                Reverse(void) const;
            void                SetReverse(bool reverse);

        protected:
            rt_sketch_internal* m_sketch;

            Segment(void) : m_sketch(0)  {}
            Segment(const Segment& original) : m_sketch(original.m_sketch) {}
            Segment(rt_sketch_internal* sketch) : m_sketch(sketch) {}

            const Segment& operator=(const Segment& original) {return *this;}
        };

        class BRLCAD_MOOSE_EXPORT Line : public Segment {
        public:
            Line(void) : Segment(), m_lineSegment(0) {}
            Line(const Line& original) : Segment(original), m_lineSegment(original.m_lineSegment) {}
            virtual ~Line(void) {}

            const Line&         operator=(const Line& original) {
                Segment::operator=(original);
                m_lineSegment = original.m_lineSegment;
                return *this;
            }

            virtual SegmentType Type(void) const;
            virtual Segment*    Clone(void) const;

            virtual Vector2D    StartPoint(void) const;
            void                SetStartPoint(const Vector2D& startPoint);
            virtual Vector2D    EndPoint(void) const;
            void                SetEndPoint(const Vector2D& endPoint);

        private:
            line_seg* m_lineSegment;

            Line(line_seg*           lineSegment,
                 rt_sketch_internal* sketch) : Segment(sketch), m_lineSegment(lineSegment) {}
            friend class Sketch;
        };

        class BRLCAD_MOOSE_EXPORT CircularArc : public Segment {
        public:
            CircularArc(void) : Segment(), m_circularArcSegment(0) {}
            CircularArc(const CircularArc& original) : Segment(original), m_circularArcSegment(original.m_circularArcSegment) {}
            virtual ~CircularArc(void) {}

            const CircularArc&  operator=(const CircularArc& original) {
                Segment::operator=(original);
                m_circularArcSegment = original.m_circularArcSegment;
                return *this;
            }

            virtual SegmentType Type(void) const;
            virtual Segment*    Clone(void) const;

            virtual Vector2D    StartPoint(void) const;
            void                SetStartPoint(const Vector2D& startPoint);
            virtual Vector2D    EndPoint(void) const;
            void                SetEndPoint(const Vector2D& endPoint);

            Vector3D            Center(void) const;
            void                SetCenter(Vector2D c);
            double              Radius(void) const;
            void                SetRadius(double radius);
            bool                CenterIsLeft(void) const;
            void                SetCenterIsLeft(bool centerIsLeft);
            bool                ClockwiseOriented(void) const;
            void                SetClockwiseOriented(bool clockwiseOriented);

        private:
            carc_seg* m_circularArcSegment;

            CircularArc(carc_seg*           circularArcSegment,
                        rt_sketch_internal* sketch) : Segment(sketch), m_circularArcSegment(circularArcSegment) {}
            friend class Sketch;
        };

        class BRLCAD_MOOSE_EXPORT Nurb : public Segment {
        public:
            Nurb(void) : Segment(), m_nurbSegment(0) {}
            Nurb(const Nurb& original) : Segment(original), m_nurbSegment(original.m_nurbSegment) {}
            virtual ~Nurb(void) {}

            const Nurb&         operator=(const Nurb& original) {
                Segment::operator=(original);
                m_nurbSegment = original.m_nurbSegment;
                return *this;
            }

            virtual SegmentType Type(void) const;
            virtual Segment*    Clone(void) const;

            virtual Vector2D    StartPoint(void) const;
            void                SetStartPoint(const Vector2D& startPoint);
            virtual Vector2D    EndPoint(void) const;
            void                SetEndPoint(const Vector2D& endPoint);

            size_t              Order(void) const;
            bool                IsRational(void) const;
            size_t              NumberOfKnots(void) const;
            double              Knot(size_t index) const;
            size_t              NumberOfControlPoints(void) const;
            Vector2D            ControlPoint(size_t index) const;
            double              ControlPointWeight(size_t index) const;

            void                SetOrder(size_t order);
            void                AddKnot(double knot);
            void                AddControlPoint(const Vector2D& Point);
            void                AddControlPointWeight(const Vector2D& Point, double weight);

        private:
            nurb_seg* m_nurbSegment;

            Nurb(nurb_seg*           nurbSegment,
                 rt_sketch_internal* sketch) : Segment(sketch), m_nurbSegment(nurbSegment) {}

            friend class Sketch;
        };

        class BRLCAD_MOOSE_EXPORT Bezier : public Segment {
        public:
            Bezier(void) : Segment(), m_bezierSegment(0) {}
            Bezier(const Bezier& original) : Segment(original), m_bezierSegment(original.m_bezierSegment) {}
            virtual ~Bezier(void) {}

            const Bezier&       operator=(const Bezier& original) {
                Segment::operator=(original);
                m_bezierSegment = original.m_bezierSegment;
                return *this;
            }

            virtual SegmentType Type(void) const;
            virtual Segment*    Clone(void) const;

            virtual Vector2D    StartPoint(void) const;
            void                SetStartPoint(const Vector2D& startPoint);
            virtual Vector2D    EndPoint(void) const;
            void                SetEndPoint(const Vector2D& endPoint);

            size_t              Degree(void) const;
            Vector2D            ControlPoint(size_t index) const;
            void                AddControlPoint(const Vector2D& Point);

        private:
            bezier_seg* m_bezierSegment;

            Bezier(bezier_seg*         bezierSegment,
                   rt_sketch_internal* sketch) : Segment(sketch), m_bezierSegment(bezierSegment) {}

            friend class Sketch;
        };

        size_t                NumberOfSegments(void) const;

        /// selects a single object and hand it over to an SegmentCallback
        void                  Get(size_t                                      index,
                                  std::function<void(const Segment& segment)> callback) const;
        void                  Get(size_t                                index,
                                  std::function<void(Segment& segment)> callback);

        /// overloaded member function, provided for convenience: selects a single segment and and returns it
        /** Do not forget to BRLCAD::Sketch::Segment::Destroy() the copy when you are finished with it! */
        Segment*              Get(size_t index) const;

        Line*                 AppendLine(void);
        Line*                 InsertLine(size_t index);
        CircularArc*          AppendArc(void);
        CircularArc*          InsertArc(size_t index);
        Nurb*                 AppendNurb(void);
        Nurb*                 InsertNurb(size_t index);
        Bezier*               AppendBezier(void);
        Bezier*               InsertBezier(size_t index);

        void                  DeleteSegment(size_t index);

        Vector3D              EmbeddingPlaneX(void) const;
        Vector3D              EmbeddingPlaneY(void) const;
        void                  SetEmbeddingPlaneX(Vector3D& u);
        void                  SetEmbeddingPlaneY(Vector3D& v);
        Vector3D              EmbeddingPlaneOrigin(void) const;
        void                  SetEmbeddingPlaneOrigin(Vector3D& point);

        // inherited from BRLCAD::Object
        virtual const Object& operator=(const Object& original);
        virtual Object*       Clone(void) const;
        static const char*    ClassName(void);
        virtual const char*   Type(void) const;
        virtual bool          IsValid(void) const;

    protected:
        Sketch(resource*       resp,
               directory*      pDir,
               rt_db_internal* ip,
               db_i*           dbip = 0);

        friend class ConstDatabase;

    private:
        // holds Objects's content if not connected to a database
        rt_sketch_internal* m_internalp;

        const rt_sketch_internal* Internal(void) const;
        rt_sketch_internal*       Internal(void);

        friend class Database;
    };
};


#endif // BRLCAD_SKETCH_INCLUDED
