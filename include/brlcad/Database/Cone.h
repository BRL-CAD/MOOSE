/*                      C O N E . H
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
/** @file Cone.h
 *
 *  BRL-CAD core C++ interface:
 *      truncated general cone (ID_TGC) database object declaration
 */

#ifndef BRLCAD_CONE_INCLUDED
#define BRLCAD_CONE_INCLUDED

#include <brlcad/vector.h>
#include <brlcad/Database/Object.h>


struct rt_tgc_internal;


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT Cone : public Object {
    public:
        Cone(void);                                                 ///< constructs a cone at the origin with unit radius and unit height
        Cone(const Vector3D& basePoint,
             const Vector3D& height,
             const Vector3D& semiPrincipalAxisA,
             const Vector3D& semiPrincipalAxisB,
             double          ratioCtoA,
             double          ratioDtoB);                            ///< tgc: basePoint, height, two perpendicular semi principal axes of base face and two scalars for the semi principal axes of top face
        Cone(const Vector3D& basePoint,
             const Vector3D& height,
             const Vector3D& semiPrincipalAxisA,
             const Vector3D& semiPrincipalAxisB,
             double          scale);                                ///< tec: basePoint, height, two perpendicular semi principal axes of base face and one ratio for scaling the semi principal axes of top face
        Cone(const Vector3D& basePoint,
             const Vector3D& height,
             const Vector3D& semiPrincipalAxisA,
             const Vector3D& semiPrincipalAxisB);                   ///< rec: basePoint, height, two perpendicular semi principal axes of base and top face
        Cone(const Vector3D& basePoint,
             const Vector3D& height,
             double          radiusBase,
             double          radiusTop);                            ///< trc: basePoint, height and two radii for base and top face respectively
        Cone(const Vector3D& basePoint,
             const Vector3D& height,
             double          radius);                               ///< rcc: basePoint, height and one radius for base and top face
        Cone(const Cone& original);
        ~Cone(void) override;

        const Cone&        operator=(const Cone& original);

        Vector3D           BasePoint(void) const;
        void               SetBasePoint(const Vector3D& basePoint);

        Vector3D           Height(void) const;
        void               SetHeight(const Vector3D& height);

        /// semi principal axes (base and top face) are accessed by their index (0/1/2/3 for the vectos a/b/c/d)
        Vector3D           SemiPrincipalAxis(size_t index) const;
        void               SetSemiPrincipalAxis(size_t          index,
                                                const Vector3D& semiPrincipalAxis);

        void               Set(const Vector3D& basePoint,
                               const Vector3D& height,
                               const Vector3D& semiPrincipalAxisA,
                               const Vector3D& semiPrincipalAxisB,
                               double          ratioCtoA,
                               double          ratioDtoB);          ///< truncated general cone (tgc)
        void               Set(const Vector3D& basePoint,
                               const Vector3D& height,
                               const Vector3D& semiPrincipalAxisA,
                               const Vector3D& semiPrincipalAxisB,
                               double          scale);              ///< truncated elliptical cone (tec)
        void               Set(const Vector3D& basePoint,
                               const Vector3D& height,
                               const Vector3D& semiPrincipalAxisA,
                               const Vector3D& semiPrincipalAxisB); ///< right elliptical cylinder (rec)
        void               Set(const Vector3D& basePoint,
                               const Vector3D& height,
                               double          radiusBase,
                               double          radiusTop);          ///< truncated right cone (trc)
        void               Set(const Vector3D& basePoint,
                               const Vector3D& height,
                               double          radius);             ///< right circular cylinder (rcc)

        // inherited from BRLCAD::Object
        const Object&      operator=(const Object& original) override;
        Object*            Clone(void) const override;
        static const char* ClassName(void);
        const char*        Type(void) const override;
        bool               IsValid(void) const override;            ///< checks if semi-principal axes are perpendicular, if the ones at the base have positive length, if height has positive length and is not in the plane of semi-principal axes and if corresponding base and top semi principal axes are parallel and pointing to the same direction

    protected:
        Cone(resource*       resp,
             directory*      pDir,
             rt_db_internal* ip,
             db_i*           dbip);

        friend class ConstDatabase;

    private:
        rt_tgc_internal* m_internalp;

        rt_tgc_internal*       Internal(void);
        const rt_tgc_internal* Internal(void) const;

        friend class Database;
    };
}


#endif // BRLCAD_CONE_INCLUDED
