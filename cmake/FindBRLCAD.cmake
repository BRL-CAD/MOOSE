#########################################################################
#
#    BRL-CAD
#
#    Copyright (c) 1997-2020 United States Government as represented by
#    the U.S. Army Research Laboratory.
#
#    This library is free software; you can redistribute it and/or
#    modify it under the terms of the GNU Lesser General Public License
#    version 2.1 as published by the Free Software Foundation.
#
#    This library is distributed in the hope that it will be useful, but
#    WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#    Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public
#    License along with this file; see the file named COPYING for more
#    information.
#
#########################################################################
#  @file cmake/FindBRLCAD.cmake
#
#  Try to find brlcad libraries.
#  Once done, this will define:
#
#     BRLCAD_FOUND - system has BRL-CAD
#     BRLCAD_VERSION - the BRL-CAD version string
#     BRLCAD_INCLUDE_DIRS - the BRL-CAD include directories
#     BRLCAD_LIBRARIES - link these to use the BRL-CAD Libraries
#
#     BRLCAD_ANALYZE_LIBRARY - BRL-CAD Analysis library
#     BRLCAD_BG_LIBRARY - BRL-CAD Basic Geometry library
#     BRLCAD_BV_LIBRARY - BRL-CAD Basic View library
#     BRLCAD_BN_LIBRARY - BRL-CAD Basic Numerical library
#     BRLCAD_BU_LIBRARY - BRL-CAD Basic Utility library
#     BRLCAD_CURSOR_LIBRARY - libcursor
#     BRLCAD_DM_LIBRARY - BRL-CAD Display Manager library
#     BRLCAD_FFT_LIBRARY - BRL-CAD FFT library
#     BRLCAD_GCV_LIBRARY - BRL-CAD Geometry Conversion library
#     BRLCAD_GED_LIBRARY - BRL-CAD Geometry Editing library
#     BRLCAD_ICV_LIBRARY - BRL-CAD Image Conversion library
#     BRLCAD_NMG_LIBRARY - BRL-CAD non-manifold geometry library
#     BRLCAD_OPTICAL_LIBRARY - BRL-CAD optical library
#     BRLCAD_PKG_LIBRARY - BRL-CAD libpkg
#     BRLCAD_RENDER_LIBRARY - librender
#     BRLCAD_RT_LIBRARY - BRL-CAD Raytracing library
#     BRLCAD_WDB_LIBRARY - BRL-CAD Write Database library
#
#  Technically these are external but we need the versions
#  tweaked for BRL-CAD.  If a developer wishes to use the
#  BRL-CAD altered versions of these libraries to satisfy a
#  "generic" request for the library, they'll need to assign
#  the results of these variables to the non-BRL-CAD specific 
#  variables they are using
#
#     BRLCAD_EXPPP_LIBRARY - SCL libexppp library
#     BRLCAD_EXPRESS_LIBRARY - SCL libexpress library
#     BRLCAD_STEPCORE_LIBRARY - SCL core library
#     BRLCAD_STEPDAI_LIBRARY - SCL dai library
#     BRLCAD_STEPEDITOR_LIBRARY - SCL editor library
#     BRLCAD_STEPUTILS_LIBRARY - SCL utils library
#     BRLCAD_OPENNURBS_LIBRARY - openNURBS library
#
#  In addition to the above variables, which are essentially unique
#  to BRL-CAD, this routine will look for local copies of libraries
#  installed with BRL-CAD and return their results as would a 
#  standard find_package for that library (if one exists).  The 
#  distinction between these libraries and those above is that these
#  libraries do not have known modifications required by BRL-CAD that
#  preclude system libraries from substituting for them, although
#  if BRL-CAD was compiled against local versions of these it is
#  not guaranteed (or in some cases expected) that a found system
#  version will successfully replace the local copy.
#
#     libregex
#     zlib
# 
#########################################################################

SET(BRLCAD_ROOT "$ENV{BRLCAD_ROOT}")
IF(BRLCAD_BASE_DIR AND BRLCAD_ROOT)
    MESSAGE("Warning - BRLCAD_ROOT was found but is overridden by BRLCAD_BASE_DIR")
