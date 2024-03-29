#########################################################################
#
#  Permission to use, copy, modify, and/or distribute this software for any
#  purpose with or without fee is hereby granted.
#
#  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
#  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
#  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
#  SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
#  RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF
#  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
#  CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#
#########################################################################


INCLUDE_DIRECTORIES(
    ${BRLCAD_MOOSE_INCLUDE_DIR}
)

SET(DatabaseSources
    PrintTitle.cpp
)

IF(MSVC)
    ADD_DEFINITIONS("-DBRLCAD_MOOSE_EXPORT=__declspec(dllimport)")
ELSE(MSVC)
    ADD_DEFINITIONS("-DBRLCAD_MOOSE_EXPORT=")
ENDIF(MSVC)

ADD_EXECUTABLE(Database ${DatabaseSources})
TARGET_LINK_LIBRARIES(Database ${BRLCAD_MOOSE_LIBRARY})
SET_TARGET_PROPERTIES(Database PROPERTIES OUTPUT_NAME "printtitle_database")
