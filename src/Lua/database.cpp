/*                         D A T A B A S E . C P P
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
 *      BRLCAD::Database functions
 */

#include <cassert>

#include "brlcad/Database/MemoryDatabase.h"

#include "database.h"


static BRLCAD::MemoryDatabase* TestDatabase
(
    lua_State* luaState,
    int        narg
) {
    BRLCAD::MemoryDatabase*  ret      = 0;
    BRLCAD::MemoryDatabase** database = static_cast<BRLCAD::MemoryDatabase**>(luaL_testudata(luaState, narg, "BRLCAD.Database"));

    if (database != 0)
        ret = *database;

    return ret;
}


static BRLCAD::MemoryDatabase& GetDatabase
(
    lua_State* luaState
) {
    BRLCAD::MemoryDatabase* object = TestDatabase(luaState, 1);
    assert(object != 0);

    return *object;
}


static int Destruct
(
    lua_State* luaState
) {
    BRLCAD::MemoryDatabase** database = static_cast<BRLCAD::MemoryDatabase**>(luaL_testudata(luaState, 1, "BRLCAD.Database"));

    if ((database != 0) && (*database != 0)) {
        delete *database;
        *database = 0;
    }

    return 0;
}


static int Load
(
    lua_State* luaState
) {
    BRLCAD::MemoryDatabase& database = GetDatabase(luaState);
    const char*             fileName = luaL_checkstring(luaState, 2);

    lua_pushboolean(luaState, database.Load(fileName));

    return 1;
}


static int Save
(
    lua_State* luaState
) {
    BRLCAD::MemoryDatabase& database = GetDatabase(luaState);
    const char*             fileName = luaL_checkstring(luaState, 2);

    lua_pushboolean(luaState, database.Save(fileName));

    return 1;
}


static int Title
(
    lua_State* luaState
) {
    BRLCAD::MemoryDatabase& database = GetDatabase(luaState);

    lua_pushstring(luaState, database.Title());

    return 1;
}


static int SetTitle
(
    lua_State* luaState
) {
    BRLCAD::MemoryDatabase& database = GetDatabase(luaState);
    const char*             title    = luaL_checkstring(luaState, 2);

    database.SetTitle(title);

    return 0;
}


static int Select
(
    lua_State* luaState
) {
    BRLCAD::MemoryDatabase& database   = GetDatabase(luaState);
    const char*             objectName = luaL_checkstring(luaState, 2);

    database.Select(objectName);

    return 0;
}


static int UnSelectAll
(
    lua_State* luaState
) {
    BRLCAD::MemoryDatabase& database = GetDatabase(luaState);

    database.UnSelectAll();

    return 0;
}


static int BoundingBoxMinima
(
    lua_State* luaState
) {
    BRLCAD::MemoryDatabase& database          = GetDatabase(luaState);
    BRLCAD::Vector3D        boundingBoxMinima = database.BoundingBoxMinima();

    lua_pushnumber(luaState, boundingBoxMinima.coordinates[0]);
    lua_pushnumber(luaState, boundingBoxMinima.coordinates[1]);
    lua_pushnumber(luaState, boundingBoxMinima.coordinates[2]);

    return 3;
}


static int BoundingBoxMaxima
(
    lua_State* luaState
) {
    BRLCAD::MemoryDatabase& database  = GetDatabase(luaState);
    BRLCAD::Vector3D        boundingBoxMaxima = database.BoundingBoxMaxima();

    lua_pushnumber(luaState, boundingBoxMaxima.coordinates[0]);
    lua_pushnumber(luaState, boundingBoxMaxima.coordinates[1]);
    lua_pushnumber(luaState, boundingBoxMaxima.coordinates[2]);

    return 3;
}


static void GetDatabaseMetatable
(
     lua_State* luaState
) {
    lua_getfield(luaState, LUA_REGISTRYINDEX, "BRLCAD.Database");

    if (!lua_istable(luaState, -1)) {
        lua_pop(luaState, 1);
        luaL_newmetatable(luaState, "BRLCAD.Database");

        lua_pushvalue(luaState, -1);
        lua_setfield(luaState, -2, "__index");

        lua_pushstring(luaState, "__gc");
        lua_pushcfunction(luaState, &Destruct);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Load");
        lua_pushcfunction(luaState, Load);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Save");
        lua_pushcfunction(luaState, Save);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Title");
        lua_pushcfunction(luaState, Title);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "SetTitle");
        lua_pushcfunction(luaState, SetTitle);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "Select");
        lua_pushcfunction(luaState, Select);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "UnSelectAll");
        lua_pushcfunction(luaState, UnSelectAll);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "BoundingBoxMinima");
        lua_pushcfunction(luaState, BoundingBoxMinima);
        lua_settable(luaState, -3);

        lua_pushstring(luaState, "BoundingBoxMaxima");
        lua_pushcfunction(luaState, BoundingBoxMaxima);
        lua_settable(luaState, -3);
    }
}


int CreateDatabase
(
    lua_State* luaState
) {
    int                     ret      = 0;
    BRLCAD::MemoryDatabase* database = new BRLCAD::MemoryDatabase();


    if (database != 0) {
        BRLCAD::MemoryDatabase** scriptDatabase = static_cast<BRLCAD::MemoryDatabase**>(lua_newuserdata(luaState, sizeof(BRLCAD::MemoryDatabase*)));

        *scriptDatabase = database;

        GetDatabaseMetatable(luaState);
        lua_setmetatable(luaState, -2);

        ret = 1;
    }

    return ret;
}
