/*                      D A T A B A S E . C P P
 * BRL-CAD
 *
 * Copyright (c) 2008-2025 United States Government as represented by
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
/** @file Database.cpp
 *
 *  BRL-CAD core C++ interface:
 *      implements the common part of handles for writable databases
 */

#include <cassert>

#include "raytrace.h"
#include "rt/geom.h"
#include "bu/parallel.h"

#include "private.h"

#include <brlcad/Database/Torus.h>
#include <brlcad/Database/Cone.h>
#include <brlcad/Database/Ellipsoid.h>
#include <brlcad/Database/Arb8.h>
#include <brlcad/Database/Halfspace.h>
#include <brlcad/Database/Sphere.h>
#include <brlcad/Database/NonManifoldGeometry.h>
#include <brlcad/Database/Pipe.h>
#include <brlcad/Database/Particle.h>
#include <brlcad/Database/ParabolicCylinder.h>
#include <brlcad/Database/HyperbolicCylinder.h>
#include <brlcad/Database/Paraboloid.h>
#include <brlcad/Database/Hyperboloid.h>
#include <brlcad/Database/EllipticalTorus.h>
#include <brlcad/Database/Sketch.h>
#include <brlcad/Database/BagOfTriangles.h>
#include <brlcad/Database/Combination.h>
#include <brlcad/Database/Database.h>

#if defined (_DEBUG)
#   define LOOKUP_NOISE LOOKUP_NOISY
#else
#   define LOOKUP_NOISE LOOKUP_QUIET
#endif


using namespace BRLCAD;


Database::~Database(void) {
    if (m_wdbp != nullptr) {
        if (!BU_SETJUMP)
            wdb_close(m_wdbp);

        BU_UNSETJUMP;
    }
}


void Database::SetTitle
(
    const char* title
) {
    if (m_wdbp != nullptr) {
        if (!BU_SETJUMP)
            db_update_ident(m_wdbp->dbip, title, m_wdbp->dbip->dbi_base2local);
        else {
            BU_UNSETJUMP;
        }

        BU_UNSETJUMP;
    }
}


