/*                      O B J E C T . C P P
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
/** @file Object.cpp
 *
 *  BRL-CAD core C++ interface:
 *      database object implementation
 */

#include <cstring>
#include <cassert>

#include "bu.h"
#include "raytrace.h"

#include <brlcad/Database/Object.h>


using namespace BRLCAD;


//
// class Object::AttributeIterator
//

const Object::AttributeIterator& Object::AttributeIterator::operator++(void) {
    if (m_avs != nullptr) {
        if (m_index > 0) {
            --m_index;

            if (m_searchKey != nullptr) {
                while (strcmp(m_avs->avp[m_index].name, m_searchKey) != 0) {
                    if (m_index == 0) {
                        m_avs = nullptr;
                        break;
                    }

                    --m_index;
                }
            }
        }
        else
            m_avs = nullptr;
    }

    return *this;
}


bool Object::AttributeIterator::Good(void) const {
    return (m_avs != nullptr);
}


const char* Object::AttributeIterator::Key(void) const {
    const char* ret = nullptr;

    assert(m_avs != nullptr);

    if (m_avs != nullptr)
        ret = m_avs->avp[m_index].name;

    return ret;
}


const char* Object::AttributeIterator::Value(void) const {
    const char* ret = nullptr;

    assert(m_avs != nullptr);

    if (m_avs != nullptr)
        ret = m_avs->avp[m_index].value;

    return ret;
}


Object::AttributeIterator::AttributeIterator
(
    const bu_attribute_value_set* avs,
    const char*                   searchKey,
    size_t                        index
) : m_avs(avs), m_searchKey(searchKey), m_index(index) {}


//
// class Object
//

Object::~Object(void) {
    if (m_name != nullptr)
        bu_free(m_name, "BRLCAD::Object::~Object::m_name");

    if (m_avs != nullptr) {
        bu_avs_free(m_avs);
        bu_free(m_avs, "BRLCAD::Object::~Object::m_avs");
    }

    if (m_pDir == nullptr) {
        rt_clean_resource_complete(nullptr, m_resp);
        bu_free(m_resp, "BRLCAD::Object::~Object::m_resp");
    }
}


void Object::Destroy(void) {
    delete this;
}


const char* Object::ClassName(void) {
    return "Object";
}


const char* Object::Name(void) const {
    const char* ret = nullptr;

    assert(!((m_pDir != RT_DIR_NULL) && (m_name != nullptr)));

    if (m_pDir != RT_DIR_NULL)
        ret = m_pDir->d_namep;
    else
        ret = m_name;

    return ret;
}


void Object::SetName
(
    const char* name
) {
    assert(!((m_pDir != RT_DIR_NULL) && (m_name != nullptr)));

    // not connected with a non-writable database
    assert(((m_dbip != nullptr) && !m_dbip->dbi_read_only) || (m_pDir == nullptr));

    if ((m_dbip != nullptr) && !m_dbip->dbi_read_only) // connected with a writable BRLCAD::Database
        db_rename(m_dbip, m_pDir, name);
    else if (m_pDir == nullptr) {                      // connected with no database at all
        if (name != nullptr) {
            if (!BU_SETJUMP) {
                if (m_name != nullptr) {
                    if (strcmp(m_name, name) != 0) {
                        bu_free(m_name, "BRLCAD::Object::SetName");
                        m_name = bu_strdupm(name, "BRLCAD::Object::SetName");
                    }
                }
                else
                    m_name = bu_strdupm(name, "BRLCAD::Object::SetName");
            }
            else {
                BU_UNSETJUMP;
                m_name = nullptr;
            }

            BU_UNSETJUMP;
        }
        else if (m_name != nullptr) {
            bu_free(m_name, "BRLCAD::Object::SetName");
            m_name = nullptr;
        }
    }
    // else: do nothing if connected to a non-writable BRLCAD::ConstDatabase
}


bool Object::HasAttribute
(
    const char* key
) const {
    return (Attribute(key) != nullptr);
}


Object::AttributeIterator Object::FirstAttribute(void) const {
    const bu_attribute_value_set* avs    = GetAvs();
    const bu_attribute_value_set* avsRet = nullptr;
    size_t                        index  = 0;

    if ((avs != nullptr) && (avs->count > 0)) {
        avsRet = avs;
        index  = avs->count - 1;
    }

    return Object::AttributeIterator(avsRet, nullptr, index);
}


const char* Object::Attribute
(
    const char* key
) const {
    const char*                   ret = nullptr;
    const bu_attribute_value_set* avs = GetAvs();

    if ((avs != nullptr) && (avs->count > 0)) {
        size_t index = avs->count;

        do {
            --index;

            if (strcmp(avs->avp[index].name, key) == 0) {
                ret = avs->avp[index].value;
                break;
            }
        } while (index != 0);
    }

    return ret;
}


Object::AttributeIterator Object::MultiAttribute
(
    const char* key
) const {
    const bu_attribute_value_set* avs       = GetAvs();
    const bu_attribute_value_set* avsRet    = nullptr;
    const char*                   keyIntern = nullptr;
    size_t                        index     = 0;

    if ((avs != nullptr) && (avs->count > 0)) {
        index = avs->count;

        do {
            --index;

            if (strcmp(avs->avp[index].name, key) == 0) {
                avsRet    = avs;
                keyIntern = avs->avp[index].name;
                break;
            }
        } while (index != 0);
    }

    return Object::AttributeIterator(avsRet, keyIntern, index);
}


