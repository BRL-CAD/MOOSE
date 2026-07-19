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

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

from brlcad import ConstDatabase

def run_test():
    #change the path of the sample .g file to your test .g file before running the test
    sample_g_file = "/home/home/Documents/work/Python/main-brlcad/cube_scene.g"
    
    # Initialize the object tracker
    db = ConstDatabase()
    
    # Pure boolean status check flow
    if db.Load(sample_g_file):
        detected_title = db.Title()
        print(f"\n[PASS] Database loaded successfully.")
        print(f"[INFO] Header Title Found: '{detected_title}'")
        
        if detected_title == "MOOSE Engineering Test Scene":
            print("[SUCCESS] Metadata assertions matched!")
            return True
            
    print("\n[FAIL] Failed to extract correct metadata.")
    return False

if __name__ == "__main__":
    run_test()