/*          P A R A B O L I C C Y L I N D E R . H
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
/** @file ParabolicCylinder.h
 *
 *  BRL-CAD core C++ interface:
 *      right parabolic cylinder (ID_RPC) database object declaration
 */

#ifndef BRLCAD_PARABOLICCYLINDER_INCLUDED
#define BRLCAD_PARABOLICCYLINDER_INCLUDED

#include <brlcad/vector.h>
#include <brlcad/Database/Object.h>


struct rt_rpc_internal;


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT ParabolicCylinder : public Object {
    public:
        ParabolicCylinder(void);                               ///< Constructs a parabolic cylinder at origin with unit height unit depth and unit half width
        ParabolicCylinder(const Vector3D& basePoint,
                          const Vector3D& height,
                          const Vector3D& depth,
                          double          halfWidth);
        ParabolicCylinder(const ParabolicCylinder& original);
        ~ParabolicCylinder(void) override;

        const ParabolicCylinder& operator=(const ParabolicCylinder& original);

        Vector3D                 BasePoint(void) const;
        void                     SetBasePoint(const Vector3D& basePoint);

        Vector3D                 Height(void) const;
        void                     SetHeight(const Vector3D& height);

        Vector3D                 Depth(void) const;
        void                     SetDepth(const Vector3D& depth);

        double                   HalfWidth(void) const;
        void                     SetHalfWidth(double length);

        void                     Set(const Vector3D& basePoint,
                                     const Vector3D& height,
                                     const Vector3D& depth,
                                     double          halfWidth);

        // inherited from BRLCAD::Object
        const Object&            operator=(const Object& original) override;
        Object*                  Clone(void) const override;
        static const char*       ClassName(void);
        const char*              Type(void) const override;
        bool                     IsValid(void) const override; ///< checks for positive length of height and depth, positive value of half width and that height and depth are perpendicular

    protected:
        ParabolicCylinder(resource*       resp,
                          directory*      pDir,
                          rt_db_internal* ip,
                          db_i*           dbip);

        friend class ConstDatabase;

    private:
        rt_rpc_internal* m_internalp;

        rt_rpc_internal*       Internal(void);
        const rt_rpc_internal* Internal(void) const;

        friend class Database;
    };
}


#endif // BRLCAD_PARABOLICCYLINDER_INCLUDED
