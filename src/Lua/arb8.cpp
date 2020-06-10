/*                         A R B 8 . C P P
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
/** @file arb8.cpp
 *
 *  BRL-CAD Lua scripting:
 *      BRLCAD::Arb8 functions
 */

#include <cassert>

#include "objectbase.h"
#include "vector3d.h"
#include "arb8.h"


struct ScriptArb8 {
    BRLCAD::Arb8* object;
    bool          own;
};


static BRLCAD::Arb8& GetArb8
(
    lua_State* luaState,
    int        narg
) {
    BRLCAD::Arb8* object = TestArb8(luaState, narg);
    assert(object != 0);

    return *object;
}


int CreateArb8
(
    lua_State* luaState
) {
    BRLCAD::Arb8* ret = 0;

    if (lua_gettop(luaState) > 0) {
        BRLCAD::Arb8* original = TestArb8(luaState, 1);

        if (original != 0) {
            ret = new BRLCAD::Arb8(*original);
        }
        else if (lua_gettop(luaState) == 4){
            BRLCAD::Vector3D point1 = GetVector3D(luaState, 1);
            BRLCAD::Vector3D point2 = GetVector3D(luaState, 2);
            BRLCAD::Vector3D point3 = GetVector3D(luaState, 3);
            BRLCAD::Vector3D point4 = GetVector3D(luaState, 4);

            ret = new BRLCAD::Arb8(point1, point2, point3, point4);
        }
        else if (lua_gettop(luaState) == 5) {
            BRLCAD::Vector3D point1 = GetVector3D(luaState, 1);
            BRLCAD::Vector3D point2 = GetVector3D(luaState, 2);
            BRLCAD::Vector3D point3 = GetVector3D(luaState, 3);
            BRLCAD::Vector3D point4 = GetVector3D(luaState, 4);
            BRLCAD::Vector3D point5 = GetVector3D(luaState, 5);

            ret = new BRLCAD::Arb8(point1, point2, point3, point4, point5);
        }
        else if (lua_gettop(luaState) == 6) {
            BRLCAD::Vector3D point1 = GetVector3D(luaState, 1);
            BRLCAD::Vector3D point2 = GetVector3D(luaState, 2);
            BRLCAD::Vector3D point3 = GetVector3D(luaState, 3);
            BRLCAD::Vector3D point4 = GetVector3D(luaState, 4);
            BRLCAD::Vector3D point5 = GetVector3D(luaState, 5);
            BRLCAD::Vector3D point6 = GetVector3D(luaState, 6);

            ret = new BRLCAD::Arb8(point1, point2, point3, point4, point5, point6);
        }
        else if (lua_gettop(luaState) == 7) {
            BRLCAD::Vector3D point1 = GetVector3D(luaState, 1);
            BRLCAD::Vector3D point2 = GetVector3D(luaState, 2);
            BRLCAD::Vector3D point3 = GetVector3D(luaState, 3);
            BRLCAD::Vector3D point4 = GetVector3D(luaState, 4);
            BRLCAD::Vector3D point5 = GetVector3D(luaState, 5);
            BRLCAD::Vector3D point6 = GetVector3D(luaState, 6);
            BRLCAD::Vector3D point7 = GetVector3D(luaState, 7);

            ret = new BRLCAD::Arb8(point1, point2, point3, point4, point5, point6, point7);
        }
        else {
            BRLCAD::Vector3D point1 = GetVector3D(luaState, 1);
            BRLCAD::Vector3D point2 = GetVector3D(luaState, 2);
            BRLCAD::Vector3D point3 = GetVector3D(luaState, 3);
            BRLCAD::Vector3D point4 = GetVector3D(luaState, 4);
            BRLCAD::Vector3D point5 = GetVector3D(luaState, 5);
            BRLCAD::Vector3D point6 = GetVector3D(luaState, 6);
            BRLCAD::Vector3D point7 = GetVector3D(luaState, 7);
            BRLCAD::Vector3D point8 = GetVector3D(luaState, 8);

          ret = new BRLCAD::Arb8(point1, point2, point3, point4, point5, point6, point7, point8);
        }
    }

    if (ret == 0)
        ret = new BRLCAD::Arb8();

    return PushArb8(luaState, ret, true);
}


static int Destruct
(
    lua_State* luaState
) {
    ScriptArb8* scriptObject = static_cast<ScriptArb8*>(luaL_testudata(luaState, 1, "BRLCAD.Arb8"));

    if ((scriptObject != 0) && (scriptObject->object != 0) && scriptObject->own)
        scriptObject->object->Destroy();

    return 0;
}


static int NumberOfVertices
(
    lua_State* luaState
) {
    BRLCAD::Arb8& object = GetArb8(luaState, 1);

    lua_pushnumber(luaState, object.NumberOfVertices());

    return 1;
}


static int Point
(
    lua_State* luaState
) {
    BRLCAD::Arb8& object = GetArb8(luaState, 1);
    size_t        number = luaL_checknumber(luaState, 2);

    PushVector3D(luaState, object.Point(number));

    return 1;
}


static int SetPoint
(
    lua_State* luaState
) {
    BRLCAD::Arb8&    object = GetArb8(luaState, 1);
    size_t           number = luaL_checknumber(luaState, 2);
    BRLCAD::Vector3D point  = GetVector3D(luaState, 3);

    object.SetPoint(number, point);

    return 0;
}


static int RawPoint
(
    lua_State* luaState
) {
    BRLCAD::Arb8& object = GetArb8(luaState, 1);
    size_t        index  = luaL_checknumber(luaState, 2);

    PushVector3D(luaState, object.RawPoint(index));

    return 1;
}


