/****
Copyright (c) 2018 Y Paritcher
****/

#ifndef UTIL_H
#define UTIL_H

#include <time.h>

typedef struct {
  struct tm tm;
  int tmz_msec;
  long int tmz_gmtoff;
} tmz;

#endif
