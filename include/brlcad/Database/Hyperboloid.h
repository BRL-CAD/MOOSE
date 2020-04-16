/*                   H Y P E R B O L O I D . H
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
/** @file Hyperboloid.h
 *
 *  BRL-CAD core C++ interface:
 *      elliptical hyperboloid (ID_EHY) database object declaration
 */

#ifndef BRLCAD_HYPERBOLOID_INCLUDED
#define BRLCAD_HYPERBOLOID_INCLUDED

#include <brlcad/vector.h>
#include <brlcad/Database/Object.h>


struct rt_ehy_internal;


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT Hyperboloid : public Object {
    public:
        Hyperboloid(void);                                  ///< constructs a hyperboloid with height 1 at origin with a circular base and unit distance from apex to asymptote
        Hyperboloid(const Vector3D& basePoint,
                    const Vector3D& height,
                    const Vector3D& semiMajorAxis,
                    double          semiMinorAxisLength,
                    double          apexAsymptoteDistance); ///< length an direction of vector semi major axis used
        Hyperboloid(const Vector3D& basePoint,
                    const Vector3D& height,
                    const Vector3D& semiMajorAxisDirection,
                    double          semiMajorAxisLength,
                    double          semiMinorAxisLength,
                    double          apexAsymptoteDistance); ///< semi major axis will be unitized and length of semi major axis is given by semiMajorAxisLength
        Hyperboloid(const Hyperboloid& original);
        virtual ~Hyperboloid(void);

        const Hyperboloid&    operator=(const Hyperboloid& original);

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

        double                ApexAsymptoteDistance(void) const;
        void                  SetApexAsymptoteDistance(double distance);

        void                  Set(const Vector3D& basePoint,
                                  const Vector3D& height,
                                  const Vector3D& semiMajorAxis,
                                  double          semiMinorAxisLength,
                                  double          apexAsymptoteDistance);
        void                  Set(const Vector3D& basePoint,
                                  const Vector3D& height,
                                  const Vector3D& semiMajorAxisDirection,
                                  double          semiMajorAxisLength,
                                  double          semiMinorAxisLength,
                                  double          apexAsymptoteDistance);

        // inherited from BRLCAD::Object
        virtual const Object& operator=(const Object& original);
        virtual Object*       Clone(void) const;
        static const char*    ClassName(void);
        virtual const char*   Type(void) const;
        virtual bool          IsValid(void) const; ///< checks for positive height, unit length of internal semi major axis vector, semi minor axis is not longer than semi major axis, both are nonzero, nonzero apex distance, and height and semi major axis are perpendicular

    protected:
        Hyperboloid(resource*       resp,
                    directory*      pDir,
                    rt_db_internal* ip,
                    db_i*           dbip);

        friend class ConstDatabase;

    private:
        rt_ehy_internal* m_internalp;

        rt_ehy_internal*       Internal(void);
        const rt_ehy_internal* Internal(void) const;

        friend class Database;
    };
}


#endif // BRLCAD_HYPERBOLOID_INCLUDED
