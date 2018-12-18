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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "hebrewcalendar.h"
#include "zmanim.h"
#include "hdateformat.h"

char* formattime(hdate date)
{
	static char final[32];
	final[0] = '\0';
	time_t time = hdatetime_t(&date);
	struct tm *tm = localtime(&time);
	strftime(final, 13, "%I:%M %p %Z", tm);
	return final;
}

int main(int argc, char *argv[])
{
	location here ={.latitude = 40.66896, .longitude = -73.94284, .elevation = 34};
	float timezone = -4.0;
	time_t now = time(NULL);
	struct tm *pltm = localtime(&now);
	struct tm ltm = *pltm;
	_Bool ey = 0;

	if ( argc != 1 )
	{
		if ( argc != 8 )
		{
			printf("usage: year month day latitude longitude timezone Eretz_Yisroel\n       2018 01 01 40.66896 -73.94284 -4.0 0\n");
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
			printf("%s: is not a valid boolean, use 0 or 1\n", argv[6]);
			return 1;
		}
	}

	long int offset = (long int) 3600 * timezone;

	hdate hebrewDate = convertDate(&ltm);
	hebrewDate.offset=offset;
	setEY(&hebrewDate, ey);
	printf("%-15.15s%s\n", "", hdateformat(&hebrewDate));
	if (getyomtov(&hebrewDate))
	{
		printf("%-15.15s%s\n", "", yomtovformat(getyomtov(&hebrewDate)));
	}
	if (getroshchodesh(&hebrewDate))
	{
		printf("%-15.15s%s\n", "", yomtovformat(getroshchodesh(&hebrewDate)));
	}
	if (getshabbosmevorchim(&hebrewDate))
	{
		printf("%-15.15s%s\n", "", yomtovformat(getshabbosmevorchim(&hebrewDate)));
	}
	if (getparshah(&hebrewDate))
	{
		printf("%-15.15sפרשת %s\n", "", parshahformat(getparshah(&hebrewDate)));
	} else {
		hdate shabbos = hebrewDate;
		hdateaddday(&shabbos, (7-hebrewDate.wday));
		if (getparshah(&shabbos))
		{
			printf("%-15.15sפרשת %s\n", "", parshahformat(getparshah(&shabbos)));
		}
	}
	if (getmacharchodesh(&hebrewDate))
	{
		printf("%-15.15s%s\n", "", yomtovformat(getmacharchodesh(&hebrewDate)));
	}
	if (getspecialshabbos(&hebrewDate))
	{
		printf("%-15.15sפרשת %s\n", "", yomtovformat(getspecialshabbos(&hebrewDate)));
	}

	printf("%-20.20s%s\n", "alos: ", formattime(getalosbaalhatanya(&hebrewDate, &here)));
	printf("%-20.20s%s\n", "misheyakir: ", formattime(getmisheyakir10p2degrees(&hebrewDate, &here)));
	printf("%-20.20s%s\n", "sunrise: ", formattime(getsunrise(&hebrewDate, &here)));
	printf("%-20.20s%s\n", "shma: ", formattime(getshmabaalhatanya(&hebrewDate, &here)));
	printf("%-20.20s%s\n", "tefila: ", formattime(gettefilabaalhatanya(&hebrewDate, &here)));
	printf("%-20.20s%s\n", "chatzos: ", formattime(getchatzosbaalhatanya(&hebrewDate, &here)));
	printf("%-20.20s%s\n", "mincha gedola: ", formattime(getminchagedolabaalhatanya(&hebrewDate, &here)));
	printf("%-20.20s%s\n", "mincha ketana: ", formattime(getminchaketanabaalhatanya(&hebrewDate, &here)));
	printf("%-20.20s%s\n", "plag hamincha: ", formattime(getplagbaalhatanya(&hebrewDate, &here)));
	if (iscandlelighting(&hebrewDate) == 1)
	{
		printf("%-20.20s%s\n", "candle lighting: ", formattime(getcandlelighting(&hebrewDate, &here)));
	}
	printf("%-20.20s%s\n", "sunset: ", formattime(getsunset(&hebrewDate, &here)));
	if (iscandlelighting(&hebrewDate) == 2)
	{
		printf("%-20.20s%s\n", "candle lighting: ", formattime(gettzais8p5(&hebrewDate, &here)));
		printf("%-20.20s%s\n", "tzais: ", formattime(gettzais8p5(&hebrewDate, &here)));
	} else if (hebrewDate.wday == 7 || isassurbemelachah(&hebrewDate)){
		printf("%-20.20s%s\n", "shabbos ends: ", formattime(gettzais8p5(&hebrewDate, &here)));
	} else {
		printf("%-20.20s%s\n", "tzais: ", formattime(gettzaisbaalhatanya(&hebrewDate, &here)));
	}
	return 0;
}
