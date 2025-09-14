/*                      T O R U S . H
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
/** @file Torus.h
 *
 *  BRL-CAD core C++ interface:
 *      torus (ID_TOR) database object declaration
 */

#ifndef BRLCAD_TORUS_INCLUDED
#define BRLCAD_TORUS_INCLUDED

#include <brlcad/vector.h>
#include <brlcad/Database/Object.h>


struct rt_tor_internal;


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT Torus : public Object {
    public:
        Torus(void);                       ///< constructs a torus at origin with unit tubeRadius, radius from center to tube-center of 2 and unit normal pointing in positive z direction
        Torus(const Vector3D& center,
              const Vector3D& normalToTubeCenterLinePlane,
              double          tubeCenterLineRadius,
              double          tubeRadius); ///< center, normal of unit length (will be unitized of not of unit length), radius and radius of tube
        Torus(const Torus& original);
        virtual ~Torus(void);

        const Torus&          operator=(const Torus& original);

        Vector3D              Center(void) const;
        void                  SetCenter(const Vector3D& center);

        Vector3D              Normal(void) const;
        void                  SetNormal(const Vector3D& normal);

        double                TubeCenterLineRadius(void) const;
        void                  SetTubeCenterLineRadius(double radius);

        double                TubeRadius(void) const;
        void                  SetTubeRadius(double radius);

        void                  Set(const Vector3D& center,
                                  const Vector3D& normalToTubeCenterLinePlane,
                                  double          tubeCenterLineRadius,
                                  double          tubeRadius);

        // inherited from BRLCAD::Object
        virtual const Object& operator=(const Object& original);
        virtual Object*       Clone(void) const;
        static const char*    ClassName(void);
        virtual const char*   Type(void) const;
        virtual bool          IsValid(void) const; ///< checks if normal has length 1, if radii are positive and if tubeCenterLineRadius is at least tubeRadius

    protected:
        Torus(resource*       resp,
              directory*      pDir,
              rt_db_internal* ip,
              db_i*           dbip);

        friend class ConstDatabase;

    private:
        rt_tor_internal* m_internalp;

        const rt_tor_internal* Internal(void) const;
        rt_tor_internal*       Internal(void);

        friend class Database;
    };
}


#endif // BRLCAD_TORUS_INCLUDED