static int SetRawPoint
(
    lua_State* luaState
) {
    BRLCAD::Arb8&    object = GetArb8(luaState, 1);
    size_t           index  = luaL_checknumber(luaState, 2);
    BRLCAD::Vector3D point  = GetVector3D(luaState, 3);

    object.SetPoint(index, point);

    return 0;
}


static int SetPoints
(
    lua_State* luaState
) {
    BRLCAD::Arb8&    object = GetArb8(luaState, 1);
    BRLCAD::Vector3D point1 = GetVector3D(luaState, 2);
    BRLCAD::Vector3D point2 = GetVector3D(luaState, 3);

    if (lua_gettop(luaState) == 5) {
        BRLCAD::Vector3D point3 = GetVector3D(luaState, 4);
        BRLCAD::Vector3D point4 = GetVector3D(luaState, 5);

        object.SetPoints(point1, point2, point3, point4);
    }
    else if (lua_gettop(luaState) == 6) {
        BRLCAD::Vector3D point3 = GetVector3D(luaState, 4);
        BRLCAD::Vector3D point4 = GetVector3D(luaState, 5);
        BRLCAD::Vector3D point5 = GetVector3D(luaState, 6);

        object.SetPoints(point1, point2, point3, point4, point5);
    }
    else if (lua_gettop(luaState) == 7) {
        BRLCAD::Vector3D point3 = GetVector3D(luaState, 4);
        BRLCAD::Vector3D point4 = GetVector3D(luaState, 5);
        BRLCAD::Vector3D point5 = GetVector3D(luaState, 6);
        BRLCAD::Vector3D point6 = GetVector3D(luaState, 7);

        object.SetPoints(point1, point2, point3, point4, point5, point6);
    }
    else if (lua_gettop(luaState) == 8) {
        BRLCAD::Vector3D point3 = GetVector3D(luaState, 4);
        BRLCAD::Vector3D point4 = GetVector3D(luaState, 5);
        BRLCAD::Vector3D point5 = GetVector3D(luaState, 6);
        BRLCAD::Vector3D point6 = GetVector3D(luaState, 7);
        BRLCAD::Vector3D point7 = GetVector3D(luaState, 8);

        object.SetPoints(point1, point2, point3, point4, point5, point6, point7);
    }
    else if (lua_gettop(luaState) == 9) {
        BRLCAD::Vector3D point3 = GetVector3D(luaState, 4);
        BRLCAD::Vector3D point4 = GetVector3D(luaState, 5);
        BRLCAD::Vector3D point5 = GetVector3D(luaState, 6);
        BRLCAD::Vector3D point6 = GetVector3D(luaState, 7);
        BRLCAD::Vector3D point7 = GetVector3D(luaState, 8);
        BRLCAD::Vector3D point8 = GetVector3D(luaState, 9);

        object.SetPoints(point1, point2, point3, point4, point5, point6, point7, point8);
    }
    else {
        object.SetPoints(point1, point2);
    }

    return 0;
}


static int ClassName
(
    lua_State* luaState
) {
    lua_pushstring(luaState, BRLCAD::Arb8::ClassName());

    return 1;
}


static BRLCAD::Object& GetObject
(
    lua_State* luaState,
    int        narg
) {
    return GetArb8(luaState, narg);
}


static void GetArb8Metatable
(
    lua_State* luaState
) {
    lua_getfield(luaState, LUA_REGISTRYINDEX, "BRLCAD.Arb8");

    if (!lua_istable(luaState, -1)) {
        lua_pop(luaState, 1);
        luaL_newmetatable(luaState, "BRLCAD.Arb8");

        lua_pushvalue(luaState, -1);
        lua_setfield(luaState, -2, "__index");

        lua_pushstring(luaState, "__gc");
        lua_pushcfunction(luaState, &Destruct);
        lua_settable(luaState, -3);

        PushObjectMetatable<GetObject>(luaState);

        lua_pushstring(luaState, "Point");
        lua_pushcfunction(luaState, &Point);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetPoint");
        lua_pushcfunction(luaState, &SetPoint);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "RawPoint");
        lua_pushcfunction(luaState, &RawPoint);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetRawPoint");
        lua_pushcfunction(luaState, &SetRawPoint);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetPoints");
        lua_pushcfunction(luaState, &SetPoints);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetPoints");
        lua_pushcfunction(luaState, &SetPoints);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetPoints");
        lua_pushcfunction(luaState, &SetPoints);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetPoints");
        lua_pushcfunction(luaState, &SetPoints);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetPoints");
        lua_pushcfunction(luaState, &SetPoints);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetPoints");
        lua_pushcfunction(luaState, &SetPoints);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Clone");
        lua_pushcfunction(luaState, &CreateArb8);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "ClassName");
        lua_pushcfunction(luaState, &ClassName);
        lua_settable(luaState, -3);
    }
}


int PushArb8
(
    lua_State*    luaState,
    BRLCAD::Arb8* object,
    bool          takeOwnership
) {
    int ret = 0;

    if (object != 0) {
        ScriptArb8* scriptObject = static_cast<ScriptArb8*>(lua_newuserdata(luaState, sizeof(ScriptArb8)));

        scriptObject->object = object;
        scriptObject->own    = takeOwnership;

        GetArb8Metatable(luaState);
        lua_setmetatable(luaState, -2);

        ret = 1;
    }

    return ret;
}


BRLCAD::Arb8* TestArb8
(
    lua_State* luaState,
    int        narg
) {
    BRLCAD::Arb8* ret          = 0;
    ScriptArb8*   scriptObject = static_cast<ScriptArb8*>(luaL_testudata(luaState, narg, "BRLCAD.Arb8"));

    if (scriptObject != 0)
        ret = scriptObject->object;

    return ret;
}
