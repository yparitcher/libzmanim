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

/************
Implementation of sunrise and sunset methods to calculate astronomical times based on the NOAA algorithm.
This calculator is based on equations from http://www.srrb.noaa.gov/highlights/sunrise/sunrise.html and
https://github.com/KosherJava/zmanim/blob/master/src/net/sourceforge/zmanim/util/NOAACalculator.java
************/

#include <time.h>
#include "util.h"
#include "zmanim.h"
#include "NOAAcalculator.h"
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

double calcTimeJulianCent(double jd)
{
	double jcent = (jd - 2451545.0)/36525.0;
	return jcent;
}

double calcJDFromJulianCent(double jcent)
{
	double JD = jcent * 36525.0 + 2451545.0;
	return JD;
}

double calcGeomMeanLongSun(double jcent)
{
	double gmls = 280.46646 + jcent * (36000.76983 + 0.0003032 * jcent);
	while(gmls > 360.0)
	{
		gmls -= 360.0;
	}
	while(gmls < 0.0)
	{
		gmls += 360.0;
	}
	return gmls;
}

double calcGeomMeanAnomalySun(double jcent)
{
	double gmas = 357.52911 + jcent * (35999.05029 - 0.0001537 * jcent);
	return gmas;
}

double calcEccentricityEarthOrbit(double jcent)
{
	double eeo = 0.016708634 - jcent * (0.000042037 + 0.0000001267 * jcent);
	return eeo;
}

double calcSunEqOfCenter(double jcent)
{
	double m = calcGeomMeanAnomalySun(jcent);

	double mrad = degToRad(m);
	double sinm = sin(mrad);
	double sin2m = sin(mrad+mrad);
	double sin3m = sin(mrad+mrad+mrad);

	double seoc = sinm * (1.914602 - jcent * (0.004817 + 0.000014 * jcent)) + sin2m * (0.019993 - 0.000101 * jcent) + sin3m * 0.000289;
	return seoc;
}

double calcSunTrueLong(double jcent)
{
	double gmls = calcGeomMeanLongSun(jcent);
	double seoc = calcSunEqOfCenter(jcent);

	double stl = gmls + seoc;
	return stl;
}

double calcSunApparentLong(double jcent)
{
	double stl = calcSunTrueLong(jcent);

	double omega = 125.04 - 1934.136 * jcent;
	double sal = stl - 0.00569 - 0.00478 * sin(degToRad(omega));
	return sal;
}

double calcMeanObliquityOfEcliptic(double jcent)
{
	double seconds = 21.448 - jcent*(46.8150 + jcent*(0.00059 - jcent*(0.001813)));
	double mooe = 23.0 + (26.0 + (seconds/60.0))/60.0;
	return mooe;
}

double calcObliquityCorrection(double jcent)
{
	double mooe = calcMeanObliquityOfEcliptic(jcent);

	double omega = 125.04 - 1934.136 * jcent;
	double oc = mooe + 0.00256 * cos(degToRad(omega));
	return oc;
}

double calcSunDeclination(double jcent)
{
	double oc = calcObliquityCorrection(jcent);
	double sal = calcSunApparentLong(jcent);

	double sint = sin(degToRad(oc)) * sin(degToRad(sal));
	double sd = radToDeg(asin(sint));
	return sd;
}

double calcEquationOfTime(double jcent)
{
	double oc = calcObliquityCorrection(jcent);
	double gmls = calcGeomMeanLongSun(jcent);
	double eeo = calcEccentricityEarthOrbit(jcent);
	double gmas = calcGeomMeanAnomalySun(jcent);

	double y = tan(degToRad(oc)/2.0);
	y *= y;

	double sin2gmls = sin(2.0 * degToRad(gmls));
	double singmas   = sin(degToRad(gmas));
	double cos2gmls = cos(2.0 * degToRad(gmls));
	double sin4gmls = sin(4.0 * degToRad(gmls));
	double sin2gmas  = sin(2.0 * degToRad(gmas));

	double Etime = y * sin2gmls - 2.0 * eeo * singmas + 4.0 * eeo * y * singmas * cos2gmls
			- 0.5 * y * y * sin4gmls - 1.25 * eeo * eeo * sin2gmas;

	return radToDeg(Etime)*4.0;
}

