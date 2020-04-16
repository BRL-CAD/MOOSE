/*                      E L L I P S O I D . H
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
/** @file Ellipsoid.h
 *
 *  BRL-CAD core C++ interface:
 *      ellipsoid (ID_ELL) database object declaration
 */

#ifndef BRLCAD_ELLIPSOID_INCLUDED
#define BRLCAD_ELLIPSOID_INCLUDED

#include <brlcad/vector.h>
#include <brlcad/Database/Object.h>


struct rt_ell_internal;


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT Ellipsoid : public Object {
    public:
        Ellipsoid(void);                               ///< constructs the unit circle around the origin
        Ellipsoid(const Vector3D& center,
                  const Vector3D& semiPrincipalAxisA,
                  const Vector3D& semiPrincipalAxisB,
                  const Vector3D& semiPrincipalAxisC); ///< center and three perpendicular semi-principal-axes
        Ellipsoid(const Vector3D& center,
                  const Vector3D& semiPrincipalAxis,
                  double          radius);             ///< center, one semi-principal-axis and radius (body of revolution)
        Ellipsoid(const Vector3D& center,
                  double          radius);             ///< sphere with center and radius
        Ellipsoid(const Ellipsoid& original);
        virtual ~Ellipsoid(void);

        const Ellipsoid&      operator=(const Ellipsoid& original);

        Vector3D              Center(void) const;
        void                  SetCenter(const Vector3D& center);

        /// semi principal axes are accessed by their index (0/1/2 for the vectos a/b/c)*/
        Vector3D              SemiPrincipalAxis(size_t index) const;
        void                  SetSemiPrincipalAxis(size_t          index,
                                                   const Vector3D& semiPrincipalAxis);

        void                  Set(const Vector3D& center,
                                  const Vector3D& semiPrincipalAxisA,
                                  const Vector3D& semiPrincipalAxisB,
                                  const Vector3D& semiPrincipalAxisC);
        void                  Set(const Vector3D& center,
                                  const Vector3D& semiPrincipalAxis,
                                  double          radius);
        void                  SetFocals(const Vector3D& focalA,
                                        const Vector3D& focalB,
                                        double          majorAxisLength);
        void                  SetSphere(const Vector3D& center,
                                        double          radius);

        // inherited from BRLCAD::Object
        virtual const Object& operator=(const Object& original);
        virtual Object*       Clone(void) const;
        static const char*    ClassName(void);
        virtual const char*   Type(void) const;
        virtual bool          IsValid(void) const; ///< checks if semi-principal axes are perpendicular and if they have positive length

    protected:
        Ellipsoid(resource*       resp,
                  directory*      pDir,
                  rt_db_internal* ip,
                  db_i*           dbip);

        friend class ConstDatabase;

    private:
        rt_ell_internal* m_internalp;

        rt_ell_internal*       Internal(void);
        const rt_ell_internal* Internal(void) const;

        friend class Database;
    };
}


#endif // BRLCAD_ELLIPSOID_INCLUDED
