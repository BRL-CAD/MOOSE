/*                         P A R A B O L O I D . C P P
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
/** @file paraboloid.cpp
 *
 *  BRL-CAD Lua scripting:
 *      BRLCAD::Paraboloid functions
 */

#include <cassert>

#include "objectbase.h"
#include "vector3d.h"
#include "paraboloid.h"


struct ScriptParaboloid {
    BRLCAD::Paraboloid* object;
    bool                own;
};


static BRLCAD::Paraboloid& GetParaboloid
(
    lua_State* luaState,
    int        narg
) {
    BRLCAD::Paraboloid* object = TestParaboloid(luaState, narg);
    assert(object != nullptr);

    return *object;
}


int CreateParaboloid
(
    lua_State* luaState
) {
    BRLCAD::Paraboloid* ret = nullptr;

    if (lua_gettop(luaState) > 0) {
        BRLCAD::Paraboloid* original = TestParaboloid(luaState, 1);

        if (original != nullptr)
            ret = new BRLCAD::Paraboloid(*original);
        else if (lua_gettop(luaState) == 4) {
            BRLCAD::Vector3D basePoint           = GetVector3D(luaState, 1);
            BRLCAD::Vector3D height              = GetVector3D(luaState, 2);
            BRLCAD::Vector3D semiMajorAxis       = GetVector3D(luaState, 3);
            double           semiMinorAxisLength = luaL_checknumber(luaState, 4);

            ret = new BRLCAD::Paraboloid(basePoint, height, semiMajorAxis, semiMinorAxisLength);
        }
        else {
            BRLCAD::Vector3D basePoint              = GetVector3D(luaState, 1);
            BRLCAD::Vector3D height                 = GetVector3D(luaState, 2);
            BRLCAD::Vector3D semiMajorAxisDirection = GetVector3D(luaState, 3);
            double           semiMajorAxisLength    = luaL_checknumber(luaState, 4);
            double           semiMinorAxisLength    = luaL_checknumber(luaState, 5);

            ret = new BRLCAD::Paraboloid(basePoint, height, semiMajorAxisDirection, semiMajorAxisLength, semiMinorAxisLength);
        }
    }

    if (ret == nullptr)
        ret = new BRLCAD::Paraboloid();

    return PushParaboloid(luaState, ret, true);
}


static int Destruct
(
    lua_State* luaState
) {
    ScriptParaboloid* scriptObject = static_cast<ScriptParaboloid*>(luaL_testudata(luaState, 1, "BRLCAD.Paraboloid"));

    if ((scriptObject != nullptr) && (scriptObject->object != nullptr) && scriptObject->own)
        scriptObject->object->Destroy();

    return 0;
}


static int BasePoint
(
    lua_State* luaState
) {
    BRLCAD::Paraboloid& object = GetParaboloid(luaState, 1);

    PushVector3D(luaState, object.BasePoint());

    return 1;
}


static int SetBasePoint
(
    lua_State* luaState
) {
    BRLCAD::Paraboloid& object    = GetParaboloid(luaState, 1);
    BRLCAD::Vector3D    basePoint = GetVector3D(luaState, 2);

    object.SetBasePoint(basePoint);

    return 0;
}


static int Height
(
    lua_State* luaState
) {
    BRLCAD::Paraboloid& object = GetParaboloid(luaState, 1);

    PushVector3D(luaState, object.Height());

    return 1;
}


static int SetHeight
(
    lua_State* luaState
) {
    BRLCAD::Paraboloid& object = GetParaboloid(luaState, 1);
    BRLCAD::Vector3D    height = GetVector3D(luaState, 2);

    object.SetHeight(height);

    return 0;
}


static int SemiMajorAxis
(
    lua_State* luaState
) {
    BRLCAD::Paraboloid& object = GetParaboloid(luaState, 1);

    PushVector3D(luaState, object.SemiMajorAxis());

    return 1;
}


static int SetSemiMajorAxis
(
    lua_State* luaState
) {
    BRLCAD::Paraboloid& object = GetParaboloid(luaState, 1);

    if (lua_gettop(luaState) == 2) {
        BRLCAD::Vector3D axis = GetVector3D(luaState, 2);

        object.SetSemiMajorAxis(axis);
    } else {
        BRLCAD::Vector3D direction = GetVector3D(luaState, 2);
        double           length    = luaL_checknumber(luaState, 3);

        object.SetSemiMajorAxis(direction, length);
    }

    return 0;
}


static int SemiMajorAxisDirection
(
    lua_State* luaState
) {
    BRLCAD::Paraboloid& object = GetParaboloid(luaState, 1);

    PushVector3D(luaState, object.SemiMajorAxisDirection());

    return 1;
}


static int SetSemiMajorAxisDirection
(
    lua_State* luaState
) {
    BRLCAD::Paraboloid& object    = GetParaboloid(luaState, 1);
    BRLCAD::Vector3D    direction = GetVector3D(luaState, 2);

    object.SetSemiMajorAxisDirection(direction);

    return 0;
}


static int SemiMajorAxisLength
(
    lua_State* luaState
) {
    BRLCAD::Paraboloid& object = GetParaboloid(luaState, 1);

    lua_pushnumber(luaState, object.SemiMajorAxisLength());

    return 1;
}


