/*                         E L L I P T I C A L T O R U S . C P P
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
/** @file ellipticaltorus.cpp
 *
 *  BRL-CAD Lua scripting:
 *      BRLCAD::EllipticalTorus functions
 */

#include <cassert>

#include "objectbase.h"
#include "vector3d.h"
#include "ellipticaltorus.h"


struct ScriptEllipticalTorus {
    BRLCAD::EllipticalTorus* object;
    bool                     own;
};


static BRLCAD::EllipticalTorus& GetEllipticalTorus
(
    lua_State* luaState,
    int        narg
) {
    BRLCAD::EllipticalTorus* object = TestEllipticalTorus(luaState, narg);
    assert(object != nullptr);

    return *object;
}


int CreateEllipticalTorus
(
    lua_State* luaState
) {
    BRLCAD::EllipticalTorus* ret = nullptr;

    if (lua_gettop(luaState) > 0) {
        BRLCAD::EllipticalTorus* original = TestEllipticalTorus(luaState, 1);

        if (original != nullptr)
            ret = new BRLCAD::EllipticalTorus(*original);
        else {
            BRLCAD::Vector3D center                      = GetVector3D(luaState, 1);
            BRLCAD::Vector3D normalToTubeCenterLinePlane = GetVector3D(luaState, 2);
            double           tubeCenterLineRadius        = luaL_checknumber(luaState, 3);
            BRLCAD::Vector3D tubeSemiMajorAxis           = GetVector3D(luaState, 4);
            double           tubeSemiMinorAxisLength     = luaL_checknumber(luaState, 5);

            ret = new BRLCAD::EllipticalTorus(center, normalToTubeCenterLinePlane, tubeCenterLineRadius, tubeSemiMajorAxis, tubeSemiMinorAxisLength);
        }
    }

    if (ret == nullptr)
        ret = new BRLCAD::EllipticalTorus();

    return PushEllipticalTorus(luaState, ret, true);
}


static int Destruct
(
    lua_State* luaState
) {
    ScriptEllipticalTorus* scriptObject = static_cast<ScriptEllipticalTorus*>(luaL_testudata(luaState, 1, "BRLCAD.EllipticalTorus"));

    if ((scriptObject != nullptr) && (scriptObject->object != nullptr) && scriptObject->own)
        scriptObject->object->Destroy();

    return 0;
}


static int Center
(
    lua_State* luaState
) {
    BRLCAD::EllipticalTorus& object = GetEllipticalTorus(luaState, 1);

    PushVector3D(luaState, object.Center());

    return 1;
}


static int SetCenter
(
    lua_State* luaState
) {
    BRLCAD::EllipticalTorus& object = GetEllipticalTorus(luaState, 1);
    BRLCAD::Vector3D         center = GetVector3D(luaState, 2);

    object.SetCenter(center);

    return 0;
}


static int Normal
(
    lua_State* luaState
) {
    BRLCAD::EllipticalTorus& object = GetEllipticalTorus(luaState, 1);

    PushVector3D(luaState, object.Normal());

    return 1;
}


static int SetNormal
(
    lua_State* luaState
) {
    BRLCAD::EllipticalTorus& object = GetEllipticalTorus(luaState, 1);
    BRLCAD::Vector3D         normal = GetVector3D(luaState, 2);

    object.SetNormal(normal);

    return 0;
}


static int TubeCenterLineRadius
(
    lua_State* luaState
) {
    BRLCAD::EllipticalTorus& object = GetEllipticalTorus(luaState, 1);

    lua_pushnumber(luaState, object.TubeCenterLineRadius());

    return 1;
}


static int SetTubeCenterLineRadius
(
    lua_State* luaState
) {
    BRLCAD::EllipticalTorus& object = GetEllipticalTorus(luaState, 1);
    double                   radius = luaL_checknumber(luaState, 2);

    object.SetTubeCenterLineRadius(radius);

    return 0;
}


static int TubeSemiMajorAxis
(
    lua_State* luaState
) {
    BRLCAD::EllipticalTorus& object = GetEllipticalTorus(luaState, 1);

    PushVector3D(luaState, object.TubeSemiMajorAxis());

    return 1;
}


static int SetTubeSemiMajorAxis
(
    lua_State* luaState
) {
    BRLCAD::EllipticalTorus& object = GetEllipticalTorus(luaState, 1);
    BRLCAD::Vector3D         axis   = GetVector3D(luaState, 2);

    object.SetTubeSemiMajorAxis(axis);

    return 0;
}


