/*                         C A S T S . H
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
/** @file casts.h
 *
 *  BRL-CAD core simplified C interface:
 *      declares helper functions to cast void* handles to the correct C++ class
 */

#ifndef BRLCAD_C_CASTS_INCLUDED
#define BRLCAD_C_CASTS_INCLUDED

#include <brlcad/Database/ConstDatabase.h>
#include <brlcad/Database/Database.h>
#include <brlcad/Database/Object.h>


BRLCAD::Handle*        CastHandle(void* handle);

BRLCAD::ConstDatabase* CastConstDatabase(void* handle);

BRLCAD::Database*      CastDatabase(void* handle);

BRLCAD::Object*        CastObject(void* handle);


#endif // BRLCAD_C_CASTS_INCLUDED
