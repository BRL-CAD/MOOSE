#########################################################################
#
#	BRL-CAD
#
#	Copyright (c) 2011-2026 United States Government as represented by
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

CMAKE_MINIMUM_REQUIRED(VERSION 3.18)

PROJECT(MOOSE)

ENABLE_TESTING()

SET(CMAKE_CXX_STANDARD 11)

# Determine the options first
OPTION(BRLCAD_USE_STATIC_LIBS "Link the BRL-CAD core libraries statically" ON)
OPTION(MODULE_COMMANDSTRING "Build the command string module" OFF)
OPTION(MODULE_C "Build the simplified C module" OFF)
OPTION(MODULE_LUA "Build the Lua module" OFF)

# We need BRL-CAD
IF(BRLCAD_USE_STATIC_LIBS)
    SET(OPENSSL_USE_STATIC_LIBS ON)
ELSE(BRLCAD_USE_STATIC_LIBS)
    UNSET(OPENSSL_USE_STATIC_LIBS)
ENDIF(BRLCAD_USE_STATIC_LIBS)

IF(MODULE_COMMANDSTRING)
    FIND_PACKAGE(OpenSSL COMPONENTS SSL Crypto)
ENDIF(MODULE_COMMANDSTRING)

FIND_PACKAGE(BRLCAD CONFIG REQUIRED)

SET(VERSION_H_CONTENT
    "#define BRLCAD_LIB_MAJOR ${BRLCAD_VERSION_MAJOR}\n"
    "#define BRLCAD_LIB_MINOR ${BRLCAD_VERSION_MINOR}\n"
    "#define BRLCAD_LIB_PATCH ${BRLCAD_VERSION_PATCH}\n"
)
FILE(WRITE ${CMAKE_BINARY_DIR}/include/brlcad/version.h ${VERSION_H_CONTENT})

ADD_SUBDIRECTORY(src)
