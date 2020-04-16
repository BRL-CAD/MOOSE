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
#	@file src/Database/CMakeLists.txt
#########################################################################


SET(DatabaseSources
    Arb8.cpp
    BagOfTriangles.cpp
    Combination.cpp
    Cone.cpp
    ConstDatabase.cpp
    Database.cpp
    Ellipsoid.cpp
    EllipticalTorus.cpp
    FileDatabase.cpp
    Halfspace.cpp
    HyperbolicCylinder.cpp
    Hyperboloid.cpp
    MemoryDatabase.cpp
    NonManifoldGeometry.cpp
    Object.cpp
    ParabolicCylinder.cpp
    Paraboloid.cpp
    Particle.cpp
    Pipe.cpp
    Sketch.cpp
    Sphere.cpp
    Torus.cpp
    Unknown.cpp
)

SET(DatabaseHeaders
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/Arb8.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/BagOfTriangles.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/Combination.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/Cone.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/ConstDatabase.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/Database.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/Ellipsoid.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/EllipticalTorus.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/FileDatabase.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/Halfspace.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/HyperbolicCylinder.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/Hyperboloid.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/MemoryDatabase.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/NonManifoldGeometry.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/Object.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/ParabolicCylinder.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/Paraboloid.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/Particle.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/Pipe.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/Sketch.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/Sphere.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/Torus.h
    ${MOOSE_SOURCE_DIR}/include/brlcad/Database/Unknown.h
)

IF(MSVC)
    add_definitions(-DBRLCAD_MOOSE_EXPORT=__declspec(dllexport))
    add_definitions(-DBU_DLL_IMPORTS -DRT_DLL_IMPORTS -DWDB_DLL_IMPORTS)
ELSE(MSVC)
    add_definitions(-DBRLCAD_MOOSE_EXPORT=)
ENDIF(MSVC)

ADD_LIBRARY(database STATIC ${DatabaseSources})

INSTALL(FILES ${DatabaseHeaders} DESTINATION include/brlcad/Database)