bool Database::Add
(
    const Object& object
) {
    bool ret = false;

    if (object.IsValid() && (m_wdbp != nullptr)) {
        if (!BU_SETJUMP) {
            int   id         = ID_NULL;
            void* rtInternal = nullptr;

            if (object.Type() == Torus::ClassName()) {
                id = ID_TOR; // 1

                const Torus* torus = dynamic_cast<const Torus*>(&object);

                assert(torus != nullptr);

                BU_GET(rtInternal, rt_tor_internal);
                memcpy(rtInternal, torus->Internal(), sizeof(rt_tor_internal));
            }
            else if (object.Type() == Cone::ClassName()) {
                id = ID_TGC; // 2

                const Cone* cone = dynamic_cast<const Cone*>(&object);

                assert(cone != nullptr);

                BU_GET(rtInternal, rt_tgc_internal);
                memcpy(rtInternal, cone->Internal(), sizeof(rt_tgc_internal));
            }
            else if (object.Type() == Ellipsoid::ClassName()) {
                id = ID_ELL; // 3

                const Ellipsoid* ellipsoid = dynamic_cast<const Ellipsoid*>(&object);

                assert(ellipsoid != nullptr);

                BU_GET(rtInternal, rt_ell_internal);
                memcpy(rtInternal, ellipsoid->Internal(), sizeof(rt_ell_internal));
            }
            else if (object.Type() == Arb8::ClassName()) {
                id = ID_ARB8; // 4

                const Arb8* arb8 = dynamic_cast<const Arb8*>(&object);

                assert(arb8 != nullptr);

                BU_GET(rtInternal, rt_arb_internal);
                memcpy(rtInternal, arb8->Internal(), sizeof(rt_arb_internal));
            }
            else if (object.Type() == Halfspace::ClassName()) {
                id = ID_HALF; // 6

                const Halfspace* halfspace = dynamic_cast<const Halfspace*>(&object);

                assert(halfspace != nullptr);

                BU_GET(rtInternal, rt_half_internal);
                memcpy(rtInternal, halfspace->Internal(), sizeof(rt_half_internal));
            }
            else if (object.Type() == Sphere::ClassName()) {
                id = ID_SPH; // 10

                const Sphere* sphere = dynamic_cast<const Sphere*>(&object);

                assert(sphere != nullptr);

                BU_GET(rtInternal, rt_ell_internal);
                memcpy(rtInternal, sphere->Internal(), sizeof(rt_ell_internal));
            }
            else if (object.Type() == NonManifoldGeometry::ClassName()) {
                id = ID_NMG; // 11

                const NonManifoldGeometry* nmg = dynamic_cast<const NonManifoldGeometry*>(&object);

                assert(nmg != nullptr);

                rtInternal = nmg_clone_model(nmg->Internal());
            }
            else if (object.Type() == Pipe::ClassName()) {
                id = ID_PIPE; // 15

                const Pipe* pipe = dynamic_cast<const Pipe*>(&object);

                assert(pipe != nullptr);

                rtInternal = ClonePipeInternal(*(pipe->Internal()));
            }
            else if (object.Type() == Particle::ClassName()) {
                id = ID_PARTICLE; // 16

                const Particle* particle = dynamic_cast<const Particle*>(&object);

                assert(particle != nullptr);

                BU_GET(rtInternal, rt_part_internal);
                memcpy(rtInternal, particle->Internal(), sizeof(rt_part_internal));
            }
            else if (object.Type() == ParabolicCylinder::ClassName()) {
                id = ID_RPC; // 17

                const ParabolicCylinder* parabolicCylinder = dynamic_cast<const ParabolicCylinder*>(&object);

                assert(parabolicCylinder != nullptr);

                BU_GET(rtInternal, rt_rpc_internal);
                memcpy(rtInternal, parabolicCylinder->Internal(), sizeof(rt_rpc_internal));
            }
            else if (object.Type() == HyperbolicCylinder::ClassName()) {
                id = ID_RHC; // 18

                const HyperbolicCylinder* hyperbolicCylinder = dynamic_cast<const HyperbolicCylinder*>(&object);

                assert(hyperbolicCylinder != nullptr);

                BU_GET(rtInternal, rt_rhc_internal);
                memcpy(rtInternal, hyperbolicCylinder->Internal(), sizeof(rt_rhc_internal));
            }
            else if (object.Type() == Paraboloid::ClassName()) {
                id = ID_EPA; // 19

                const Paraboloid* paraboloid = dynamic_cast<const Paraboloid*>(&object);

                assert(paraboloid != nullptr);

                BU_GET(rtInternal, rt_epa_internal);
                memcpy(rtInternal, paraboloid->Internal(), sizeof(rt_epa_internal));
            }
            else if (object.Type() == Hyperboloid::ClassName()) {
                id = ID_EHY; // 20

                const Hyperboloid* hyperboloid = dynamic_cast<const Hyperboloid*>(&object);

                assert(hyperboloid != nullptr);

                BU_GET(rtInternal, rt_ehy_internal);
                memcpy(rtInternal, hyperboloid->Internal(), sizeof(rt_ehy_internal));
            }
            else if (object.Type() == EllipticalTorus::ClassName()) {
                id = ID_ETO; // 21

                const EllipticalTorus* ellipticalTorus = dynamic_cast<const EllipticalTorus*>(&object);

                assert(ellipticalTorus != nullptr);

                BU_GET(rtInternal, rt_eto_internal);
                memcpy(rtInternal, ellipticalTorus->Internal(), sizeof(rt_eto_internal));
            }
            else if (object.Type() == Sketch::ClassName()) {
                id = ID_SKETCH; // 26

                const Sketch* sketch = dynamic_cast<const Sketch*>(&object);

                assert(sketch != nullptr);

                rtInternal = rt_copy_sketch(sketch->Internal());
            }
            else if (object.Type() == BagOfTriangles::ClassName()) {
                id = ID_BOT; // 30

                const BagOfTriangles* bagOfTriangles = dynamic_cast<const BagOfTriangles*>(&object);

                assert(bagOfTriangles != nullptr);

                rt_bot_internal* bot = CloneBotInternal(*(bagOfTriangles->Internal()));
                CleanUpBotInternal(*bot);

                rtInternal = bot;
            }
            else if (object.Type() == Combination::ClassName()) {
                id = ID_COMBINATION;  // 31

                const Combination* combination = dynamic_cast<const Combination*>(&object);

                assert(combination != nullptr);

                const rt_comb_internal* internalFrom = combination->Internal();

                BU_GET(rtInternal, rt_comb_internal);
                memcpy(rtInternal, internalFrom, sizeof(rt_comb_internal));

                rt_comb_internal* internalTo = static_cast<rt_comb_internal*>(rtInternal);

                if (internalFrom->tree != nullptr)
                    internalTo->tree = db_dup_subtree(internalFrom->tree, object.m_resp);

                bu_vls_init(&internalTo->shader);
                bu_vls_strcpy(&internalTo->shader, bu_vls_addr(&internalFrom->shader));
                bu_vls_init(&internalTo->material);
                bu_vls_strcpy(&internalTo->material, bu_vls_addr(&internalFrom->material));
            }

            const char* objectName = object.Name();

            if ((id != ID_NULL) && (objectName != nullptr) && (strlen(objectName) > 0)) {
                ret = (wdb_export(m_wdbp, objectName, rtInternal, id, 1.) == 0);

                // copy attributes
                if (ret) {
                    const bu_attribute_value_set* origAvs = object.GetAvs();

                    if ((origAvs != nullptr) && (origAvs->count > 0)) {
                        directory* pDir = db_lookup(m_rtip->rti_dbip, object.Name(), LOOKUP_NOISE);

                        assert(pDir != nullptr);

                        if (pDir != nullptr) {
                            bu_attribute_value_set avs;
                            bu_avs_init(&avs, origAvs->count, "BRLCAD::Database::Add");

                            for (size_t i = 0; i < origAvs->count; ++i)
                                bu_avs_add_nonunique(&avs, origAvs->avp[i].name, origAvs->avp[i].value);

                            ret = (db5_update_attributes(pDir, &avs, m_rtip->rti_dbip) == 0);
                        }
                    }
                }

            }
        }

        BU_UNSETJUMP;
    }

    return ret;
}


