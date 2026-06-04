/*                      F I L E D A T A B A S E . C P P
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
/** @file fileDatabase.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements a handle and functions for a read-write file based
 *      database
 */

#include <brlcad/Database/FileDatabase.h>

#include <brlcad/C/fileDatabase.h>

#include "Handle.h"


using namespace BRLCAD;


BrlFileDatabase BrlNewFileDatabase(void) {
    return new FileDatabaseHandle(new FileDatabase);
}
