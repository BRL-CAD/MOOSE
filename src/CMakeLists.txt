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
        ${ZLIB_INCLUDE_DIRS}
)

# Module: Database
SET(DatabaseSources "")
ADD_SUBDIRECTORY(Database)
GET_DIRECTORY_PROPERTY(DatabaseSources DIRECTORY Database DEFINITION DatabaseSources)

FIND_PACKAGE(Threads)

# Module: Command string
SET(CommandStringSources "")
OPTION(MODULE_COMMANDSTRING "Build the command string module" OFF)
if(MODULE_COMMANDSTRING)
    ADD_SUBDIRECTORY(CommandString)
    GET_DIRECTORY_PROPERTY(CommandStringSources DIRECTORY CommandString DEFINITION CommandStringSources)
    SET(COMMANDSTRING_LIBRARIES
        ${BRLCAD_GED_STATIC_LIBRARY}
        ${BRLCAD_ANALYZE_STATIC_LIBRARY}
        ${BRLCAD_BG_STATIC_LIBRARY}
        ${BRLCAD_BV_STATIC_LIBRARY}
    )
ENDIF(MODULE_COMMANDSTRING)

# Module: Lua
SET(LuaSources "")
OPTION(MODULE_LUA "Build the Lua module" OFF)
if(MODULE_LUA)
    FIND_PACKAGE(Lua REQUIRED)
    INCLUDE_DIRECTORIES(${LUA_INCLUDE_DIR})
    ADD_SUBDIRECTORY(Lua)
    GET_DIRECTORY_PROPERTY(LuaSources DIRECTORY Lua DEFINITION LuaSources)
ENDIF(MODULE_LUA)

SET(MooseSources
    ${DatabaseSources}
    ${CommandStringSources}
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
    add_definitions("-DBRLCAD_MOOSE_EXPORT=__declspec(dllexport)")
    set(MSVC_LIBRARIES
        Ws2_32
        Psapi
        Rpcrt4
    )
ELSE(MSVC)
    add_definitions("-DBRLCAD_MOOSE_EXPORT=")
ENDIF(MSVC)

# uuid library
find_package(UUID REQUIRED)

link_directories(${BRLCAD_LIB_DIR})

ADD_LIBRARY(brlcad SHARED ${MooseSources})
TARGET_LINK_LIBRARIES(brlcad
    ${COMMANDSTRING_LIBRARIES}
    ${BRLCAD_RT_STATIC_LIBRARY}
    ${BRLCAD_NMG_STATIC_LIBRARY}
    ${BRLCAD_WDB_STATIC_LIBRARY}
    ${BRLCAD_BN_STATIC_LIBRARY}
    ${BRLCAD_BU_STATIC_LIBRARY}
    ${BRLCAD_BREP_STATIC_LIBRARY}
    ${BRLCAD_BG_STATIC_LIBRARY}
    ${BRLCAD_BV_STATIC_LIBRARY}
    ${BRLCAD_GDIAM_STATIC_LIBRARY}
    ${BRLCAD_OPENNURBS_STATIC_LIBRARY}
    ${BRLCAD_POLY2TRI_STATIC_LIBRARY}
    ${BRLCAD_VDS_STATIC_LIBRARY}
    ${REGEX_STATIC_LIBRARIES}
    ${ZLIB_STATIC_LIBRARIES}
    ${MSVC_LIBRARIES}
    ${UUID_LIBRARY}
    ${LUA_LIBRARIES}
    regex_brl
    z_brl
    ${CMAKE_DL_LIBS}
    Threads::Threads
)

INSTALL(TARGETS brlcad DESTINATION lib)
INSTALL(FILES ${MooseHeaders} DESTINATION include/brlcad)
