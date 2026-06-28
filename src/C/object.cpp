/*                  O B J E C T . C P P
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
/** @file object.cpp
 *
 *  BRL-CAD core simplified C interface:
 *      implements database objects
 */

#include <cassert>

#include <brlcad/C/object.h>

#include "casts.h"


using namespace BRLCAD;


BrlObject BrlObjectClone
(
    BrlObject object
) {
    BrlObject ret = nullptr;

    if (object != nullptr) {
        Object *obj = CastObject(object);
        assert(obj != nullptr);

        if (obj != nullptr)
            ret = new ObjectData(obj->Clone());
    }

    return ret;
}


const char* BrlObjectType
(
    BrlObject object
) {
    const char* ret = nullptr;

    if (object != nullptr) {
        Object* objectIntern = CastObject(object);

        assert(objectIntern != nullptr);

        if (objectIntern != nullptr)
            ret = objectIntern->Type();
    }

    return ret;
}


int BrlObjectIsValid
(
    BrlObject object
) {
    int ret = 0;

    if (object != nullptr) {
        Object* objectIntern = CastObject(object);

        assert(objectIntern != nullptr);

        if (objectIntern != nullptr)
            ret = objectIntern->IsValid() ? 1 : 0;
    }

    return ret;
}


const char* BrlObjectName
(
    BrlObject object
) {
    const char* ret = nullptr;

    if (object != nullptr) {
        Object* objectIntern = CastObject(object);

        assert(objectIntern != nullptr);

        if (objectIntern != nullptr)
            ret = objectIntern->Name();
    }

    return ret;
}


void BrlObjectSetName
(
    BrlObject   object,
    const char* name
) {
    if (object != nullptr) {
        Object* objectIntern = CastObject(object);

        assert(objectIntern != nullptr);

        if (objectIntern != nullptr)
            objectIntern->SetName(name);
    }
}


void BrlObjectAttributeIteratorNext
(
    BrlObjectAttributeIterator iterator
) {
    if (iterator != nullptr) {
        Object::AttributeIterator* iteratorIntern = CastObjectAttributeIterator(iterator);

        assert(iteratorIntern != nullptr);

        if (iteratorIntern != nullptr)
            ++(*iteratorIntern);
    }
}


int BrlObjectAttributeIteratorGood
(
    BrlObjectAttributeIterator iterator
) {
    int ret = 0;

    if (iterator != nullptr) {
        Object::AttributeIterator* iteratorIntern = CastObjectAttributeIterator(iterator);

        assert(iteratorIntern != nullptr);

        if (iteratorIntern != nullptr)
            ret = iteratorIntern->Good() ? 1 : 0;
    }

    return ret;
}


const char* BrlObjectAttributeIteratorKey
(
    BrlObjectAttributeIterator iterator
) {
    const char* ret = nullptr;

    if (iterator != nullptr) {
        Object::AttributeIterator* iteratorIntern = CastObjectAttributeIterator(iterator);

        assert(iteratorIntern != nullptr);

        if (iteratorIntern != nullptr)
            ret = iteratorIntern->Key();
    }

    return ret;
}


const char* BrlObjectAttributeIteratorValue
(
    BrlObjectAttributeIterator iterator
) {
    const char* ret = nullptr;

    if (iterator != nullptr) {
        Object::AttributeIterator* iteratorIntern = CastObjectAttributeIterator(iterator);

        assert(iteratorIntern != nullptr);

        if (iteratorIntern != nullptr)
            ret = iteratorIntern->Value();
    }

    return ret;
}


int BrlObjectHasAttribute
(
    BrlObject   object,
    const char* key
) {
    int ret = 0;

    if (object != nullptr) {
        Object* objectIntern = CastObject(object);

        assert(objectIntern != nullptr);

        if (objectIntern != nullptr)
            ret = objectIntern->HasAttribute(key) ? 1 : 0;
    }

    return ret;
}


BrlObjectAttributeIterator BrlObjectFirstAttribute
(
    BrlObject object
) {
    BrlObjectAttributeIterator ret = nullptr;

    if (object != nullptr) {
        Object* objectIntern = CastObject(object);

        assert(objectIntern != nullptr);

        if (objectIntern != nullptr)
            ret = new ObjectAttributeIteratorData(objectIntern->FirstAttribute());
    }

    return ret;
}


const char* BrlObjectAttribute
(
    BrlObject   object,
    const char* key
) {
    const char* ret = nullptr;

    if (object != nullptr) {
        Object* objectIntern = CastObject(object);

        assert(objectIntern != nullptr);

        if (objectIntern != nullptr)
            ret = objectIntern->Attribute(key);
    }

    return ret;
}


BrlObjectAttributeIterator BrlObjectMultiAttribute
(
    BrlObject   object,
    const char* key
) {
    BrlObjectAttributeIterator ret = nullptr;

    if (object != nullptr) {
        Object* objectIntern = CastObject(object);

        assert(objectIntern != nullptr);

        if (objectIntern != nullptr)
            ret = new ObjectAttributeIteratorData(objectIntern->MultiAttribute(key));
    }

    return ret;
}


void BrlObjectSetAttribute
(
    BrlObject   object,
    const char* key,
    const char* value
) {
    if (object != nullptr) {
        Object* objectIntern = CastObject(object);

        assert(objectIntern != nullptr);

        if (objectIntern != nullptr)
            objectIntern->SetAttribute(key, value);
    }
}


void BrlObjectAddMultiAttribute
(
    BrlObject   object,
    const char* key,
    const char* value
) {
    if (object != nullptr) {
        Object* objectIntern = CastObject(object);

        assert(objectIntern != nullptr);

        if (objectIntern != nullptr)
            objectIntern->AddMultiAttribute(key, value);
    }
}


void BrlObjectRemoveAttribute
(
    BrlObject   object,
    const char* key
) {
    if (object != nullptr) {
        Object* objectIntern = CastObject(object);

        assert(objectIntern != nullptr);

        if (objectIntern != nullptr)
            objectIntern->RemoveAttribute(key);
    }
}


void BrlObjectClearAttributes
(
    BrlObject object
) {
    if (object != nullptr) {
        Object* objectIntern = CastObject(object);

        assert(objectIntern != nullptr);

        if (objectIntern != nullptr)
            objectIntern->ClearAttributes();
    }
}
