# Libzmanim

a C library for zmanim

a port of [KosherJava/Zmanim](https://github.com/KosherJava/zmanim) developed by Eliyahu Hershfeld.

## Installation

run ` make` to build the library (shared and static) in the lib folder.

run `make test` to build a test wrapper (in the test folder) to display the daily zmanim.

this creates a shared and static library that can be used by including `zmanim.h` and linking with `-lzmanim` (you must add the library and header to your `PATH`)

## Usage

this library has a new type `ltime` which is a `long long int` used to store a time instance with milisecond precision (simalar to `time_t`).

the library need to be initialized with the desired date and location using the setall function.
```c
int setall(time_t *time, double offset, double latitude, double longitude, double elevation)
```
this returns `0` with valid input otherwise a `int` equal to the binary number of which fields are invalid.
(eg: 1 if the time is invalid, 2 for the offset, 3 for both ...)
one can also set individual field with the other set functions
the set date and location can be retrieved with the corresponding get functions

once this setup is complete:

call any of the get functions to get that zman as a ltime that can easily be converted to a `time_t` by `/ 1000`

for further examples see the test.c file that implements a basic wrapper to show daily zmanim
<!---
### test usage:

./teststatic date latitude longitude timezone
```
./teststatic 2018-01-01 40.66896 -73.94284 -4.0
```
./teststatic is interchangeable with ./testshared.
--->

## License
sms-bot is Copyright (c) 2018 [Yparitcher](https://github.com/yparitcher).
licensed under the [LGPL 2.1](https://opensource.org/licenses/LGPL-2.1) license. 
