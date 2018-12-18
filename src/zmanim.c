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
#include <math.h>
#include "hebrewcalendar.h"
#include "NOAAcalculator.h"
#include "zmanim.h"

const hdate invalid = {0};

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

hdate calcsunrise(hdate *date, location *here, double zenith, unsigned int adjustForElevation)
{
	double sunrise = getUTCSunrise(hdatejulian(date), here, zenith, adjustForElevation);
	return getDateFromTime(date, sunrise, here, 1);
}

hdate calcsunset(hdate *date, location *here, double zenith, unsigned int adjustForElevation)
{
	double sunset = getUTCSunset(hdatejulian(date), here, zenith, adjustForElevation);
	return getDateFromTime(date, sunset, here, 0);
}

long calcshaahzmanis(hdate startday, hdate endday)
{
	long int start = HebrewCalendarElapsedDays(startday.year)+(startday.dayofyear-1);
	long int end = HebrewCalendarElapsedDays(endday.year)+(endday.dayofyear-1);
	long int diff = end - start;
	diff = (diff * 24) + (endday.hour - startday.hour);
	diff = (diff * 60) + (endday.min - startday.min);
	diff = (diff * 60) + (endday.sec - startday.sec);
	diff = (diff * 1000) + (endday.msec - startday.msec);
	if (startday.year == 0 || endday.year == 0) return 0;
	return diff / 12;
}

hdate calctimeoffset(hdate time, long offset)
{
	hdate result = {0};
	if (time.year == 0 || offset == 0) return result;
	result = time;
	hdateaddmsecond(&result, offset);
	return result;
}

hdate getalos(hdate *date, location *here)
{
	return calcsunrise(date, here, ZENITH_16_P_1, 0);
}

hdate getalosbaalhatanya(hdate *date, location *here)
{
	return calcsunrise(date, here, ZENITH_16_P_9, 0);
}

hdate getalos26degrees(hdate *date, location *here)
{
	return calcsunrise(date, here, ZENITH_26_D, 0);
}

hdate getalos19p8degrees(hdate *date, location *here)
{
	return calcsunrise(date, here, ZENITH_19_P_8, 0);
}

hdate getalos18degrees(hdate *date, location *here)
{
	return calcsunrise(date, here, ZENITH_18_D, 0);
}

hdate getalos120(hdate *date, location *here)
{
	return calctimeoffset(getsunrise(date, here), -MINUTES120);
}

hdate getalos120zmanis(hdate *date, location *here)
{
	long shaahzmanis = getshaahzmanisgra(date, here);
	if (shaahzmanis == 0) return invalid;
	return calctimeoffset(getsunrise(date, here), shaahzmanis * -2);
}

hdate getalos96(hdate *date, location *here)
{
	return calctimeoffset(getsunrise(date, here), -MINUTES96);
}

hdate getalos96zmanis(hdate *date, location *here)
{
	long shaahzmanis = getshaahzmanisgra(date, here);
	if (shaahzmanis == 0) return invalid;
	return calctimeoffset(getsunrise(date, here), shaahzmanis * -1.6);
}

hdate getalos90(hdate *date, location *here)
{
	return calctimeoffset(getsunrise(date, here), -MINUTES90);
}

hdate getalos90zmanis(hdate *date, location *here)
{
	long shaahzmanis = getshaahzmanisgra(date, here);
	if (shaahzmanis == 0) return invalid;
	return calctimeoffset(getsunrise(date, here), shaahzmanis * -1.5);
}

hdate getalos72(hdate *date, location *here)
{
	return calctimeoffset(getsunrise(date, here), -MINUTES72);
}

hdate getalos72zmanis(hdate *date, location *here)
{
	long shaahzmanis = getshaahzmanisgra(date, here);
	if (shaahzmanis == 0) return invalid;
	return calctimeoffset(getsunrise(date, here), shaahzmanis * -1.2);
}

hdate getalos60(hdate *date, location *here)
{
	return calctimeoffset(getsunrise(date, here), -MINUTES60);
}

hdate getmisheyakir11p5degrees(hdate *date, location *here)
{
	return calcsunrise(date, here, ZENITH_11_P_5, 0);
}

hdate getmisheyakir11degrees(hdate *date, location *here)
{
	return calcsunrise(date, here, ZENITH_11_D, 0);
}

hdate getmisheyakir10p2degrees(hdate *date, location *here)
{
	return calcsunrise(date, here, ZENITH_10_P_2, 0);
}

hdate getsunrise(hdate *date, location *here)
{
	return calcsunrise(date, here, GEOMETRIC_ZENITH, 0);
}

hdate getsunrisebaalhatanya(hdate *date, location *here)
{
	return calcsunrise(date, here, ZENITH_AMITIS, 0);
}

hdate getelevationsunrise(hdate *date, location *here)
{
	return calcsunrise(date, here, GEOMETRIC_ZENITH, 1);
}

hdate calcshma(hdate startday, hdate endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, shaahzmanis * 3);
}

hdate getshmabaalhatanya(hdate *date, location *here)
{
	return calcshma(getsunrisebaalhatanya(date, here), getsunsetbaalhatanya(date, here));
}

hdate getshmagra(hdate *date, location *here)
{
	return calcshma(getsunrise(date, here), getsunset(date, here));
}

hdate getshmamga(hdate *date, location *here)
{
	return calcshma(getalos72(date, here), gettzais72(date, here));
}

hdate calctefila(hdate startday, hdate endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, shaahzmanis * 4);
}

hdate gettefilabaalhatanya(hdate *date, location *here)
{
	return calctefila(getsunrisebaalhatanya(date, here), getsunsetbaalhatanya(date, here));
}

hdate gettefilagra(hdate *date, location *here)
{
	return calctefila(getsunrise(date, here), getsunset(date, here));
}

