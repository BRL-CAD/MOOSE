/*                      H A L F S P A C E . H
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
/** @file Halfspace.h
 *
 *  BRL-CAD core C++ interface:
 *      half-space (ID_HALF) database object declaration
 */

#ifndef BRLCAD_HALFSPACE_INCLUDED
#define BRLCAD_HALFSPACE_INCLUDED

#include <brlcad/vector.h>
#include <brlcad/Database/Object.h>


struct rt_half_internal;


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT Halfspace : public Object {
    public:
        Halfspace(void);
        Halfspace(const  Vector3D& normal,
                  double           distanceFromOrigin);
        Halfspace(const Halfspace& original);
        virtual ~Halfspace(void);

        const Halfspace&      operator=(const Halfspace& original);

        Vector3D              Normal(void) const;
        void                  SetNormal(const Vector3D& normal);

        double                DistanceFromOrigin(void) const;
        void                  SetDistanceFromOrigin(double distance);

        void                  Set(const Vector3D& normal,
                                  double          distanceFromOrigin);

        // inherited from BRLCAD::Object
        virtual const Object& operator=(const Object& original);
        virtual Object*       Clone(void) const;
        static const char*    ClassName(void);
        virtual const char*   Type(void) const;
        virtual bool          IsValid(void) const;

    protected:
        Halfspace(resource*       resp,
                  directory*      pDir,
                  rt_db_internal* ip,
                  db_i*           dbip = 0);

        friend class ConstDatabase;

    private:
        // holds Objects's content if not connected to a database
        rt_half_internal* m_internalp;

        const rt_half_internal* Internal(void) const;
        rt_half_internal*       Internal(void);

        friend class Database;
    };
}


#endif // BRLCAD_HALFSPACE_INCLUDED