void Database::Delete
(
    const char* objectName
) {
    if (m_wdbp != nullptr) {
        if (!BU_SETJUMP) {
            directory* pDir = db_lookup(m_rtip->rti_dbip, objectName, LOOKUP_NOISE);

            if (pDir != RT_DIR_NULL) {
                if (db_delete(m_wdbp->dbip, pDir) == 0)
                    db_dirdelete(m_wdbp->dbip, pDir);
            }
        }

        BU_UNSETJUMP;
    }
}


bool Database::Get
(
    const char*                                objectName,
    const std::function<void(Object& object)>& callback
) {
    bool ret = true;

    ConstDatabase::Get(objectName, [callback, &ret](const Object& object) {
        Object& objectIntern = const_cast<Object&>(object);

        callback(objectIntern);

        if (objectIntern.IsValid()) {
            bool success = false;

            if (!BU_SETJUMP)
                success = (rt_db_put_internal(objectIntern.m_pDir,
                                              objectIntern.m_dbip,
                                              objectIntern.m_ip,
                                              objectIntern.m_resp) == 0);

            BU_UNSETJUMP;

            if (!success)
                ret = false;
        }
        else
            ret = false;
    });

    return ret;
}


bool Database::Set
(
    const Object& object
) {
    return Get(object.Name(), [&object](Object& obj){obj = object;});
}


Database::Database(void) : ConstDatabase(), m_wdbp(nullptr) {}
