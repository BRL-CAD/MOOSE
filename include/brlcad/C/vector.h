/*                      V E C T O R . H
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
/** @file vector.h
 *
 *  BRL-CAD core simplified C interface:
 *      declarations of vector data types
 */

#ifndef BRLCAD_C_VECTOR_INCLUDED
#define BRLCAD_C_VECTOR_INCLUDED

#include <brlcad/C/globals.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef BrlHandle BrlVector3D;


double BrlVector3DX(BrlVector3D vector);
double BrlVector3DY(BrlVector3D vector);
double BrlVector3DZ(BrlVector3D vector);


#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_GLOBALS_INCLUDED
