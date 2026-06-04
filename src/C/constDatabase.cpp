/*                      C O N S T D A T A B A S E . C P P
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
/** @file constDatabase.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements a handle and functions for a read-only database
 */

#include <cassert>

#include "casts.h"

#include <brlcad/C/constDatabase.h>

#include <brlcad/C/vectorList.h>

#include <brlcad/Database/NonManifoldGeometry.h>

using namespace BRLCAD;


BrlConstDatabase BrlNewConstDatabase(void) {
    return new ConstDatabase;
}


void BrlDeleteConstDatabase
(
    BrlConstDatabase db
) {
    if (db != nullptr) {
        ConstDatabase* constDatabase = CastConstDatabase(db);

        assert(constDatabase != nullptr);

        if (constDatabase != nullptr)
            delete constDatabase;
    }
}


int BrlConstDatabaseLoad
(
    BrlConstDatabase db,
    const char*      fileName
) {
    int ret = 1;

    if (db != nullptr) {
        ConstDatabase* constDatabase = CastConstDatabase(db);

        assert(constDatabase != nullptr);

        if (constDatabase != nullptr)
            ret = constDatabase->Load(fileName) ? 0 : 1;
    }

    return ret;
}


const char* BrlConstDatabaseTitle
(
    BrlConstDatabase db
) {
    const char* ret = nullptr;

    if (db != nullptr) {
        ConstDatabase* constDatabase = CastConstDatabase(db);

        assert(constDatabase != nullptr);

        if (constDatabase != nullptr)
            ret = constDatabase->Title();
    }

    return ret;
}


void BrlConstDatabasePlot
(
    BrlConstDatabase db,
    const char*      objectName,
    BrlVectorList    vlist
) {
    if (db != nullptr) {
        ConstDatabase* constDatabase = CastConstDatabase(db);

        assert(constDatabase != nullptr);

        if (constDatabase != nullptr) {
            VectorList* vl = CastVectorList(vlist);

            assert(vl != nullptr);

            if (vl != nullptr)
                constDatabase->Plot(objectName, *vl);
        }
    }
}


BrlTopObjectIterator BrlConstDatabaseFirstTopObject
(
    BrlConstDatabase db
) {
    BrlTopObjectIterator ret = nullptr;

    if (db != nullptr) {
        ConstDatabase* constDatabase = CastConstDatabase(db);

        assert(constDatabase != nullptr);

        if (constDatabase != nullptr) {
            ConstDatabase::TopObjectIterator it = constDatabase->FirstTopObject();

            ret = new ConstDatabase::TopObjectIterator(it);
        }
    }

    return ret;
}


int BrlTopObjectIteratorGood
(
    BrlTopObjectIterator it
) {
    int ret = 0;

    if (it != nullptr) {
        ConstDatabase::TopObjectIterator* iter =
        static_cast<ConstDatabase::TopObjectIterator*>(it);

        ret = iter->Good() ? 1 : 0;
    }

    return ret;
}


void BrlTopObjectIteratorNext
(
    BrlTopObjectIterator it
) {
    if (it != nullptr) {
        ConstDatabase::TopObjectIterator* iter =
        static_cast<ConstDatabase::TopObjectIterator*>(it);

        ++(*iter);
    }
}


const char* BrlTopObjectIteratorName
(
    BrlTopObjectIterator it
) {
    const char* ret = nullptr;

    if (it != nullptr) {
        ConstDatabase::TopObjectIterator* iter =
        static_cast<ConstDatabase::TopObjectIterator*>(it);

        ret = iter->Name();
    }

    return ret;
}


void BrlDeleteTopObjectIterator
(
    BrlTopObjectIterator it
) {
    if (it != nullptr) {
        ConstDatabase::TopObjectIterator* iter =
        static_cast<ConstDatabase::TopObjectIterator*>(it);

        delete iter;
    }
}


BrlObject BrlConstDatabaseGet
(
    BrlConstDatabase db,
    const char*      objectName
) {
    BrlObject ret = nullptr;

    if (db != nullptr) {
        ConstDatabase* constDatabase = CastConstDatabase(db);

        assert(constDatabase != nullptr);

        if (constDatabase != nullptr)
            ret = constDatabase->Get(objectName);
    }

    return ret;
}


BrlNonManifoldGeometry BrlConstDatabaseFacetize
(
    BrlConstDatabase db,
    const char*      objectName
) {
    BrlNonManifoldGeometry ret = nullptr;

    if (db != nullptr) {
        ConstDatabase* constDatabase = CastConstDatabase(db);

        assert(constDatabase != nullptr);

        if (constDatabase != nullptr)
            ret = constDatabase->Facetize(objectName);
    }

    return ret;
}


void BrlDeleteNonManifoldGeometry
(
    BrlNonManifoldGeometry nm
) {
    if (nm != nullptr) {
        BRLCAD::NonManifoldGeometry* p =
            static_cast<BRLCAD::NonManifoldGeometry*>(nm);

        delete p;
    }
}


void BrlConstDatabaseSelect
(
    BrlConstDatabase db,
    const char*      objectName
) {
    if (db != nullptr) {
        ConstDatabase* constDatabase = CastConstDatabase(db);

        assert(constDatabase != nullptr);

        if (constDatabase != nullptr)
            constDatabase->Select(objectName);
    }
}


void BrlConstDatabaseUnSelectAll
(
    BrlConstDatabase db
) {
    if (db != nullptr) {
        ConstDatabase* constDatabase = CastConstDatabase(db);

        assert(constDatabase != nullptr);

        if (constDatabase != nullptr)
            constDatabase->UnSelectAll();
    }
}


int BrlConstDatabaseSelectionIsEmpty
(
    BrlConstDatabase db
) {
    int ret = 1;

    if (db != nullptr) {
        ConstDatabase* constDatabase = CastConstDatabase(db);

        assert(constDatabase != nullptr);

        if (constDatabase != nullptr)
            ret = constDatabase->SelectionIsEmpty() ? 1 : 0;
    }

    return ret;
}


void BrlConstDatabaseBoundingBoxMinima
(
    BrlConstDatabase db,
    double*          x,
    double*          y,
    double*          z
) {
    if ((db != nullptr) && (x != nullptr) && (y != nullptr) && (z != nullptr)) {
        ConstDatabase* constDatabase = CastConstDatabase(db);

        assert(constDatabase != nullptr);

        if (constDatabase != nullptr) {
            BRLCAD::Vector3D v = constDatabase->BoundingBoxMinima();

            *x = v.coordinates[0];
            *y = v.coordinates[1];
            *z = v.coordinates[2];
        }
    }
}


void BrlConstDatabaseBoundingBoxMaxima
(
    BrlConstDatabase db,
    double*          x,
    double*          y,
    double*          z
) {
    if ((db != nullptr) && (x != nullptr) && (y != nullptr) && (z != nullptr)) {
        ConstDatabase* constDatabase = CastConstDatabase(db);

        assert(constDatabase != nullptr);

        if (constDatabase != nullptr) {
            BRLCAD::Vector3D v = constDatabase->BoundingBoxMaxima();

            *x = v.coordinates[0];
            *y = v.coordinates[1];
            *z = v.coordinates[2];
        }
    }
}