double calcHourAngleSunrise(double lat, double solarDec, double zenith)
{
	double latRad = degToRad(lat);
	double sdRad  = degToRad(solarDec);

	double HA = (acos(cos(degToRad(zenith))/(cos(latRad)*cos(sdRad))-tan(latRad) * tan(sdRad)));

	return HA;
}

double calcHourAngleSunset(double lat, double solarDec, double zenith)
{
	double latRad = degToRad(lat);
	double sdRad  = degToRad(solarDec);

	double HA = (acos(cos(degToRad(zenith))/(cos(latRad)*cos(sdRad))-tan(latRad) * tan(sdRad)));

	return -HA;
}

double calcSolNoonUTC(double jcent, double longitude)
{
	double tnoon = calcTimeJulianCent(calcJDFromJulianCent(jcent) + longitude/360.0);
	double eqTime = calcEquationOfTime(tnoon);
	double solNoonUTC = 720 + (longitude * 4) - eqTime;

	double newt = calcTimeJulianCent(calcJDFromJulianCent(jcent) -0.5 + solNoonUTC/1440.0);

	eqTime = calcEquationOfTime(newt);
	solNoonUTC = 720 + (longitude * 4) - eqTime;

	return solNoonUTC;
}

double calcSunriseUTC(double JD, double latitude, double longitude, double zenith)
{
	double jcent = calcTimeJulianCent(JD);

	double noonmin = calcSolNoonUTC(jcent, longitude);
	double tnoon = calcTimeJulianCent (JD+noonmin/1440.0);

	double eqTime = calcEquationOfTime(tnoon);
	double solarDec = calcSunDeclination(tnoon);
	double hourAngle = calcHourAngleSunrise(latitude, solarDec, zenith);

	double delta = longitude - radToDeg(hourAngle);
	double timeDiff = 4 * delta;
	double timeUTC = 720 + timeDiff - eqTime;

	double newt = calcTimeJulianCent(calcJDFromJulianCent(jcent) + timeUTC/1440.0);
	eqTime = calcEquationOfTime(newt);
	solarDec = calcSunDeclination(newt);
	hourAngle = calcHourAngleSunrise(latitude, solarDec, zenith);
	delta = longitude - radToDeg(hourAngle);
	timeDiff = 4 * delta;
	timeUTC = 720 + timeDiff - eqTime;

	return timeUTC;
}

double calcSunsetUTC(double JD, double latitude, double longitude, double zenith)
{
	double jcent = calcTimeJulianCent(JD);

	double noonmin = calcSolNoonUTC(jcent, longitude);
	double tnoon = calcTimeJulianCent (JD+noonmin/1440.0);

	double eqTime = calcEquationOfTime(tnoon);
	double solarDec = calcSunDeclination(tnoon);
	double hourAngle = calcHourAngleSunset(latitude, solarDec, zenith);

	double delta = longitude - radToDeg(hourAngle);
	double timeDiff = 4 * delta;
	double timeUTC = 720 + timeDiff - eqTime;

	double newt = calcTimeJulianCent(calcJDFromJulianCent(jcent) + timeUTC/1440.0);
	eqTime = calcEquationOfTime(newt);
	solarDec = calcSunDeclination(newt);
	hourAngle = calcHourAngleSunset(latitude, solarDec, zenith);

	delta = longitude - radToDeg(hourAngle);
	timeDiff = 4 * delta;
	timeUTC = 720 + timeDiff - eqTime;

	return timeUTC;
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

double getUTCSunrise(double JD, location *here, double zenith, unsigned int adjustForElevation)
{
	double elevation = adjustForElevation ? here->elevation : 0;
	double adjustedZenith = adjustZenith(zenith, elevation);

	double sunrise = calcSunriseUTC(JD, here->latitude, -here->longitude, adjustedZenith);
	sunrise = sunrise / 60;

	while (sunrise < 0.0)
	{
		sunrise += 24.0;
	}
	while (sunrise >= 24.0)
	{
		sunrise -= 24.0;
	}
	return sunrise;
}

double getUTCSunset(double JD, location *here, double zenith, unsigned int adjustForElevation)
{
	double elevation = adjustForElevation ? here->elevation : 0;
	double adjustedZenith = adjustZenith(zenith, elevation);

	double sunset = calcSunsetUTC(JD, here->latitude, -here->longitude, adjustedZenith);
	sunset = sunset / 60;

	while (sunset < 0.0)
	{
		sunset += 24.0;
	}
	while (sunset >= 24.0)
	{
		sunset -= 24.0;
	}
	return sunset;
}
