#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "hebrewcalendar.h"
#include "zmanim.h"
#include "hdateformat.h"
#include "shuir.h"

extern double calcSolNoonUTC(double jcent, double longitude);

double getUTCNoon(double JD, location here)
{

	double noon = calcSolNoonUTC(JD, -here.longitude);
	noon = noon / 60;

	while (noon < 0.0)
	{
		noon += 24.0;
	}
	while (noon >= 24.0)
	{
		noon -= 24.0;
	}
	return noon;
}

hdate getDateFromNoon(hdate current, double time)
{
	hdate result = {0};
	if (isnan(time)) {
		return result;
	}
	//int adjustment = getAntimeridianAdjustment(current, here);
	double calculatedTime = time;
	result.year = current.year;
	result.EY = current.EY;
	result.offset = current.offset;
	result.month = current.month;
	result.day = current.day;
	//if (adjustment){hdateaddday(&result, adjustment);}

	int hours = (int)calculatedTime;
	calculatedTime -= hours;
	int minutes = (int)(calculatedTime *= 60);
	calculatedTime -= minutes;
	int seconds = (int)(calculatedTime *= 60);
	calculatedTime -= seconds;
	int miliseconds = (int)(calculatedTime * 1000);
/*	int localTimeHours = (int)here.longitude / 15;
	if (isSunrise && localTimeHours + hours > 18) {
		hdateaddday(&result, -1);
	} else if (!isSunrise && localTimeHours + hours < 6) {
		hdateaddday(&result, +1);
	}
*/
	result.hour = hours;
	result.min = minutes;
	result.sec = seconds;
	result.msec = miliseconds;
	hdateaddsecond(&result, current.offset);
	return result;
}

hdate calcnoon(hdate date, location here)
{
	double noon = getUTCNoon(hdatejulian(date), here);
	return getDateFromNoon(date, noon);
}

char* formattime(hdate date)
{
	static char final[32];
	final[0] = '\0';
	time_t time = hdatetime_t(date);
	struct tm *tm = localtime(&time);
	strftime(final, 13, "%I:%M %p %Z", tm);
	return final;
}

int main(int argc, char *argv[])
{
	int limit = 1461;
	location here ={.latitude = 40.66896, .longitude = -73.94284, .elevation = 34};
	float timezone = -5.0;
	time_t now = time(NULL);
	struct tm *pltm = localtime(&now);
	struct tm ltm = *pltm;
	_Bool ey = 0;
	
	if ( argc != 1 )
	{
		if ( argc != 9 )
		{
			printf("usage: year month day latitude longitude timezone Eretz_Yisroel cycles\n       2018 01 01 40.66896 -73.94284 -4.0 0 1\n");
			return 1;
		}
		if ( atoi(argv[1]) )
		{
			ltm.tm_year = (atoi(argv[1]) - 1900 );
		}
		else
		{
			printf("%s: is not a valid year\n", argv[1]);
			return 1;
		}
		if ( atoi(argv[2]) )
		{
			ltm.tm_mon = (atoi(argv[2]) -1);
		}
		else
		{
			printf("%s: is not a valid month\n", argv[2]);
			return 1;
		}
		if ( atoi(argv[3]) )
		{
			ltm.tm_mday = atoi(argv[3]);
		}
		else
		{
			printf("%s: is not a valid year\n", argv[3]);
			return 1;
		}
		now = mktime(&ltm);
		if ( -90 < atof(argv[4]) && atof(argv[4]) < 90 )
		{
			here.latitude = atof(argv[4]);
		}
		else
		{
			printf("Latitude must be between -90 and 90!\n");
			return 1;
		}
		if ( -180 < atof(argv[5]) && atof(argv[5]) < 180)
		{
			here.longitude = atof(argv[5]);
		}
		else
		{
			printf("Longitude must be between -180 and 180!\n");
			return 1;
		}
		if( -13 < atof(argv[6]) && atof(argv[6]) < 15 )
		{
			timezone = atof(argv[6]);
		}
		else
		{
			printf("%s: is not a valid timezone\n", argv[6]);
			return 1;
		}
		if( -1 < atof(argv[7]) && atof(argv[7]) < 2 )
		{
				ey = atof(argv[7]);
		}
		else
		{
			printf("%s: is not a valid boolean, use 0 or 1\n", argv[7]);
			return 1;
		}
		if( 0 < atof(argv[8]) )
		{
				limit *= atof(argv[8]);
		}
		else
		{
			printf("%s: is not a valid cycle, use 1 or more\n", argv[8]);
			return 1;
		}
	}

	long int offset = (long int) 3600 * timezone;

	hdate hebrewDate = convertDate(ltm);
	hebrewDate.offset=offset;
	setEY(&hebrewDate, ey);

//	unsigned long int res[1461];
	unsigned long long int total = 0;
	for (int i = 0; i < limit; hdateaddday(&hebrewDate, 1),i++)
	{
		hdate ctz = calcnoon(hebrewDate, here);
//printf("%s\n", formattime(hebrewDate));
		//hdate ctz = getchatzosbaalhatanya(hebrewDate, here);
		unsigned long int tme = (((((ctz.hour*60)+ctz.min)*60)+ctz.sec)*1000)+ctz.msec;
//		res[i] = tme;
		total += tme;
	}

	unsigned long long int final = total/limit;
	unsigned long int msec = final%1000;
	unsigned long int sec = final/1000;
	unsigned long int min = sec/60;
	unsigned long int hour = min/60;
	min = min%60;
	sec = sec%60;
	printf("%ld:%ld:%ld.%ld\n", hour, min, sec, msec);

	return 0;
}
