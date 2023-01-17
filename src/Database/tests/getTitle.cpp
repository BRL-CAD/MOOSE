/*
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF
 * CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <cstring>
#include <iostream>

#include <brlcad/Database/FileDatabase.h>
#include <brlcad/Database/MemoryDatabase.h>


int main
(
    int   argc,
    char* argv[]
) {
    int ret = 1;

    if ((argc < 2) || (argv[1] == nullptr))
        std::cerr << "Usage: " << argv[0] << " <test type>";
    else {
        if (strcmp(argv[1], "const") == 0) {
            BRLCAD::ConstDatabase database;

            if (database.Load("gettitle.g")) {
                if (strcmp(database.Title(), "get title") == 0)
                    ret = 0;
            }
            else
                std::cerr << "Could not load file";
        }
        else if (strcmp(argv[1], "file") == 0) {
            BRLCAD::FileDatabase database;

            if (database.Load("gettitle.g")) {
                if (strcmp(database.Title(), "get title") == 0)
                    ret = 0;
            }
            else
                std::cerr << "Could not load file";
        }
        else if (strcmp(argv[1], "memory") == 0) {
            BRLCAD::MemoryDatabase database;

            if (database.Load("gettitle.g")) {
                if (strcmp(database.Title(), "get title") == 0)
                    ret = 0;
            }
            else
                std::cerr << "Could not load file";
        }
        else
            std::cerr << "Unknown test type: " << argv[1];
    }

    return ret;
}
