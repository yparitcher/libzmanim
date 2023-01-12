#include <stdlib.h>
#include <stdio.h>
#include "hebrewcalendar.h"
#include "zmanim.h"
#include "hdateformat.h"

int main()
{
	printf("year:\tWeekday\tchanukah\n");
	for(int i = 40; i<122;	i++)
	{
		
		struct tm Edate = {.tm_year=i, .tm_mon=11, .tm_mday=25 };
		hdate date = convertDate(Edate);
		yomtov chag = getyomtov(date);
		if (chag >= CHANUKAH_DAY1 && chag <= CHANUKAH_DAY8)
		{
			printf("%d:\t%d\t%d\n", date.year, date.wday, chag - TU_BAV);
		}
	}
}
