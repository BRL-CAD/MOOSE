/*                         G L O B A L S . H
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
/** @file globals.h
 *
 *  BRL-CAD core simplified C interface:
 *      declarations of general types and functions
 */

#ifndef BRLCAD_C_GLOBALS_INCLUDED
#define BRLCAD_C_GLOBALS_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


BRLCAD_MOOSE_EXPORT int BrlMajorVersion(void);
BRLCAD_MOOSE_EXPORT int BrlMinorVersion(void);
BRLCAD_MOOSE_EXPORT int BrlPatchVersion(void);


typedef struct BrlData* BrlHandle;

BRLCAD_MOOSE_EXPORT void BrlDeleteHandle(BrlHandle handle);


typedef void (*BrlLogHandler)(const char* logString,
                              void*       environmentHandle);

BRLCAD_MOOSE_EXPORT void BrlRegisterLogHandler(BrlLogHandler logHandler,
                                               void*         environmentHandle);
BRLCAD_MOOSE_EXPORT void BrlDeRegisterLogHandler(BrlLogHandler logHandler);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_GLOBALS_INCLUDED
