#########################################################################
#
#	BRL-CAD
#
#	Copyright (c) 2026 United States Government as represented by
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
#	@file src/C/CMakeLists.txt
#########################################################################


SET(CSources
    C/arb8.cpp
    C/casts.cpp
    C/constDatabase.cpp
    C/Database.cpp
    C/fileDatabase.cpp
    C/globals.cpp
    C/handle.cpp
    C/memoryDatabase.cpp
    C/Object.cpp
)

SET(CHeaders
    ${MOOSE_SOURCE_DIR}/include/brlcad/C/arb8.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/C/constDatabase.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/C/Database.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/C/fileDatabase.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/C/globals.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/C/handle.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/C/memoryDatabase.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/C/Object.h
)

INSTALL(FILES ${CHeaders} DESTINATION include/brlcad/C)
