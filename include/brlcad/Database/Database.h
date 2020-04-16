/*                      D A T A B A S E . H
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
/** @file Database.h
 *
 *  BRL-CAD core C++ interface:
 *      declares the common part of the handles on a writable database
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

        class ObjectCallback {
        public:
            virtual ~ObjectCallback(void) {}

            /// the user has to implement this object method to evaluate and modify the object
            virtual void operator()(Object& object) = 0;

        protected:
            ObjectCallback(void) {}
            ObjectCallback(const ObjectCallback&) {}
            const ObjectCallback& operator=(const ObjectCallback&) {return *this;}
        };

        /// selects a single object and hand it over to an ObjectCallback (for read and write)
        void         Get(const char*     objectName,
                         ObjectCallback& callback);

        /// provided for convenience: selects a single object and sets it to \a object
        /** The type of the object in the database and \a object must match. */
        void         Set(const Object& object);
        //@}

    protected:
        rt_wdb* m_wdbp;

        Database(void);

    private:
        Database(const Database&);                  // not implemented
        const Database& operator=(const Database&); // not implemented
    };
}


#endif // BRLCAD_DATABASE_INCLUDED