static int TubeSemiMinorAxis
(
    lua_State* luaState
) {
    BRLCAD::EllipticalTorus& object = GetEllipticalTorus(luaState, 1);

    lua_pushnumber(luaState, object.TubeSemiMinorAxis());

    return 1;
}


static int SetTubeSemiMinorAxis
(
    lua_State* luaState
) {
    BRLCAD::EllipticalTorus& object = GetEllipticalTorus(luaState, 1);
    double                   length = luaL_checknumber(luaState, 2);

    object.SetTubeSemiMinorAxis(length);

    return 0;
}


static int Set
(
    lua_State* luaState
) {
    BRLCAD::EllipticalTorus& object                      = GetEllipticalTorus(luaState, 1);
    BRLCAD::Vector3D         center                      = GetVector3D(luaState, 2);
    BRLCAD::Vector3D         normalToTubeCenterLinePlane = GetVector3D(luaState, 3);
    double                   tubeCenterLineRadius        = luaL_checknumber(luaState, 4);
    BRLCAD::Vector3D         tubeSemiMajorAxis           = GetVector3D(luaState, 5);
    double                   tubeSemiMinorAxisLength     = luaL_checknumber(luaState, 6);

    object.Set(center, normalToTubeCenterLinePlane, tubeCenterLineRadius, tubeSemiMajorAxis, tubeSemiMinorAxisLength);

    return 0;
}


static int ClassName
(
    lua_State* luaState
) {
    lua_pushstring(luaState, BRLCAD::EllipticalTorus::ClassName());

    return 1;
}


static BRLCAD::Object& GetObject
(
    lua_State* luaState,
    int        narg
) {
    return GetEllipticalTorus(luaState, narg);
}


static void GetEllipticalTorusMetatable
(
     lua_State* luaState
) {
    lua_getfield(luaState, LUA_REGISTRYINDEX, "BRLCAD.EllipticalTorus");

    if (!lua_istable(luaState, -1)) {
        lua_pop(luaState, 1);
        luaL_newmetatable(luaState, "BRLCAD.EllipticalTorus");

        lua_pushvalue(luaState, -1);
        lua_setfield(luaState, -2, "__index");

        lua_pushstring(luaState, "__gc");
        lua_pushcfunction(luaState, &Destruct);
        lua_settable(luaState, -3);

        PushObjectMetatable<GetObject>(luaState);

        lua_pushstring(luaState, "Center");
        lua_pushcfunction(luaState, &Center);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetCenter");
        lua_pushcfunction(luaState, &SetCenter);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Normal");
        lua_pushcfunction(luaState, &Normal);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetNormal");
        lua_pushcfunction(luaState, &SetNormal);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "TubeCenterLineRadius");
        lua_pushcfunction(luaState, &TubeCenterLineRadius);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetTubeCenterLineRadius");
        lua_pushcfunction(luaState, &SetTubeCenterLineRadius);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "TubeSemiMajorAxis");
        lua_pushcfunction(luaState, &TubeSemiMajorAxis);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetTubeSemiMajorAxis");
        lua_pushcfunction(luaState, &SetTubeSemiMajorAxis);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "TubeSemiMinorAxis");
        lua_pushcfunction(luaState, &TubeSemiMinorAxis);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetTubeSemiMinorAxis");
        lua_pushcfunction(luaState, &SetTubeSemiMinorAxis);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Set");
        lua_pushcfunction(luaState, &Set);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Clone");
        lua_pushcfunction(luaState, &CreateEllipticalTorus);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "ClassName");
        lua_pushcfunction(luaState, &ClassName);
        lua_settable(luaState, -3);
    }
}


int PushEllipticalTorus
(
    lua_State*               luaState,
    BRLCAD::EllipticalTorus* object,
    bool                     takeOwnership
) {
    int ret = 0;

    if (object != nullptr) {
        ScriptEllipticalTorus* scriptObject = static_cast<ScriptEllipticalTorus*>(lua_newuserdata(luaState, sizeof(ScriptEllipticalTorus)));

        scriptObject->object = object;
        scriptObject->own    = takeOwnership;

        GetEllipticalTorusMetatable(luaState);
        lua_setmetatable(luaState, -2);

        ret = 1;
    }

    return ret;
}


BRLCAD::EllipticalTorus* TestEllipticalTorus
(
    lua_State* luaState,
    int        narg
) {
    BRLCAD::EllipticalTorus* ret          = nullptr;
    ScriptEllipticalTorus*   scriptObject = static_cast<ScriptEllipticalTorus*>(luaL_testudata(luaState, narg, "BRLCAD.EllipticalTorus"));

    if (scriptObject != nullptr)
        ret = scriptObject->object;

    return ret;
}
