/*                      C O N S T D A T A B A S E . C P P
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
/** @file ConstDatabase.cpp
 *
 *  BRL-CAD core C++ interface:
 *      implements a handle for a read-only database
 */

#include <cstdlib>
#include <cstring>
#include <cassert>

#include "raytrace.h"
#include "bu/parallel.h"

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
#include <brlcad/Database/Unknown.h>
#include <brlcad/Database/ConstDatabase.h>

#if defined (_DEBUG)
#   define LOOKUP_NOISE LOOKUP_NOISY
#else
#   define LOOKUP_NOISE LOOKUP_QUIET
#endif


using namespace BRLCAD;


ConstDatabase::ConstDatabase(void) : m_rtip(nullptr), m_resp(nullptr), m_changeSignalHandlers(nullptr), m_selfUpdateNref(false) {
    assert(rt_uniresource.re_magic == RESOURCE_MAGIC);

    if (!BU_SETJUMP) {
        m_resp = static_cast<resource*>(bu_calloc(1, sizeof(resource), "BRLCAD::ConstDatabase::~ConstDatabase::m_resp"));
        rt_init_resource(m_resp, 0, nullptr);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


ConstDatabase::~ConstDatabase(void) {
    if (m_changeSignalHandlers != nullptr)
        free(m_changeSignalHandlers);

    if (m_rtip != nullptr) {
        if (!BU_SETJUMP) {
            DeRegisterCoreCallbacks();
            rt_free_rti(m_rtip);
        }

        BU_UNSETJUMP;
    }

    if (m_resp != nullptr) {
        rt_clean_resource_complete(nullptr, m_resp);
        bu_free(m_resp, "BRLCAD::ConstDatabase::~ConstDatabase::m_resp");
    }
}


bool ConstDatabase::Load
(
    const char* fileName
) {
    if (m_resp != nullptr) {
        if (m_rtip != nullptr) {
            if (!BU_SETJUMP) {
                DeRegisterCoreCallbacks();
                rt_free_rti(m_rtip);
            }

            BU_UNSETJUMP;

            m_rtip = nullptr;
        }

        if (!BU_SETJUMP)
            m_rtip = rt_dirbuild(fileName, nullptr, 0);

        BU_UNSETJUMP;

        if (m_rtip != nullptr) {
            if (!BU_SETJUMP) {
                rt_init_resource(m_resp, 0, m_rtip);
                RegisterCoreCallbacks();
            }
            else {
                BU_UNSETJUMP;

                if (!BU_SETJUMP) {
                    DeRegisterCoreCallbacks();
                    rt_free_rti(m_rtip);
                }

                m_rtip = nullptr;
            }

            BU_UNSETJUMP;
        }
    }

    return (m_rtip != nullptr);
}


const char* ConstDatabase::Title(void) const {
    const char* ret = nullptr;

    if (m_rtip != nullptr)
        ret = m_rtip->rti_dbip->dbi_title;

    return ret;
}


const ConstDatabase::TopObjectIterator& ConstDatabase::TopObjectIterator::operator++(void) {
    if (m_pDir != nullptr) {
        const directory* oldPDir = m_pDir;

        for (const directory* pDir = m_pDir->d_forw; pDir != RT_DIR_NULL; pDir = pDir->d_forw) {
            if (pDir->d_nref == 0) {
                m_pDir = pDir;
                break;
            }
        }

        if (m_pDir == oldPDir) {
            for (size_t i = m_hashTablePosition + 1; (i < RT_DBNHASH) && (m_pDir == oldPDir); ++i) {
                for (const directory* pDir = m_rtip->rti_dbip->dbi_Head[i]; pDir != RT_DIR_NULL; pDir = pDir->d_forw) {
                    if (pDir->d_nref == 0) {
                        m_hashTablePosition = i;
                        m_pDir              = pDir;
                        break;
                    }
                }
            }
        }

        if (m_pDir == oldPDir)
            m_pDir = nullptr;
    }

    return *this;
}


bool ConstDatabase::TopObjectIterator::Good(void) const {
    return (m_pDir != nullptr);
}


const char* ConstDatabase::TopObjectIterator::Name(void) const {
    assert(m_pDir != nullptr);

    const char* ret = nullptr;

    if (m_pDir != nullptr)
        ret = m_pDir->d_namep;

    return ret;
}


ConstDatabase::TopObjectIterator::TopObjectIterator
(
    size_t           hashTablePosition,
    const directory* pDir,
    const rt_i*      rtip
) : m_hashTablePosition(hashTablePosition), m_pDir(pDir), m_rtip(rtip) {}


ConstDatabase::TopObjectIterator ConstDatabase::FirstTopObject(void) const {
    size_t           hashTablePosition = 0;
    const directory* pDirectory        = nullptr;

    if (m_rtip != nullptr) {
        if (!BU_SETJUMP) {
            m_selfUpdateNref = true;
            db_update_nref(m_rtip->rti_dbip, m_resp);
            m_selfUpdateNref = false;

            for (size_t i = 0; (i < RT_DBNHASH) && (pDirectory == nullptr); ++i) {
                for (const directory* pDir = m_rtip->rti_dbip->dbi_Head[i]; pDir != RT_DIR_NULL; pDir = pDir->d_forw) {
                    if (pDir->d_nref == 0) {
                        hashTablePosition = i;
                        pDirectory        = pDir;
                        break;
                    }
                }
            }
        }

        BU_UNSETJUMP;
    }

    return ConstDatabase::TopObjectIterator(hashTablePosition, pDirectory, m_rtip);
}


void ConstDatabase::Get
(
    const char*                                      objectName,
    const std::function<void(const Object& object)>& callback
) const {
    if (m_rtip != nullptr) {
        if (!BU_SETJUMP) {
            if ((objectName != nullptr) && (strlen(objectName) > 0)) {
                directory* pDir = db_lookup(m_rtip->rti_dbip, objectName, LOOKUP_NOISE);

                GetInternal(pDir, callback);
            }
        }

        BU_UNSETJUMP;
    }
}


Object* ConstDatabase::Get
(
    const char* objectName
) const {
    Object* ret = nullptr;

    Get(objectName, [&ret](const Object& object){try{ret = object.Clone();}catch(std::bad_alloc&){}});

    return ret;
}


static tree* FacetizeRegionEnd
(
    db_tree_state*      tsp,
    const db_full_path* pathp,
    tree*               curtree,
    void*               clientData
) {
    tree* ret = TREE_NULL;

    if (tsp != nullptr)
        RT_CK_DBTS(tsp);

    if (pathp != nullptr)
        RT_CK_FULL_PATH(pathp);

    tree**  facetizeTree = static_cast<tree**>(clientData);
    bu_list vhead;
    BU_LIST_INIT(&vhead);

    if (curtree->tr_op == OP_NOP)
        ret = curtree;
    else {
        if (*facetizeTree) {
            tree *tr;

            BU_GET(tr, tree);
            RT_TREE_INIT(tr);

            tr->tr_op           = OP_UNION;
            tr->tr_b.tb_regionp = REGION_NULL;
            tr->tr_b.tb_left    = *facetizeTree;
            tr->tr_b.tb_right   = curtree;

            *facetizeTree = tr;
        }
        else
            *facetizeTree = curtree;
    }

    return ret;
}


NonManifoldGeometry* ConstDatabase::Facetize
(
    const char* objectName
) const {
    NonManifoldGeometry* ret          = new NonManifoldGeometry;

    if (m_rtip != nullptr) {
        if (!BU_SETJUMP) {
            tree*                facetizeTree = nullptr;
            db_tree_state        initState;

            db_init_db_tree_state(&initState, m_rtip->rti_dbip, m_resp);
            initState.ts_ttol = &m_rtip->rti_ttol;
            initState.ts_tol  = &m_rtip->rti_tol;
            initState.ts_m    = &ret->m_internalp;

            if (db_walk_tree(m_rtip->rti_dbip,
                             1,
                             &objectName,
                             1,
                             &initState,
                             nullptr,
                             FacetizeRegionEnd,
                             rt_booltree_leaf_tess,
                             &facetizeTree) == 0) {
                if (facetizeTree != nullptr) {
                    nmg_boolean(facetizeTree, ret->m_internalp, &rt_vlfree, &m_rtip->rti_tol, &rt_uniresource);

                    // ok, now we have a mess here: the model/region with the faces is both in ret and facetizeTree
                    // freeing facetizeTree would destroy the ret too
                    // therefore we make a copy and destroy facetizeTree and the old ret->m_internalp afterwards
                    assert(ret->m_internalp == facetizeTree->tr_d.td_r->m_p);

                    model* messedModel = ret->m_internalp;
                    ret->m_internalp   = nmg_clone_model(messedModel);

                    db_free_tree(facetizeTree, &rt_uniresource);
                    nmg_km(messedModel);
                }
            }
        }
        else {
            BU_UNSETJUMP;
        }

        BU_UNSETJUMP;
    }

    return ret;
}


static tree* PlotLeaf
(
    db_tree_state*      tsp,
    const db_full_path* pathp,
    rt_db_internal*     ip,
    void*               clientData
) {
    tree*    ret   = TREE_NULL;
    bu_list* vlist = static_cast<bu_list*>(clientData);

    if (ip->idb_meth->ft_plot != nullptr) {
        if (ip->idb_meth->ft_plot(vlist, ip, tsp->ts_ttol, tsp->ts_tol, nullptr) == 0) {
            // Indicate success by returning something other than TREE_NULL
            BU_GET(ret, tree);
            RT_TREE_INIT(ret);
            ret->tr_op = OP_NOP;
        }
    }

    return ret;
}


void ConstDatabase::Plot
(
    const char* objectName,
    VectorList& vectorList
) const {
    if (m_rtip != nullptr) {
        if (!BU_SETJUMP) {
            db_tree_state initState;

            db_init_db_tree_state(&initState, m_rtip->rti_dbip, m_resp);
            initState.ts_ttol = &m_rtip->rti_ttol;
            initState.ts_tol  = &m_rtip->rti_tol;

            db_walk_tree(m_rtip->rti_dbip,
                         1,
                         &objectName,
                         1,
                         &initState,
                         nullptr,
                         nullptr,
                         PlotLeaf,
                         vectorList.m_vlist);
        }
        else
            BU_UNSETJUMP;

        BU_UNSETJUMP;
    }
}


void ConstDatabase::Select
(
    const char* objectName
) {
    if (m_rtip != nullptr) {
        if (!BU_SETJUMP)
            rt_gettree(m_rtip, objectName);

        BU_UNSETJUMP;
    }
}


void ConstDatabase::UnSelectAll(void) {
    if (m_rtip != nullptr) {
        if (!BU_SETJUMP)
            rt_clean(m_rtip);

        BU_UNSETJUMP;
    }
}


bool ConstDatabase::SelectionIsEmpty(void) const {
    bool ret = true;

    if (m_rtip != nullptr)
        ret = m_rtip->nsolids < 1;

    return ret;
}


Vector3D ConstDatabase::BoundingBoxMinima(void) const {
    Vector3D ret;

    if (!SelectionIsEmpty()) {
        if (!BU_SETJUMP) {
            if (m_rtip->needprep)
                rt_prep(m_rtip);

            VMOVE(ret.coordinates, m_rtip->mdl_min);
        }

        BU_UNSETJUMP;
    }

    return ret;
}


Vector3D ConstDatabase::BoundingBoxMaxima(void) const {
    Vector3D ret;

    if (!SelectionIsEmpty()) {
        if (!BU_SETJUMP) {
            if (m_rtip->needprep)
                rt_prep(m_rtip);

            VMOVE(ret.coordinates, m_rtip->mdl_max);
        }

        BU_UNSETJUMP;
    }

    return ret;
}


class ConstDatabaseHit : public ConstDatabase::Hit {
public:
    ConstDatabaseHit(application* ap,
                     partition*   part,
                     region*      reg) : ConstDatabase::Hit(),
                                                  m_application(ap),
                                                  m_partition(part),
                                                  m_region(reg),
                                                  m_inVectorsComputed(false),
                                                  m_outVectorsComputed(false) {
        assert(m_application != nullptr);
        assert(m_partition != nullptr);
        assert(m_region != nullptr);
   }

    const char* Name(void) const override {
        return m_region->reg_name;
    }

    double      DistanceIn(void) const override {
        return m_partition->pt_inhit->hit_dist;
    }

    double      DistanceOut(void) const override {
        return m_partition->pt_outhit->hit_dist;
    }

    Vector3D    PointIn(void) const override {
        ComputeInVectors();
        return m_partition->pt_inhit->hit_point;
    }

    Vector3D    PointOut(void) const override {
        ComputeOutVectors();
        return m_partition->pt_outhit->hit_point;
    }

    Vector3D    SurfaceNormalIn(void) const override {
        ComputeInVectors();
        return m_partition->pt_inhit->hit_normal;
    }

    Vector3D    SurfaceNormalOut(void) const override {
        ComputeOutVectors();
        return m_partition->pt_outhit->hit_normal;
    }

    Curvature3D SurfaceCurvatureIn(void) const override {
        ComputeInVectors();

        curvature curv;
        RT_CURVATURE(&curv, m_partition->pt_inhit, m_partition->pt_inflip, m_partition->pt_inseg->seg_stp);

        return Curvature3D(curv.crv_pdir, curv.crv_c1, curv.crv_c2);
    }

    Curvature3D SurfaceCurvatureOut(void) const override {
        ComputeOutVectors();

        curvature curv;
        RT_CURVATURE(&curv, m_partition->pt_outhit, m_partition->pt_outflip, m_partition->pt_outseg->seg_stp);

        return Curvature3D(curv.crv_pdir, curv.crv_c1, curv.crv_c2);
    }

    Mapping2D   Surface2DMappingIn(void) const override {
        uvcoord uv;
        RT_HIT_UVCOORD(m_application, m_partition->pt_inseg->seg_stp, m_partition->pt_inhit, &uv);

        return Mapping2D(Vector2D(uv.uv_u, uv.uv_v), Vector2D(uv.uv_du, uv.uv_dv));
    }

    Mapping2D   Surface2DMappingOut(void) const override {
        uvcoord uv;
        RT_HIT_UVCOORD(m_application, m_partition->pt_outseg->seg_stp, m_partition->pt_outhit, &uv);

        return Mapping2D(Vector2D(uv.uv_u, uv.uv_v), Vector2D(uv.uv_du, uv.uv_dv));
    }

    bool        HasColor(void) const override {
        return (m_region->reg_mater.ma_color_valid != 0);
    }

    double      Red(void) const override {
        return m_region->reg_mater.ma_color[0];
    }

    double      Green(void) const override {
        return m_region->reg_mater.ma_color[1];
    }

    double      Blue(void) const override {
        return m_region->reg_mater.ma_color[2];
    }

private:
    application* m_application;
    partition*   m_partition;
    region*      m_region;
    mutable bool m_inVectorsComputed;
    mutable bool m_outVectorsComputed;

    void ComputeInVectors(void) const {
        if (!m_inVectorsComputed) {
            hit* pHit = m_partition->pt_inhit;

            RT_HIT_NORMAL(pHit->hit_normal, pHit, m_partition->pt_inseg->seg_stp, nullptr, m_partition->pt_inflip);
            m_inVectorsComputed = true;
        }
    }

    void ComputeOutVectors(void) const {
        if (!m_outVectorsComputed) {
            hit* pHit = m_partition->pt_outhit;

            RT_HIT_NORMAL(pHit->hit_normal, pHit, m_partition->pt_outseg->seg_stp, nullptr, m_partition->pt_outflip);
            m_outVectorsComputed = true;
        }
    }
};


static int HitDo
(
    application* ap,
    partition*   partitionHead,
    seg*         UNUSED(segment)
) {
    std::function<bool(const ConstDatabase::Hit& hit)>* callback = static_cast<std::function<bool(const ConstDatabase::Hit& hit)>*>(ap->a_uptr);
    int&                                                ret      = ap->a_return;

    if (ret == 0) {
        for (partition* part = partitionHead->pt_forw;
             part != partitionHead;
             part = part->pt_forw) {
            if (!((*callback)(ConstDatabaseHit(ap, part, part->pt_regionp)))) {
                ret = 1;
                break;
            }
        }
    }

    return ret;
}


void ConstDatabase::ShootRay
(
    const Ray3D&                               ray,
    const std::function<bool(const Hit& hit)>& callback
) const {
    if (!SelectionIsEmpty()) {
        application ap;
        RT_APPLICATION_INIT(&ap);

        ap.a_hit          = HitDo;
        ap.a_miss         = nullptr;
        ap.a_overlap      = nullptr;
        ap.a_multioverlap = nullptr;
        ap.a_rt_i         = m_rtip;
        ap.a_level        = 0;
        ap.a_onehit       = 0; // all hits
        ap.a_resource     = m_resp;
        ap.a_return       = 0;
        ap.a_uptr         = const_cast<std::function<bool(const Hit& hit)>*>(&callback);

        VMOVE(ap.a_ray.r_pt, ray.origin.coordinates);
        VMOVE(ap.a_ray.r_dir, ray.direction.coordinates);
        VUNITIZE(ap.a_ray.r_dir);

        if (!BU_SETJUMP) {
            try {
                rt_shootray(&ap);
            }
            catch(...) {
                BU_UNSETJUMP;
            }
        }

        BU_UNSETJUMP;
    }
}


static void MultioverlapDo
(
    application* ap,
    partition*   part,
    bu_ptbl*     regiontable,
    partition*   UNUSED(inputHdp)
) {
    std::function<bool(const ConstDatabase::Hit& hit)>* callback = static_cast<std::function<bool(const ConstDatabase::Hit& hit)>*>(ap->a_uptr);
    int&                                                ret      = ap->a_return;

    if (ret == 0) {
        for (size_t i = 0; i < BU_PTBL_LEN(regiontable); ++i) {
            region* reg = reinterpret_cast<region*>(BU_PTBL_GET(regiontable, i));

            if (reg == REGION_NULL)
                continue;

            RT_CK_REGION(reg);

            if (!((*callback)(ConstDatabaseHit(ap, part, reg)))) {
                ret = 1;
                break;
            }
        }
    }

    bu_ptbl_reset(regiontable);
}


void ConstDatabase::ShootRay
(
    const Ray3D&                               ray,
    const std::function<bool(const Hit& hit)>& callback,
    int                                        flags
) const {
    if (!SelectionIsEmpty()) {
        application ap;
        RT_APPLICATION_INIT(&ap);

        ap.a_hit      = HitDo;
        ap.a_miss     = nullptr;
        ap.a_overlap  = nullptr;
        ap.a_rt_i     = m_rtip;
        ap.a_level    = 0;
        ap.a_onehit   = flags & StopAfterFirstHit;
        ap.a_resource = m_resp;
        ap.a_return   = 0;
        ap.a_uptr     = const_cast<std::function<bool(const Hit& hit)>*>(&callback);

        if (flags & WithOverlaps)
            ap.a_multioverlap = MultioverlapDo;
        else
            ap.a_multioverlap = nullptr;

        VMOVE(ap.a_ray.r_pt, ray.origin.coordinates);
        VMOVE(ap.a_ray.r_dir, ray.direction.coordinates);
        VUNITIZE(ap.a_ray.r_dir);

        if (!BU_SETJUMP) {
            try {
                rt_shootray(&ap);
            }
            catch(...) {
                BU_UNSETJUMP;
            }
        }

        BU_UNSETJUMP;
    }
}


void ConstDatabase::RegisterChangeSignalHandler
(
    ChangeSignalHandler& changeSignalHandler
) {
    if (m_changeSignalHandlers != nullptr) {
        size_t i = 0;

        while (m_changeSignalHandlers[i] != nullptr) {
            if (m_changeSignalHandlers[i] == &changeSignalHandler)
                break;

            ++i;
        }

        if (m_changeSignalHandlers[i] == nullptr) {
            m_changeSignalHandlers        = static_cast<ChangeSignalHandler**>(realloc(m_changeSignalHandlers, (i + 2) * sizeof(ChangeSignalHandler*)));
            m_changeSignalHandlers[i]     = &changeSignalHandler;
            m_changeSignalHandlers[i + 1] = nullptr;
        }
    }
    else {
        m_changeSignalHandlers    = static_cast<ChangeSignalHandler**>(malloc(2 * sizeof(ChangeSignalHandler*)));
        m_changeSignalHandlers[0] = &changeSignalHandler;
        m_changeSignalHandlers[1] = nullptr;
    }
}


void ConstDatabase::DeRegisterChangeSignalHandler
(
    ChangeSignalHandler& changeSignalHandler
) {
    if (m_changeSignalHandlers != nullptr) {
        size_t i = 0;

        while (m_changeSignalHandlers[i] != nullptr) {
            if (m_changeSignalHandlers[i] == &changeSignalHandler)
                break;

            ++i;
        }

        if (m_changeSignalHandlers[i] != nullptr) {
            while (m_changeSignalHandlers[i] != nullptr) {
                m_changeSignalHandlers[i] = m_changeSignalHandlers[i + 1];
                ++i;
            }

            m_changeSignalHandlers = static_cast<ChangeSignalHandler**>(realloc(m_changeSignalHandlers, (i + 1) * sizeof(ChangeSignalHandler*)));
        }
    }
}


class CallBackHooks {
public:
    static void DatabaseChanged(db_i*      dbip,
                                directory* pDir,
                                int        mode,
                                void*      myself) {
        if (myself != nullptr) {
            ConstDatabase* constDatabase = static_cast<ConstDatabase*>(myself);

            constDatabase->SignalDatabaseChange(dbip, pDir, mode);
        }
    }

    static void ReferencesChanged(db_i*       dbip,
                                  directory*  parentPDir,
                                  directory*  childPDir,
                                  const char* childName,
                                  db_op_t     childIncludingOperation,
                                  matp_t      matrixAboveChild,
                                  void*       myself) {
        if (myself != nullptr) {
            ConstDatabase* constDatabase = static_cast<ConstDatabase*>(myself);

            if (!constDatabase->m_selfUpdateNref && (parentPDir == nullptr) && (childPDir == nullptr) && (childName == nullptr) && (childIncludingOperation == DB_OP_SUBTRACT) && (matrixAboveChild == nullptr))
                constDatabase->SignalChange(nullptr, ConstDatabase::ChangeType::References);
        }
    }
};


void ConstDatabase::RegisterCoreCallbacks(void) {
    if (m_rtip != nullptr) {
        db_add_changed_clbk(m_rtip->rti_dbip, CallBackHooks::DatabaseChanged, this);
        db_add_update_nref_clbk(m_rtip->rti_dbip, CallBackHooks::ReferencesChanged, this);
    }
}


void ConstDatabase::DeRegisterCoreCallbacks(void) {
    if (m_rtip != nullptr) {
        db_rm_changed_clbk(m_rtip->rti_dbip, CallBackHooks::DatabaseChanged, this);
        db_rm_update_nref_clbk(m_rtip->rti_dbip, CallBackHooks::ReferencesChanged, this);
    }
}


void ConstDatabase::GetInternal
(
    directory*                                       pDir,
    const std::function<void(const Object& object)>& callback
) const {
    if (pDir != RT_DIR_NULL) {
        rt_db_internal intern;
        int            id = rt_db_get_internal(&intern, pDir, m_rtip->rti_dbip, nullptr, m_resp);

        try {
            switch(id) {
            case ID_TOR: // 1
                callback(Torus(m_resp, pDir, &intern, m_rtip->rti_dbip));
                break;

            case ID_TGC: // 2
                callback(Cone(m_resp, pDir, &intern, m_rtip->rti_dbip));
                break;

            case ID_ELL: // 3
                callback(Ellipsoid(m_resp, pDir, &intern, m_rtip->rti_dbip));
                break;

            case ID_ARB8: // 4
                callback(Arb8(m_resp, pDir, &intern, m_rtip->rti_dbip));
                break;

            case ID_HALF: // 6
                callback(Halfspace(m_resp, pDir, &intern, m_rtip->rti_dbip));
                break;

            case ID_SPH: // 10
                callback(Sphere(m_resp, pDir, &intern, m_rtip->rti_dbip));
                break;

            case ID_NMG: // 11
                callback(NonManifoldGeometry(m_resp, pDir, &intern, m_rtip->rti_dbip));
                break;

            case ID_PIPE: // 15
                callback(Pipe(m_resp, pDir, &intern, m_rtip->rti_dbip));
                break;

            case ID_PARTICLE: // 16
                callback(Particle(m_resp, pDir, &intern, m_rtip->rti_dbip));
                break;

            case ID_RPC: // 17
                callback(ParabolicCylinder(m_resp, pDir, &intern, m_rtip->rti_dbip));
                break;

            case ID_RHC: // 18
                callback(HyperbolicCylinder(m_resp, pDir, &intern, m_rtip->rti_dbip));
                break;

            case ID_EPA: // 19
                callback(Paraboloid(m_resp, pDir, &intern, m_rtip->rti_dbip));
                break;

            case ID_EHY: // 20
                callback(Hyperboloid(m_resp, pDir, &intern, m_rtip->rti_dbip));
                break;

            case ID_ETO: // 21
                callback(EllipticalTorus(m_resp, pDir, &intern, m_rtip->rti_dbip));
                break;

            case ID_SKETCH: // 26
                callback(Sketch(m_resp, pDir, &intern, m_rtip->rti_dbip));
                break;

            case ID_BOT: // 30
                callback(BagOfTriangles(m_resp, pDir, &intern, m_rtip->rti_dbip));
                break;

            case ID_COMBINATION: // 31
                callback(Combination(m_resp, pDir, &intern, m_rtip->rti_dbip));
                break;

            default:
                callback(Unknown(m_resp, pDir, &intern, m_rtip->rti_dbip));
            }
        }
        catch(...) {}

        rt_db_free_internal(&intern);
    }
}


void ConstDatabase::SignalDatabaseChange
(
    db_i*      dbip,
    directory* pDir,
    int        mode
) const {
    if ((m_rtip != nullptr) && (m_rtip->rti_dbip == dbip)) {
        ChangeType changeType;

        switch (mode) {
        case 0:
            changeType = ChangeType::Modification;
            break;

        case 1:
            changeType = ChangeType::Addition;
            break;

        case 2:
            changeType = ChangeType::Removal;
            break;

        default:
            changeType = ChangeType::Unknown;
        }

        assert(pDir != nullptr);

        const char* objectName = nullptr;

        if (pDir != nullptr)
            objectName = pDir->d_namep;

        SignalChange(objectName, changeType);
    }
}


void ConstDatabase::SignalChange
(
    const char* objectName,
    ChangeType  changeType
) const {
    if (m_changeSignalHandlers != nullptr) {
        for (size_t i = 0; m_changeSignalHandlers[i] != nullptr; ++i)
            (*m_changeSignalHandlers[i])(objectName, changeType);
    }
}
