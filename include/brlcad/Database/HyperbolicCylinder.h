/*          H Y P E R B O L I C C Y L I N D E R . H
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
/** @file HyperbolicCylinder.h
 *
 *  BRL-CAD core C++ interface:
 *      right hyperbolic cylinder (ID_RHC) database object declaration
 */

#ifndef BRLCAD_HYPERBOLICCYLINDER_INCLUDED
#define BRLCAD_HYPERBOLICCYLINDER_INCLUDED

#include <brlcad/vector.h>
#include <brlcad/Database/Object.h>


struct rt_rhc_internal;


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT HyperbolicCylinder : public Object {
    public:
        HyperbolicCylinder(void); ///< constructs a hyperbolic cylinder at origin with unit height, unit depth in x direction, unit half width and apex to asymptotes distance of 1
        HyperbolicCylinder(const Vector3D& basePoint,
                           const Vector3D& height,
                           const Vector3D& depth,
                           double          halfWidth,
                           double          apexAsymptoteDistance);
        HyperbolicCylinder(const HyperbolicCylinder& original);
        virtual ~HyperbolicCylinder(void);

        const HyperbolicCylinder& operator=(const HyperbolicCylinder& original);

        Vector3D                  BasePoint(void) const;
        void                      SetBasePoint(const Vector3D& basePoint);

        Vector3D                  Height(void) const;
        void                      SetHeight(const Vector3D& height);

        Vector3D                  Depth(void) const;
        void                      SetDepth(const Vector3D& depth);

        double                    HalfWidth(void) const;
        void                      SetHalfWidth(double length);

        double                    ApexAsymptoteDistance(void) const;
        void                      SetApexAsymptoteDistance(double distance);

        void                      Set(const Vector3D& basePoint,
                                      const Vector3D& height,
                                      const Vector3D& depth,
                                      double          halfWidth,
                                      double          apexAsymptoteDistance);

        // inherited from BRLCAD::Object
        virtual const Object&     operator=(const Object& original);
        virtual Object*           Clone(void) const;
        static const char*        ClassName(void);
        virtual const char*       Type(void) const;
        virtual bool              IsValid(void) const; ///< checks for positive length of height and depth, positive values of half width and apex to asymptotes distance and that height and depth are perpendicular

    protected:
        HyperbolicCylinder(resource*       resp,
                           directory*      pDir,
                           rt_db_internal* ip,
                           db_i*           dbip);

        friend class ConstDatabase;

    private:
        rt_rhc_internal* m_internalp;

        rt_rhc_internal*       Internal(void);
        const rt_rhc_internal* Internal(void) const;

        friend class Database;
    };
}


#endif // BRLCAD_HYPERBOLICCYLINDER_INCLUDED
