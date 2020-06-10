/*                         P A R A B O L I C C Y L I N D E R . H
 * BRL-CAD
 *
 * Copyright (c) 2020 United States Government as represented by
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
/** @file paraboliccylinder.h
 *
 *  BRL-CAD Lua scripting:
 *      BRLCAD::ParabolicCylinder functions
 */

#ifndef PARABOLICCYLINDER_INCLUDED
#define PARABOLICCYLINDER_INCLUDED

#include "lua.hpp"

#include "brlcad/Database/ParabolicCylinder.h"


int CreateParabolicCylinder
(
    lua_State* luaState
);


int PushParabolicCylinder
(
    lua_State*                 luaState,
    BRLCAD::ParabolicCylinder* object,
    bool                       takeOwnership
);


BRLCAD::ParabolicCylinder* TestParabolicCylinder
(
    lua_State* luaState,
    int        narg
);


#endif // HYPERBOLICCYLINDER_INCLUDED
