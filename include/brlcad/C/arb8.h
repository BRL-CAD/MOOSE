/*                      A R B 8 . H
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
/** @file arb8.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares a handle and functions for Arb8 geometry construction
 */

#ifndef BRLCAD_C_ARB8_INCLUDED
#define BRLCAD_C_ARB8_INCLUDED

#include <brlcad/C/handle.h>

#ifdef __cplusplus
extern "C" {
#endif

// Creates an Arb8 by passing 2 points (diagonals for a box)
BRLCAD_MOOSE_EXPORT BrlHandle BrlNewArb8FromBox(const double* p1, const double* p2);

// Creates an Arb8 by passing all 8 points (24 numbers total)
BRLCAD_MOOSE_EXPORT BrlHandle BrlNewArb8FromPoints(const double* flatPoints24);

#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_ARB8_INCLUDED