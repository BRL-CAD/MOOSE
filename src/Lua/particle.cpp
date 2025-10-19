/*                         P A R T I C L E . C P P
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
/** @file particle.cpp
 *
 *  BRL-CAD Lua scripting:
 *      BRLCAD::Particle functions
 */

#include <cassert>

#include "objectbase.h"
#include "vector3d.h"
#include "particle.h"


struct ScriptParticle {
    BRLCAD::Particle* object;
    bool              own;
};


static BRLCAD::Particle& GetParticle
(
    lua_State* luaState,
    int        narg
) {
    BRLCAD::Particle* object = TestParticle(luaState, narg);
    assert(object != nullptr);

    return *object;
}


int CreateParticle
(
    lua_State* luaState
) {
    BRLCAD::Particle* ret = nullptr;

    if (lua_gettop(luaState) > 0) {
        BRLCAD::Particle* original = TestParticle(luaState, 1);

        if (original != nullptr)
            ret = new BRLCAD::Particle(*original);
        else {
            BRLCAD::Vector3D basePoint  = GetVector3D(luaState, 1);
            BRLCAD::Vector3D height     = GetVector3D(luaState, 2);
            double           baseRadius = luaL_checknumber(luaState, 3);
            double           topRadius  = luaL_checknumber(luaState, 4);

            ret = new BRLCAD::Particle(basePoint, height, baseRadius, topRadius);
        }
    }

    if (ret == nullptr)
        ret = new BRLCAD::Particle();

    return PushParticle(luaState, ret, true);
}


static int Destruct
(
    lua_State* luaState
) {
    ScriptParticle* scriptObject = static_cast<ScriptParticle*>(luaL_testudata(luaState, 1, "BRLCAD.Particle"));

    if ((scriptObject != nullptr) && (scriptObject->object != nullptr) && scriptObject->own)
        scriptObject->object->Destroy();

    return 0;
}


static int BasePoint
(
    lua_State* luaState
) {
    BRLCAD::Particle& object = GetParticle(luaState, 1);

    PushVector3D(luaState, object.BasePoint());

    return 1;
}


static int SetBasePoint
(
    lua_State* luaState
) {
    BRLCAD::Particle& object    = GetParticle(luaState, 1);
    BRLCAD::Vector3D  basePoint = GetVector3D(luaState, 2);

    object.SetBasePoint(basePoint);

    return 0;
}


static int Height
(
    lua_State* luaState
) {
    BRLCAD::Particle& object = GetParticle(luaState, 1);

    PushVector3D(luaState, object.Height());

    return 1;
}


static int SetHeight
(
    lua_State* luaState
) {
    BRLCAD::Particle& object = GetParticle(luaState, 1);
    BRLCAD::Vector3D  height = GetVector3D(luaState, 2);

    object.SetHeight(height);

    return 0;
}


static int BaseRadius
(
    lua_State* luaState
) {
    BRLCAD::Particle& object = GetParticle(luaState, 1);

    lua_pushnumber(luaState, object.BaseRadius());

    return 1;
}


static int SetBaseRadius
(
    lua_State* luaState
) {
    BRLCAD::Particle& object     = GetParticle(luaState, 1);
    double            baseRadius = luaL_checknumber(luaState, 2);

    object.SetBaseRadius(baseRadius);

    return 0;
}


static int TopRadius
(
    lua_State* luaState
) {
    BRLCAD::Particle& object = GetParticle(luaState, 1);

    lua_pushnumber(luaState, object.TopRadius());

    return 1;
}


static int SetTopRadius
(
    lua_State* luaState
) {
    BRLCAD::Particle& object    = GetParticle(luaState, 1);
    double            topRadius = luaL_checknumber(luaState, 2);

    object.SetTopRadius(topRadius);

    return 0;
}


static int Set
(
    lua_State* luaState
) {
    BRLCAD::Particle& object     = GetParticle(luaState, 1);
    BRLCAD::Vector3D  basePoint  = GetVector3D(luaState, 2);
    BRLCAD::Vector3D  height     = GetVector3D(luaState, 3);
    double            baseRadius = luaL_checknumber(luaState, 4);
    double            topRadius  = luaL_checknumber(luaState, 5);

    object.Set(basePoint, height, baseRadius, topRadius);

    return 0;
}


static int ClassName
(
    lua_State* luaState
) {
    lua_pushstring(luaState, BRLCAD::Particle::ClassName());

    return 1;
}


static BRLCAD::Object& GetObject
(
    lua_State* luaState,
    int        narg
) {
    return GetParticle(luaState, narg);
}


static void GetParticleMetatable
(
     lua_State* luaState
) {
    lua_getfield(luaState, LUA_REGISTRYINDEX, "BRLCAD.Particle");

    if (!lua_istable(luaState, -1)) {
        lua_pop(luaState, 1);
        luaL_newmetatable(luaState, "BRLCAD.Particle");

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

        lua_pushstring(luaState, "BaseRadius");
        lua_pushcfunction(luaState, &SetBaseRadius);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "TopRadius");
        lua_pushcfunction(luaState, &TopRadius);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetTopRadius");
        lua_pushcfunction(luaState, &SetTopRadius);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Set");
        lua_pushcfunction(luaState, &Set);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Clone");
        lua_pushcfunction(luaState, &CreateParticle);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "ClassName");
        lua_pushcfunction(luaState, &ClassName);
        lua_settable(luaState, -3);
    }
}


int PushParticle
(
    lua_State*        luaState,
    BRLCAD::Particle* object,
    bool              takeOwnership
) {
    int ret = 0;

    if (object != nullptr) {
        ScriptParticle* scriptObject = static_cast<ScriptParticle*>(lua_newuserdata(luaState, sizeof(ScriptParticle)));

        scriptObject->object = object;
        scriptObject->own    = takeOwnership;

        GetParticleMetatable(luaState);
        lua_setmetatable(luaState, -2);

        ret = 1;
    }

    return ret;
}


BRLCAD::Particle* TestParticle
(
    lua_State* luaState,
    int        narg
) {
    BRLCAD::Particle* ret          = nullptr;
    ScriptParticle*   scriptObject = static_cast<ScriptParticle*>(luaL_testudata(luaState, narg, "BRLCAD.Particle"));

    if (scriptObject != nullptr)
        ret = scriptObject->object;

    return ret;
}
