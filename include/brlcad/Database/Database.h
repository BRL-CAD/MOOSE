/*                      D A T A B A S E . H
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
/** @file Database.h
 *
 *  BRL-CAD core C++ interface:
 *      declares the common part of handles for writable databases
 */

#ifndef BRLCAD_DATABASE_INCLUDED
#define BRLCAD_DATABASE_INCLUDED

#include <brlcad/Database/ConstDatabase.h>


struct rt_wdb;


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT Database : public ConstDatabase {
    public:
        virtual ~Database(void);

        /// loads a BRL-CAD database file (*.g)
        /** The implementation will be determed by the subclasses. */
        virtual bool Load(const char* fileName) = 0;

        void         SetTitle(const char* title);

        /// adds an object to the database
        bool         Add(const Object& object);

        /// removes an object from the database
        /** The object but not its references are removed. */
        void         Delete(const char* objectName);

        /// @name Accessing objects
        //@{
        using ConstDatabase::Get;

        /// selects a single object and hand it over to a callback (for read and write)
        bool         Get(const char*                                objectName,
                         const std::function<void(Object& object)>& callback);

        /// provided for convenience: selects a single object and sets it to \a object
        /** The type of the object in the database and \a object must match. */
        bool         Set(const Object& object);
        //@}

    protected:
        rt_wdb* m_wdbp;

        Database(void);

    private:
        friend class CommandString;

        Database(const Database&);                  // not implemented
        const Database& operator=(const Database&); // not implemented
    };
}


#endif // BRLCAD_DATABASE_INCLUDED
