#include <stdio.h>
#include "hebrewcalendar.h"

void avosrun(hdate arg, int year)
{
	hdate date = arg;
	hdatesetdoy(&date);
	for (;date.year == year; hdateaddday(&date, 1))
	{
		int x;
		if (x = getavos(date))
		{
			char today[32] = {"\0"};
			hdateformat(today, 32, date);
			printf("%s\t%d\n", today, x);
		}
	}
}

void avostest(int year){
	printf("%d			EY\n", year);
	hdate date = {.year=year, .month=1, .day=1, .EY=1};
	avosrun(date, year);
	printf("%d			!!\n", year);
	hdate date2 = {.year=year, .month=1, .day=1};
	avosrun(date2, year);
}
