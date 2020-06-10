/*                         T O R U S . C P P
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
/** @file torus.cpp
 *
 *  BRL-CAD Lua scripting:
 *      BRLCAD::Torus functions
 */

#include <cassert>

#include "objectbase.h"
#include "vector3d.h"
#include "torus.h"


struct ScriptTorus {
    BRLCAD::Torus* object;
    bool           own;
};


static BRLCAD::Torus& GetTorus
(
    lua_State* luaState,
    int        narg
) {
    BRLCAD::Torus* object = TestTorus(luaState, narg);
    assert(object != 0);

    return *object;
}


int CreateTorus
(
    lua_State* luaState
) {
    BRLCAD::Torus* ret = 0;

    if (lua_gettop(luaState) > 0) {
        BRLCAD::Torus* original = TestTorus(luaState, 1);

        if (original != 0)
            ret = new BRLCAD::Torus(*original);
        else {
            BRLCAD::Vector3D center                      = GetVector3D(luaState, 1);
            BRLCAD::Vector3D normalToTubeCenterLinePlane = GetVector3D(luaState, 2);
            double           tubeCenterLineRadius        = luaL_checknumber(luaState, 3);
            double           tubeRadius                  = luaL_checknumber(luaState, 4);

            ret = new BRLCAD::Torus(center, normalToTubeCenterLinePlane, tubeCenterLineRadius, tubeRadius);
        }
    }

    if (ret == 0)
        ret = new BRLCAD::Torus();

    return PushTorus(luaState, ret, true);
}


static int Destruct
(
    lua_State* luaState
) {
    ScriptTorus* scriptObject = static_cast<ScriptTorus*>(luaL_testudata(luaState, 1, "BRLCAD.Torus"));

    if ((scriptObject != 0) && (scriptObject->object != 0) && scriptObject->own)
        scriptObject->object->Destroy();

    return 0;
}


static int Center
(
    lua_State* luaState
) {
    BRLCAD::Torus& object = GetTorus(luaState, 1);

    PushVector3D(luaState, object.Center());

    return 1;
}


static int SetCenter
(
    lua_State* luaState
) {
    BRLCAD::Torus&   object = GetTorus(luaState, 1);
    BRLCAD::Vector3D center = GetVector3D(luaState, 2);

    object.SetCenter(center);

    return 0;
}


static int Normal
(
    lua_State* luaState
) {
    BRLCAD::Torus& object = GetTorus(luaState, 1);

    PushVector3D(luaState, object.Normal());

    return 1;
}


static int SetNormal
(
    lua_State* luaState
) {
    BRLCAD::Torus&   object = GetTorus(luaState, 1);
    BRLCAD::Vector3D normal = GetVector3D(luaState, 2);

    object.SetNormal(normal);

    return 0;
}


static int TubeCenterLineRadius
(
    lua_State* luaState
) {
    BRLCAD::Torus& object = GetTorus(luaState, 1);

    lua_pushnumber(luaState, object.TubeCenterLineRadius());

    return 1;
}


static int SetTubeCenterLineRadius
(
    lua_State* luaState
) {
    BRLCAD::Torus& object = GetTorus(luaState, 1);
    double         radius = luaL_checknumber(luaState, 2);

    object.SetTubeCenterLineRadius(radius);

    return 0;
}


static int TubeRadius
(
    lua_State* luaState
) {
    BRLCAD::Torus& object = GetTorus(luaState, 1);

    lua_pushnumber(luaState, object.TubeRadius());

    return 1;
}


static int SetTubeRadius
(
    lua_State* luaState
) {
    BRLCAD::Torus& object = GetTorus(luaState, 1);
    double         radius = luaL_checknumber(luaState, 2);

    object.SetTubeRadius(radius);

    return 0;
}


static int Set
(
    lua_State* luaState
) {
    BRLCAD::Torus&   object                      = GetTorus(luaState, 1);
    BRLCAD::Vector3D center                      = GetVector3D(luaState, 2);
    BRLCAD::Vector3D normalToTubeCenterLinePlane = GetVector3D(luaState, 3);
    double           tubeCenterLineRadius        = luaL_checknumber(luaState, 4);
    double           tubeRadius                  = luaL_checknumber(luaState, 5);

    object.Set(center, normalToTubeCenterLinePlane, tubeCenterLineRadius, tubeRadius);

    return 0;
}


static int ClassName
(
    lua_State* luaState
) {
    lua_pushstring(luaState, BRLCAD::Torus::ClassName());

    return 1;
}


static BRLCAD::Object& GetObject
(
    lua_State* luaState,
    int        narg
) {
    return GetTorus(luaState, narg);
}


static void GetTorusMetatable
(
     lua_State* luaState
) {
    lua_getfield(luaState, LUA_REGISTRYINDEX, "BRLCAD.Torus");

    if (!lua_istable(luaState, -1)) {
        lua_pop(luaState, 1);
        luaL_newmetatable(luaState, "BRLCAD.Torus");

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

        lua_pushstring(luaState, "TubeRadius");
        lua_pushcfunction(luaState, &TubeRadius);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetTubeRadius");
        lua_pushcfunction(luaState, &SetTubeRadius);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Set");
        lua_pushcfunction(luaState, &Set);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Clone");
        lua_pushcfunction(luaState, &CreateTorus);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "ClassName");
        lua_pushcfunction(luaState, &ClassName);
        lua_settable(luaState, -3);
    }
}


int PushTorus
(
    lua_State*     luaState,
    BRLCAD::Torus* object,
    bool           takeOwnership
) {
    int ret = 0;

    if (object != 0) {
        ScriptTorus* scriptObject = static_cast<ScriptTorus*>(lua_newuserdata(luaState, sizeof(ScriptTorus)));

        scriptObject->object = object;
        scriptObject->own    = takeOwnership;

        GetTorusMetatable(luaState);
        lua_setmetatable(luaState, -2);

        ret = 1;
    }

    return ret;
}


BRLCAD::Torus* TestTorus
(
    lua_State* luaState,
    int        narg
) {
    BRLCAD::Torus* ret          = 0;
    ScriptTorus*   scriptObject = static_cast<ScriptTorus*>(luaL_testudata(luaState, narg, "BRLCAD.Torus"));

    if (scriptObject != 0)
        ret = scriptObject->object;

    return ret;
}
