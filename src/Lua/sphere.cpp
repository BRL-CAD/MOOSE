/*                         S P H E R E . C P P
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
/** @file sphere.cpp
 *
 *  BRL-CAD Lua scripting:
 *      BRLCAD::Sphere functions
 */

#include <cassert>

#include "objectbase.h"
#include "vector3d.h"
#include "sphere.h"


struct ScriptSphere {
    BRLCAD::Sphere* object;
    bool            own;
};


static BRLCAD::Sphere& GetSphere
(
    lua_State* luaState,
    int        narg
) {
    BRLCAD::Sphere* object = TestSphere(luaState, narg);
    assert(object != 0);

    return *object;
}


int CreateSphere
(
    lua_State* luaState
) {
    BRLCAD::Sphere* ret = 0;

    if (lua_gettop(luaState) > 0) {
        BRLCAD::Sphere* original = TestSphere(luaState, 1);

        if (original != 0)
            ret = new BRLCAD::Sphere(*original);
        else {
            BRLCAD::Vector3D center = GetVector3D(luaState, 1);
            double           radius = luaL_checknumber(luaState, 2);

            ret = new BRLCAD::Sphere(center, radius);
        }
    }

    if (ret == 0)
        ret = new BRLCAD::Sphere();

    return PushSphere(luaState, ret, true);
}


static int Destruct
(
    lua_State* luaState
) {
    ScriptSphere* scriptObject = static_cast<ScriptSphere*>(luaL_testudata(luaState, 1, "BRLCAD.Sphere"));

    if ((scriptObject != 0) && (scriptObject->object != 0) && scriptObject->own)
        scriptObject->object->Destroy();

    return 0;
}


static int Center
(
    lua_State* luaState
) {
    BRLCAD::Sphere& object = GetSphere(luaState, 1);

    PushVector3D(luaState, object.Center());

    return 1;
}


static int SetCenter
(
    lua_State* luaState
) {
    BRLCAD::Sphere&  object = GetSphere(luaState, 1);
    BRLCAD::Vector3D center = GetVector3D(luaState, 2);

    object.SetCenter(center);

    return 0;
}


static int Radius
(
    lua_State* luaState
) {
    BRLCAD::Sphere& object = GetSphere(luaState, 1);

    lua_pushnumber(luaState, object.Radius());

    return 1;
}


static int SetRadius
(
    lua_State* luaState
) {
    BRLCAD::Sphere& object   = GetSphere(luaState, 1);
    double          distance = luaL_checknumber(luaState, 2);

    object.SetRadius(distance);

    return 0;
}


static int Set
(
    lua_State* luaState
) {
    BRLCAD::Sphere&  object = GetSphere(luaState, 1);
    BRLCAD::Vector3D center = GetVector3D(luaState, 2);
    double           radius = luaL_checknumber(luaState, 3);

    object.Set(center, radius);

    return 0;
}


static int ClassName
(
    lua_State* luaState
) {
    lua_pushstring(luaState, BRLCAD::Sphere::ClassName());

    return 1;
}


static BRLCAD::Object& GetObject
(
    lua_State* luaState,
    int        narg
) {
    return GetSphere(luaState, narg);
}


static void GetSphereMetatable
(
     lua_State* luaState
) {
    lua_getfield(luaState, LUA_REGISTRYINDEX, "BRLCAD.Sphere");

    if (!lua_istable(luaState, -1)) {
        lua_pop(luaState, 1);
        luaL_newmetatable(luaState, "BRLCAD.Sphere");

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

        lua_pushstring(luaState, "Radius");
        lua_pushcfunction(luaState, &Radius);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetRadius");
        lua_pushcfunction(luaState, &SetRadius);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Set");
        lua_pushcfunction(luaState, &Set);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Clone");
        lua_pushcfunction(luaState, &CreateSphere);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "ClassName");
        lua_pushcfunction(luaState, &ClassName);
        lua_settable(luaState, -3);
    }
}


int PushSphere
(
    lua_State*      luaState,
    BRLCAD::Sphere* object,
    bool            takeOwnership
) {
    int ret = 0;

    if (object != 0) {
        ScriptSphere* scriptObject = static_cast<ScriptSphere*>(lua_newuserdata(luaState, sizeof(ScriptSphere)));

        scriptObject->object = object;
        scriptObject->own    = takeOwnership;

        GetSphereMetatable(luaState);
        lua_setmetatable(luaState, -2);

        ret = 1;
    }

    return ret;
}


BRLCAD::Sphere* TestSphere
(
    lua_State* luaState,
    int        narg
) {
    BRLCAD::Sphere* ret          = 0;
    ScriptSphere*   scriptObject = static_cast<ScriptSphere*>(luaL_testudata(luaState, narg, "BRLCAD.Sphere"));

    if (scriptObject != 0)
        ret = scriptObject->object;

    return ret;
}
