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
#include "NOAAcalculator.h"
#include "calculatorutil.h"

settings setup;
tmz utmz;
location ulocation;
hdate invalid = {0};

int settime(time_t *time)
{
	utmz.tm = *localtime(time);
	setup.bf.tm |= 1;
	return 0;
}

int setoffset(double offset)
{
	if ( -46800000 < offset && offset < 54000000 )
	{
		utmz.tmz_gmtoff = offset;
		setup.bf.of |= 1;
		return 0;
	}
	return 2;
}

int setlatitude(double latitude)
{
	if ( -90 < latitude && latitude < 90 )
	{
		ulocation.latitude = latitude;
		setup.bf.la |= 1;
		return 0;
	}
	return 4;
}

int setlongitude(double longitude)
{
	if ( -180 < longitude && longitude < 180 )
	{
		ulocation.longitude = longitude;
		setup.bf.lo |= 1;
		return 0;
	}
	return 8;
}

int setelevation(double elevation)
{
	if ( -5000 < elevation && elevation < 5000 )
	{
		ulocation.elevation = elevation;
		setup.bf.el |= 1;
		return 0;
	}
	return 16;
}

time_t gettime()
{
	return mktime(&(utmz.tm));
}

double getoffset()
{
	return utmz.tmz_gmtoff;
}

double getlatitude()
{
	return ulocation.latitude;
}

double getlongitude()
{
	return ulocation.longitude;
}

double getelevation()
{
	return ulocation.elevation;
}

int setall(time_t *time, double offset, double latitude, double longitude, double elevation)
{
	int ti = settime(time);
	int of = setoffset(offset);
	int la = setlatitude(latitude);
	int lo = setlongitude(longitude);
	int el = setelevation(elevation);
	return (ti + of + la + lo + el);
}

unsigned int  checksetup()
{
	return ((unsigned int) FULLSETUP & setup.s);
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

hdate getalos(hdate *date)
{
	return calcsunrise(date, &ulocation, ZENITH_16_P_1, 0);
}

hdate getalosbaalhatanya(hdate *date)
{
	return calcsunrise(date, &ulocation, ZENITH_16_P_9, 0);
}

hdate getalos26degrees(hdate *date)
{
	return calcsunrise(date, &ulocation, ZENITH_26_D, 0);
}

hdate getalos19p8degrees(hdate *date)
{
	return calcsunrise(date, &ulocation, ZENITH_19_P_8, 0);
}

hdate getalos18degrees(hdate *date)
{
	return calcsunrise(date, &ulocation, ZENITH_18_D, 0);
}

hdate getalos120(hdate *date)
{
	return calctimeoffset(getsunrise(date), -MINUTES120);
}

hdate getalos120zmanis(hdate *date)
{
	long shaahzmanis = getshaahzmanisgra(date);
	if (shaahzmanis == 0) return invalid;
	return calctimeoffset(getsunrise(date), shaahzmanis * -2);
}

hdate getalos96(hdate *date)
{
	return calctimeoffset(getsunrise(date), -MINUTES96);
}

hdate getalos96zmanis(hdate *date)
{
	long shaahzmanis = getshaahzmanisgra(date);
	if (shaahzmanis == 0) return invalid;
	return calctimeoffset(getsunrise(date), shaahzmanis * -1.6);
}

hdate getalos90(hdate *date)
{
	return calctimeoffset(getsunrise(date), -MINUTES90);
}

hdate getalos90zmanis(hdate *date)
{
	long shaahzmanis = getshaahzmanisgra(date);
	if (shaahzmanis == 0) return invalid;
	return calctimeoffset(getsunrise(date), shaahzmanis * -1.5);
}

hdate getalos72(hdate *date)
{
	return calctimeoffset(getsunrise(date), -MINUTES72);
}

hdate getalos72zmanis(hdate *date)
{
	long shaahzmanis = getshaahzmanisgra(date);
	if (shaahzmanis == 0) return invalid;
	return calctimeoffset(getsunrise(date), shaahzmanis * -1.2);
}

hdate getalos60(hdate *date)
{
	return calctimeoffset(getsunrise(date), -MINUTES60);
}

hdate getmisheyakir11p5degrees(hdate *date)
{
	return calcsunrise(date, &ulocation, ZENITH_11_P_5, 0);
}

hdate getmisheyakir11degrees(hdate *date)
{
	return calcsunrise(date, &ulocation, ZENITH_11_D, 0);
}

hdate getmisheyakir10p2degrees(hdate *date)
{
	return calcsunrise(date, &ulocation, ZENITH_10_P_2, 0);
}

hdate getsunrise(hdate *date)
{
	return calcsunrise(date, &ulocation, GEOMETRIC_ZENITH, 0);
}

hdate getsunrisebaalhatanya(hdate *date)
{
	return calcsunrise(date, &ulocation, ZENITH_AMITIS, 0);
}

hdate getelevationsunrise(hdate *date)
{
	return calcsunrise(date, &ulocation, GEOMETRIC_ZENITH, 1);
}

hdate calcshma(hdate startday, hdate endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, shaahzmanis * 3);
}

hdate getshmabaalhatanya(hdate *date)
{
	return calcshma(getsunrisebaalhatanya(date), getsunsetbaalhatanya(date));
}

hdate getshmagra(hdate *date)
{
	return calcshma(getsunrise(date), getsunset(date));
}

