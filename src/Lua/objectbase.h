/*                  O B J E C T B A S E . H
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
/** @file objectbase.h
 *
 *  BRL-CAD Lua scripting:
 *      BRLCAD::Object functions
 */

#ifndef OBJECTBASE_INCLUDED
#define OBJECTBASE_INCLUDED

#include "lua.hpp"

#include "brlcad/Database/Object.h"


typedef BRLCAD::Object& (*_GetObject)(lua_State* luaState,
                                      int        narg);


template<_GetObject getObject> static int Name
(
    lua_State* luaState
) {
    BRLCAD::Object& object = (*getObject)(luaState, 1);

    lua_pushstring(luaState, object.Name());

    return 1;
}


template<_GetObject getObject> static int SetName
(
    lua_State* luaState
) {
    BRLCAD::Object& object = (*getObject)(luaState, 1);
    const char*     name   = luaL_checkstring(luaState, -1);

    object.SetName(name);

    return 0;
}


template<_GetObject getObject> static int Type
(
    lua_State* luaState
) {
    BRLCAD::Object& object = (*getObject)(luaState, 1);

    lua_pushstring(luaState, object.Type());

    return 1;
}


template<_GetObject getObject> static int IsValid
(
    lua_State* luaState
) {
    BRLCAD::Object& object = (*getObject)(luaState, 1);

    lua_pushboolean(luaState, object.IsValid());

    return 1;
}


template<_GetObject getObject> static void PushObjectMetatable
(
    lua_State* luaState
) {
    lua_pushstring(luaState, "Name");
    lua_pushcfunction(luaState, &Name<getObject>);
    lua_settable(luaState, -3);

    lua_pushstring(luaState, "SetName");
    lua_pushcfunction(luaState, &SetName<getObject>);
    lua_settable(luaState, -3);

    lua_pushstring(luaState, "Type");
    lua_pushcfunction(luaState, &SetName<getObject>);
    lua_settable(luaState, -3);

    lua_pushstring(luaState, "IsValid");
    lua_pushcfunction(luaState, &SetName<getObject>);
    lua_settable(luaState, -3);
}


#endif // OBJECTBASE_INCLUDED
