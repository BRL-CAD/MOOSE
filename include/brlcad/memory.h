/*                      M E M O R Y . H
 * BRL-CAD
 *
 * Copyright (c) 2008-2020 United States Government as represented by
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
/** @file memory.h
 *
 *  BRL-CAD core C++ interface:
 *      memory related stuff
 */

#ifndef BRLCAD_MEMORY_INCLUDED
#define BRLCAD_MEMORY_INCLUDED

#include <new>


namespace BRLCAD {
    class bad_alloc : public std::bad_alloc {
    public:
        bad_alloc(const char* hint) : std::bad_alloc(), m_hint(hint) {}

        bad_alloc(const bad_alloc& original) : std::bad_alloc(original), m_hint(original.m_hint) {}

        virtual const bad_alloc& operator=(const bad_alloc& original) {
            std::bad_alloc::operator=(original);
            m_hint = original.m_hint;

            return *this;
        }

        virtual const char* what(void) const throw(){
            return m_hint;
        }

    private:
        const char* m_hint;

        bad_alloc(void); // not implemented
    };
}


#endif // BRLCAD_MEMORY_INCLUDED