hdate gettefilamga(hdate *date, location *here)
{
	return calctefila(getalos72(date, here), gettzais72(date, here));
}

hdate getachilaschometzbaalhatanya(hdate *date, location *here)
{
	return calctefila(getsunrisebaalhatanya(date, here), getsunsetbaalhatanya(date, here));
}

hdate getachilaschometzgra(hdate *date, location *here)
{
	return calctefila(getsunrise(date, here), getsunset(date, here));
}

hdate getachilaschometzmga(hdate *date, location *here)
{
	return calctefila(getalos72(date, here), gettzais72(date, here));
}

hdate calcbiurchometz(hdate startday, hdate endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, shaahzmanis * 5);
}

hdate getbiurchometzbaalhatanya(hdate *date, location *here)
{
	return calcbiurchometz(getsunrisebaalhatanya(date, here), getsunsetbaalhatanya(date, here));
}

hdate getbiurchometzgra(hdate *date, location *here)
{
	return calcbiurchometz(getsunrise(date, here), getsunset(date, here));
}

hdate getbiurchometzmga(hdate *date, location *here)
{
	return calcbiurchometz(getalos72(date, here), gettzais72(date, here));
}

hdate calcchatzos(hdate startday, hdate endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, shaahzmanis * 6);
}

hdate getchatzosbaalhatanya(hdate *date, location *here)
{
	return calcchatzos(getsunrisebaalhatanya(date, here), getsunsetbaalhatanya(date, here));
}

hdate getchatzosgra(hdate *date, location *here)
{
	return calcchatzos(getsunrise(date, here), getsunset(date, here));
}

hdate calcminchagedola(hdate startday, hdate endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, shaahzmanis * 6.5);
}

hdate getminchagedolabaalhatanya(hdate *date, location *here)
{
	return calcminchagedola(getsunrisebaalhatanya(date, here), getsunsetbaalhatanya(date, here));
}

hdate getminchagedolagra(hdate *date, location *here)
{
	return calcminchagedola(getsunrise(date, here), getsunset(date, here));
}

hdate getminchagedolamga(hdate *date, location *here)
{
	return calcminchagedola(getalos72(date, here), gettzais72(date, here));
}

hdate calcminchagedola30min(hdate startday, hdate endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, (shaahzmanis * 6) + 1800000);
}

hdate calcminchagedolagreater30min(hdate startday, hdate endday)
{
	return ((calcshaahzmanis(startday, endday)*0.5) >= 1800000) ? calcminchagedola(startday, endday) : calcminchagedola30min(startday, endday);
}

hdate getminchagedolabaalhatanyag30m(hdate *date, location *here)
{
	return calcminchagedolagreater30min(getsunrisebaalhatanya(date, here), getsunsetbaalhatanya(date, here));
}

hdate getminchagedolagrag30m(hdate *date, location *here)
{
	return calcminchagedolagreater30min(getsunrise(date, here), getsunset(date, here));
}

hdate getminchagedolamgag30m(hdate *date, location *here)
{
	return calcminchagedolagreater30min(getalos72(date, here), gettzais72(date, here));
}

hdate calcminchaketana(hdate startday, hdate endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, shaahzmanis * 9.5);
}

hdate getminchaketanabaalhatanya(hdate *date, location *here)
{
	return calcminchaketana(getsunrisebaalhatanya(date, here), getsunsetbaalhatanya(date, here));
}

hdate getminchaketanagra(hdate *date, location *here)
{
	return calcminchaketana(getsunrise(date, here), getsunset(date, here));
}

hdate getminchaketanamga(hdate *date, location *here)
{
	return calcminchaketana(getalos72(date, here), gettzais72(date, here));
}

hdate calcplag(hdate startday, hdate endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, shaahzmanis * 10.75);
}

hdate getplagbaalhatanya(hdate *date, location *here)
{
	return calcplag(getsunrisebaalhatanya(date, here), getsunsetbaalhatanya(date, here));
}

hdate getplaggra(hdate *date, location *here)
{
	return calcplag(getsunrise(date, here), getsunset(date, here));
}

hdate getplagmga(hdate *date, location *here)
{
	return calcplag(getalos72(date, here), gettzais72(date, here));
}

hdate getcandlelighting(hdate *date, location *here)
{
	return calctimeoffset(calcsunset(date, here, GEOMETRIC_ZENITH, 0), -MINUTES18);
}

hdate getsunset(hdate *date, location *here)
{
	return calcsunset(date, here, GEOMETRIC_ZENITH, 0);
}

hdate getsunsetbaalhatanya(hdate *date, location *here)
{
	return calcsunset(date, here, ZENITH_AMITIS, 0);
}

hdate getelevationsunset(hdate *date, location *here)
{
	return calcsunset(date, here, GEOMETRIC_ZENITH, 1);
}

hdate gettzaisbaalhatanya(hdate *date, location *here)
{
	return calcsunset(date, here, ZENITH_6_D, 1);
}

hdate gettzais8p5(hdate *date, location *here)
{
	return calcsunset(date, here, ZENITH_8_P_5, 1);
}

hdate gettzais72(hdate *date, location *here)
{
	return calctimeoffset(getsunset(date, here), MINUTES72);
}

long getshaahzmanisbaalhatanya(hdate *date, location *here)
{
	return calcshaahzmanis(getsunrisebaalhatanya(date, here), getsunsetbaalhatanya(date, here));
}

long getshaahzmanisgra(hdate *date, location *here)
{
	return calcshaahzmanis(getsunrise(date, here), getsunset(date, here));
}

long getshaahzmanismga(hdate *date, location *here)
{
	return calcshaahzmanis(getalos72(date, here), gettzais72(date, here));
}
