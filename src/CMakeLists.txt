#########################################################################
#
#	BRL-CAD
#
#	Copyright (c) 2011-2020 United States Government as represented by
#	the U.S. Army Research Laboratory.
#
#	This library is free software; you can redistribute it and/or
#	modify it under the terms of the GNU Lesser General Public License
#	version 2.1 as published by the Free Software Foundation.
#
#	This library is distributed in the hope that it will be useful, but
#	WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#	Lesser General Public License for more details.
#
#	You should have received a copy of the GNU Lesser General Public
#	License along with this file; see the file named COPYING for more
#	information.
#
#########################################################################
#	@file src/CMakeLists.txt
#########################################################################


INCLUDE_DIRECTORIES(
        ${MOOSE_SOURCE_DIR}/include
        ${MOOSE_BINARY_DIR}/include
        ${BRLCAD_INCLUDE_DIRS}
)

# Module: Database
SET(DatabaseSources "")
ADD_SUBDIRECTORY(Database)
GET_DIRECTORY_PROPERTY(DatabaseSources DIRECTORY Database DEFINITION DatabaseSources)

# Module: Lua
SET(LuaSources "")
SET(LuaHeaders "")
OPTION(MODULE_LUA "Build the Lua module" ON)
if(MODULE_LUA)
    FIND_PACKAGE(Lua REQUIRED)
    INCLUDE_DIRECTORIES(${LUA_INCLUDE_DIR})
    ADD_SUBDIRECTORY(Lua)
    GET_DIRECTORY_PROPERTY(LuaSources DIRECTORY Lua DEFINITION LuaSources)
ENDIF(MODULE_LUA)

SET(MooseSources
    ${DatabaseSources}
    ${LuaSources}
    globals.cpp
    init.cpp
    VectorList.cpp
)

SET(MooseHeaders
    ${MOOSE_SOURCE_DIR}/include/brlcad/globals.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/memory.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/vector.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/VectorList.h
    ${MOOSE_BINARY_DIR}/include/brlcad/version.h
)

IF(MSVC)
    add_definitions(-DBRLCAD_MOOSE_EXPORT=__declspec(dllexport))
    add_definitions(-DBU_DLL_IMPORTS -DRT_DLL_IMPORTS -DWDB_DLL_IMPORTS)
ELSE(MSVC)
    add_definitions(-DBRLCAD_MOOSE_EXPORT=)
ENDIF(MSVC)

ADD_LIBRARY(brlcad SHARED ${MooseSources})
TARGET_LINK_LIBRARIES(brlcad
    ${BRLCAD_RT_STATIC_LIBRARY}
    ${BRLCAD_NMG_STATIC_LIBRARY}
    ${BRLCAD_WDB_STATIC_LIBRARY}
    ${BRLCAD_BN_STATIC_LIBRARY}
    ${BRLCAD_BU_STATIC_LIBRARY}
    ${BRLCAD_BREP_STATIC_LIBRARY}
    ${BRLCAD_BG_STATIC_LIBRARY}
    ${BRLCAD_GDIAM_STATIC_LIBRARY}
    ${BRLCAD_LZ4_STATIC_LIBRARY}
    ${BRLCAD_OPENNURBS_STATIC_LIBRARY}
    ${BRLCAD_POLY2TRI_STATIC_LIBRARY}
    ${BRLCAD_VDS_STATIC_LIBRARY}
    pthread
    uuid
    z
    ${LUA_LIBRARIES}
)

INSTALL(TARGETS brlcad DESTINATION lib)
INSTALL(FILES ${MooseHeaders} DESTINATION include/brlcad)
