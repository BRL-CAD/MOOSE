/*                    C O M M A N D S T R I N G . H
 * BRL-CAD
 *
 * Copyright (c) 2022-2025 United States Government as represented by
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
/** @file CommandString.h
 *
 *  BRL-CAD core C++ interface:
 *      libged command string parser module
 */

#ifndef BRLCAD_COMMANDSTRING_INCLUDED
#define BRLCAD_COMMANDSTRING_INCLUDED

#include <vector>

#include <brlcad/Database/Database.h>


struct ged;


namespace BRLCAD {
    class BRLCAD_MOOSE_EXPORT CommandString {
    public:
        CommandString(Database& database);
        ~CommandString(void);

        bool Parse(const std::vector<const char*>& arguments);

        enum class ParseFlag {
            Ok,        // Command execution was successful (no further informations)
            Help,      // Invalid command, the Result string contains usage informations
            More,      // Incomplete specification, the Result string will ask for more parameters
            Quiet,     // Command won't set or modify the Result string
            Unknown,   // Unknown command (arguments.front() not recognized)
            Exit,      // Command is requesting a clean application shutdown
            Override,  // Indicates settings have been overridden
            Undefined
        };

        bool Parse(const std::vector<const char*>& arguments,
                   ParseFlag                       flag);

        const char* Results(void) const;
        size_t      NumberOfResults(void) const;
        const char* Result(size_t index) const;
        void        ClearResults(void);

        void        CompleteCommand(const char*                                          pattern,
                                    const std::function<bool(const char* commandMatch)>& callback);
        void        CompleteObject(const char*                                         pattern,
                                   const std::function<bool(const char* objectMatch)>& callback);

    private:
        ged* m_ged;

        CommandString(void);                                  // not implemented
        CommandString(const CommandString&);                  // not implemented
        const CommandString& operator=(const CommandString&); // not implemented
    };
}


#endif // BRLCAD_COMMANDSTRING_INCLUDED
