/*                      H A N D L E . H
 * BRL-CAD
 *
 * Copyright (c) 2026 United States Government as represented by
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
/** @file Handle.h
 *
 *  BRL-CAD core C++ interface:
 *      declares the base for all classes, which shall get a handle
 *      in the simplified C interface
 */

#ifndef BRLCAD_HANDLE_INCLUDED
#define BRLCAD_HANDLE_INCLUDED


namespace BRLCAD {
    class Handle {
    public:
        Handle(void);
        Handle(const char* magic);
        virtual ~Handle(void);

    protected:
        const char* m_magic;
    };

    extern const char* const Arb8Magic;
    extern const char* const ConstDatabaseMagic;
    extern const char* const ObjectMagic;
    extern const char* const VectorListMagic;
}


#endif // BRLCAD_HANDLE_INCLUDED
