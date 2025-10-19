/*                         E L L I P S O I D . H
 * BRL-CAD
 *
 * Copyright (c) 2020-2025 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/** @file ellipsoid.h
 *
 *  BRL-CAD Lua scripting:
 *      BRLCAD::Ellipsoid functions
 */

#ifndef ELLIPSOID_INCLUDED
#define ELLIPSOID_INCLUDED

#include "lua.hpp"

#include "brlcad/Database/Ellipsoid.h"


int CreateEllipsoid
(
    lua_State* luaState
);


int PushEllipsoid
(
    lua_State*         luaState,
    BRLCAD::Ellipsoid* object,
    bool               takeOwnership
);


BRLCAD::Ellipsoid* TestEllipsoid
(
    lua_State* luaState,
    int        narg
);


#endif // ELLIPSOID_INCLUDED
