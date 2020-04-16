/*                      F I L E D A T A B A S E . C P P
 * BRL-CAD
 *
 * Copyright (c) 2008-2020 United States Government as represented by
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
/** @file FileDatabase.cpp
 *
 *  BRL-CAD core C++ interface:
 *      implements a handle on a writable file-based database
 */

#include "raytrace.h"
#include "bu/parallel.h"

#include <brlcad/Database/FileDatabase.h>


using namespace BRLCAD;


FileDatabase::FileDatabase(void) : Database() {}


FileDatabase::~FileDatabase(void) {}


bool FileDatabase::Load
(
    const char* fileName
) {
    bool ret = false;

    if (m_resp != 0) {
        if (m_rtip != 0) {
            if (!BU_SETJUMP)
                rt_free_rti(m_rtip);

            BU_UNSETJUMP;
            m_rtip = 0;
        }

        if (m_wdbp != 0) {
            if (!BU_SETJUMP)
                wdb_close(m_wdbp);

            BU_UNSETJUMP;
            m_wdbp = 0;
        }

        if (!BU_SETJUMP) {
            struct db_i* dbip = db_open(fileName, "rw");

            if (dbip != DBI_NULL) {
                if (db_dirbuild(dbip) != 0) {
                    db_close(dbip);
                    dbip = DBI_NULL;
                }
            }
            else
                dbip = db_create(fileName, 5);

            if (dbip != DBI_NULL) {
                m_wdbp = wdb_dbopen(dbip, RT_WDB_TYPE_DB_DISK); // takes ownership of dbip

                if (m_wdbp != 0) {
                    m_rtip = rt_new_rti(m_wdbp->dbip);          // clones dbip

                    if (m_rtip != 0) {
                        rt_init_resource(m_resp, 0, m_rtip);
                        ret = true;
                    }
                    else {
                        wdb_close(m_wdbp);
                        m_wdbp = 0;
                    }
                }
                else
                    db_close(dbip);
            }
        }
        else {
            m_wdbp = 0;
            m_rtip = 0;
        }

        BU_UNSETJUMP;
    }

    return ret;
}
