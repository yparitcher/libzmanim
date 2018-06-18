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
#include "zmanim.h"
#include "NOAAcalculator.h"
#include "calculatorutil.h"

settings setup;
tmz utmz;
location ulocation;

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
ltime calcsunrise(tmz *date, location *here, double zenith, unsigned int adjustForElevation)
{
	if (checksetup() != FULLSETUP) return 0;
	double sunrise = getUTCSunrise(&(date->tm), here, zenith, adjustForElevation);
	return getDateFromTime(date, sunrise, here, 1);
}

ltime calcsunset(tmz *date, location *here, double zenith, unsigned int adjustForElevation)
{
	if (checksetup() != FULLSETUP) return 0;
	double sunset = getUTCSunset(&(date->tm), here, zenith, adjustForElevation);
	return getDateFromTime(date, sunset, here, 0);
}

long calcshaahzmanis(ltime startday, ltime endday)
{
	if (startday == 0 || endday == 0) return 0;
	return (endday - startday) / 12;
}

ltime calctimeoffset(ltime time, long offset)
{
	if (time == 0 || offset == 0) return 0;
	return time + offset;
}

ltime getalos()
{
	return calcsunrise(&utmz, &ulocation, ZENITH_16_P_1, 0);
}

ltime getalosbaalhatanya()
{
	return calcsunrise(&utmz, &ulocation, ZENITH_16_P_9, 0);
}

ltime getalos26degrees()
{
	return calcsunrise(&utmz, &ulocation, ZENITH_26_D, 0);
}

ltime getalos19p8degrees()
{
	return calcsunrise(&utmz, &ulocation, ZENITH_19_P_8, 0);
}

ltime getalos18degrees()
{
	return calcsunrise(&utmz, &ulocation, ZENITH_18_D, 0);
}

ltime getalos120()
{
	return calctimeoffset(getsunrise(), -MINUTES120);
}

ltime getalos120zmanis()
{
	long shaahzmanis = getshaahzmanisgra();
	if (shaahzmanis == 0) return 0;
	return calctimeoffset(getsunrise(), shaahzmanis * -2);
}

ltime getalos96()
{
	return calctimeoffset(getsunrise(), -MINUTES96);
}

ltime getalos96zmanis()
{
	long shaahzmanis = getshaahzmanisgra();
	if (shaahzmanis == 0) return 0;
	return calctimeoffset(getsunrise(), shaahzmanis * -1.6);
}

ltime getalos90()
{
	return calctimeoffset(getsunrise(), -MINUTES90);
}

ltime getalos90zmanis()
{
	long shaahzmanis = getshaahzmanisgra();
	if (shaahzmanis == 0) return 0;
	return calctimeoffset(getsunrise(), shaahzmanis * -1.5);
}

ltime getalos72()
{
	return calctimeoffset(getsunrise(), -MINUTES72);
}

ltime getalos72zmanis()
{
	long shaahzmanis = getshaahzmanisgra();
	if (shaahzmanis == 0) return 0;
	return calctimeoffset(getsunrise(), shaahzmanis * -1.2);
}

ltime getalos60()
{
	return calctimeoffset(getsunrise(), -MINUTES60);
}

ltime getmisheyakir11p5degrees()
{
	return calcsunrise(&utmz, &ulocation, ZENITH_11_P_5, 0);
}

ltime getmisheyakir11degrees()
{
	return calcsunrise(&utmz, &ulocation, ZENITH_11_D, 0);
}

ltime getmisheyakir10p2degrees()
{
	return calcsunrise(&utmz, &ulocation, ZENITH_10_P_2, 0);
}

ltime getsunrise()
{
	return calcsunrise(&utmz, &ulocation, GEOMETRIC_ZENITH, 0);
}

ltime getsunrisebaalhatanya()
{
	return calcsunrise(&utmz, &ulocation, ZENITH_AMITIS, 0);
}

ltime getelevationsunrise()
{
	return calcsunrise(&utmz, &ulocation, GEOMETRIC_ZENITH, 1);
}

ltime calcshma(ltime startday, ltime endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, shaahzmanis * 3);
}

ltime getshmabaalhatanya()
{
	return calcshma(getsunrisebaalhatanya(), getsunsetbaalhatanya());
}

ltime getshmagra()
{
	return calcshma(getsunrise(), getsunset());
}

ltime getshmamga()
{
	return calcshma(getalos72(), gettzais72());
}

ltime calctefila(ltime startday, ltime endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, shaahzmanis * 4);
}

ltime gettefilabaalhatanya()
{
	return calctefila(getsunrisebaalhatanya(), getsunsetbaalhatanya());
}

ltime gettefilagra()
{
	return calctefila(getsunrise(), getsunset());
}

