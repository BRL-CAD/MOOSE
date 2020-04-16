/*                P A R A B O L O I D . H
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
/** @file Paraboloid.h
 *
 *  BRL-CAD core C++ interface:
 *      elliptical paraboloid (ID_EPA) database object declaration
 */

#ifndef BRLCAD_PARABOLOID_INCLUDED
#define BRLCAD_PARABOLOID_INCLUDED

#include <brlcad/vector.h>
#include <brlcad/Database/Object.h>


struct rt_epa_internal;


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT Paraboloid : public Object {
    public:
        Paraboloid(void);                                ///< constructs a paraboloid with unit height at origin with a circular base
        Paraboloid(const Vector3D& basePoint,
                   const Vector3D& height,
                   const Vector3D& semiMajorAxis,
                   double          semiMinorAxisLength); ///< length an direction of vector semi major axis used
        Paraboloid(const Vector3D& basePoint,
                   const Vector3D& height,
                   const Vector3D& semiMajorAxisDirection,
                   double          semiMajorAxisLength,
                   double          semiMinorAxisLength); ///< semi major axis will be unitized and length of semi major axis is given by semiMajorAxisLength
        Paraboloid(const Paraboloid& original);
        virtual ~Paraboloid(void);

        const Paraboloid&     operator=(const Paraboloid& original);

        Vector3D              BasePoint(void) const;
        void                  SetBasePoint(const Vector3D& point);

        Vector3D              Height(void) const;
        void                  SetHeight(const Vector3D& height);

        Vector3D              SemiMajorAxis(void) const;
        void                  SetSemiMajorAxis(const Vector3D& axis);
        void                  SetSemiMajorAxis(const Vector3D& direction,
                                               double          length);

        Vector3D              SemiMajorAxisDirection(void) const;
        void                  SetSemiMajorAxisDirection(const Vector3D& direction);

        double                SemiMajorAxisLength(void) const;
        void                  SetSemiMajorAxisLength(double length);

        double                SemiMinorAxisLength(void) const;
        void                  SetSemiMinorAxisLength(double length);

        void                  Set(const Vector3D& basePoint,
                                  const Vector3D& height,
                                  const Vector3D& semiMajorAxis,
                                  double          semiMinorAxisLength);
        void                  Set(const Vector3D& basePoint,
                                  const Vector3D& height,
                                  const Vector3D& semiMajorAxisDirection,
                                  double          semiMajorAxisLength,
                                  double          semiMinorAxisLength);

        // inherited from BRLCAD::Object
        virtual const Object& operator=(const Object& original);
        virtual Object*       Clone(void) const;
        static const char*    ClassName(void);
        virtual const char*   Type(void) const;
        virtual bool          IsValid(void) const; ///< checks for positive height, unit length of internal semi major axis vector, semi minor axis is not longer than semi major axis, both are nonzero and height and semi major axis are perpendicular

    protected:
        Paraboloid(resource*       resp,
                   directory*      pDir,
                   rt_db_internal* ip,
                   db_i*           dbip);

        friend class ConstDatabase;

    private:
        rt_epa_internal* m_internalp;

        rt_epa_internal*       Internal(void);
        const rt_epa_internal* Internal(void) const;

        friend class Database;
    };
}


#endif // BRLCAD_PARABOLOID_INCLUDED
