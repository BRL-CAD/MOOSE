/*                      U N K N O W N . H
 * BRL-CAD
 *
 * Copyright (c) 2008-2025 United States Government as represented by
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
/** @file Unknown.h
 *
 *  BRL-CAD core C++ interface:
 *      yet unknown database object declaration
 */

#ifndef BRLCAD_UNKNOWN_INCLUDED
#define BRLCAD_UNKNOWN_INCLUDED

#include <brlcad/Database/Object.h>


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT Unknown : public Object {
    public:
        Unknown(const Unknown& original);
        virtual ~Unknown(void);

        const Unknown&        operator=(const Unknown& original);

        // inherited from BRLCAD::Object
        virtual const Object& operator=(const Object& original);
        virtual Object*       Clone(void) const;
        static const char*    ClassName(void);
        virtual const char*   Type(void) const;
        virtual bool          IsValid(void) const;

        // there is nothing special with BRLCAD::Unknown

    protected:
        Unknown(resource*       resp,
                directory*      pDir,
                rt_db_internal* ip,
                db_i*           dbip = nullptr);

        friend class ConstDatabase;

    private:
        Unknown(void); // not implemented
    };
}


#endif // BRLCAD_UNKNOWN_INCLUDED
