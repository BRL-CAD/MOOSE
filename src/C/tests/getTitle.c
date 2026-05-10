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

#include <stdio.h>
#include <string.h>

#include <brlcad/C/ConstDatabase.h>


int main
(
    int   argc,
    char* argv[]
) {
    int ret = 1;

    if ((argc < 2) || (argv[1] == 0))
        printf("Usage: %s <test type>", argv[0]);
    else {
        if (strcmp(argv[1], "const") == 0) {
            BrlConstDatabase database = BrlNewConstDatabase();

            if (database != 0) {

                if (BrlConstDatabaseLoad(database, "gettitle.g") == 0) {
                    if (strcmp(BrlConstDatabaseTitle(database), "get title") == 0)
                        ret = 0;
                }
                else
                    fprintf(stderr, "Could not load file gettitle.g");

                BrlDeleteConstDatabase(database);
            }
            else
                fprintf(stderr, "Could not create BrlConstDatabase");
        }
        else
            fprintf(stderr, "Unknown test type: %s", argv[1]);
    }

    return ret;
}
