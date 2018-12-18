/****
Copyright (c) 2018 Y Paritcher

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser GeneralPublic License as published by the Free Software Foundation; 
either version 2.1 of the License, or (at your option)any later version.

This library is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY; 
without even the impliedwarranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for more details. 
You should have received a copy of the GNU Lesser General Public License along with this library; 
if not, write tothe Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA, 
or connect to: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html
****/

#include <time.h>
#include "util.h"
#include "hebrewcalendar.h"
#include "zmanim.h"
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

long int getLocalMeanTimeOffset(hdate *now, location *here)
{
	return (long int) (here->longitude * 4 * 60 - now->offset);
}

int getAntimeridianAdjustment(hdate *now, location *here)
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

hdate getDateFromTime(hdate *current, double time, location *here, int isSunrise)
{
	hdate result = {0};
	if (isnan(time)) {
		return result;
	}
	int adjustment = getAntimeridianAdjustment(current, here);
	double calculatedTime = time;
	result.year = current->year;
	result.EY = current->EY;
	result.offset = current->offset;
	result.month = current->month;
	result.day = current->day;
	if (adjustment){hdateaddday(&result, adjustment);}

	int hours = (int)calculatedTime;
	calculatedTime -= hours;
	int minutes = (int)(calculatedTime *= 60);
	calculatedTime -= minutes;
	int seconds = (int)(calculatedTime *= 60);
	calculatedTime -= seconds;
	int miliseconds = (int)(calculatedTime * 1000);
	int localTimeHours = (int)here->longitude / 15;
	if (isSunrise && localTimeHours + hours > 18) {
		hdateaddday(&result, -1);
	} else if (!isSunrise && localTimeHours + hours < 6) {
		hdateaddday(&result, +1);
	}

	result.hour = hours;
	result.min = minutes;
	result.sec = seconds;
	result.msec = miliseconds;
	hdateaddsecond(&result, current->offset);
	return result;
}
