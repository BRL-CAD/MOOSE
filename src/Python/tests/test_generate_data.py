#   Permission to use, copy, modify, and/or distribute this software for any
#   purpose with or without fee is hereby granted.
#  
#   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
#   WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
#   MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
#   SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
#   RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF
#   CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
#   CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.


import os
import sys

# Ensure the root directory is on Python's path before importing packages
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))

from brlcad import FileDatabase


def main(argv=None):
    if argv is None:
        argv = sys.argv
        
    argc = len(argv)
    ret = 1

    if argc < 2 or argv[1] is None:
        print(f"Usage: {argv[0]} <test type>", file=sys.stderr)
    else:
        if argv[1] == "getTitle":
            
            with FileDatabase() as database:
                filename = "gettitle.g"

                if not os.path.exists(filename):
                    print(f"Error: {filename} not found", file=sys.stderr)
                    return 1

                if database.Load(filename):
                    database.SetTitle("get Title")
                    
                    print(f"[SUCCESS] Updated Title value: '{database.Title()}'")
                    ret = 0
                else:
                    print("Could not load file", file=sys.stderr)
        else:
            print(f"Unknown test type: {argv[1]}", file=sys.stderr)

    return ret


if __name__ == "__main__":
    sys.exit(main())