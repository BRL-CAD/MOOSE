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

#include <iostream>

#include <brlcad/Database/FileDatabase.h>
#include <brlcad/CommandString/CommandString.h>


int main
(
    int   argc,
    char* argv[]
) {
    int ret = 0;

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <BRL-CAD Database>";
        ret = 1;
    }
    else {
        BRLCAD::FileDatabase database;

        if (database.Load(argv[1])) {
            BRLCAD::CommandString    parser(database);
            std::vector<const char*> arguments = {"title"};

            if (parser.Parse(arguments) == BRLCAD::CommandString::State::Success)
                std::cout << parser.Results() << std::endl;
            else {
                ret = 3;
                std::cerr << "Could not parse file: " << argv[1] << std::endl;
            }
        }
        else {
            std::cerr << "Could not load file: " << argv[1] << std::endl;
            ret = 2;
        }
    }

    return ret;
}
