/****
Copyright (c) 2018 Y Paritcher
****/

#include <stdio.h>
#include <time.h>
#include "hebrewcalendar.h"
#include "zmanim.h"

hdate tstart = {0};
hdate tend = {0};
long long int daylength = 0;
_Bool meridian;

hdate getNow()
{
	struct timespec now;
	clock_gettime(CLOCK_REALTIME, &now);
	struct tm *pltm = localtime(&now.tv_sec);
	hdate hebrewDate = convertDate(*pltm);
	hebrewDate.offset = pltm->tm_gmtoff;
	hebrewDate.msec = now.tv_nsec / 1000000;
	setEY(&hebrewDate, 0);
	return hebrewDate;
}

long getdaylength(hdate startday, hdate endday)
{
	long int start = HebrewCalendarElapsedDays(startday.year)+(startday.dayofyear-1);
	long int end = HebrewCalendarElapsedDays(endday.year)+(endday.dayofyear-1);
	long int diff = end - start;
	diff = (diff * 24) + (endday.hour - startday.hour);
	diff = (diff * 60) + (endday.min - startday.min);
	diff = (diff * 60) + (endday.sec - startday.sec);
	diff = (diff * 1000) + (endday.msec - startday.msec);
	return diff * 1000000;
}

int newDay(hdate now, location here)
{
	int ret;
	hdate date = now;
	hdate rise = getsunrisebaalhatanya(date, here);
	hdate set = getsunsetbaalhatanya(date, here);
	if (hdatecompare(rise, date) == -1) {
		tend = rise;
		hdateaddday(&date, -1);
		tstart = getsunsetbaalhatanya(date, here);
		meridian = 1;
		ret = -1;
	} else if (hdatecompare(set, date) == -1) {
		tstart = rise;
		tend = set;
		meridian = 1;
		ret = 0;
	} else {
		tstart = set;
		hdateaddday(&date, 1);
		tend = getsunrisebaalhatanya(date, here);
		meridian = 0;
		ret = 1;
	}
	daylength = getdaylength(tstart, tend) / 43200;
	return ret;
}

void zmprint(long long int elapsed, long long int daylength)
{
	long int zm = elapsed / daylength;
	zm += (6 * 3600000);
	int hour = zm/3600000;
	zm = zm%3600000;
	int min = zm/60000;
	zm = zm%60000;
	int sec = zm/1000;
	int msec = zm%1000;
	if (hour > 12){hour -= 12;}
	printf("%02d:%02d:%02d %03d\n", hour, min, sec, msec);
}

void sleeper(long long int elapsed, long long int length)
{
	long int remain = length - ((elapsed / 1000) % length);

	struct timespec sleeptime;
	sleeptime.tv_sec = remain / 1000000000;
	sleeptime.tv_nsec = (((remain / 1000000) + 1) % 1000) * 1000000;
	nanosleep(&sleeptime, NULL);
}


void loopsimple(location here)
{
	hdate now = getNow();
	if (hdatecompare(tend, now) >= 0) {
		newDay(now, here);
	}
	long long int elapsed = getdaylength(tstart, now) * 1000;
	zmprint(elapsed, daylength);
	sleeper(elapsed, daylength);
}

void loopmin(location here)
{
	hdate now = getNow();
	if (hdatecompare(tend, now) >= 0) {
		newDay(now, here);
	}
	long long int elapsed = getdaylength(tstart, now) * 1000;
	zmprint(elapsed, daylength);
	sleeper(elapsed, daylength*60);
}

// int argc, char *argv[]
/*
	struct timespec rez;
	clock_getres(CLOCK_REALTIME, &rez);
	printf("%-20.20s%ld:%09ld\n", "resolution: ",  rez.tv_sec, rez.tv_nsec);
*/
int main()
{
	location here ={.latitude = 40.66896, .longitude = -73.94284, .elevation = 34};

	//while(1){loopmin(here);}
	while(1){loopsimple(here);}
	
	return 0;
}
