/*                         H Y P E R B O L I C C Y L I N D E R . C P P
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
/** @file hyperboliccylinder.cpp
 *
 *  BRL-CAD Lua scripting:
 *      BRLCAD::HyperbolicCylinder functions
 */

#include <cassert>

#include "objectbase.h"
#include "vector3d.h"
#include "hyperboliccylinder.h"


struct ScriptHyperbolicCylinder {
    BRLCAD::HyperbolicCylinder* object;
    bool                        own;
};


static BRLCAD::HyperbolicCylinder& GetHyperbolicCylinder
(
    lua_State* luaState,
    int        narg
) {
    BRLCAD::HyperbolicCylinder* object = TestHyperbolicCylinder(luaState, narg);
    assert(object != nullptr);

    return *object;
}


int CreateHyperbolicCylinder
(
    lua_State* luaState
) {
    BRLCAD::HyperbolicCylinder* ret = nullptr;

    if (lua_gettop(luaState) > 0) {
        BRLCAD::HyperbolicCylinder* original = TestHyperbolicCylinder(luaState, 1);

        if (original != nullptr)
            ret = new BRLCAD::HyperbolicCylinder(*original);
        else {
            BRLCAD::Vector3D basePoint             = GetVector3D(luaState, 1);
            BRLCAD::Vector3D height                = GetVector3D(luaState, 2);
            BRLCAD::Vector3D depth                 = GetVector3D(luaState, 3);
            double           halfWidth             = luaL_checknumber(luaState, 4);
            double           apexAsymptoteDistance = luaL_checknumber(luaState, 5);

            ret = new BRLCAD::HyperbolicCylinder(basePoint, height, depth, halfWidth, apexAsymptoteDistance);
        }
    }

    if (ret == nullptr)
        ret = new BRLCAD::HyperbolicCylinder();

    return PushHyperbolicCylinder(luaState, ret, true);
}


static int Destruct
(
    lua_State* luaState
) {
    ScriptHyperbolicCylinder* scriptObject = static_cast<ScriptHyperbolicCylinder*>(luaL_testudata(luaState, 1, "BRLCAD.HyperbolicCylinder"));

    if ((scriptObject != nullptr) && (scriptObject->object != nullptr) && scriptObject->own)
        scriptObject->object->Destroy();

    return 0;
}


static int BasePoint
(
    lua_State* luaState
) {
    BRLCAD::HyperbolicCylinder& object = GetHyperbolicCylinder(luaState, 1);

    PushVector3D(luaState, object.BasePoint());

    return 1;
}


static int SetBasePoint
(
    lua_State* luaState
) {
    BRLCAD::HyperbolicCylinder& object    = GetHyperbolicCylinder(luaState, 1);
    BRLCAD::Vector3D            basePoint = GetVector3D(luaState, 2);

    object.SetBasePoint(basePoint);

    return 0;
}


static int Height
(
    lua_State* luaState
) {
    BRLCAD::HyperbolicCylinder& object = GetHyperbolicCylinder(luaState, 1);

    PushVector3D(luaState, object.Height());

    return 1;
}


static int SetHeight
(
    lua_State* luaState
) {
    BRLCAD::HyperbolicCylinder& object = GetHyperbolicCylinder(luaState, 1);
    BRLCAD::Vector3D            height = GetVector3D(luaState, 2);

    object.SetHeight(height);

    return 0;
}


static int Depth
(
    lua_State* luaState
) {
    BRLCAD::HyperbolicCylinder& object = GetHyperbolicCylinder(luaState, 1);

    PushVector3D(luaState, object.Depth());

    return 1;
}


static int SetDepth
(
    lua_State* luaState
) {
    BRLCAD::HyperbolicCylinder& object = GetHyperbolicCylinder(luaState, 1);
    BRLCAD::Vector3D            depth  = GetVector3D(luaState, 2);

    object.SetDepth(depth);

    return 0;
}


static int HalfWidth
(
    lua_State* luaState
) {
    BRLCAD::HyperbolicCylinder& object = GetHyperbolicCylinder(luaState, 1);

    lua_pushnumber(luaState, object.HalfWidth());

    return 1;
}


