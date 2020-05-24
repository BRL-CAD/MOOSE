/*                         I N I T . C P P
 * BRL-CAD
 *
 * Copyright (c) 2020 United States Government as represented by
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
/** @file init.cpp
 *
 *  BRL-CAD core C++ interface:
 *      private initialization function implementation
 */

#include "bu/parallel.h"
#include "rt/global.h"

#include "init.h"


static int NullLogger
(
    void* data,
    void* string
) {
    return 0;
}


void InitBrlCad(void) {
    static bool init = true;

    if (init) { // do it only once
        init = false;

        if (!BU_SETJUMP) {
            BU_LIST_INIT(&RTG.rtg_vlfree);
            bu_log_add_hook(NullLogger, 0);
        }

        BU_UNSETJUMP;
    }
}
