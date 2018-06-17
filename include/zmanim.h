/****
Copyright (c) 2018 Y Paritcher
****/

#ifndef ZMANIM_H
#define ZMANIM_H

int settime(time_t *time);
int setoffset(double offset);
int setlatitude(double latitude);
int setlongitude(double longitude);
int setelevation(double elevation);
int setall(time_t *time, double offset, double latitude, double longitude, double elevation);

time_t gettime();
double getoffset();
double getlatitude();
double getlongitude();
double getelevation();


ltime calcsunrise(tmz *date, location *here, double zenith, unsigned int adjustForElevation);
ltime calcsunset(tmz *date, location *here, double zenith, unsigned int adjustForElevation);

#endif
