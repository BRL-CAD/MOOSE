/*                      S P H E R E . H
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
/** @file Sphere.h
 *
 *  BRL-CAD core C++ interface:
 *      sphere (ID_SPH) database object declaration
 */

#ifndef BRLCAD_SPHERE_INCLUDED
#define BRLCAD_SPHERE_INCLUDED

#include <brlcad/vector.h>
#include <brlcad/Database/Object.h>


struct rt_ell_internal;


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT Sphere : public Object {
    public:
        Sphere(void);
        Sphere(const  Vector3D& center,
               double radius);
        Sphere(const Sphere& original);
        ~Sphere(void) override;

        const Sphere&      operator=(const Sphere& original);

        Vector3D           Center(void) const;
        void               SetCenter(const Vector3D& normal);
        double             Radius(void) const;
        void               SetRadius(double distance);
        void               Set(const Vector3D& center,
                               double          radius);

        // inherited from BRLCAD::Object
        const Object&      operator=(const Object& original) override;
        Object*            Clone(void) const override;
        static const char* ClassName(void);
        const char*        Type(void) const override;
        bool               IsValid(void) const override;

    protected:
        Sphere(resource*       resp,
               directory*      pDir,
               rt_db_internal* ip,
               db_i*           dbip = nullptr);

        friend class ConstDatabase;

    private:
        // holds Objects's content if not connected to a database
        rt_ell_internal* m_internalp;

        const rt_ell_internal* Internal(void) const;
        rt_ell_internal*       Internal(void);

        friend class Database;
    };
}


#endif // BRLCAD_SPHERE_INCLUDED
