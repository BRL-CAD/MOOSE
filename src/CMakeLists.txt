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

ADD_SUBDIRECTORY(Database)

SET(MooseSources
    globals.cpp
)

SET(MooseHeaders
    ${MOOSE_SOURCE_DIR}/include/brlcad/globals.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/memory.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/vector.h
    ${MOOSE_BINARY_DIR}/include/brlcad/version.h
)

IF(MSVC)
    add_definitions(-DBRLCAD_MOOSE_EXPORT=__declspec(dllexport))
    add_definitions(-DBU_DLL_IMPORTS -DRT_DLL_IMPORTS -DWDB_DLL_IMPORTS)
ELSE(MSVC)
    add_definitions(-DBRLCAD_MOOSE_EXPORT=)
ENDIF(MSVC)

ADD_LIBRARY(brlcad SHARED ${MooseSources})
TARGET_LINK_LIBRARIES(brlcad ${BRLCAD_NMG_LIBRARY} ${BRLCAD_WDB_LIBRARY} ${BRLCAD_RT_LIBRARY} ${BRLCAD_BN_LIBRARY} ${BRLCAD_BU_LIBRARY})

INSTALL(TARGETS brlcad DESTINATION lib)
INSTALL(FILES ${MooseHeaders} DESTINATION include/brlcad)
