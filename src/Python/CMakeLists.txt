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
#	@file src/Python/CMakeLists.txt
#########################################################################

FIND_PACKAGE(Python3 COMPONENTS Interpreter REQUIRED)

EXECUTE_PROCESS(
    COMMAND ${Python3_EXECUTABLE} -c "import sysconfig; p=sysconfig.get_path('purelib'); print(p[p.find('lib/'):] if 'lib/' in p else p)"
    OUTPUT_VARIABLE PYTHON_INSTALL_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

IF(NOT PYTHON_INSTALL_DIR)
    IF(WIN32)
        SET(PYTHON_INSTALL_DIR "Lib/site-packages")
    ELSE()
        SET(PYTHON_INSTALL_DIR "lib/python${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}/site-packages")
    ENDIF()
ENDIF()

SET(PythonSources
    brlcad/Arb8.py
    brlcad/BagOfTriangles.py
    brlcad/Combinations.py
    brlcad/Cone.py
    brlcad/ConstDatabase.py
    brlcad/Database.py
    brlcad/Ellipsoid.py
    brlcad/FileDatabase.py
    brlcad/Handle.py
    brlcad/MemoryDatabase.py
    brlcad/Object.py
    brlcad/Sphere.py
    brlcad/VectorList.py
    brlcad/__init__.py
    brlcad/_bindings.py
)

INSTALL(FILES ${PythonSources} DESTINATION ${PYTHON_INSTALL_DIR}/brlcad)
