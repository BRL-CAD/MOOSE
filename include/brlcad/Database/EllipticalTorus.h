/*               E L L I P T I C A L T O R U S . H
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
/** @file EllipticalTorus.h
 *
 *  BRL-CAD core C++ interface:
 *      elliptical torus (ID_ETO) database object declaration
 */

#ifndef BRLCAD_ELLIPTICALTORUS_INCLUDED
#define BRLCAD_ELLIPTICALTORUS_INCLUDED

#include <brlcad/vector.h>
#include <brlcad/Database/Object.h>


struct rt_eto_internal;


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT EllipticalTorus : public Object {
    public:
        EllipticalTorus(void);                                    ///< constructs a torus at origin with circular tube of unit radius, radius from center to tube-center of 2 and unit normal pointing in positive z direction
        EllipticalTorus(const Vector3D& center,
                        const Vector3D& normalToTubeCenterLinePlane,
                        double          tubeCenterLineRadius,
                        const Vector3D& tubeSemiMajorAxis,
                        double          tubeSemiMinorAxisLength); ///< center, normal of unit length (will be unitized of not of unit length), radius of revolution, semi-major axis of ellipse, length semi-minor axis of ellipse
        EllipticalTorus(const EllipticalTorus& original);
        virtual ~EllipticalTorus(void);

        const EllipticalTorus& operator=(const EllipticalTorus& original);

        Vector3D               Center(void) const;
        void                   SetCenter(const Vector3D& center);

        Vector3D               Normal(void) const;
        void                   SetNormal(const Vector3D& normal);

        double                 TubeCenterLineRadius(void) const;
        void                   SetTubeCenterLineRadius(double radius);

        Vector3D               TubeSemiMajorAxis(void) const;
        void                   SetTubeSemiMajorAxis(const Vector3D& axis);

        double                 TubeSemiMinorAxis(void) const;
        void                   SetTubeSemiMinorAxis(double length);

        void                   Set(const Vector3D& center,
                                   const Vector3D& normalToTubeCenterLinePlane,
                                   double          tubeCenterLineRadius,
                                   const Vector3D& tubeSemiMajorAxis,
                                   double          tubeSemiMinorAxisLength);

        // inherited from BRLCAD::Object
        virtual const Object&  operator=(const Object& original);
        virtual Object*        Clone(void) const;
        static const char*     ClassName(void);
        virtual const char*    Type(void) const;
        virtual bool           IsValid(void) const; ///< checks if normal has positive length, if radii are not 0 and if ellipse not overlap itself when revolved

    protected:
        EllipticalTorus(resource*       resp,
                        directory*      pDir,
                        rt_db_internal* ip,
                        db_i*           dbip);

        friend class ConstDatabase;

    private:
        rt_eto_internal* m_internalp;

        const rt_eto_internal* Internal(void) const;
        rt_eto_internal*       Internal(void);

        friend class Database;
    };
}


#endif // BRLCAD_ELLIPTICALTORUS_INCLUDED
