/*                         V E C T O R 3 D . H
 * BRL-CAD
 *
 * Copyright (c) 2019 United States Government as represented by
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
/** @file vector3d.h
 *
 *  BRL-CAD Lua scripting:
 *      BRLCAD::Vector3D functions
 */

#ifndef VECTOR3D_INCLUDED
#define VECTOR3D_INCLUDED

#include "lua.hpp"

#include "brlcad/vector.h"


int CreateVector3D
(
    lua_State* luaState
);


void PushVector3D
(
    lua_State*              luaState,
    const BRLCAD::Vector3D& value
);


BRLCAD::Vector3D GetVector3D
(
    lua_State* luaState,
    int        narg
);


#endif // VECTOR3D_INCLUDED
