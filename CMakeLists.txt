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
#	@file CMakeLists.txt
#########################################################################

CMAKE_MINIMUM_REQUIRED(VERSION 3.1.3)

PROJECT(MOOSE)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
SET(CMAKE_CXX_STANDARD 11)

# We need BRL-CAD
FIND_PACKAGE(BRLCAD REQUIRED)

IF(BRLCAD_VERSION_FOUND)
    SET(VERSION_H_CONTENT
        "#define BRLCAD_LIB_MAJOR ${BRLCAD_MAJOR_VERSION}\n"
        "#define BRLCAD_LIB_MINOR ${BRLCAD_MINOR_VERSION}\n"
        "#define BRLCAD_LIB_PATCH ${BRLCAD_PATCH_VERSION}\n"
    )
    FILE(WRITE ${CMAKE_BINARY_DIR}/include/brlcad/version.h ${VERSION_H_CONTENT})

    ADD_SUBDIRECTORY(src)
ELSE(BRLCAD_VERSION_FOUND)
    MESSAGE(FATAL_ERROR "\tCould not find BRL-CAD")
ENDIF(BRLCAD_VERSION_FOUND)
