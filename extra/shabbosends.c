/****
Copyright (c) 2021 Y Paritcher
****/

#include <stdlib.h>
#include <stdio.h>
#include "hebrewcalendar.h"
#include "zmanim.h"
#include "hdateformat.h"

extern void hdatesetdoy(hdate *date);

void diffprint(long diff)
{
	int sec = diff % 60;
	int min = diff / 60;
	int hour = min / 60;
	if (hour)
	{
		min = min % 60;
		printf("%d:%d:%d\n", hour, min, sec);
	}
	else
	{
		printf("%d:%d\n", min, sec);
	}
}

int main(int argc, char *argv[])
{
	location here = {.latitude = 40.66896, .longitude = -73.94284, .elevation = 34};
	float timezone = -4.0;
	long diff = 0;
	int ystart = 5660;
	int yend = 5860;
	char fdate[32] = {"\0"};

	if ( argc != 1 )
	{
		if ( argc != 6 )
		{
			printf("usage: year year latitude longitude timezone\n       5660 5860 40.66896 -73.94284 -4.0\n");
			return 1;
		}
		if ( atoi(argv[1]) )
		{
			ystart = atoi(argv[1]);
		}
		else
		{
			printf("%s: is not a valid year\n", argv[1]);
			return 1;
		}
		if ( atoi(argv[2]) )
		{
			yend = atoi(argv[2]);
		}
		else
		{
			printf("%s: is not a valid year\n", argv[2]);
			return 1;
		}
		if ( -90 < atof(argv[3]) && atof(argv[3]) < 90 )
		{
			here.latitude = atof(argv[3]);
		}
		else
		{
			printf("Latitude must be between -90 and 90!\n");
			return 1;
		}
		if ( -180 < atof(argv[4]) && atof(argv[4]) < 180)
		{
			here.longitude = atof(argv[4]);
		}
		else
		{
			printf("Longitude must be between -180 and 180!\n");
			return 1;
		}
		if( -13 < atof(argv[5]) && atof(argv[5]) < 15 )
		{
			timezone = atof(argv[5]);
		}
		else
		{
			printf("%s: is not a valid timezone\n", argv[6]);
			return 1;
		}
	}
	long int offset = (long int) 3600 * timezone;
	if (ystart == yend) {printf("Years must be different\n"); return 1;}
	int increment = ystart < yend ? 1 : -1 ;
	
	hdate hebrewDate = {ystart, 7, 1, 9, 0, 0, 0, 0, 0, offset, 0, 0};
	hdatesetdoy(&hebrewDate);
	for(; hebrewDate.year != yend; hdateaddday(&hebrewDate, increment))
	{
		hdate sunset = getsunset(hebrewDate, here);
		hdate tzais = gettzais8p5(hebrewDate, here);
		long st = (((((sunset.hour * 60) + sunset.min) * 60) + sunset.sec) *1000) + sunset.msec;
		long tz = (((((tzais.hour * 60) + tzais.min) * 60) + tzais.sec) *1000) + tzais.msec;
		long ldiff = (tz - st) / 1000;
		if(ldiff >= diff)
		{
			diff = ldiff;
			hdateformat(fdate, 32, hebrewDate);
			printf("%s: ", fdate);
			diffprint(diff);
		}
	}
	diffprint(diff);
}
