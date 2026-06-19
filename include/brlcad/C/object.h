/*                           O B J E C T . H
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
/** @file object.h
 *
 *  BRL-CAD core simplified C interface:
 *      database object declaration
 */

#ifndef BRLCAD_C_OBJECT_INCLUDED
#define BRLCAD_C_OBJECT_INCLUDED

#include <brlcad/C/globals.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef BrlHandle BrlObject;
typedef BrlHandle BrlAttributeIterator;


BRLCAD_MOOSE_EXPORT const char*          BrlObjectType(BrlObject object);

BRLCAD_MOOSE_EXPORT int                  BrlObjectIsValid(BrlObject object);

BRLCAD_MOOSE_EXPORT void                 BrlObjectSetName(BrlObject   object,
                                                          const char* name);

                                                          BRLCAD_MOOSE_EXPORT const char* BrlObjectName(BrlObject object);

BRLCAD_MOOSE_EXPORT int                  BrlObjectHasAttribute(BrlObject object, const char* key);

BRLCAD_MOOSE_EXPORT const char*          BrlObjectAttribute(BrlObject object, const char* key);

BRLCAD_MOOSE_EXPORT void                 BrlObjectSetAttribute(BrlObject object, const char* key, const char* value);

BRLCAD_MOOSE_EXPORT void                 BrlObjectAddMultiAttribute(BrlObject object, const char* key, const char* value);

BRLCAD_MOOSE_EXPORT void                 BrlObjectRemoveAttribute(BrlObject object, const char* key);

BRLCAD_MOOSE_EXPORT void                 BrlObjectClearAttributes(BrlObject object);

BRLCAD_MOOSE_EXPORT BrlAttributeIterator BrlObjectFirstAttribute(BrlObject object);

BRLCAD_MOOSE_EXPORT BrlAttributeIterator BrlObjectMultiAttribute(BrlObject   object,
                                                                 const char* key);

BRLCAD_MOOSE_EXPORT void                 BrlAttributeIteratorNext(BrlAttributeIterator iterator);

BRLCAD_MOOSE_EXPORT int                  BrlAttributeIteratorGood(BrlAttributeIterator iterator);

BRLCAD_MOOSE_EXPORT const char*          BrlAttributeIteratorKey(BrlAttributeIterator iterator);

BRLCAD_MOOSE_EXPORT const char*          BrlAttributeIteratorValue(BrlAttributeIterator iterator);

#ifdef __cplusplus
}
#endif

#endif // BRLCAD_C_OBJECT_INCLUDED
