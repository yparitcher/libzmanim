/****
Copyright (c) 2018 Y Paritcher
****/

#ifndef CALCULATORUTIL_H
#define CALCULATORUTIL_H

#define M_PI	3.14159265358979323846	/* pi */

double radToDeg(double angleRad);
double degToRad(double angleDeg);

double adjustZenith(double zenith, double elevation);

ltime getDateFromTime(tmz *current, double time, location *here, int isSunrise);

#endif
