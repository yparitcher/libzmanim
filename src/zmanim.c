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
	if ( -86400000 < offset && offset < 86400000 )
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
