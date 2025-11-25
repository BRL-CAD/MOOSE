/*                      M E M O R Y D A T A B A S E . H
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
/** @file MemoryDatabase.h
 *
 *  BRL-CAD core C++ interface:
 *      declares a handle for an in-memory database
 */

#ifndef BRLCAD_MEMORYDATABASE_INCLUDED
#define BRLCAD_MEMORYDATABASE_INCLUDED

#include <brlcad/Database/Database.h>


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT MemoryDatabase : public Database {
    public:
        /// creates a new in-memory database with default _GLOBAL object
        MemoryDatabase(void);
        ~MemoryDatabase(void) override;

        /// loads a BRL-CAD database file (*.g) into the memory
        /** The old content of the in-memory database will be discarded.
            The file will be opened for reading only and closed after finishing the operation. */
        bool Load(const char* fileName) override;
        bool Load(const void* data,
                  size_t      dataSize);
        bool Save(const char* fileName);

    private:
        MemoryDatabase(const MemoryDatabase&);                  // not implemented
        const MemoryDatabase& operator=(const MemoryDatabase&); // not implemented
    };
}


#endif // BRLCAD_MEMORYDATABASE_INCLUDED
