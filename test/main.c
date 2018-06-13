/****
Copyright (c) 2018 Y Paritcher
****/

#include <stdio.h>
#include <time.h>
#include "util.h"
#include "NOAAcalculator.h"
#include "calculatorutil.h"

int main()
{
	location here = { 40.66896, -73.94284, 0 };
	double zenith = 90.0;
	float timezone = -4.0;
	time_t now = time(NULL);
	tmz nowlocal;
	struct tm *tm2 = localtime(&now);
	nowlocal.tm = *tm2;
	nowlocal.tmz_gmtoff = (long int) 3600 * timezone;
	double utcrise = getUTCSunrise(tm2, &here, zenith, 0);
	double utcset = getUTCSunset(tm2, &here, zenith, 0);
	char *form = "%m/%d/%Y %I:%M:%S %p %Z";
	char sunrise[28];
	char sunset[28];
	tmz tmzrise = getDateFromTime(&nowlocal, utcrise, &here, 1);
	tmz tmzset = getDateFromTime(&nowlocal, utcset, &here, 0);
	strftime(sunrise, 27, form, &tmzrise.tm);
	strftime(sunset, 27, form, &tmzset.tm);
	printf("sunrise: %s %i\nsunset:  %s %i\n", sunrise, tmzrise.tmz_msec, sunset, tmzset.tmz_msec);

	return 0;
}
