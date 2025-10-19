/*                      B A G O F T R I A N G L E S . H
 * BRL-CAD
 *
 * Copyright (c) 2014-2025 United States Government as represented by
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
/** @file BagOfTriangles.h
 *
 *  BRL-CAD core C++ interface:
 *      bag of triangles (ID_BOT) database object declaration
 */

#ifndef BRLCAD_BAGOFTRIANGLES_INCLUDED
#define BRLCAD_BAGOFTRIANGLES_INCLUDED

#include <brlcad/vector.h>
#include <brlcad/Database/Object.h>


struct rt_bot_internal;


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT BagOfTriangles : public Object {
    public:
        enum BotMode {
            Surface,
            Solid,
            Plate,
            EqualLineOfSightPlate // LOS is set equal to face thickness, not the thickness divided by the cosine of the obliquity angle
        };

        enum BotOrientation {
            Unoriented,
            ClockWise,
            CounterClockWise
        };

        BagOfTriangles(void);
        BagOfTriangles(const BagOfTriangles& original);
        virtual ~BagOfTriangles(void);

        const BagOfTriangles& operator=(const BagOfTriangles& original);

        class BRLCAD_MOOSE_EXPORT Face {
        public:
            Face(void) : m_bot(nullptr), m_faceIndex(0) {}
            Face(const Face& original) : m_bot(original.m_bot), m_faceIndex(original.m_faceIndex) {}
            ~Face(void) {}

            const Face& operator=(const Face& original) {
                m_bot       = original.m_bot;
                m_faceIndex = original.m_faceIndex;

                return *this;
            }

            Vector3D    Point(size_t index) const;
            void        SetPoint(size_t          index,
                                 const Vector3D& point);
            void        SetPoints(const Vector3D& point1,
                                  const Vector3D& point2,
                                  const Vector3D& point3);

            double      Thickness(void) const;
            void        SetThickness(double value);

            bool        ApendThickness(void) const;
            void        SetApendThickness(bool apendThickness);

            Vector3D    Normal(size_t index) const;
            void        SetNormal(size_t          index,
                                  const Vector3D& normal);
            void        SetNormals(const Vector3D& normal1,
                                   const Vector3D& normal2,
                                   const Vector3D& normal3);

                        operator void*(void) { ///< to test if the face is NULL
                return m_bot;
            }

        protected:
            Face(rt_bot_internal* original,
                 size_t           originalIndex) : m_bot(original), m_faceIndex(originalIndex) {}

            friend BagOfTriangles;

        private:
            rt_bot_internal* m_bot;
            size_t           m_faceIndex;
        };

        BotMode               Mode(void) const;
        void                  SetMode(BotMode mode);

        BotOrientation        Orientation(void) const;
        void                  SetOrientation(BotOrientation orientation);

        bool                  FacesHaveNormals(void) const;
        void                  SetFacesHaveNormals(bool facesHaveNormals);

        bool                  UseFaceNormals(void) const;
        void                  SetUseFaceNormals(bool useFaceNormals);

        bool                  UseFloats(void) const;
        void                  SetUseFloats(bool useFloats);

        size_t                NumberOfFaces(void) const;

        Face                  GetFace(size_t index);
        Face                  AddFace(const Vector3D& point1,
                                      const Vector3D& point2,
                                      const Vector3D& point3);

        void                  DeleteFace(size_t index);

        // inherited from BRLCAD::Object
        virtual const Object& operator=(const Object& original);
        virtual Object*       Clone(void) const;
        static const char*    ClassName(void);
        virtual const char*   Type(void) const;
        virtual bool          IsValid(void) const;

    protected:
        BagOfTriangles(resource*       resp,
                       directory*      pDir,
                       rt_db_internal* ip,
                       db_i*           dbip = nullptr);

        friend class ConstDatabase;

    private:
        struct rt_bot_internal *m_internalp;
        const rt_bot_internal* Internal(void) const;
        rt_bot_internal*       Internal(void);

        friend class Database;
    };
};


#endif // BRLCAD_BAGOFTRIANGLES_INCLUDED
