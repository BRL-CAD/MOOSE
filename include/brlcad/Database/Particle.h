/*                    P A R T I C L E . H
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
/** @file Particle.h
 *
 *  BRL-CAD core C++ interface:
 *      particle (ID_PARTICLE) database object declaration
 */

#ifndef BRLCAD_PARTICLE_INCLUDED
#define BRLCAD_PARTICLE_INCLUDED

#include <brlcad/vector.h>
#include <brlcad/Database/Object.h>


struct rt_part_internal;


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT Particle : public Object {
    public:
        Particle(void);                                  ///< constructs a particle at the origin with hight (0, 0, 1) and radii 1
        Particle(const Vector3D& basePoint,
                 const Vector3D& height,
                 double          baseRadius,
                 double          topRadius);
        Particle(const Particle& original);
        ~Particle(void) override;

        const Particle&    operator=(const Particle& original);

        Vector3D           BasePoint(void) const;
        void               SetBasePoint(const Vector3D& basePoint);

        Vector3D           Height(void) const;
        void               SetHeight(const Vector3D& height);

        double             BaseRadius(void) const;
        void               SetBaseRadius(double baseRadius);

        double             TopRadius(void) const;
        void               SetTopRadius(double topRadius);

        void               Set(const Vector3D& basePoint,
                               const Vector3D& height,
                               double          baseRadius,
                               double          topRadius);

        // inherited from BRLCAD::Object
        const Object&      operator=(const Object& original) override;
        Object*            Clone(void) const override;
        static const char* ClassName(void);
        const char*        Type(void) const override;
        bool               IsValid(void) const override; ///< checks for positive radii, one radius > 0 and if the height is 0 the radii have to be equal

    protected:
        Particle(resource*       resp,
                 directory*      pDir,
                 rt_db_internal* ip,
                 db_i*           dbip);

        friend class ConstDatabase;

    private:
        rt_part_internal* m_internalp;

        void                    SetType(void);

        const rt_part_internal* Internal(void) const;
        rt_part_internal*       Internal(void);

        friend class Database;
    };
}


#endif // BRLCAD_PARTICLE_INCLUDED
