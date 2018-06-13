/****
Copyright (c) 2018 Y Paritcher
****/

#include <time.h>
#include "util.h"
#include "calculatorutil.h"
#include <math.h>

const double refraction = 34 / 60.0;
const double solarradius = 16 / 60.0;
const double earthradius = 6356.9;

double radToDeg(double angleRad)
{
	return (180.0 * angleRad / M_PI);
}

double degToRad(double angleDeg)
{
	return (M_PI * angleDeg / 180.0);
}

long int getLocalMeanTimeOffset(tmz *now, location *here)
{
	return (long int) (here->longitude * 4 * 60 - now->tmz_gmtoff);
}

int getAntimeridianAdjustment(tmz *now, location *here)
{
	double localHoursOffset = getLocalMeanTimeOffset(now, here) / (double)3600;
	/*if the offset is 20 hours or more in the future (never expected anywhere other
	 * than a location using a timezone across the anti meridian to the east such as Samoa) */
	if (localHoursOffset >= 20)
	{
		/* roll the date forward a day */
		return 1;
	}
	/* if the offset is 20 hours or more in the past (no current location is known
	 * that crosses the antimeridian to the west, but better safe than sorry) */
	else if (localHoursOffset <= -20)
	{
		/* roll the date back a day */
		return -1;
	}
	/*99.999% of the world will have no adjustment */
	return 0;
}

double getElevationAdjustment(double elevation)
{
	double elevationAdjustment = radToDeg(acos(earthradius / (earthradius + (elevation / 1000))));
	return elevationAdjustment;
}

double adjustZenith(double zenith, double elevation)
{
	double adjustedZenith = zenith;
	if (zenith == GEOMETRIC_ZENITH)
	{
		adjustedZenith = zenith + (solarradius + refraction + getElevationAdjustment(elevation));
	}
	return adjustedZenith;
}

tmz getDateFromTime(tmz *current, double time, location *here, int isSunrise)
{
	tmz result;
	if (isnan(time)) {
		return result;
	}
	int adjustment = getAntimeridianAdjustment(current, here);
	double calculatedTime = time;
	result.tm.tm_year = current->tm.tm_year;
	result.tm.tm_mon = current->tm.tm_mon;
	result.tm.tm_mday = current->tm.tm_mday;
	result.tm.tm_isdst = -1;
	result.tm.tm_mon += adjustment;

	int hours = (int)calculatedTime;
	calculatedTime -= hours;
	int minutes = (int)(calculatedTime *= 60);
	calculatedTime -= minutes;
	int seconds = (int)(calculatedTime *= 60);
	calculatedTime -= seconds;
	int miliseconds = (int)(calculatedTime * 1000);
	result.tmz_msec = miliseconds;
	int localTimeHours = (int)here->longitude / 15;
	if (isSunrise && localTimeHours + hours > 18) {
		result.tm.tm_mday -= 1;
	} else if (!isSunrise && localTimeHours + hours < 6) {
		result.tm.tm_mday += 1;
	}

	result.tm.tm_hour = hours;
	result.tm.tm_min = minutes;
	result.tm.tm_sec = seconds;
	result.tm.tm_sec += current->tmz_gmtoff;
	result.tmz_gmtoff = current->tmz_gmtoff;
	mktime(&(result.tm));
	mktime(&(result.tm));

	return result;
}
