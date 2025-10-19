/*                         P A R A B O L I C C Y L I N D E R . C P P
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
/** @file paraboliccylinder.cpp
 *
 *  BRL-CAD Lua scripting:
 *      BRLCAD::ParabolicCylinder functions
 */

#include <cassert>

#include "objectbase.h"
#include "vector3d.h"
#include "paraboliccylinder.h"


struct ScriptParabolicCylinder {
    BRLCAD::ParabolicCylinder* object;
    bool                       own;
};


static BRLCAD::ParabolicCylinder& GetParabolicCylinder
(
    lua_State* luaState,
    int        narg
) {
    BRLCAD::ParabolicCylinder* object = TestParabolicCylinder(luaState, narg);
    assert(object != nullptr);

    return *object;
}


int CreateParabolicCylinder
(
    lua_State* luaState
) {
    BRLCAD::ParabolicCylinder* ret = nullptr;

    if (lua_gettop(luaState) > 0) {
        BRLCAD::ParabolicCylinder* original = TestParabolicCylinder(luaState, 1);

        if (original != nullptr)
            ret = new BRLCAD::ParabolicCylinder(*original);
        else {
            BRLCAD::Vector3D basePoint = GetVector3D(luaState, 1);
            BRLCAD::Vector3D height    = GetVector3D(luaState, 2);
            BRLCAD::Vector3D depth     = GetVector3D(luaState, 3);
            double           halfWidth = luaL_checknumber(luaState, 4);

            ret = new BRLCAD::ParabolicCylinder(basePoint, height, depth, halfWidth);
        }
    }

    if (ret == nullptr)
        ret = new BRLCAD::ParabolicCylinder();

    return PushParabolicCylinder(luaState, ret, true);
}


static int Destruct
(
    lua_State* luaState
) {
    ScriptParabolicCylinder* scriptObject = static_cast<ScriptParabolicCylinder*>(luaL_testudata(luaState, 1, "BRLCAD.ParabolicCylinder"));

    if ((scriptObject != nullptr) && (scriptObject->object != nullptr) && scriptObject->own)
        scriptObject->object->Destroy();

    return 0;
}


static int BasePoint
(
    lua_State* luaState
) {
    BRLCAD::ParabolicCylinder& object = GetParabolicCylinder(luaState, 1);

    PushVector3D(luaState, object.BasePoint());

    return 1;
}


static int SetBasePoint
(
    lua_State* luaState
) {
    BRLCAD::ParabolicCylinder& object    = GetParabolicCylinder(luaState, 1);
    BRLCAD::Vector3D           basePoint = GetVector3D(luaState, 2);

    object.SetBasePoint(basePoint);

    return 0;
}


static int Height
(
    lua_State* luaState
) {
    BRLCAD::ParabolicCylinder& object = GetParabolicCylinder(luaState, 1);

    PushVector3D(luaState, object.Height());

    return 1;
}


static int SetHeight
(
    lua_State* luaState
) {
    BRLCAD::ParabolicCylinder& object = GetParabolicCylinder(luaState, 1);
    BRLCAD::Vector3D           height = GetVector3D(luaState, 2);

    object.SetHeight(height);

    return 0;
}


static int Depth
(
    lua_State* luaState
) {
    BRLCAD::ParabolicCylinder& object = GetParabolicCylinder(luaState, 1);

    PushVector3D(luaState, object.Depth());

    return 1;
}


static int SetDepth
(
    lua_State* luaState
) {
    BRLCAD::ParabolicCylinder& object = GetParabolicCylinder(luaState, 1);
    BRLCAD::Vector3D           depth  = GetVector3D(luaState, 2);

    object.SetDepth(depth);

    return 0;
}


static int HalfWidth
(
    lua_State* luaState
) {
    BRLCAD::ParabolicCylinder& object = GetParabolicCylinder(luaState, 1);

    lua_pushnumber(luaState, object.HalfWidth());

    return 1;
}


static int SetHalfWidth
(
    lua_State* luaState
) {
    BRLCAD::ParabolicCylinder& object = GetParabolicCylinder(luaState, 1);
    double                     length = luaL_checknumber(luaState, 2);

    object.SetHalfWidth(length);

    return 0;
}


static int Set
(
    lua_State* luaState
) {
    BRLCAD::ParabolicCylinder& object    = GetParabolicCylinder(luaState, 1);
    BRLCAD::Vector3D           basePoint = GetVector3D(luaState, 2);
    BRLCAD::Vector3D           height    = GetVector3D(luaState, 3);
    BRLCAD::Vector3D           depth     = GetVector3D(luaState, 4);
    double                     halfWidth = luaL_checknumber(luaState, 5);

    object.Set(basePoint, height, depth, halfWidth);

    return 0;
}


static int ClassName
(
    lua_State* luaState
) {
    lua_pushstring(luaState, BRLCAD::ParabolicCylinder::ClassName());

    return 1;
}


static BRLCAD::Object& GetObject
(
    lua_State* luaState,
    int        narg
) {
    return GetParabolicCylinder(luaState, narg);
}


static void GetParabolicCylinderMetatable
(
     lua_State* luaState
) {
    lua_getfield(luaState, LUA_REGISTRYINDEX, "BRLCAD.ParabolicCylinder");

    if (!lua_istable(luaState, -1)) {
        lua_pop(luaState, 1);
        luaL_newmetatable(luaState, "BRLCAD.ParabolicCylinder");

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

        lua_pushstring(luaState, "Depth");
        lua_pushcfunction(luaState, &Depth);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetDepth");
        lua_pushcfunction(luaState, &SetDepth);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "HalfWidth");
        lua_pushcfunction(luaState, &HalfWidth);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetHalfWidth");
        lua_pushcfunction(luaState, &SetHalfWidth);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Set");
        lua_pushcfunction(luaState, &Set);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Clone");
        lua_pushcfunction(luaState, &CreateParabolicCylinder);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "ClassName");
        lua_pushcfunction(luaState, &ClassName);
        lua_settable(luaState, -3);
    }
}


int PushParabolicCylinder
(
    lua_State*                 luaState,
    BRLCAD::ParabolicCylinder* object,
    bool                       takeOwnership
) {
    int ret = 0;

    if (object != nullptr) {
        ScriptParabolicCylinder* scriptObject = static_cast<ScriptParabolicCylinder*>(lua_newuserdata(luaState, sizeof(ScriptParabolicCylinder)));

        scriptObject->object = object;
        scriptObject->own    = takeOwnership;

        GetParabolicCylinderMetatable(luaState);
        lua_setmetatable(luaState, -2);

        ret = 1;
    }

    return ret;
}


BRLCAD::ParabolicCylinder* TestParabolicCylinder
(
    lua_State* luaState,
    int        narg
) {
    BRLCAD::ParabolicCylinder* ret          = nullptr;
    ScriptParabolicCylinder*   scriptObject = static_cast<ScriptParabolicCylinder*>(luaL_testudata(luaState, narg, "BRLCAD.ParabolicCylinder"));

    if (scriptObject != nullptr)
        ret = scriptObject->object;

    return ret;
}