static int SetSemiMajorAxisLength
(
    lua_State* luaState
) {
    BRLCAD::Paraboloid& object = GetParaboloid(luaState, 1);
    double              length = luaL_checknumber(luaState, 2);

    object.SetSemiMajorAxisLength(length);

    return 0;
}

static int SemiMinorAxisLength
(
    lua_State* luaState
) {
    BRLCAD::Paraboloid& object = GetParaboloid(luaState, 1);

    lua_pushnumber(luaState, object.SemiMinorAxisLength());

    return 1;
}


static int SetSemiMinorAxisLength
(
    lua_State* luaState
) {
    BRLCAD::Paraboloid& object = GetParaboloid(luaState, 1);
    double              length = luaL_checknumber(luaState, 2);

    object.SetSemiMinorAxisLength(length);

    return 0;
}


static int Set
(
    lua_State* luaState
) {
    BRLCAD::Paraboloid& object    = GetParaboloid(luaState, 1);
    BRLCAD::Vector3D    basePoint = GetVector3D(luaState, 2);
    BRLCAD::Vector3D    height    = GetVector3D(luaState, 3);

    if (lua_gettop(luaState) == 5) {
        BRLCAD::Vector3D semiMajorAxis       = GetVector3D(luaState, 4);
        double           semiMinorAxisLength = luaL_checknumber(luaState, 5);

        object.Set(basePoint, height, semiMajorAxis, semiMinorAxisLength);
    } else {
        BRLCAD::Vector3D semiMajorAxisDirection = GetVector3D(luaState, 4);
        double           semiMajorAxisLength    = luaL_checknumber(luaState, 5);
        double           semiMinorAxisLength    = luaL_checknumber(luaState, 6);

        object.Set(basePoint, height, semiMajorAxisDirection, semiMajorAxisLength, semiMinorAxisLength);
    }

    return 0;
}


static int ClassName
(
    lua_State* luaState
) {
    lua_pushstring(luaState, BRLCAD::Paraboloid::ClassName());

    return 1;
}


static BRLCAD::Object& GetObject
(
    lua_State* luaState,
    int        narg
) {
    return GetParaboloid(luaState, narg);
}


static void GetParaboloidMetatable
(
     lua_State* luaState
) {
    lua_getfield(luaState, LUA_REGISTRYINDEX, "BRLCAD.Paraboloid");

    if (!lua_istable(luaState, -1)) {
        lua_pop(luaState, 1);
        luaL_newmetatable(luaState, "BRLCAD.Paraboloid");

        lua_pushvalue(luaState, -1);
        lua_setfield(luaState, -2, "__index");

        lua_pushstring(luaState, "__gc");
        lua_pushcfunction(luaState, &Destruct);
        lua_settable(luaState, -3);

        PushObjectMetatable<GetObject>(luaState);

        lua_pushstring(luaState, "BasePoint");
        lua_pushcfunction(luaState, &BasePoint);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetBasePoint");
        lua_pushcfunction(luaState, &SetBasePoint);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Height");
        lua_pushcfunction(luaState, &Height);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetHeight");
        lua_pushcfunction(luaState, &SetHeight);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SemiMajorAxis");
        lua_pushcfunction(luaState, &SemiMajorAxis);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetSemiMajorAxis");
        lua_pushcfunction(luaState, &SetSemiMajorAxis);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetSemiMajorAxis");
        lua_pushcfunction(luaState, &SetSemiMajorAxis);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SemiMajorAxisDirection");
        lua_pushcfunction(luaState, &SemiMajorAxisDirection);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetSemiMajorAxisDirection");
        lua_pushcfunction(luaState, &SetSemiMajorAxisDirection);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SemiMajorAxisLength");
        lua_pushcfunction(luaState, &SemiMajorAxisLength);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetSemiMajorAxisLength");
        lua_pushcfunction(luaState, &SetSemiMajorAxisLength);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SemiMinorAxisLength");
        lua_pushcfunction(luaState, &SemiMinorAxisLength);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetSemiMinorAxisLength");
        lua_pushcfunction(luaState, &SetSemiMinorAxisLength);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Set");
        lua_pushcfunction(luaState, &Set);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Set");
        lua_pushcfunction(luaState, &Set);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Clone");
        lua_pushcfunction(luaState, &CreateParaboloid);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "ClassName");
        lua_pushcfunction(luaState, &ClassName);
        lua_settable(luaState, -3);
    }
}


int PushParaboloid
(
    lua_State*          luaState,
    BRLCAD::Paraboloid* object,
    bool                takeOwnership
) {
    int ret = 0;

    if (object != nullptr) {
        ScriptParaboloid* scriptObject = static_cast<ScriptParaboloid*>(lua_newuserdata(luaState, sizeof(ScriptParaboloid)));

        scriptObject->object = object;
        scriptObject->own    = takeOwnership;

        GetParaboloidMetatable(luaState);
        lua_setmetatable(luaState, -2);

        ret = 1;
    }

    return ret;
}


BRLCAD::Paraboloid* TestParaboloid
(
    lua_State* luaState,
    int        narg
) {
    BRLCAD::Paraboloid* ret          = nullptr;
    ScriptParaboloid*   scriptObject = static_cast<ScriptParaboloid*>(luaL_testudata(luaState, narg, "BRLCAD.Paraboloid"));

    if (scriptObject != nullptr)
        ret = scriptObject->object;

    return ret;
}
