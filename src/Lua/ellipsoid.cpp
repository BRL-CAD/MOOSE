/*                         E L L I P S O I D . C P P
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
/** @file ellipsoid.cpp
 *
 *  BRL-CAD Lua scripting:
 *      BRLCAD::Ellipsoid functions
 */

#include <cassert>

#include "objectbase.h"
#include "vector3d.h"
#include "ellipsoid.h"


struct ScriptEllipsoid {
    BRLCAD::Ellipsoid* object;
    bool          own;
};


static BRLCAD::Ellipsoid& GetEllipsoid
(
    lua_State* luaState,
    int        narg
) {
    BRLCAD::Ellipsoid* object = TestEllipsoid(luaState, narg);
    assert(object != nullptr);

    return *object;
}


int CreateEllipsoid
(
    lua_State* luaState
) {
    BRLCAD::Ellipsoid* ret = nullptr;

    if (lua_gettop(luaState) > 0) {
        BRLCAD::Ellipsoid* original = TestEllipsoid(luaState, 1);

        if (original != nullptr) {
            ret = new BRLCAD::Ellipsoid(*original);
        }
        else if (lua_gettop(luaState) == 4) {
            BRLCAD::Vector3D center             = GetVector3D(luaState, 1);
            BRLCAD::Vector3D semiPrincipalAxisA = GetVector3D(luaState, 2);
            BRLCAD::Vector3D semiPrincipalAxisB = GetVector3D(luaState, 3);
            BRLCAD::Vector3D semiPrincipalAxisC = GetVector3D(luaState, 4);

            ret = new BRLCAD::Ellipsoid(center, semiPrincipalAxisA, semiPrincipalAxisB, semiPrincipalAxisC);
        }
        else if (lua_gettop(luaState) == 3) {
            BRLCAD::Vector3D center            = GetVector3D(luaState, 1);
            BRLCAD::Vector3D semiPrincipalAxis = GetVector3D(luaState, 2);
            double           radius            = luaL_checknumber(luaState, 3);

            ret = new BRLCAD::Ellipsoid(center, semiPrincipalAxis, radius);
        }
        else {
            BRLCAD::Vector3D center = GetVector3D(luaState, 1);
            double           radius = luaL_checknumber(luaState, 2);

            ret = new BRLCAD::Ellipsoid(center, radius);
        }
    }

    if (ret == nullptr)
        ret = new BRLCAD::Ellipsoid();

    return PushEllipsoid(luaState, ret, true);
}


static int Destruct
(
    lua_State* luaState
) {
    ScriptEllipsoid* scriptObject = static_cast<ScriptEllipsoid*>(luaL_testudata(luaState, 1, "BRLCAD.Ellipsoid"));

    if ((scriptObject != nullptr) && (scriptObject->object != nullptr) && scriptObject->own)
        scriptObject->object->Destroy();

    return 0;
}


static int Center
(
    lua_State* luaState
) {
    BRLCAD::Ellipsoid& object = GetEllipsoid(luaState, 1);

    PushVector3D(luaState, object.Center());

    return 1;
}


static int SetCenter
(
    lua_State* luaState
) {
    BRLCAD::Ellipsoid& object = GetEllipsoid(luaState, 1);
    BRLCAD::Vector3D   center = GetVector3D(luaState, 2);

    object.SetCenter(center);

    return 0;
}


static int SemiPrincipalAxis
(
    lua_State* luaState
) {
    BRLCAD::Ellipsoid& object = GetEllipsoid(luaState, 1);
    size_t             index  = luaL_checknumber(luaState, 2);

    PushVector3D(luaState, object.SemiPrincipalAxis(index));

    return 1;
}


static int SetSemiPrincipalAxis
(
    lua_State* luaState
) {
    BRLCAD::Ellipsoid& object            = GetEllipsoid(luaState, 1);
    size_t             index             = luaL_checknumber(luaState, 2);
    BRLCAD::Vector3D   semiPrincipalAxis = GetVector3D(luaState, 3);

    object.SetSemiPrincipalAxis(index, semiPrincipalAxis);

    return 0;
}


