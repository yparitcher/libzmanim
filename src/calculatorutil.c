
#include <time.h>
#include "util.h"
#include "calculatorutil.h"
#include <math.h>

tmz getDateFromTime(tmz *current, double time, double longitude, int isSunrise)
{
	tmz result;
	if (isnan(time)) {
		return result;
	}
	double calculatedTime = time;
	result.tm.tm_year = current->tm.tm_year;
	result.tm.tm_mon = current->tm.tm_mon;
	result.tm.tm_mday = current->tm.tm_mday;
	result.tm.tm_isdst = -1;

	int hours = (int)calculatedTime;
	calculatedTime -= hours;
	int minutes = (int)(calculatedTime *= 60);
	calculatedTime -= minutes;
	int seconds = (int)(calculatedTime *= 60);
	calculatedTime -= seconds;
	int miliseconds = (int)(calculatedTime * 1000);
	result.tmz_msec = miliseconds;
	int localTimeHours = (int)longitude / 15;
	if (isSunrise && localTimeHours + hours > 18) {
		result.tm.tm_mday -= 1;
	} else if (!isSunrise && localTimeHours + hours < 6) {
		result.tm.tm_mday += 1;
	}

	result.tm.tm_hour = hours;
	result.tm.tm_min = minutes;
	result.tm.tm_sec = seconds;
	result.tm.tm_sec += current->tmz_gmtoff;
	result.tmz_gmtoff = current->tmz_gmtoff;
	mktime(&(result.tm));
	mktime(&(result.tm));

	return result;
}