ELSE(BRLCAD_BASE_DIR AND BRLCAD_ROOT)
    IF(BRLCAD_ROOT)
        SET(BRLCAD_BASE_DIR ${BRLCAD_ROOT})
    ENDIF(BRLCAD_ROOT)
ENDIF(BRLCAD_BASE_DIR AND BRLCAD_ROOT)

#First, find the install directories.
IF(NOT BRLCAD_BASE_DIR)
    #try looking for BRL-CAD's brlcad-config - it should give us
    #a location for bin, and the parent will be the root dir
    IF(NOT BRLCAD_BASE_DIR)
        FIND_PROGRAM(BRLCAD_CONFIGEXE brlcad-config)
        IF(BRLCAD_CONFIGEXE)
            EXEC_PROGRAM(brlcad-config ARGS --prefix OUTPUT_VARIABLE BRLCAD_BASE_DIR)
        ENDIF(BRLCAD_CONFIGEXE)
    ENDIF(NOT BRLCAD_BASE_DIR)

    #if that didn't work, see if we can find brlcad-config and use the parent path
    IF(NOT BRLCAD_BASE_DIR)
        FIND_PATH(BRLCAD_BIN_DIR brlcad-config)
        IF(BRLCAD_BIN_DIR)
            GET_FILENAME_COMPONENT(BRLCAD_BASE_DIR ${BRLCAD_BIN_DIR} PATH)
        ENDIF(BRLCAD_BIN_DIR)
    ENDIF(NOT BRLCAD_BASE_DIR)

    #Look for headers if we come up empty with brlcad-config
    IF(NOT BRLCAD_BASE_DIR)
        SET(BRLCAD_HEADERS_DIR_CANDIDATES 
            /usr/brlcad/include/brlcad 
            /usr/local/brlcad/include/brlcad
            )
        FIND_PATH(BRLCAD_HEADERS_DIR NAMES bu.h bn.h rt.h PATHS ${BRLCAD_HEADERS_DIR_CANDIDATES})
        IF(BRLCAD_HEADERS_DIR)
            GET_FILENAME_COMPONENT(BRLCAD_BASE_DIR ${BRLCAD_HEADERS_DIR} PATH)
        ENDIF(BRLCAD_HEADERS_DIR)
    ENDIF(NOT BRLCAD_BASE_DIR)

    IF(NOT BRLCAD_BASE_DIR)
        MESSAGE(FATAL_ERROR "\nCould not find BRL-CAD root directory - please set BRLCAD_BASE_DIR in CMake")
    ENDIF(NOT BRLCAD_BASE_DIR)
ENDIF(NOT BRLCAD_BASE_DIR)

#Find include directories
IF(NOT BRLCAD_HEADERS_DIR)
    FIND_PATH(BRLCAD_HEADERS_DIR NAMES bu.h HINTS ${BRLCAD_BASE_DIR} PATH_SUFFIXES include/brlcad)
    GET_FILENAME_COMPONENT(BRLCAD_HEADERS_PARENT_DIR ${BRLCAD_HEADERS_DIR} PATH)
ENDIF(NOT BRLCAD_HEADERS_DIR)
FIND_PATH(BRLCAD_OPENNURBS_HEADERS_DIR NAMES opennurbs.h HINTS ${BRLCAD_BASE_DIR} PATH_SUFFIXES include/OpenNURBS include/openNURBS include/opennurbs)
SET(BRLCAD_INCLUDE_DIRS ${BRLCAD_HEADERS_PARENT_DIR} ${BRLCAD_HEADERS_DIR} ${BRLCAD_OPENNURBS_HEADERS_DIR})
SET(BRLCAD_INCLUDE_DIRS ${BRLCAD_INCLUDE_DIRS} CACHE STRING "BRL-CAD include directories")

#Find library directory
IF(CMAKE_LINK_LIBRARY_SUFFIX)
    FIND_PATH(BRLCAD_LIB_DIR "libbu${CMAKE_LINK_LIBRARY_SUFFIX}" PATHS ${BRLCAD_BASE_DIR} PATH_SUFFIXES lib libs bin)