ltime gettefilamga()
{
	return calctefila(getalos72(), gettzais72());
}

ltime getachilaschometzbaalhatanya()
{
	return calctefila(getsunrisebaalhatanya(), getsunsetbaalhatanya());
}

ltime getachilaschometzgra()
{
	return calctefila(getsunrise(), getsunset());
}

ltime getachilaschometzmga()
{
	return calctefila(getalos72(), gettzais72());
}

ltime calcbiurchometz(ltime startday, ltime endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, shaahzmanis * 5);
}

ltime getbiurchometzbaalhatanya()
{
	return calcbiurchometz(getsunrisebaalhatanya(), getsunsetbaalhatanya());
}

ltime getbiurchometzgra()
{
	return calcbiurchometz(getsunrise(), getsunset());
}

ltime getbiurchometzmga()
{
	return calcbiurchometz(getalos72(), gettzais72());
}

ltime calcchatzos(ltime startday, ltime endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, shaahzmanis * 6);
}

ltime getchatzosbaalhatanya()
{
	return calcchatzos(getsunrisebaalhatanya(), getsunsetbaalhatanya());
}

ltime getchatzosgra()
{
	return calcchatzos(getsunrise(), getsunset());
}

ltime calcminchagedola(ltime startday, ltime endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, shaahzmanis * 6.5);
}

ltime getminchagedolabaalhatanya()
{
	return calcminchagedola(getsunrisebaalhatanya(), getsunsetbaalhatanya());
}

ltime getminchagedolagra()
{
	return calcminchagedola(getsunrise(), getsunset());
}

ltime getminchagedolamga()
{
	return calcminchagedola(getalos72(), gettzais72());
}

ltime calcminchagedola30min(ltime startday, ltime endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, (shaahzmanis * 6) + 1800000);
}

ltime calcminchagedolagreater30min(ltime startday, ltime endday)
{
	ltime mg = calcminchagedola(startday, endday);
	ltime mg30 = calcminchagedola30min(startday, endday);
	return (mg >= mg30) ? mg : mg30;
}

ltime getminchagedolabaalhatanyag30m()
{
	return calcminchagedolagreater30min(getsunrisebaalhatanya(), getsunsetbaalhatanya());
}

ltime getminchagedolagrag30m()
{
	return calcminchagedolagreater30min(getsunrise(), getsunset());
}

ltime getminchagedolamgag30m()
{
	return calcminchagedolagreater30min(getalos72(), gettzais72());
}

ltime calcminchaketana(ltime startday, ltime endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, shaahzmanis * 9.5);
}

ltime getminchaketanabaalhatanya()
{
	return calcminchaketana(getsunrisebaalhatanya(), getsunsetbaalhatanya());
}

ltime getminchaketanagra()
{
	return calcminchaketana(getsunrise(), getsunset());
}

ltime getminchaketanamga()
{
	return calcminchaketana(getalos72(), gettzais72());
}

ltime calcplag(ltime startday, ltime endday)
{
	long shaahzmanis = calcshaahzmanis(startday, endday);
	return calctimeoffset(startday, shaahzmanis * 10.75);
}

ltime getplagbaalhatanya()
{
	return calcplag(getsunrisebaalhatanya(), getsunsetbaalhatanya());
}

ltime getplaggra()
{
	return calcplag(getsunrise(), getsunset());
}

ltime getplagmga()
{
	return calcplag(getalos72(), gettzais72());
}

ltime getcandlelighting()
{
	return calctimeoffset(calcsunset(&utmz, &ulocation, GEOMETRIC_ZENITH, 0), -MINUTES18);
}

ltime getsunset()
{
	return calcsunset(&utmz, &ulocation, GEOMETRIC_ZENITH, 0);
}

ltime getsunsetbaalhatanya()
{
	return calcsunset(&utmz, &ulocation, ZENITH_AMITIS, 0);
}

ltime getelevationsunset()
{
	return calcsunset(&utmz, &ulocation, GEOMETRIC_ZENITH, 1);
}

ltime gettzaisbaalhatanya()
{
	return calcsunset(&utmz, &ulocation, ZENITH_6_D, 1);
}

ltime gettzais8p5()
{
	return calcsunset(&utmz, &ulocation, ZENITH_8_P_5, 1);
}

ltime gettzais72()
{
	return calctimeoffset(getsunset(), MINUTES72);
}

long getshaahzmanisbaalhatanya()
{
	return calcshaahzmanis(getsunrisebaalhatanya(), getsunsetbaalhatanya());
}

long getshaahzmanisgra()
{
	return calcshaahzmanis(getsunrise(), getsunset());
}

long getshaahzmanismga()
{
	return calcshaahzmanis(getalos72(), gettzais72());
}