void Object::SetAttribute
(
    const char* key,
    const char* value
) {
    if (!BU_SETJUMP) {
        bu_attribute_value_set* avs = GetAvs(true);

        if (avs != nullptr)
            bu_avs_add(avs, key, value);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


void Object::AddMultiAttribute
(
    const char* key,
    const char* value
) {
    if (!BU_SETJUMP) {
        bu_attribute_value_set* avs = GetAvs(true);

        if (avs != nullptr)
            bu_avs_add_nonunique(avs, key, value);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


void Object::RemoveAttribute
(
    const char* key
) {
    bu_attribute_value_set* avs = GetAvs(false);

    if (avs != nullptr)
       bu_avs_remove(avs, key);
}


void Object::ClearAttributes(void) {
    bu_attribute_value_set* avs = GetAvs(false);

    if (avs != nullptr)
       bu_avs_free(avs);
}


Object::Object(void) : m_pDir(nullptr), m_ip(nullptr), m_dbip(nullptr), m_name(nullptr), m_avs(nullptr) {
    if (!BU_SETJUMP) {
        m_resp = static_cast<resource*>(bu_calloc(1, sizeof(resource), "BRLCAD::Object::Object::m_resp"));
        rt_init_resource(m_resp, 0, NULL);
    }
    else {
        BU_UNSETJUMP;
    }

    BU_UNSETJUMP;
}


Object::Object
(
    resource*       resp,
    directory*      pDir,
    rt_db_internal* ip,
    db_i*           dbip
) : m_resp(resp), m_pDir(pDir), m_ip(ip), m_dbip(dbip), m_name(nullptr), m_avs(nullptr) {
    assert(m_pDir != nullptr);
}


Object::Object
(
    const Object& original
) : m_resp(nullptr), m_pDir(nullptr), m_ip(nullptr), m_dbip(nullptr), m_name(nullptr), m_avs(nullptr) {
    if (!BU_SETJUMP) {
        m_resp = static_cast<resource*>(bu_calloc(1, sizeof(resource), "BRLCAD::Object::Object::m_resp"));
        rt_init_resource(m_resp, 0, NULL);
    }
    else {
        BU_UNSETJUMP;

        if (m_resp != nullptr)
            bu_free(m_resp, "BRLCAD::Object::Object::m_resp");

    }

    BU_UNSETJUMP;

    Copy(original);
}


void Object::Copy
(
    const Object& original
) {
    if (&original != this) {
        SetName(original.Name());

        if (((m_dbip != nullptr) && !m_dbip->dbi_read_only) || // connected with a writable BRLCAD::Database
            (m_pDir == nullptr)) {                             // connected with no database at all

            bu_attribute_value_set*       avs     = GetAvs(false);
            const bu_attribute_value_set* origAvs = original.GetAvs();

            if ((origAvs != nullptr) && (origAvs->count > 0)) {
                if (!BU_SETJUMP) {
                    // get a clean bu_attribute_value_set
                    if (avs == nullptr) {
                        assert(m_pDir == nullptr); // &m_ip->idb_avs can't be 0 therefore we are connected with no database at all
                        m_avs = bu_avs_new(origAvs->count, "BRLCAD::Object::Copy");
                        avs   = m_avs;
                    }
                    else
                        bu_avs_free(avs);

                    // copy the bu_attribute_value_set
                    for (size_t i = 0; i < origAvs->count; ++i)
                        bu_avs_add_nonunique(avs, origAvs->avp->name, origAvs->avp->value);
                }
                else {
                    BU_UNSETJUMP;
                }

                BU_UNSETJUMP;
            }
            else if ((avs != nullptr) && (avs->count > 0))
                bu_avs_free(avs);
        }
    }
}


bool Object::Validate(void) const {
    const char* name = Name();

    return (name != nullptr) && (strlen(name) > 0);
}

const bu_attribute_value_set* Object::GetAvs(void) const {
    const bu_attribute_value_set* ret = nullptr;

    assert(!((m_pDir != RT_DIR_NULL) && (m_avs != nullptr)));

    if (m_pDir != RT_DIR_NULL)
        ret = &m_ip->idb_avs;
    else
        ret = m_avs;

    return ret;
}


bu_attribute_value_set* Object::GetAvs
(
    bool create
) {
    bu_attribute_value_set* ret = nullptr;

    assert(!((m_pDir != RT_DIR_NULL) && (m_avs != nullptr)));

    // not connected with a non-writable database
    assert(((m_dbip != nullptr) && !m_dbip->dbi_read_only) || (m_pDir == nullptr));

    if ((m_dbip != nullptr) && !m_dbip->dbi_read_only) // connected with a writable BRLCAD::Database
        ret = &m_ip->idb_avs;
    else if (m_pDir == nullptr) {                      // connected with no database at all
        if ((m_avs == nullptr) && create)
            m_avs = bu_avs_new(0, "BRLCAD::Object::GetAvs");

        ret = m_avs;
    }
    // else: do nothing if connected to a non-writable BRLCAD::ConstDatabase

    return ret;
}
