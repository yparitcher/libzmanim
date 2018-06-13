/****
Copyright (c) 2018 Y Paritcher
****/

#ifndef NOAACALCULATOR_H
#define NOAACALCULATOR_H

double getUTCSunrise(struct tm *date, location *here, double zenith, unsigned int adjustForElevation);
double getUTCSunset(struct tm *date, location *here, double zenith, unsigned int adjustForElevation);

#endif
