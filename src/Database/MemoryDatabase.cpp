/*                      M E M O R Y D A T A B A S E . C P P
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
/** @file MemoryDatabase.cpp
 *
 *  BRL-CAD core C++ interface:
 *      implements a handle on an in-memory database
 */

#include <cassert>

#include "raytrace.h"
#include "bu/parallel.h"

#include <brlcad/Database/MemoryDatabase.h>


using namespace BRLCAD;


MemoryDatabase::MemoryDatabase(void) : Database() {
    db_i* dbip = 0;

    if (!BU_SETJUMP) {
        dbip = db_create_inmem();
        RT_CK_DBI(dbip);
    }

    BU_UNSETJUMP;

    if (!BU_SETJUMP) {
        m_rtip = rt_new_rti(dbip); // clones dbip
        rt_init_resource(m_resp, 0, m_rtip);
    }
    else {
        BU_UNSETJUMP;
        db_close(dbip);
        m_rtip = 0;
    }

    BU_UNSETJUMP;

    m_wdbp = dbip->dbi_wdbp;   // takes ownership of dbip
}


MemoryDatabase::~MemoryDatabase(void) {}


bool MemoryDatabase::Load
(
    const char* fileName
) {
    bool ret = false;

    if (!BU_SETJUMP) {
        rt_i* source = rt_dirbuild(fileName, 0, 0);

        if (source != 0) {
            // free old database
            if (m_wdbp != 0) {
                wdb_close(m_wdbp);
                m_wdbp = 0;
            }

            if (m_rtip != 0) {
                rt_free_rti(m_rtip);
                m_rtip = 0;
            }

            // build new database
            db_i* dbip = db_open_inmem();
            RT_CK_DBI(dbip);

            m_rtip = rt_new_rti(dbip);
            rt_init_resource(m_resp, 0, m_rtip);
            m_wdbp = dbip->dbi_wdbp;

            // fill database
            ret = (db_dump(m_wdbp, source->rti_dbip) == 0);

            assert(m_wdbp->dbip == m_rtip->rti_dbip);
            db_update_ident(m_wdbp->dbip, source->rti_dbip->dbi_title, source->rti_dbip->dbi_base2local);

            rt_free_rti(source);
        }
    }

    BU_UNSETJUMP;

    return ret;
}


bool MemoryDatabase::Load
(
    const void* data,
    size_t      dataSize
) {
    bool ret = false;

    if (!BU_SETJUMP) {
        rt_i* source = rt_dirbuild_inmem(data, dataSize, 0, 0);

        if (source != 0) {
            // free old database
            if (m_wdbp != 0) {
                wdb_close(m_wdbp);
                m_wdbp = 0;
            }

            if (m_rtip != 0) {
                rt_free_rti(m_rtip);
                m_rtip = 0;
            }

            // build new database
            db_i* dbip = db_open_inmem();
            RT_CK_DBI(dbip);

            m_rtip = rt_new_rti(dbip);
            rt_init_resource(m_resp, 0, m_rtip);
            m_wdbp = dbip->dbi_wdbp;

            // fill database
            ret = (db_dump(m_wdbp, source->rti_dbip) == 0);

            assert(m_wdbp->dbip == m_rtip->rti_dbip);
            db_update_ident(m_wdbp->dbip, source->rti_dbip->dbi_title, source->rti_dbip->dbi_base2local);

            rt_free_rti(source);
        }
    }

    BU_UNSETJUMP;

    return ret;
}


bool MemoryDatabase::Save
(
    const char* fileName
) {
    bool ret = false;

    if (!BU_SETJUMP) {
        rt_wdb* target = wdb_fopen(fileName);

        if (target != 0) {
            ret = (db_dump(target, m_wdbp->dbip) == 0);
            wdb_close(target);
        }
    }

    BU_UNSETJUMP;

    return ret;
}
