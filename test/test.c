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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "zmanim.h"

char* formattime(ltime ltime)
{
	static char final[32];
	final[0] = '\0';
	time_t time = ltime / 1000;
	struct tm *tm = localtime(&time);
	strftime(final, 31, "%m/%d/%Y %I:%M:%S.~~~ %p %Z", tm);
	char msec[4];
	snprintf(msec, 4, "%03i", (int)(ltime % 1000));
	memcpy(strchr(final, (int)'~'), msec, 3);
	return final;
}

int main(int argc, char *argv[])
{
	double latitude = 40.66896;
	double longitude = -73.94284;
	double elevation = 34;
	float timezone = -4.0;
	time_t now = time(NULL);
	long int offset = (long int) 3600 * timezone;

	if ( argc != 1 ) {
			if ( argc != 7 )
			{
				printf("usage: year month day latitude longitude timezone\n       2018 01 01 40.66896 -73.94284 -4.0\n");
				return 1;
			}
			struct tm *pltm = localtime(&now);
			struct tm ltm = *pltm;
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
			if ( atof(argv[4]) && -90 < atof(argv[4]) && atof(argv[4]) < 90 )
			{
				latitude = atof(argv[4]);
			}
			else
			{
				printf("Latitude must be between -90 and 90!\n");
				return 1;
			}
			if (atof(argv[5]) && -180 < atof(argv[5]) && atof(argv[5]) < 180)
			{
				longitude = atof(argv[5]);
			}
			else
			{
				printf("Longitude must be between -180 and 180!\n");
				return 1;
			}
			if( atof(argv[6]) && -13 < atof(argv[6]) && atof(argv[6]) < 15 )
			{
				timezone = atof(argv[6]);
			}
			else
			{
				printf("%s: is not a valid timezone\n", argv[6]);
				return 1;
			}
		}


	setall(&now, offset, latitude, longitude, elevation);
/*	printf("%li\n%f\n%f\n%f\n%f\n", gettime(), getoffset(), getlatitude(), getlongitude(), getelevation());
*/

/*	for (int i = 100; i > 0; i--)
	{
*/
		printf("sunrise: %s\n", formattime(getsunrise()));
		printf("shma:    %s\n", formattime(getshmabaalhatanya()));
		printf("sunset:  %s\n", formattime(getsunset()));
/*	}
*/
	return 0;
}
