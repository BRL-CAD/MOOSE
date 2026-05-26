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


typedef BrlHandle BrlArb8;


BRLCAD_MOOSE_EXPORT BrlArb8 BrlNewArb8FromBoxCoords(
	double p1x, double p1y, double p1z,
	double p2x, double p2y, double p2z);

BRLCAD_MOOSE_EXPORT BrlArb8 BrlNewArb8From4Points(
	double p1x, double p1y, double p1z,
	double p2x, double p2y, double p2z,
	double p3x, double p3y, double p3z,
	double p4x, double p4y, double p4z);

BRLCAD_MOOSE_EXPORT BrlArb8 BrlNewArb8From8Points(
	double p1x, double p1y, double p1z,
	double p2x, double p2y, double p2z,
	double p3x, double p3y, double p3z,
	double p4x, double p4y, double p4z,
	double p5x, double p5y, double p5z,
	double p6x, double p6y, double p6z,
	double p7x, double p7y, double p7z,
	double p8x, double p8y, double p8z);

    
#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_ARB8_INCLUDED