ELSE(CMAKE_LINK_LIBRARY_SUFFIX)
    FIND_PATH(BRLCAD_LIB_DIR "libbu${CMAKE_SHARED_LIBRARY_SUFFIX}" PATHS ${BRLCAD_BASE_DIR} PATH_SUFFIXES lib libs bin)
ENDIF(CMAKE_LINK_LIBRARY_SUFFIX)

#Find binary directory
IF(NOT BRLCAD_BIN_DIR)
    FIND_PATH(BRLCAD_BIN_DIR brlcad-config PATHS ${BRLCAD_BASE_DIR} PATH_SUFFIXES bin)
ENDIF(NOT BRLCAD_BIN_DIR)

#Attempt to get brlcad version.
IF(NOT BRLCAD_CONFIGEXE)
    FIND_PROGRAM(BRLCAD_CONFIGEXE brlcad-config)
ENDIF(NOT BRLCAD_CONFIGEXE)
IF(BRLCAD_CONFIGEXE)
    EXECUTE_PROCESS(COMMAND ${BRLCAD_CONFIGEXE} --version OUTPUT_VARIABLE BRLCAD_VERSION)
    STRING(STRIP "${BRLCAD_VERSION}" BRLCAD_VERSION)
    IF(BRLCAD_VERSION)
        STRING(REGEX REPLACE "([0-9]+)\\.[0-9]+\\.[0-9]+" "\\1" BRLCAD_VERSION_MAJOR "${BRLCAD_VERSION}")
        STRING(REGEX REPLACE "[0-9]+\\.([0-9]+)\\.[0-9]+" "\\1" BRLCAD_VERSION_MINOR "${BRLCAD_VERSION}")
        STRING(REGEX REPLACE "[0-9]+\\.[0-9]+\\.([0-9]+)" "\\1" BRLCAD_VERSION_PATCH "${BRLCAD_VERSION}")
        SET(BRLCAD_VERSION_FOUND TRUE)
    ELSE(BRLCAD_VERSION)
        MESSAGE(WARNING "\t\t'brlcad-config --version' was found and executed, but produced no output.")
        SET(BRLCAD_VERSION_FOUND FALSE)
    ENDIF(BRLCAD_VERSION)
ELSE(BRLCAD_CONFIGEXE)
    IF(BRLCAD_VERSION)
        STRING(REGEX REPLACE "([0-9]+)\\.[0-9]+\\.[0-9]+" "\\1" BRLCAD_VERSION_MAJOR "${BRLCAD_VERSION}")
        STRING(REGEX REPLACE "[0-9]+\\.([0-9]+)\\.[0-9]+" "\\1" BRLCAD_VERSION_MINOR "${BRLCAD_VERSION}")
        STRING(REGEX REPLACE "[0-9]+\\.[0-9]+\\.([0-9]+)" "\\1" BRLCAD_VERSION_PATCH "${BRLCAD_VERSION}")
        SET(BRLCAD_VERSION_FOUND TRUE)
    ELSE(BRLCAD_VERSION)
        MESSAGE(WARNING "Could not locate 'brlcad-config' - please set BRLCAD_VERSION in CMake")
        SET(BRLCAD_VERSION_FOUND FALSE)
    ENDIF(BRLCAD_VERSION)
ENDIF(BRLCAD_CONFIGEXE)

#Determine static libraries name schema
IF("${CMAKE_STATIC_LIBRARY_SUFFIX}" STREQUAL "${CMAKE_LINK_LIBRARY_SUFFIX}")
    SET(STATIC_LIBRARY_SUFFIX -static${CMAKE_STATIC_LIBRARY_SUFFIX})
ELSE("${CMAKE_STATIC_LIBRARY_SUFFIX}" STREQUAL "${CMAKE_LINK_LIBRARY_SUFFIX}")
    SET(STATIC_LIBRARY_SUFFIX ${CMAKE_STATIC_LIBRARY_SUFFIX})
ENDIF("${CMAKE_STATIC_LIBRARY_SUFFIX}" STREQUAL "${CMAKE_LINK_LIBRARY_SUFFIX}")
MESSAGE(STATUS "BRL-CAD static library suffix: ${STATIC_LIBRARY_SUFFIX}")

