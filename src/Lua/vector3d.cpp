/*                         V E C T O R 3 D . C P P
 * BRL-CAD
 *
 * Copyright (c) 2019-2025 United States Government as represented by
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
/** @file vector3d.cpp
 *
 *  BRL-CAD Lua scripting:
 *      BRLCAD::Vector3D functions
 */

#include "vector3d.h"


int CreateVector3D
(
    lua_State* luaState
) {
    int    numberOfParameters = lua_gettop(luaState);
    double x                  = 0.;
    double y                  = 0.;
    double z                  = 0.;

    if (numberOfParameters > 0) {
        if(lua_istable(luaState, -1)) {
            BRLCAD::Vector3D vec = GetVector3D(luaState, 1);

            x = vec.coordinates[0];
            y = vec.coordinates[1];
            z = vec.coordinates[2];
        } else {
            x = luaL_checknumber(luaState, 1);

            if (numberOfParameters > 1) {
                y = luaL_checknumber(luaState, 2);

                if (numberOfParameters > 2)
                    z = luaL_checknumber(luaState, 3);
            }
        }
    }

    lua_newtable(luaState);

    lua_pushnumber(luaState, x);
    lua_setfield(luaState, -2, "x");

    lua_pushnumber(luaState, y);
    lua_setfield(luaState, -2, "y");

    lua_pushnumber(luaState, z);
    lua_setfield(luaState, -2, "z");

    return 1;
}


void PushVector3D
(
    lua_State*              luaState,
    const BRLCAD::Vector3D& value
) {
    lua_newtable(luaState);

    lua_pushnumber(luaState, value.coordinates[0]);
    lua_setfield(luaState, -2, "x");

    lua_pushnumber(luaState, value.coordinates[1]);
    lua_setfield(luaState, -2, "y");

    lua_pushnumber(luaState, value.coordinates[2]);
    lua_setfield(luaState, -2, "z");
}


BRLCAD::Vector3D GetVector3D
(
    lua_State* luaState,
    int        narg
) {
    BRLCAD::Vector3D ret;

    luaL_checktype(luaState, narg, LUA_TTABLE);

    lua_pushstring(luaState, "x");
    lua_gettable(luaState, narg);
    ret.coordinates[0] = luaL_checknumber(luaState, -1);
    lua_pop(luaState, 1);

    lua_pushstring(luaState, "y");
    lua_gettable(luaState, narg);
    ret.coordinates[1] = luaL_checknumber(luaState, -1);
    lua_pop(luaState, 1);

    lua_pushstring(luaState, "z");
    lua_gettable(luaState, narg);
    ret.coordinates[2] = luaL_checknumber(luaState, -1);
    lua_pop(luaState, 1);

    return ret;
}
