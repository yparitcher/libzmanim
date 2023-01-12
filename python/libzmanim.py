#! /usr/bin/python
from libzmanim_cdef import ffi as ffi
ffi.set_source("libzmanim_python",
"""
#include <time.h>
#include "hebrewcalendar.h"
#include "NOAAcalculator.h"
#include "zmanim.h"
#include "hdateformat.h"
#include "shuir.h"
""",
	include_dirs = ["include"],
	sources = ["src/hebrewcalendar.c", "src/zmanim.c", "src/hdateformat.c", "src/shuir.c", "src/NOAAcalculator.c", ],
	libraries = ["m"]
	)

if __name__ == "__main__":
    ffi.compile(verbose=True)