#TODO figure out why brlcad-config isn't present on Windows.
##########################################################################
# First, search for BRL-CAD's own libraries
SET(BRL-CAD_LIBS_SEARCH_LIST
    analyze
    bg
    bv
    bn
    brep
    bu
    dm
    fft
    gcv
    ged
    icv
    nmg
    optical
    pkg
    render
    rt
    wdb
)

FOREACH(brl_lib ${BRL-CAD_LIBS_SEARCH_LIST})
    STRING(TOUPPER ${brl_lib} LIBCORE)
    FIND_LIBRARY(BRLCAD_${LIBCORE}_LIBRARY NAMES ${brl_lib} lib${brl_lib} PATHS ${BRLCAD_LIB_DIR} NO_SYSTEM_PATH)
    IF(BRLCAD_${LIBCORE}_LIBRARY)
        SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} ${BRLCAD_${LIBCORE}_LIBRARY})
    ELSE(BRLCAD_${LIBCORE}_LIBRARY)
        SET(BRLCAD_LIBRARIES_NOTFOUND ${BRLCAD_LIBRARIES_NOTFOUND} ${brl_lib})
    ENDIF(BRLCAD_${LIBCORE}_LIBRARY)
ENDFOREACH(brl_lib ${BRL-CAD_LIBS_SEARCH_LIST})

FOREACH(brl_lib ${BRL-CAD_LIBS_SEARCH_LIST})
    STRING(TOUPPER ${brl_lib} LIBCORE)
    FIND_LIBRARY(BRLCAD_${LIBCORE}_STATIC_LIBRARY NAMES ${brl_lib}${STATIC_LIBRARY_SUFFIX} lib${brl_lib}${STATIC_LIBRARY_SUFFIX} PATHS ${BRLCAD_LIB_DIR} NO_SYSTEM_PATH)
ENDFOREACH(brl_lib ${BRL-CAD_LIBS_SEARCH_LIST})

# Then, look for customized src/other libraries that we need
# local versions of

SET(BRL-CAD_SRC_OTHER_REQUIRED
    exppp
    express
    lmdb
    openNURBS
    stepcore
    stepdai
    stepeditor
    steputils
)

FOREACH(ext_lib ${BRL-CAD_SRC_OTHER_REQUIRED})
    STRING(TOUPPER ${ext_lib} LIBCORE)
    FIND_LIBRARY(BRLCAD_${LIBCORE}_LIBRARY NAMES ${ext_lib} lib${ext_lib} ${ext_lib}_brl lib${ext_lib}_brl PATHS ${BRLCAD_LIB_DIR} NO_SYSTEM_PATH)
    IF(BRLCAD_${LIBCORE}_LIBRARY)
        SET(BRLCAD_LIBRARIES ${BRLCAD_LIBRARIES} ${BRLCAD_${LIBCORE}_LIBRARY})
    ELSE(BRLCAD_${LIBCORE}_LIBRARY)
        SET(BRLCAD_LIBRARIES_NOTFOUND ${BRLCAD_LIBRARIES_NOTFOUND} ${ext_lib})
    ENDIF(BRLCAD_${LIBCORE}_LIBRARY)
ENDFOREACH(ext_lib ${BRL-CAD_SRC_OTHER_REQUIRED})

FOREACH(ext_lib ${BRL-CAD_SRC_OTHER_REQUIRED})
    STRING(TOUPPER ${ext_lib} LIBCORE)
    FIND_LIBRARY(BRLCAD_${LIBCORE}_STATIC_LIBRARY NAMES ${ext_lib}${STATIC_LIBRARY_SUFFIX} lib${ext_lib}${STATIC_LIBRARY_SUFFIX} ${ext_lib}_brl${STATIC_LIBRARY_SUFFIX} lib${ext_lib}_brl${STATIC_LIBRARY_SUFFIX} PATHS ${BRLCAD_LIB_DIR} NO_SYSTEM_PATH)
ENDFOREACH(ext_lib ${BRL-CAD_SRC_OTHER_REQUIRED})

# Do another check for opennurbs static lib
FIND_LIBRARY(BRLCAD_OPENNURBS_STATIC_LIBRARY NAMES opennurbsStatic PATHS ${BRLCAD_LIB_DIR} NO_SYSTEM_PATH)

