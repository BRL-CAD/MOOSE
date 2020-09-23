/*                      G L O B A L S . H
 * BRL-CAD
 *
 * Copyright (c) 2011-2020 United States Government as represented by
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
/** @file globals.h
 *
 *  BRL-CAD core C++ interface:
 *      declares global functions which influence the behavior
 *      of the BRL-CAD core
 */

#ifndef BRLCAD_GLOBALS_INCLUDED
#define BRLCAD_GLOBALS_INCLUDED

#include <functional>


namespace BRLCAD {
    /// @name get BRL-CAD version information
    //@{
    int BRLCAD_MOOSE_EXPORT  MajorVersion(void);
    int BRLCAD_MOOSE_EXPORT  MinorVersion(void);
    int BRLCAD_MOOSE_EXPORT  PatchVersion(void);
    //@}


    /// @name capturing the logging output
    //@{
    /// log handler (to be implemented by the caller)
    typedef std::function<void(const char* logString)> LogHandler;

    void BRLCAD_MOOSE_EXPORT RegisterLogHandler(LogHandler& logHandler);
    void BRLCAD_MOOSE_EXPORT DeRegisterLogHandler(LogHandler& logHandler);
    //@}
}


#endif // BRLCAD_GLOBALS_INCLUDED
