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
---------------------------------------------------------------------------------
Based on code from Calendrical Calculations 
by Nachum Dershowitz and Edward M. Reingold, 
Software---Practice & Experience, vol. 20, no. 9 (September, 1990), pp. 899--928.

and code from ICU licensed under the Unicode license
	COPYRIGHT AND PERMISSION NOTICE (ICU 58 and later)

	Copyright © 1991-2018 Unicode, Inc. All rights reserved.
	Distributed under the Terms of Use in http://www.unicode.org/copyright.html.

	Permission is hereby granted, free of charge, to any person obtaining
	a copy of the Unicode data files and any associated documentation
	(the "Data Files") or Unicode software and any associated documentation
	(the "Software") to deal in the Data Files or Software
	without restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, and/or sell copies of
	the Data Files or Software, and to permit persons to whom the Data Files
	or Software are furnished to do so, provided that either
	(a) this copyright and permission notice appear with all copies
	of the Data Files or Software, or
	(b) this copyright and permission notice appear in associated
	Documentation.

	THE DATA FILES AND SOFTWARE ARE PROVIDED "AS IS", WITHOUT WARRANTY OF
	ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
	WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT OF THIRD PARTY RIGHTS.
	IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS
	NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL
	DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
	DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
	TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
	PERFORMANCE OF THE DATA FILES OR SOFTWARE.

	Except as contained in this notice, the name of a copyright holder
	shall not be used in advertising or otherwise to promote the sale,
	use or other dealings in these Data Files or Software without prior
	written authorization of the copyright holder.
---------------------------------------------------------------------------------
****/

#include <time.h>
#include "util.h"
#include "NOAAcalculator.h"
#include "hebrewcalendar.h"

int HebrewLeapYear(int year)
{  
  if ((((7 * year) + 1) % 19) < 7)
    return 1;
  else
    return 0;
}

long int HebrewCalendarElapsedDays(int year)
{
  long int MonthsElapsed =
    (235 * ((year - 1) / 19))           // Months in complete cycles so far.
    + (12 * ((year - 1) % 19))          // Regular months in this cycle.
    + (7 * ((year - 1) % 19) + 1) / 19; // Leap months this cycle
  long int PartsElapsed = 204 + 793 * (MonthsElapsed % 1080);
  long int HoursElapsed =
    5 + 12 * MonthsElapsed + 793 * (MonthsElapsed  / 1080)
    + PartsElapsed / 1080;
  long int ConjunctionDay = 1 + 29 * MonthsElapsed + HoursElapsed / 24;
  long int ConjunctionParts = 1080 * (HoursElapsed % 24) + PartsElapsed % 1080;
  long int AlternativeDay;
  int cdw = (ConjunctionDay % 7);
  if ((ConjunctionParts >= 19440)        // If new moon is at or after midday,
      || ((cdw == 2)    // ...or is on a Tuesday...
          && (ConjunctionParts >= 9924)  // at 9 hours, 204 parts or later...
          && !(HebrewLeapYear(year)))   // ...of a common year,
      || ((cdw == 1)    // ...or is on a Monday at...
          && (ConjunctionParts >= 16789) // 15 hours, 589 parts or later...
          && (HebrewLeapYear(year - 1))))// at the end of a leap year
    // Then postpone Rosh HaShanah one day
    AlternativeDay = ConjunctionDay + 1;
  else
    AlternativeDay = ConjunctionDay;
  int adw = (AlternativeDay % 7);
  if (( adw == 0)// If Rosh HaShanah would occur on Sunday,
      || (adw == 3)     // or Wednesday,
      || (adw == 5))    // or Friday
    // Then postpone it one (more) day
    return (1+ AlternativeDay);
  else
    return AlternativeDay;
}

int DaysInHebrewYear(int year)
{
  return ((HebrewCalendarElapsedDays(year + 1)) -
          (HebrewCalendarElapsedDays(year)));
}

int LongHeshvan(int year)
{
  if ((DaysInHebrewYear(year) % 10) == 5)
    return 1;
  else
    return 0;
}

int ShortKislev(int year)
{
  if ((DaysInHebrewYear(year) % 10) == 3)
    return 1;
  else
    return 0;
}

int LastDayOfHebrewMonth(int month, int year)
{
  if ((month == 2)
      || (month == 4)
      || (month == 6)
      || ((month == 8) && !(LongHeshvan(year)))
      || ((month == 9) && ShortKislev(year))
      || (month == 10)
      || ((month == 12) && !(HebrewLeapYear(year)))
      || (month == 13))
    return 29;
  else
    return 30;
}

int nissanCount(int year)
{
	int count= 0;
	switch(DaysInHebrewYear(year))
	{
		case 353:
			count = 176;
			break;
		case 354:
			count = 177;
			break;
		case 355:
			count = 178;
			break;
		case 383:
			count = 206;
			break;
		case 384:
			count = 207;
			break;
		case 385:
			count = 208;
			break;
	}
	return count;
}

void convertDate(struct tm *date, hdate *result)
{
    double julianDay = calcJD(date);
    long int d = (long int)julianDay - 347996;
	double m = ((d * (double)25920) / (double)765433);
	int year = (int)((19. * m) / 235.);
    int month;
    int dayCount;
    
    while (d >= HebrewCalendarElapsedDays(year + 1))
    {
  		year++;
  	}
    long int ys  = HebrewCalendarElapsedDays(year);
    int dayOfYear = (d - ys)+1;
    int nissanStart = nissanCount(year);
    if (dayOfYear <= nissanStart) {
	  month = 7;  //  Start at Tishri
	  dayCount = 0;
    } else {
      month = 1;  //  Start at Nisan
      dayCount = nissanStart;
  	}
    while (dayOfYear > (dayCount + LastDayOfHebrewMonth(month, year)))
    {
      dayCount += LastDayOfHebrewMonth(month, year);
      month++;
  	}
    int day = dayOfYear - dayCount ;
	result->year = year;
	result->month = month;
	result->day = day;
	result->leap = HebrewLeapYear(year);
}
