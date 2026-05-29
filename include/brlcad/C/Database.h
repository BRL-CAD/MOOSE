/*                      D A T A B A S E . H
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
/** @file Database.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares functions for a writable database
 */

#ifndef BRLCAD_C_DATABASE_INCLUDED
#define BRLCAD_C_DATABASE_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


typedef void* BrlDatabase;


BRLCAD_MOOSE_EXPORT void BrlDatabaseSetTitle(BrlDatabase db,
                                             const char* title);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_DATABASE_INCLUDED