hdate getshmamga(hdate *date)
{
	return calcshma(getalos72(date), gettzais72(date));
}

hdate calctefila(hdate startday, hdate endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, shaahzmanis * 4);
}

hdate gettefilabaalhatanya(hdate *date)
{
	return calctefila(getsunrisebaalhatanya(date), getsunsetbaalhatanya(date));
}

hdate gettefilagra(hdate *date)
{
	return calctefila(getsunrise(date), getsunset(date));
}

hdate gettefilamga(hdate *date)
{
	return calctefila(getalos72(date), gettzais72(date));
}

hdate getachilaschometzbaalhatanya(hdate *date)
{
	return calctefila(getsunrisebaalhatanya(date), getsunsetbaalhatanya(date));
}

hdate getachilaschometzgra(hdate *date)
{
	return calctefila(getsunrise(date), getsunset(date));
}

hdate getachilaschometzmga(hdate *date)
{
	return calctefila(getalos72(date), gettzais72(date));
}

hdate calcbiurchometz(hdate startday, hdate endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, shaahzmanis * 5);
}

hdate getbiurchometzbaalhatanya(hdate *date)
{
	return calcbiurchometz(getsunrisebaalhatanya(date), getsunsetbaalhatanya(date));
}

hdate getbiurchometzgra(hdate *date)
{
	return calcbiurchometz(getsunrise(date), getsunset(date));
}

hdate getbiurchometzmga(hdate *date)
{
	return calcbiurchometz(getalos72(date), gettzais72(date));
}

hdate calcchatzos(hdate startday, hdate endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, shaahzmanis * 6);
}

hdate getchatzosbaalhatanya(hdate *date)
{
	return calcchatzos(getsunrisebaalhatanya(date), getsunsetbaalhatanya(date));
}

hdate getchatzosgra(hdate *date)
{
	return calcchatzos(getsunrise(date), getsunset(date));
}

hdate calcminchagedola(hdate startday, hdate endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, shaahzmanis * 6.5);
}

hdate getminchagedolabaalhatanya(hdate *date)
{
	return calcminchagedola(getsunrisebaalhatanya(date), getsunsetbaalhatanya(date));
}

hdate getminchagedolagra(hdate *date)
{
	return calcminchagedola(getsunrise(date), getsunset(date));
}

hdate getminchagedolamga(hdate *date)
{
	return calcminchagedola(getalos72(date), gettzais72(date));
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

hdate getminchagedolabaalhatanyag30m(hdate *date)
{
	return calcminchagedolagreater30min(getsunrisebaalhatanya(date), getsunsetbaalhatanya(date));
}

hdate getminchagedolagrag30m(hdate *date)
{
	return calcminchagedolagreater30min(getsunrise(date), getsunset(date));
}

hdate getminchagedolamgag30m(hdate *date)
{
	return calcminchagedolagreater30min(getalos72(date), gettzais72(date));
}

hdate calcminchaketana(hdate startday, hdate endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, shaahzmanis * 9.5);
}

hdate getminchaketanabaalhatanya(hdate *date)
{
	return calcminchaketana(getsunrisebaalhatanya(date), getsunsetbaalhatanya(date));
}

hdate getminchaketanagra(hdate *date)
{
	return calcminchaketana(getsunrise(date), getsunset(date));
}

hdate getminchaketanamga(hdate *date)
{
	return calcminchaketana(getalos72(date), gettzais72(date));
}

hdate calcplag(hdate startday, hdate endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, shaahzmanis * 10.75);
}

hdate getplagbaalhatanya(hdate *date)
{
	return calcplag(getsunrisebaalhatanya(date), getsunsetbaalhatanya(date));
}

hdate getplaggra(hdate *date)
{
	return calcplag(getsunrise(date), getsunset(date));
}

hdate getplagmga(hdate *date)
{
	return calcplag(getalos72(date), gettzais72(date));
}

hdate getcandlelighting(hdate *date)
{
	return calctimeoffset(calcsunset(date, &ulocation, GEOMETRIC_ZENITH, 0), -MINUTES18);
}

hdate getsunset(hdate *date)
{
	return calcsunset(date, &ulocation, GEOMETRIC_ZENITH, 0);
}

hdate getsunsetbaalhatanya(hdate *date)
{
	return calcsunset(date, &ulocation, ZENITH_AMITIS, 0);
}

hdate getelevationsunset(hdate *date)
{
	return calcsunset(date, &ulocation, GEOMETRIC_ZENITH, 1);
}

hdate gettzaisbaalhatanya(hdate *date)
{
	return calcsunset(date, &ulocation, ZENITH_6_D, 1);
}

hdate gettzais8p5(hdate *date)
{
	return calcsunset(date, &ulocation, ZENITH_8_P_5, 1);
}

hdate gettzais72(hdate *date)
{
	return calctimeoffset(getsunset(date), MINUTES72);
}

long getshaahzmanisbaalhatanya(hdate *date)
{
	return calcshaahzmanis(getsunrisebaalhatanya(date), getsunsetbaalhatanya(date));
}

long getshaahzmanisgra(hdate *date)
{
	return calcshaahzmanis(getsunrise(date), getsunset(date));
}

long getshaahzmanismga(hdate *date)
{
	return calcshaahzmanis(getalos72(date), gettzais72(date));
}
