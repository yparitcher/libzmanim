/****
Copyright (c) 2018 Y Paritcher
****/

#ifndef UTIL_H
#define UTIL_H

#include <time.h>

#define GEOMETRIC_ZENITH 90.0

typedef struct {
  struct tm tm;
  int tmz_msec;
  long int tmz_gmtoff;
} tmz;

typedef struct {
	double latitude;
	double longitude;
	double elevation;
} location;

#endif
