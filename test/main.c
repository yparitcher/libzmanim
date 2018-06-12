
#include <stdio.h>
#include <time.h>
#include "util.h"
#include "NOAAcalculator.h"
#include "calculatorutil.h"

int main()
{
	double latitude = 40.66896;
	double longitude = -73.94284;
	double zenith = 90.0;
	float timezone = -4.0;
	time_t now = time(NULL);
	tmz nowlocal;
	struct tm *tm2 = localtime(&now);
	nowlocal.tm = *tm2;
	nowlocal.tmz_gmtoff = (long int) 3600 * timezone;
	double utcrise = getUTCSunrise(tm2, latitude, longitude, zenith);
	double utcset = getUTCSunset(tm2, latitude, longitude, zenith);
	char *form = "%m/%d/%Y %I:%M:%S %p %Z";
	char sunrise[28];
	char sunset[28];
	tmz tmzrise = getDateFromTime(&nowlocal, utcrise, longitude, 1);
	tmz tmzset = getDateFromTime(&nowlocal, utcset, longitude, 0);
	strftime(sunrise, 27, form, &tmzrise.tm);
	strftime(sunset, 27, form, &tmzset.tm);
	printf("sunrise: %s %i\nsunset:  %s %i\n", sunrise, tmzrise.tmz_msec, sunset, tmzset.tmz_msec);

	return 0;
}
