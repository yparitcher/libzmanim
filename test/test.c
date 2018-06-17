/****
Copyright (c) 2018 Y Paritcher
****/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "util.h"
#include "NOAAcalculator.h"
#include "calculatorutil.h"
#include "zmanim.h"

char* formattime(ltime ltime, char* final)
{
	time_t time = ltime / 1000;
	struct tm *tm = localtime(&time);
	strftime(final, 31, "%m/%d/%Y %I:%M:%S.~~~ %p %Z", tm);
	char msec[4];
	snprintf(msec, 4, "%i", (int)(ltime % 1000));
	memcpy(strchr(final, (int)'~'), msec, 3);
	return final;
}

int main()
{
	location here = { 40.66896, -73.94284, 34 };
	double zenith = 90.0;
	float timezone = -4.0;
	time_t now = time(NULL);
	tmz nowlocal;
	nowlocal.tm = *localtime(&now);
	nowlocal.tmz_gmtoff = (long int) 3600 * timezone;

	setall(&now, nowlocal.tmz_gmtoff, here.latitude, here.longitude, here.elevation);
/*	printf("%li\n%f\n%f\n%f\n%f\n", gettime(), getoffset(), getlatitude(), getlongitude(), getelevation());
*/

	ltime rise = calcsunrise(&nowlocal, &here, zenith, 0);
	char sunrise[32];
	formattime(rise, sunrise);
	printf("sunrise: %s\n", sunrise);

	ltime set = calcsunset(&nowlocal, &here, zenith, 0);
	char sunset[32];
	formattime(set, sunset);
	printf("sunset:  %s\n", sunset);

	return 0;
}
