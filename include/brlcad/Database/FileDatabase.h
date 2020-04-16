/*                      F I L E D A T A B A S E . H
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
/** @file FileDatabase.h
 *
 *  BRL-CAD core C++ interface:
 *      declares a handle on a writable file-based database
 */

#ifndef BRLCAD_FILEDATABASE_INCLUDED
#define BRLCAD_FILEDATABASE_INCLUDED

#include <brlcad/Database/Database.h>


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT FileDatabase : public Database {
    public:
        /// creates a dysfunctional database
        /** Use Load() to enable this object. */
        FileDatabase(void);
        virtual ~FileDatabase(void);

        /// loads a BRL-CAD database file (*.g)
        /** If the file doesn't exist it will becreated
         *  All changes to the database will be immediately written to this file. */
        virtual bool Load(const char* fileName);

    private:
        FileDatabase(const FileDatabase&);                  // not implemented
        const FileDatabase& operator=(const FileDatabase&); // not implemented
    };
}


#endif // BRLCAD_FILEDATABASE_INCLUDED