static int Set
(
    lua_State* luaState
) {
    BRLCAD::Ellipsoid& object = GetEllipsoid(luaState, 1);
    BRLCAD::Vector3D   center = GetVector3D(luaState, 2);

    if (lua_gettop(luaState) == 5) {
        BRLCAD::Vector3D semiPrincipalAxisA = GetVector3D(luaState, 3);
        BRLCAD::Vector3D semiPrincipalAxisB = GetVector3D(luaState, 4);
        BRLCAD::Vector3D semiPrincipalAxisC = GetVector3D(luaState, 5);

        object.Set(center, semiPrincipalAxisA, semiPrincipalAxisB, semiPrincipalAxisC);
    }
    else {
        BRLCAD::Vector3D semiPrincipalAxis = GetVector3D(luaState, 3);
        double           radius            = luaL_checknumber(luaState, 4);

        object.Set(center, semiPrincipalAxis, radius);
    }

    return 0;
}


static int SetFocals
(
    lua_State* luaState
) {
    BRLCAD::Ellipsoid& object          = GetEllipsoid(luaState, 1);
    BRLCAD::Vector3D   focalA          = GetVector3D(luaState, 2);
    BRLCAD::Vector3D   focalB          = GetVector3D(luaState, 3);
    size_t             majorAxisLength = luaL_checknumber(luaState, 4);

    object.SetFocals(focalA, focalB, majorAxisLength);

    return 0;
}


static int SetSphere
(
    lua_State* luaState
) {
    BRLCAD::Ellipsoid& object = GetEllipsoid(luaState, 1);
    BRLCAD::Vector3D   center = GetVector3D(luaState, 2);
    double             radius = luaL_checknumber(luaState, 3);

    object.SetSphere(center, radius);

    return 0;
}


static int ClassName
(
    lua_State* luaState
) {
    lua_pushstring(luaState, BRLCAD::Ellipsoid::ClassName());

    return 1;
}


static BRLCAD::Object& GetObject
(
    lua_State* luaState,
    int        narg
) {
    return GetEllipsoid(luaState, narg);
}


static void GetEllipsoidMetatable
(
    lua_State* luaState
) {
    lua_getfield(luaState, LUA_REGISTRYINDEX, "BRLCAD.Ellipsoid");

    if (!lua_istable(luaState, -1)) {
        lua_pop(luaState, 1);
        luaL_newmetatable(luaState, "BRLCAD.Ellipsoid");

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

        lua_pushstring(luaState, "SemiPrincipalAxis");
        lua_pushcfunction(luaState, &SemiPrincipalAxis);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetSemiPrincipalAxis");
        lua_pushcfunction(luaState, &SetSemiPrincipalAxis);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Set");
        lua_pushcfunction(luaState, &Set);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Set");
        lua_pushcfunction(luaState, &Set);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetFocals");
        lua_pushcfunction(luaState, &SetFocals);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetSphere");
        lua_pushcfunction(luaState, &SetSphere);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Clone");
        lua_pushcfunction(luaState, &CreateEllipsoid);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "ClassName");
        lua_pushcfunction(luaState, &ClassName);
        lua_settable(luaState, -3);
    }
}


int PushEllipsoid
(
    lua_State*         luaState,
    BRLCAD::Ellipsoid* object,
    bool               takeOwnership
) {
    int ret = 0;

    if (object != nullptr) {
        ScriptEllipsoid* scriptObject = static_cast<ScriptEllipsoid*>(lua_newuserdata(luaState, sizeof(ScriptEllipsoid)));

        scriptObject->object = object;
        scriptObject->own    = takeOwnership;

        GetEllipsoidMetatable(luaState);
        lua_setmetatable(luaState, -2);

        ret = 1;
    }

    return ret;
}


BRLCAD::Ellipsoid* TestEllipsoid
(
    lua_State* luaState,
    int        narg
) {
    BRLCAD::Ellipsoid* ret          = nullptr;
    ScriptEllipsoid*   scriptObject = static_cast<ScriptEllipsoid*>(luaL_testudata(luaState, narg, "BRLCAD.Ellipsoid"));

    if (scriptObject != nullptr)
        ret = scriptObject->object;

    return ret;
}
