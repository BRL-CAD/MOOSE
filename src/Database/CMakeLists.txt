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
    Database/Arb8.cpp
    Database/BagOfTriangles.cpp
    Database/Combination.cpp
    Database/Cone.cpp
    Database/ConstDatabase.cpp
    Database/Database.cpp
    Database/Ellipsoid.cpp
    Database/EllipticalTorus.cpp
    Database/FileDatabase.cpp
    Database/Halfspace.cpp
    Database/HyperbolicCylinder.cpp
    Database/Hyperboloid.cpp
    Database/MemoryDatabase.cpp
    Database/NonManifoldGeometry.cpp
    Database/Object.cpp
    Database/ParabolicCylinder.cpp
    Database/Paraboloid.cpp
    Database/Particle.cpp
    Database/Pipe.cpp
    Database/Sketch.cpp
    Database/Sphere.cpp
    Database/Torus.cpp
    Database/Unknown.cpp
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

INSTALL(FILES ${DatabaseHeaders} DESTINATION include/brlcad/Database)
