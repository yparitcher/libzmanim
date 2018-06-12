/****
Copyright (c) 2018 Y Paritcher
****/

#ifndef NOAACALCULATOR_H
#define NOAACALCULATOR_H

double getUTCSunrise(struct tm *date, double latitude, double longitude, double zenith);
double getUTCSunset(struct tm *date, double latitude, double longitude, double zenith);

#endif
