/*                      C O N S T D A T A B A S E . H
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
/** @file ConstDatabase.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares a handle and functions for a read-only database
 */

#ifndef BRLCAD_C_CONSTDATABASE_INCLUDED
#define BRLCAD_C_CONSTDATABASE_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


typedef void* BrlConstDatabase;


BRLCAD_MOOSE_EXPORT BrlConstDatabase BrlNewConstDatabase(void);
BRLCAD_MOOSE_EXPORT void             BrlDeleteConstDatabase(BrlConstDatabase db);

BRLCAD_MOOSE_EXPORT int              BrlConstDatabaseLoad(BrlConstDatabase db,
                                                          const char*      fileName);

BRLCAD_MOOSE_EXPORT const char*      BrlConstDatabaseTitle(BrlConstDatabase db);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_CONSTDATABASE_INCLUDED
