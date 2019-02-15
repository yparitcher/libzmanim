# Libzmanim

a C library for zmanim and hebrew dates

a port of [KosherJava/Zmanim](https://github.com/KosherJava/zmanim) developed by Eliyahu Hershfeld.

## Installation

run ` make` to build the library (shared and static) in the lib folder.

run `make test` to build a test wrapper (in the test folder) to display the daily zmanim.

this creates a shared and static library that can be used by including the header files in `include` and linking with `-lzmanim` (you must add the library and headers to your `PATH`)

## Usage

this library has a new struct `hdate` which is like `struct tm` used to store a date instance in the hebrew calendar.

one can initialize the members directly or use the `hdate convertDate(struct tm date)` function to convert a gregorian date, along with other functions in `hebrewcalendar.c` to manipulate it or get yomtov parshah etc.

for more documentation read the header files.

to format the date in hebrew use the functions in `hdateformat.h`.

one can then use this `hdate` along with the `location` struct (lat, long, elevation) in one of the getzmanim functions in `zmanim.h` that return a `hdate` with the correct zman.

for further examples see the test.c file that implements a basic wrapper to show daily zmanim

### Test usage

./test year month day latitude longitude timezone Eretz_Yisroel
```
./test 2018 12 18 40.66896 -73.94284 -4.0 0

               י טבת תשע״ט
               עשרה בטבת
               פרשת ויחי
alos:               05:41 AM EST
misheyakir:         06:19 AM EST
sunrise:            07:14 AM EST
shma:               09:31 AM EST
tefila:             10:18 AM EST
chatzos:            11:52 AM EST
mincha gedola:      12:15 PM EST
mincha ketana:      02:37 PM EST
plag hamincha:      03:36 PM EST
sunset:             04:30 PM EST
tzais:              05:01 PM EST
```

note: due to the limitations of the C standard library all times will show as if they in the computers timezone even though they are correctly calculated in the given timezone.

## License
Libzmanim is Copyright (c) 2018 [Yparitcher](https://github.com/yparitcher).
licensed under the [LGPL 2.1](https://opensource.org/licenses/LGPL-2.1) license. 
