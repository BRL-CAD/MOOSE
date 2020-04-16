/*                      A R B 8 . H
 * BRL-CAD
 *
 * Copyright (c) 2011-2020 United States Government as represented by
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
/** @file Arb8.h
 *
 *  BRL-CAD core C++ interface:
 *      arbitrary regular polyhedron with as many as 8 vertices (ID_ARB8) database object declaration
 */

#ifndef BRLCAD_ARB8_INCLUDED
#define BRLCAD_ARB8_INCLUDED

#include <brlcad/vector.h>
#include <brlcad/Database/Object.h>


struct rt_arb_internal;


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT Arb8 : public Object {
    public:
        Arb8(void);
        Arb8(const Vector3D& point1,
             const Vector3D& point2,
             const Vector3D& point3,
             const Vector3D& point4); ///< arb4 constructor
        Arb8(const Vector3D& point1,
             const Vector3D& point2,
             const Vector3D& point3,
             const Vector3D& point4,
             const Vector3D& point5); ///< arb5 constructor
        Arb8(const Vector3D& point1,
             const Vector3D& point2,
             const Vector3D& point3,
             const Vector3D& point4,
             const Vector3D& point5,
             const Vector3D& point6); ///< arb6 constructor
        Arb8(const Vector3D& point1,
             const Vector3D& point2,
             const Vector3D& point3,
             const Vector3D& point4,
             const Vector3D& point5,
             const Vector3D& point6,
             const Vector3D& point7); ///< arb7 constructor
        Arb8(const Vector3D& point1,
             const Vector3D& point2,
             const Vector3D& point3,
             const Vector3D& point4,
             const Vector3D& point5,
             const Vector3D& point6,
             const Vector3D& point7,
             const Vector3D& point8); ///< arb8 constructor
        Arb8(const Vector3D& point1,
             const Vector3D& point2); ///< rectangular parallel piped constructor
        Arb8(const Arb8& original);
        virtual ~Arb8(void);

        const Arb8&           operator=(const Arb8& original);

        /// number of effective vertices
        /** returns 0 in case of en error */
        size_t                NumberOfVertices(void) const;

        /** The argument is the number (1..8) of the vertex as used in the documentation,
            not the index at the storage-structure of an arb8.
            E.g. with an arb4 "number = 3" returns the vertex with index 2
            and "number = 4" returns the vertex with index 4.
        */
        Vector3D              Point(size_t number) const;
        void                  SetPoint(size_t    number,
                                       Vector3D& point);

        /** for convenience one can access the internal storage-structure too */
        Vector3D              RawPoint(size_t index) const;
        void                  SetRawPoint(size_t    index,
                                          Vector3D& point);

        void                  SetPoints(const Vector3D& point1,
                                        const Vector3D& point2,
                                        const Vector3D& point3,
                                        const Vector3D& point4); ///< this becomes an arb4
        void                  SetPoints(const Vector3D& point1,
                                        const Vector3D& point2,
                                        const Vector3D& point3,
                                        const Vector3D& point4,
                                        const Vector3D& point5); ///< this becomes an arb5
        void                  SetPoints(const Vector3D& point1,
                                        const Vector3D& point2,
                                        const Vector3D& point3,
                                        const Vector3D& point4,
                                        const Vector3D& point5,
                                        const Vector3D& point6); ///< this becomes an arb6
        void                  SetPoints(const Vector3D& point1,
                                        const Vector3D& point2,
                                        const Vector3D& point3,
                                        const Vector3D& point4,
                                        const Vector3D& point5,
                                        const Vector3D& point6,
                                        const Vector3D& point7); ///< this becomes an arb7
        void                  SetPoints(const Vector3D& point1,
                                        const Vector3D& point2,
                                        const Vector3D& point3,
                                        const Vector3D& point4,
                                        const Vector3D& point5,
                                        const Vector3D& point6,
                                        const Vector3D& point7,
                                        const Vector3D& point8); ///< this becomes an arb8
        void                  SetPoints(const Vector3D& point1,
                                        const Vector3D& point2); ///< this becomes an rectangular parallel piped

        // inherited from BRLCAD::Object
        virtual const Object& operator=(const Object& original);
        virtual Object*       Clone(void) const;
        static const char*    ClassName(void);
        virtual const char*   Type(void) const;
        virtual bool          IsValid(void) const; ///< checks for planarity of faces and direction of face normals

    protected:
        Arb8(resource*       resp,
             directory*      pDir,
             rt_db_internal* ip,
             db_i*           dbip);

        friend class ConstDatabase;

    private:
        rt_arb_internal* m_internalp;

        rt_arb_internal*	Internal(void);
        const rt_arb_internal*	Internal(void) const;

        friend class Database;
    };
}


#endif // BRLCAD_ARB8_INCLUDED
