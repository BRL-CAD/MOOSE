/*                 O B J E C T A T T R I B U T E I T E R A T O R . C P P
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
/** @file objectattributeiterator.cpp
 *
 *  BRL-CAD Lua scripting:
 *      BRLCAD::Object::AttributeIterator functions
 */

#include <cassert>

#include "objectattributeiterator.h"


static BRLCAD::Object::AttributeIterator& GetObjectAttributeIterator
(
    lua_State* luaState,
    int        narg
) {
    BRLCAD::Object::AttributeIterator** object = static_cast<BRLCAD::Object::AttributeIterator**>(luaL_testudata(luaState, narg, "BRLCAD.ObjectAttributeIterator"));

    assert((object != nullptr) && (*object != nullptr));

    return **object;
}


static int Destruct
(
    lua_State* luaState
) {
    BRLCAD::Object::AttributeIterator** object = static_cast<BRLCAD::Object::AttributeIterator**>(luaL_testudata(luaState, 1, "BRLCAD.ObjectAttributeIterator"));

    if ((object != nullptr) && (*object != nullptr))
        delete *object;

    return 0;
}


static int Next
(
    lua_State* luaState
) {
    BRLCAD::Object::AttributeIterator& iterator = GetObjectAttributeIterator(luaState, 1);

    ++iterator;

    lua_pushboolean(luaState, iterator.Good());

    return 1;
}


static int Good
(
    lua_State* luaState
) {
    BRLCAD::Object::AttributeIterator& iterator = GetObjectAttributeIterator(luaState, 1);

    lua_pushboolean(luaState, iterator.Good());

    return 1;
}


static int Key
(
    lua_State* luaState
) {
    BRLCAD::Object::AttributeIterator& iterator = GetObjectAttributeIterator(luaState, 1);

    lua_pushstring(luaState, iterator.Key());

    return 1;
}


static int Value
(
    lua_State* luaState
) {
    BRLCAD::Object::AttributeIterator& iterator = GetObjectAttributeIterator(luaState, 1);

    lua_pushstring(luaState, iterator.Value());

    return 1;
}


static void GetObjectAttributeIteratorMetatable
(
    lua_State* luaState
) {
    lua_getfield(luaState, LUA_REGISTRYINDEX, "BRLCAD.ObjectAttributeIterator");

    if (!lua_istable(luaState, -1)) {
        lua_pop(luaState, 1);
        luaL_newmetatable(luaState, "BRLCAD.ObjectAttributeIterator");

        lua_pushvalue(luaState, -1);
        lua_setfield(luaState, -2, "__index");

        lua_pushstring(luaState, "__gc");
        lua_pushcfunction(luaState, &Destruct);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Next");
        lua_pushcfunction(luaState, &Next);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Good");
        lua_pushcfunction(luaState, &Good);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Key");
        lua_pushcfunction(luaState, &Key);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Value");
        lua_pushcfunction(luaState, &Value);
        lua_settable(luaState, -3);
    }
}


int PushObjectAttributeIterator
(
    lua_State*                               luaState,
    const BRLCAD::Object::AttributeIterator& iterator
) {
    BRLCAD::Object::AttributeIterator** iteratorObject = static_cast<BRLCAD::Object::AttributeIterator**>(lua_newuserdata(luaState, sizeof(BRLCAD::Object::AttributeIterator*)));

    *iteratorObject = new BRLCAD::Object::AttributeIterator(iterator);

    GetObjectAttributeIteratorMetatable(luaState);
    lua_setmetatable(luaState, -2);

    return 1;
}
