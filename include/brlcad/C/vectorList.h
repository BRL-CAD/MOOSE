/*                           V E C T O R L I S T . H
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
/** @file vectorList.h
 *
 *  BRL-CAD core simplified C interface:
 *       header for VectorList opaque wrapper 
 */

#ifndef BRLCAD_C_VECTORLIST_INCLUDED
#define BRLCAD_C_VECTORLIST_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


typedef void* BrlVectorList;


BRLCAD_MOOSE_EXPORT BrlVectorList BrlNewVectorList(void);

BRLCAD_MOOSE_EXPORT void          BrlDeleteVectorList(BrlVectorList vlist);

BRLCAD_MOOSE_EXPORT void          BrlVectorListClear(BrlVectorList vlist);

#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_VECTORLIST_INCLUDED
