/****
Copyright (c) 2018 Y Paritcher
****/

#ifndef UTIL_H
#define UTIL_H

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

typedef union {
	unsigned int s;
	struct t {
		unsigned int tm :1;
		unsigned int of :1;
		unsigned int la :1;
		unsigned int lo :1;
		unsigned int el :1;
	}bf;
}settings;

#define FULLSETUP 31

typedef long long int ltime;

#endif