# Lastly, we need to check for local installs in the BRL-CAD install of
# libraries that might otherwise be present on the system - if they are
# found in the BRL-CAD install tree, use those versions instead of any
# system results by setting the variables a find_package result would 
# produce.

#  zlib
FIND_LIBRARY(ZLIB_LIBRARY NAMES z_brl z zlib zdll PATHS ${BRLCAD_LIB_DIR})
FIND_LIBRARY(ZLIB_STATIC_LIBRARY NAMES z_brl${STATIC_LIBRARY_SUFFIX} libz_brl${STATIC_LIBRARY_SUFFIX} z${STATIC_LIBRARY_SUFFIX} libz${STATIC_LIBRARY_SUFFIX} zlib${STATIC_LIBRARY_SUFFIX} zdll${STATIC_LIBRARY_SUFFIX} PATHS ${BRLCAD_LIB_DIR} NO_SYSTEM_PATH)
IF("${ZLIB_STATIC_LIBRARY}" STREQUAL "ZLIB_STATIC_LIBRARY-NOTFOUND")
    # use the dynamic one
    FIND_LIBRARY(ZLIB_STATIC_LIBRARY NAMES z_brl z zlib zdll PATHS ${BRLCAD_LIB_DIR})
ENDIF("${ZLIB_STATIC_LIBRARY}" STREQUAL "ZLIB_STATIC_LIBRARY-NOTFOUND")
FIND_PATH(ZLIB_INCLUDE_DIR zlib.h PATHS ${BRLCAD_INCLUDE_DIRS})
SET(ZLIB_LIBRARIES ${ZLIB_LIBRARY})
SET(ZLIB_STATIC_LIBRARIES ${ZLIB_STATIC_LIBRARY})
SET(ZLIB_INCLUDE_DIRS ${ZLIB_INCLUDE_DIR})

#  libregex
FIND_LIBRARY(REGEX_LIBRARY NAMES regex_brl c regex compat PATHS ${BRLCAD_LIB_DIR})
FIND_LIBRARY(REGEX_STATIC_LIBRARY NAMES regex_brl${STATIC_LIBRARY_SUFFIX} libregex_brl${STATIC_LIBRARY_SUFFIX} c${STATIC_LIBRARY_SUFFIX} libc${STATIC_LIBRARY_SUFFIX} regex${STATIC_LIBRARY_SUFFIX} libregex${STATIC_LIBRARY_SUFFIX} compat${STATIC_LIBRARY_SUFFIX} libcompat${STATIC_LIBRARY_SUFFIX} PATHS ${BRLCAD_LIB_DIR} NO_SYSTEM_PATH)
IF("${REGEX_STATIC_LIBRARY}" STREQUAL "REGEX_STATIC_LIBRARY-NOTFOUND")
    # use the dynamic one
    FIND_LIBRARY(REGEX_STATIC_LIBRARY NAMES regex_brl c regex compat PATHS ${BRLCAD_LIB_DIR})
ENDIF("${REGEX_STATIC_LIBRARY}" STREQUAL "REGEX_STATIC_LIBRARY-NOTFOUND")
FIND_PATH(REGEX_INCLUDE_DIR regex.h PATHS ${BRLCAD_INCLUDE_DIRS})
SET(REGEX_LIBRARIES ${REGEX_LIBRARY})
SET(REGEX_STATIC_LIBRARIES ${REGEX_STATIC_LIBRARY})
SET(REGEX_INCLUDE_DIRS ${REGEX_INCLUDE_DIR})

##########################################################################
#Print status
IF(BRLCAD_VERSION)
    MESSAGE(STATUS "Found BRL-CAD ${BRLCAD_VERSION} at ${BRLCAD_BASE_DIR}")
ELSE(BRLCAD_VERSION)
    MESSAGE(STATUS "Found BRL-CAD at ${BRLCAD_BASE_DIR}")
ENDIF(BRLCAD_VERSION)

#Set found flag - TODO: this is wrong, need to set this based on variables
SET(BRLCAD_FOUND TRUE)
