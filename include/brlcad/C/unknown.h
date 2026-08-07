/*                      U N K N O W N . H
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
/** @file unknown.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares a handle and functions for Unknown solid handling
 */


#ifndef BRLCAD_C_UNKNOWN_INCLUDED
#define BRLCAD_C_UNKNOWN_INCLUDED

#include <brlcad/C/object.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef BrlObject BrlUnknown;


BRLCAD_MOOSE_EXPORT BrlUnknown  BrlUnknownClone(BrlUnknown unknown);

BRLCAD_MOOSE_EXPORT const char* BrlUnknownType(BrlUnknown unknown);

BRLCAD_MOOSE_EXPORT int         BrlUnknownIsValid(BrlUnknown unknown);

BRLCAD_MOOSE_EXPORT const char* BrlUnknownClassName(void);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_UNKNOWN_INCLUDED
