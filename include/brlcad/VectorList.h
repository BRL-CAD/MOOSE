/*                    V E C T O R L I S T . H
 * BRL-CAD
 *
 * Copyright (c) 2020-2025 United States Government as represented by
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
/** @file VectorList.h
 *
 *  BRL-CAD core C++ interface:
 *      vlist declaration
 */

#ifndef BRLCAD_VECTORLIST_INCLUDED
#define BRLCAD_VECTORLIST_INCLUDED

#include <cstddef>

#include <brlcad/globals.h>
#include <brlcad/vector.h>


struct bu_list;
struct bv_vlist;


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT VectorList {
    public:
        VectorList(void);
        VectorList(const VectorList& original);
        ~VectorList(void);

        const VectorList& operator=(const VectorList& original);

        class BRLCAD_MOOSE_EXPORT Element {
        public:
            virtual ~Element(void) {}

            enum class ElementType {
                PointDraw,
                PointSize,
                LineMove,
                LineDraw,
                LineWidth,
                TriangleStart,
                TriangleMove,
                TriangleDraw,
                TriangleEnd,
                TriangleVertexNormal,
                PolygonStart,
                PolygonMove,
                PolygonDraw,
                PolygonEnd,
                PolygonVertexNormal,
                DisplaySpace,
                ModelSpace
            };

            virtual ElementType Type(void) const = 0;

        protected:
            bv_vlist* m_chunk;
            size_t    m_index;

            Element(void) : m_chunk(nullptr), m_index(-1) {}
            Element(const Element& original) : m_chunk(nullptr), m_index(-1) {}
            Element(bv_vlist* chunk,
                    size_t    index) : m_chunk(chunk), m_index(index) {}

            const Element& operator=(const Element& original); // not implemented
        };

        class BRLCAD_MOOSE_EXPORT PointDraw : public Element {
        public:
            PointDraw(void) : Element(), m_point() {}
            PointDraw(const PointDraw& original) : VectorList::Element(original), m_point(original.m_point) {}
            PointDraw(const Vector3D& point) : Element(), m_point(point) {}
            ~PointDraw(void) override {}

            const PointDraw& operator=(const PointDraw& original);

            ElementType      Type(void) const override;

            Vector3D         Point(void) const;
            void             SetPoint(const Vector3D& point);

        private:
            Vector3D m_point;

            PointDraw(bv_vlist* chunk,
                      size_t    index);

            friend class VectorList;
        };

        class BRLCAD_MOOSE_EXPORT PointSize : public Element {
        public:
            PointSize(void) : Element(), m_size(1.) {}
            PointSize(const PointSize& original) : VectorList::Element(original), m_size(original.m_size) {}
            PointSize(double size) : Element(), m_size(size) {}
            ~PointSize(void) override {}

            const PointSize& operator=(const PointSize& original);

            ElementType      Type(void) const override;

            double           Size(void) const;
            void             SetSize(double size);

        private:
            double m_size;

            PointSize(bv_vlist* chunk,
                      size_t    index);

            friend class VectorList;
        };

        class BRLCAD_MOOSE_EXPORT LineMove : public Element {
        public:
            LineMove(void) : Element(), m_point() {}
            LineMove(const LineMove& original) : VectorList::Element(original), m_point(original.m_point) {}
            LineMove(const Vector3D& point) : Element(), m_point(point) {}
            ~LineMove(void) override {}

            const LineMove& operator=(const LineMove& original);

            ElementType     Type(void) const override;

            Vector3D        Point(void) const;
            void            SetPoint(const Vector3D& point);

        private:
            Vector3D m_point;

            LineMove(bv_vlist* chunk,
                     size_t    index);

            friend class VectorList;
        };

        class BRLCAD_MOOSE_EXPORT LineDraw : public Element {
        public:
            LineDraw(void) : Element(), m_point() {}
            LineDraw(const LineDraw& original) : VectorList::Element(original), m_point(original.m_point) {}
            LineDraw(const Vector3D& point) : Element(), m_point(point) {}
            ~LineDraw(void) override {}

            const LineDraw& operator=(const LineDraw& original);

            ElementType     Type(void) const override;

            Vector3D        Point(void) const;
            void            SetPoint(const Vector3D& point);

        private:
            Vector3D m_point;

            LineDraw(bv_vlist* chunk,
                     size_t    index);

            friend class VectorList;
        };

        class BRLCAD_MOOSE_EXPORT LineWidth : public Element {
        public:
            LineWidth(void) : Element(), m_width(1.) {}
            LineWidth(const LineWidth& original) : VectorList::Element(original), m_width(original.m_width) {}
            LineWidth(double width) : Element(), m_width(width) {}
            ~LineWidth(void) override {}

            const LineWidth& operator=(const LineWidth& original);

            ElementType      Type(void) const override;

            double           Width(void) const;
            void             SetWidth(double width);

        private:
            double m_width;

            LineWidth(bv_vlist* chunk,
                      size_t    index);

            friend class VectorList;
       };

        class BRLCAD_MOOSE_EXPORT TriangleStart : public Element {
        public:
            TriangleStart(void) : Element(), m_normal() {}
            TriangleStart(const TriangleStart& original) : VectorList::Element(original), m_normal(original.m_normal) {}
            TriangleStart(const Vector3D& normal) : Element(), m_normal(normal) {}
            ~TriangleStart(void) override {}

            const TriangleStart& operator=(const TriangleStart& original);

            ElementType          Type(void) const override;

            Vector3D             Normal(void) const;
            void                 SetNormal(const Vector3D& normal);

        private:
            Vector3D m_normal;

            TriangleStart(bv_vlist* chunk,
                          size_t    index);

            friend class VectorList;
        };

        class BRLCAD_MOOSE_EXPORT TriangleMove : public Element {
        public:
            TriangleMove(void) : Element(), m_point() {}
            TriangleMove(const TriangleMove& original) : VectorList::Element(original), m_point(original.m_point) {}
            TriangleMove(const Vector3D& point) : Element(), m_point(point) {}
            ~TriangleMove(void) override {}

            const TriangleMove& operator=(const TriangleMove& original);

            ElementType         Type(void) const override;

            Vector3D            Point(void) const;
            void                SetPoint(const Vector3D& point);

        private:
            Vector3D m_point;

            TriangleMove(bv_vlist* chunk,
                         size_t    index);

            friend class VectorList;
        };

        class BRLCAD_MOOSE_EXPORT TriangleDraw : public Element {
        public:
            TriangleDraw(void) : Element(), m_point() {}
            TriangleDraw(const TriangleDraw& original) : VectorList::Element(original), m_point(original.m_point) {}
            TriangleDraw(const Vector3D& point) : Element(), m_point(point) {}
            ~TriangleDraw(void) override {}

            const TriangleDraw& operator=(const TriangleDraw& original);

            ElementType         Type(void) const override;

            Vector3D            Point(void) const;
            void                SetPoint(const Vector3D& point);

        private:
            Vector3D m_point;

            TriangleDraw(bv_vlist* chunk,
                         size_t    index);

            friend class VectorList;
        };

        class BRLCAD_MOOSE_EXPORT TriangleEnd : public Element {
        public:
            TriangleEnd(void) : Element(), m_point() {}
            TriangleEnd(const TriangleEnd& original) : VectorList::Element(original), m_point(original.m_point) {}
            TriangleEnd(const Vector3D& point) : Element(), m_point(point) {}
            ~TriangleEnd(void) override {}

            const TriangleEnd& operator=(const TriangleEnd& original);

            ElementType        Type(void) const override;

            Vector3D           Point(void) const;
            void               SetPoint(const Vector3D& point);

        private:
            Vector3D m_point;

            TriangleEnd(bv_vlist* chunk,
                        size_t    index);

            friend class VectorList;
        };

        class BRLCAD_MOOSE_EXPORT TriangleVertexNormal : public Element {
        public:
            TriangleVertexNormal(void) : Element(), m_normal() {}
            TriangleVertexNormal(const TriangleVertexNormal& original) : VectorList::Element(original), m_normal(original.m_normal) {}
            TriangleVertexNormal(const Vector3D& normal) : Element(), m_normal(normal) {}
            ~TriangleVertexNormal(void) override {}

            const TriangleVertexNormal& operator=(const TriangleVertexNormal& original);

            ElementType                 Type(void) const override;

            Vector3D                    Normal(void) const;
            void                        SetNormal(const Vector3D& normal);

        private:
            Vector3D m_normal;

            TriangleVertexNormal(bv_vlist* chunk,
                                 size_t    index);

            friend class VectorList;
        };

        class BRLCAD_MOOSE_EXPORT PolygonStart : public Element {
        public:
            PolygonStart(void) : Element(), m_normal() {}
            PolygonStart(const PolygonStart& original) : VectorList::Element(original), m_normal(original.m_normal) {}
            PolygonStart(const Vector3D& normal) : Element(), m_normal(normal) {}
            ~PolygonStart(void) override {}

            const PolygonStart& operator=(const PolygonStart& original);

            ElementType         Type(void) const override;

            Vector3D            Normal(void) const;
            void                SetNormal(const Vector3D& normal);

        private:
            Vector3D m_normal;

            PolygonStart(bv_vlist* chunk,
                         size_t    index);

            friend class VectorList;
       };

        class BRLCAD_MOOSE_EXPORT PolygonMove : public Element {
        public:
            PolygonMove(void) : Element(), m_point() {}
            PolygonMove(const PolygonMove& original) : VectorList::Element(original), m_point(original.m_point) {}
            PolygonMove(const Vector3D& point) : Element(), m_point(point) {}
            ~PolygonMove(void) override {}

            const PolygonMove&  operator=(const PolygonMove& original);

            ElementType         Type(void) const override;

            Vector3D            Point(void) const;
            void                SetPoint(const Vector3D& point);

        private:
            Vector3D m_point;

            PolygonMove(bv_vlist* chunk,
                        size_t    index);

            friend class VectorList;
        };

        class BRLCAD_MOOSE_EXPORT PolygonDraw : public Element {
        public:
            PolygonDraw(void) : Element(), m_point() {}
            PolygonDraw(const PolygonDraw& original) : VectorList::Element(original), m_point(original.m_point) {}
            PolygonDraw(const Vector3D& point) : Element(), m_point(point) {}
            ~PolygonDraw(void) override {}

            const PolygonDraw& operator=(const PolygonDraw& original);

            ElementType        Type(void) const override;

            Vector3D           Point(void) const;
            void               SetPoint(const Vector3D& point);

        private:
            Vector3D m_point;

            PolygonDraw(bv_vlist* chunk,
                        size_t    index);

            friend class VectorList;
        };

        class BRLCAD_MOOSE_EXPORT PolygonEnd : public Element {
        public:
            PolygonEnd(void) : Element(), m_point() {}
            PolygonEnd(const PolygonEnd& original) : VectorList::Element(original), m_point(original.m_point) {}
            PolygonEnd(const Vector3D& point) : Element(), m_point(point) {}
            ~PolygonEnd(void) override {}

            const PolygonEnd& operator=(const PolygonEnd& original);

            ElementType       Type(void) const override;

            Vector3D          Point(void) const;
            void              SetPoint(const Vector3D& point);

        private:
            Vector3D m_point;

            PolygonEnd(bv_vlist* chunk,
                       size_t    index);

            friend class VectorList;
        };

        class BRLCAD_MOOSE_EXPORT PolygonVertexNormal : public Element {
        public:
            PolygonVertexNormal(void) : Element(), m_normal() {}
            PolygonVertexNormal(const PolygonVertexNormal& original) : VectorList::Element(original), m_normal(original.m_normal) {}
            PolygonVertexNormal(const Vector3D& normal) : Element(), m_normal(normal) {}
            ~PolygonVertexNormal(void) override {}

            const PolygonVertexNormal& operator=(const PolygonVertexNormal& original);

            ElementType                Type(void) const override;

            Vector3D                   Normal(void) const;
            void                       SetNormal(const Vector3D& normal);

        private:
            Vector3D m_normal;

            PolygonVertexNormal(bv_vlist* chunk,
                                size_t    index);

            friend class VectorList;
        };

        class BRLCAD_MOOSE_EXPORT DisplaySpace : public Element {
        public:
            DisplaySpace(void) : Element(), m_referencePoint() {}
            DisplaySpace(const DisplaySpace& original) : VectorList::Element(original), m_referencePoint(original.m_referencePoint) {}
            DisplaySpace(const Vector3D& referencePoint) : Element(), m_referencePoint(referencePoint) {}
            ~DisplaySpace(void) override {}

            const DisplaySpace& operator=(const DisplaySpace& original);

            ElementType         Type(void) const override;

            Vector3D            ReferencePoint(void) const;
            void                SetReferencePoint(const Vector3D& referencePoint);

        private:
            Vector3D m_referencePoint;

            DisplaySpace(bv_vlist* chunk,
                         size_t    index);

            friend class VectorList;
        };

        class BRLCAD_MOOSE_EXPORT ModelSpace : public Element {
        public:
            ModelSpace(void) : Element() {}
            ModelSpace(const ModelSpace& original) : VectorList::Element(original) {}
            ~ModelSpace(void) override {}

            const ModelSpace& operator=(const ModelSpace& original);

            ElementType       Type(void) const override;

        private:
            ModelSpace(bv_vlist* chunk,
                       size_t    index);

            friend class VectorList;
        };

        void              Iterate(const std::function<bool(const Element* element)>& callback) const;
        void              Iterate(const std::function<bool(Element* element)>& callback);

        bool              Append(const Element& element);
        void              Clear(void);

    private:
        bu_list* m_vlist;

        friend class ConstDatabase;
    };
};


#endif // BRLCAD_VECTORLIST_INCLUDED
