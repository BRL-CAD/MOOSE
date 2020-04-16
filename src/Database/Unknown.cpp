/*                      U N K N O W N . C P P
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
/** @file Unknown.cpp
 *
 *  BRL-CAD core C++ interface:
 *      yet unknown database object implementation
 */

#include <cassert>

#include <brlcad/Database/Unknown.h>


using namespace BRLCAD;


Unknown::Unknown
(
    const Unknown& original
) : Object(original) {}


Unknown::~Unknown(void) {}


const Unknown& Unknown::operator=
(
    const Unknown& original
) {
    Copy(original);

    return *this;
}


const Object& Unknown::operator=
(
    const Object& original
) {
    const Unknown* unknown = dynamic_cast<const Unknown*>(&original);
    assert(unknown != 0);

    if (unknown != 0)
        *this = *unknown;

    return *this;
}


Object* Unknown::Clone(void) const {
    return new Unknown(*this);
}


const char* Unknown::ClassName(void) {
    return "Unknown";
}


const char* Unknown::Type(void) const {
    return ClassName();
}


bool Unknown::IsValid(void) const {
    return Validate(); // the opportunistic solution
}


Unknown::Unknown
(
    resource*       resp,
    directory*      pDir,
    rt_db_internal* ip,
    db_i*           dbip
) : Object(resp, pDir, ip, dbip) {}