static int SetHalfWidth
(
    lua_State* luaState
) {
    BRLCAD::HyperbolicCylinder& object = GetHyperbolicCylinder(luaState, 1);
    double                      length = luaL_checknumber(luaState, 2);

    object.SetHalfWidth(length);

    return 0;
}


static int ApexAsymptoteDistance
(
    lua_State* luaState
) {
    BRLCAD::HyperbolicCylinder& object = GetHyperbolicCylinder(luaState, 1);

    lua_pushnumber(luaState, object.ApexAsymptoteDistance());

    return 1;
}


static int SetApexAsymptoteDistance
(
    lua_State* luaState
) {
    BRLCAD::HyperbolicCylinder& object   = GetHyperbolicCylinder(luaState, 1);
    double                      distance = luaL_checknumber(luaState, 2);

    object.SetApexAsymptoteDistance(distance);

    return 0;
}


static int Set
(
    lua_State* luaState
) {
    BRLCAD::HyperbolicCylinder& object                = GetHyperbolicCylinder(luaState, 1);
    BRLCAD::Vector3D            basePoint             = GetVector3D(luaState, 2);
    BRLCAD::Vector3D            height                = GetVector3D(luaState, 3);
    BRLCAD::Vector3D            depth                 = GetVector3D(luaState, 4);
    double                      halfWidth             = luaL_checknumber(luaState, 5);
    double                      apexAsymptoteDistance = luaL_checknumber(luaState, 6);

    object.Set(basePoint, height, depth, halfWidth, apexAsymptoteDistance);

    return 0;
}


static int ClassName
(
    lua_State* luaState
) {
    lua_pushstring(luaState, BRLCAD::HyperbolicCylinder::ClassName());

    return 1;
}


static BRLCAD::Object& GetObject
(
    lua_State* luaState,
    int        narg
) {
    return GetHyperbolicCylinder(luaState, narg);
}


static void GetHyperbolicCylinderMetatable
(
     lua_State* luaState
) {
    lua_getfield(luaState, LUA_REGISTRYINDEX, "BRLCAD.HyperbolicCylinder");

    if (!lua_istable(luaState, -1)) {
        lua_pop(luaState, 1);
        luaL_newmetatable(luaState, "BRLCAD.HyperbolicCylinder");

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

        lua_pushstring(luaState, "ApexAsymptoteDistance");
        lua_pushcfunction(luaState, &ApexAsymptoteDistance);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetApexAsymptoteDistance");
        lua_pushcfunction(luaState, &SetApexAsymptoteDistance);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Set");
        lua_pushcfunction(luaState, &Set);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Clone");
        lua_pushcfunction(luaState, &CreateHyperbolicCylinder);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "ClassName");
        lua_pushcfunction(luaState, &ClassName);
        lua_settable(luaState, -3);
    }
}


int PushHyperbolicCylinder
(
    lua_State*                  luaState,
    BRLCAD::HyperbolicCylinder* object,
    bool                        takeOwnership
) {
    int ret = 0;

    if (object != nullptr) {
        ScriptHyperbolicCylinder* scriptObject = static_cast<ScriptHyperbolicCylinder*>(lua_newuserdata(luaState, sizeof(ScriptHyperbolicCylinder)));

        scriptObject->object = object;
        scriptObject->own    = takeOwnership;

        GetHyperbolicCylinderMetatable(luaState);
        lua_setmetatable(luaState, -2);

        ret = 1;
    }

    return ret;
}


BRLCAD::HyperbolicCylinder* TestHyperbolicCylinder
(
    lua_State* luaState,
    int        narg
) {
    BRLCAD::HyperbolicCylinder* ret          = nullptr;
    ScriptHyperbolicCylinder*   scriptObject = static_cast<ScriptHyperbolicCylinder*>(luaL_testudata(luaState, narg, "BRLCAD.HyperbolicCylinder"));

    if (scriptObject != nullptr)
        ret = scriptObject->object;

    return ret;
}
