#########################################################################
#
#	BRL-CAD
#
#	Copyright (c) 2022 United States Government as represented by
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
#	@file src/CommandString/CMakeLists.txt
#########################################################################


SET(CommandStringSources
    CommandString/CommandString.cpp
)

SET(CommandStringHeaders
    ${MOOSE_SOURCE_DIR}/include/brlcad/CommandString/CommandString.h
)

INSTALL(FILES ${CommandStringHeaders} DESTINATION include/brlcad/CommandString)
