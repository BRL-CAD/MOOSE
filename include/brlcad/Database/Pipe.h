/*                      P I P E . H
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
/** @file Pipe.h
 *
 *  BRL-CAD core C++ interface:
 *      pipe (ID_PIPE) database object declaration
 */

#ifndef BRLCAD_PIPE_INCLUDED
#define BRLCAD_PIPE_INCLUDED

#include <brlcad/vector.h>
#include <brlcad/Database/Object.h>


struct rt_pipe_internal;
struct wdb_pipe_pnt;


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT Pipe : public Object {
    public:
        Pipe(void);
        Pipe(const Pipe& original);
        ~Pipe(void) override;

        const Pipe&        operator=(const Pipe& original);

        class BRLCAD_MOOSE_EXPORT ControlPoint {
        public:
            ControlPoint(void) : m_pipe(nullptr), m_controlPoint(nullptr) {}
            ControlPoint(const ControlPoint& original) : m_pipe(original.m_pipe), m_controlPoint(original.m_controlPoint) {}
            ~ControlPoint(void) {}

            const ControlPoint& operator=(const ControlPoint& original) {
                m_pipe         = original.m_pipe;
                m_controlPoint = original.m_controlPoint;

                return *this;
            }

                                operator void*(void) {
                return m_pipe;
            }

            Vector3D            Point(void) const;
            void                SetPoint(const Vector3D& point);

            double              InnerDiameter(void) const;
            void                SetInnerDiameter(double id);

            double              OuterDiameter(void) const;
            void                SetOuterDiameter(double od);

            double              BendRadius(void) const;
            void                SetBendRadius(double br);

        private:
            rt_pipe_internal* m_pipe;
            wdb_pipe_pnt*     m_controlPoint;

            ControlPoint(rt_pipe_internal* pipe,
                         wdb_pipe_pnt*     controlPoint) : m_pipe(pipe), m_controlPoint(controlPoint) {}

            friend class Pipe;
        };

        size_t             NumberOfControlPoints(void) const;
        ControlPoint       GetControlPoint(size_t index);
        ControlPoint       AppendControlPoint(const Vector3D& point,
                                              double          innerDiameter,
                                              double          outerDiameter,
                                              double          bendRadius);
        ControlPoint       InsertControlPoint(size_t          index,
                                              const Vector3D& point,
                                              double          innerDiameter,
                                              double          outerDiameter,
                                              double          bendRadius);
        void               DeleteControlPoint(size_t index);

        // inherited from BRLCAD::Object
        const Object&      operator=(const Object& original) override;
        Object*            Clone(void) const override;
        static const char* ClassName(void);
        const char*        Type(void) const override;
        bool               IsValid(void) const override;

    protected:
        Pipe(resource*       resp,
             directory*      pDir,
             rt_db_internal* ip,
             db_i*           dbip = nullptr);

        friend class ConstDatabase;

    private:
        rt_pipe_internal* m_internalp;

        const rt_pipe_internal* Internal(void) const;
        rt_pipe_internal*       Internal(void);

        friend class Database;
    };
};


#endif // BRLCAD_PIPE_INCLUDED
