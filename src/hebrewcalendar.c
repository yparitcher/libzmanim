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

and code from Astronomical Algorithms by Jean Meeus

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
#include <math.h>
#include "hebrewcalendar.h"

const parshah parshahlist[17][56] = {
{NOPARSHAH, VAYELECH, HAAZINU, NOPARSHAH, BERESHIT, NOACH, LECH_LECHA, VAYEIRA, CHAYEI_SARAH, TOLEDOT, VAYETZE, VAYISHLACH, VAYESHEV, MIKETZ, VAYIGASH, VAYECHI, SHEMOT, VAEIRA, BO, BESHALACH, YITRO, MISHPATIM, TERUMAH, TETZAVEH, KI_TISA, VAYAKHEL_PEKUDEI, VAYIKRA, TZAV, NOPARSHAH, SHEMINI, TAZRIA_METZORA, ACHAREI_MOT_KEDOSHIM, EMOR, BEHAR_BECHUKOTAI, BAMIDBAR, NASO, BEHAALOTECHA, SHLACH, KORACH, CHUKAT, BALAK, PINCHAS, MATOT_MASEI, DEVARIM, VAETCHANAN, EIKEV, REEH, SHOFTIM, KI_TEITZEI, KI_TAVO, NITZAVIM_VAYELECH},
{NOPARSHAH, VAYELECH, HAAZINU, NOPARSHAH, BERESHIT, NOACH, LECH_LECHA, VAYEIRA, CHAYEI_SARAH, TOLEDOT, VAYETZE, VAYISHLACH, VAYESHEV, MIKETZ, VAYIGASH, VAYECHI, SHEMOT, VAEIRA, BO, BESHALACH, YITRO, MISHPATIM, TERUMAH, TETZAVEH, KI_TISA, VAYAKHEL_PEKUDEI, VAYIKRA, TZAV, NOPARSHAH, SHEMINI, TAZRIA_METZORA, ACHAREI_MOT_KEDOSHIM, EMOR, BEHAR_BECHUKOTAI, BAMIDBAR, NOPARSHAH, NASO, BEHAALOTECHA, SHLACH, KORACH, CHUKAT_BALAK, PINCHAS, MATOT_MASEI, DEVARIM, VAETCHANAN, EIKEV, REEH, SHOFTIM, KI_TEITZEI, KI_TAVO, NITZAVIM_VAYELECH},
{NOPARSHAH, HAAZINU, NOPARSHAH, NOPARSHAH, BERESHIT, NOACH, LECH_LECHA, VAYEIRA, CHAYEI_SARAH, TOLEDOT, VAYETZE, VAYISHLACH, VAYESHEV, MIKETZ, VAYIGASH, VAYECHI, SHEMOT, VAEIRA, BO, BESHALACH, YITRO, MISHPATIM, TERUMAH, TETZAVEH, KI_TISA, VAYAKHEL_PEKUDEI, VAYIKRA, TZAV, NOPARSHAH, NOPARSHAH, SHEMINI, TAZRIA_METZORA, ACHAREI_MOT_KEDOSHIM, EMOR, BEHAR_BECHUKOTAI, BAMIDBAR, NASO, BEHAALOTECHA, SHLACH, KORACH, CHUKAT, BALAK, PINCHAS, MATOT_MASEI, DEVARIM, VAETCHANAN, EIKEV, REEH, SHOFTIM, KI_TEITZEI, KI_TAVO, NITZAVIM},
{NOPARSHAH, HAAZINU, NOPARSHAH, NOPARSHAH, BERESHIT, NOACH, LECH_LECHA, VAYEIRA, CHAYEI_SARAH, TOLEDOT, VAYETZE, VAYISHLACH, VAYESHEV, MIKETZ, VAYIGASH, VAYECHI, SHEMOT, VAEIRA, BO, BESHALACH, YITRO, MISHPATIM, TERUMAH, TETZAVEH, KI_TISA, VAYAKHEL, PEKUDEI, VAYIKRA, TZAV, NOPARSHAH, SHEMINI, TAZRIA_METZORA, ACHAREI_MOT_KEDOSHIM, EMOR, BEHAR_BECHUKOTAI, BAMIDBAR, NASO, BEHAALOTECHA, SHLACH, KORACH, CHUKAT, BALAK, PINCHAS, MATOT_MASEI, DEVARIM, VAETCHANAN, EIKEV, REEH, SHOFTIM, KI_TEITZEI, KI_TAVO, NITZAVIM},
{NOPARSHAH, NOPARSHAH, HAAZINU, NOPARSHAH, NOPARSHAH, BERESHIT, NOACH, LECH_LECHA, VAYEIRA, CHAYEI_SARAH, TOLEDOT, VAYETZE, VAYISHLACH, VAYESHEV, MIKETZ, VAYIGASH, VAYECHI, SHEMOT, VAEIRA, BO, BESHALACH, YITRO, MISHPATIM, TERUMAH, TETZAVEH, KI_TISA, VAYAKHEL_PEKUDEI, VAYIKRA, TZAV, NOPARSHAH, SHEMINI, TAZRIA_METZORA, ACHAREI_MOT_KEDOSHIM, EMOR, BEHAR_BECHUKOTAI, BAMIDBAR, NASO, BEHAALOTECHA, SHLACH, KORACH, CHUKAT, BALAK, PINCHAS, MATOT_MASEI, DEVARIM, VAETCHANAN, EIKEV, REEH, SHOFTIM, KI_TEITZEI, KI_TAVO, NITZAVIM},
{NOPARSHAH, NOPARSHAH, HAAZINU, NOPARSHAH, NOPARSHAH, BERESHIT, NOACH, LECH_LECHA, VAYEIRA, CHAYEI_SARAH, TOLEDOT, VAYETZE, VAYISHLACH, VAYESHEV, MIKETZ, VAYIGASH, VAYECHI, SHEMOT, VAEIRA, BO, BESHALACH, YITRO, MISHPATIM, TERUMAH, TETZAVEH, KI_TISA, VAYAKHEL_PEKUDEI, VAYIKRA, TZAV, NOPARSHAH, SHEMINI, TAZRIA_METZORA, ACHAREI_MOT_KEDOSHIM, EMOR, BEHAR_BECHUKOTAI, BAMIDBAR, NASO, BEHAALOTECHA, SHLACH, KORACH, CHUKAT, BALAK, PINCHAS, MATOT_MASEI, DEVARIM, VAETCHANAN, EIKEV, REEH, SHOFTIM, KI_TEITZEI, KI_TAVO, NITZAVIM_VAYELECH},
{NOPARSHAH, VAYELECH, HAAZINU, NOPARSHAH, BERESHIT, NOACH, LECH_LECHA, VAYEIRA, CHAYEI_SARAH, TOLEDOT, VAYETZE, VAYISHLACH, VAYESHEV, MIKETZ, VAYIGASH, VAYECHI, SHEMOT, VAEIRA, BO, BESHALACH, YITRO, MISHPATIM, TERUMAH, TETZAVEH, KI_TISA, VAYAKHEL, PEKUDEI, VAYIKRA, TZAV, SHEMINI, TAZRIA, METZORA, NOPARSHAH, ACHAREI_MOT, KEDOSHIM, EMOR, BEHAR, BECHUKOTAI, BAMIDBAR, NOPARSHAH, NASO, BEHAALOTECHA, SHLACH, KORACH, CHUKAT_BALAK, PINCHAS, MATOT_MASEI, DEVARIM, VAETCHANAN, EIKEV, REEH, SHOFTIM, KI_TEITZEI, KI_TAVO, NITZAVIM_VAYELECH},
{NOPARSHAH, VAYELECH, HAAZINU, NOPARSHAH, BERESHIT, NOACH, LECH_LECHA, VAYEIRA, CHAYEI_SARAH, TOLEDOT, VAYETZE, VAYISHLACH, VAYESHEV, MIKETZ, VAYIGASH, VAYECHI, SHEMOT, VAEIRA, BO, BESHALACH, YITRO, MISHPATIM, TERUMAH, TETZAVEH, KI_TISA, VAYAKHEL, PEKUDEI, VAYIKRA, TZAV, SHEMINI, TAZRIA, METZORA, NOPARSHAH, NOPARSHAH, ACHAREI_MOT, KEDOSHIM, EMOR, BEHAR, BECHUKOTAI, BAMIDBAR, NASO, BEHAALOTECHA, SHLACH, KORACH, CHUKAT, BALAK, PINCHAS, MATOT_MASEI, DEVARIM, VAETCHANAN, EIKEV, REEH, SHOFTIM, KI_TEITZEI, KI_TAVO, NITZAVIM},
{NOPARSHAH, HAAZINU, NOPARSHAH, NOPARSHAH, BERESHIT, NOACH, LECH_LECHA, VAYEIRA, CHAYEI_SARAH, TOLEDOT, VAYETZE, VAYISHLACH, VAYESHEV, MIKETZ, VAYIGASH, VAYECHI, SHEMOT, VAEIRA, BO, BESHALACH, YITRO, MISHPATIM, TERUMAH, TETZAVEH, KI_TISA, VAYAKHEL, PEKUDEI, VAYIKRA, TZAV, SHEMINI, TAZRIA, METZORA, ACHAREI_MOT, NOPARSHAH, KEDOSHIM, EMOR, BEHAR, BECHUKOTAI, BAMIDBAR, NASO, BEHAALOTECHA, SHLACH, KORACH, CHUKAT, BALAK, PINCHAS, MATOT, MASEI, DEVARIM, VAETCHANAN, EIKEV, REEH, SHOFTIM, KI_TEITZEI, KI_TAVO, NITZAVIM},
{NOPARSHAH, HAAZINU, NOPARSHAH, NOPARSHAH, BERESHIT, NOACH, LECH_LECHA, VAYEIRA, CHAYEI_SARAH, TOLEDOT, VAYETZE, VAYISHLACH, VAYESHEV, MIKETZ, VAYIGASH, VAYECHI, SHEMOT, VAEIRA, BO, BESHALACH, YITRO, MISHPATIM, TERUMAH, TETZAVEH, KI_TISA, VAYAKHEL, PEKUDEI, VAYIKRA, TZAV, SHEMINI, TAZRIA, METZORA, ACHAREI_MOT, NOPARSHAH, KEDOSHIM, EMOR, BEHAR, BECHUKOTAI, BAMIDBAR, NASO, BEHAALOTECHA, SHLACH, KORACH, CHUKAT, BALAK, PINCHAS, MATOT, MASEI, DEVARIM, VAETCHANAN, EIKEV, REEH, SHOFTIM, KI_TEITZEI, KI_TAVO, NITZAVIM_VAYELECH},
{NOPARSHAH, NOPARSHAH, HAAZINU, NOPARSHAH, NOPARSHAH, BERESHIT, NOACH, LECH_LECHA, VAYEIRA, CHAYEI_SARAH, TOLEDOT, VAYETZE, VAYISHLACH, VAYESHEV, MIKETZ, VAYIGASH, VAYECHI, SHEMOT, VAEIRA, BO, BESHALACH, YITRO, MISHPATIM, TERUMAH, TETZAVEH, KI_TISA, VAYAKHEL, PEKUDEI, VAYIKRA, TZAV, SHEMINI, TAZRIA, METZORA, NOPARSHAH, ACHAREI_MOT, KEDOSHIM, EMOR, BEHAR, BECHUKOTAI, BAMIDBAR, NASO, BEHAALOTECHA, SHLACH, KORACH, CHUKAT, BALAK, PINCHAS, MATOT_MASEI, DEVARIM, VAETCHANAN, EIKEV, REEH, SHOFTIM, KI_TEITZEI, KI_TAVO, NITZAVIM_VAYELECH},
{NOPARSHAH, NOPARSHAH, HAAZINU, NOPARSHAH, NOPARSHAH, BERESHIT, NOACH, LECH_LECHA, VAYEIRA, CHAYEI_SARAH, TOLEDOT, VAYETZE, VAYISHLACH, VAYESHEV, MIKETZ, VAYIGASH, VAYECHI, SHEMOT, VAEIRA, BO, BESHALACH, YITRO, MISHPATIM, TERUMAH, TETZAVEH, KI_TISA, VAYAKHEL, PEKUDEI, VAYIKRA, TZAV, SHEMINI, TAZRIA, METZORA, NOPARSHAH, ACHAREI_MOT, KEDOSHIM, EMOR, BEHAR, BECHUKOTAI, BAMIDBAR, NOPARSHAH, NASO, BEHAALOTECHA, SHLACH, KORACH, CHUKAT_BALAK, PINCHAS, MATOT_MASEI, DEVARIM, VAETCHANAN, EIKEV, REEH, SHOFTIM, KI_TEITZEI, KI_TAVO, NITZAVIM_VAYELECH},
{NOPARSHAH, VAYELECH, HAAZINU, NOPARSHAH, BERESHIT, NOACH, LECH_LECHA, VAYEIRA, CHAYEI_SARAH, TOLEDOT, VAYETZE, VAYISHLACH, VAYESHEV, MIKETZ, VAYIGASH, VAYECHI, SHEMOT, VAEIRA, BO, BESHALACH, YITRO, MISHPATIM, TERUMAH, TETZAVEH, KI_TISA, VAYAKHEL_PEKUDEI, VAYIKRA, TZAV, NOPARSHAH, SHEMINI, TAZRIA_METZORA, ACHAREI_MOT_KEDOSHIM, EMOR, BEHAR_BECHUKOTAI, BAMIDBAR, NASO, BEHAALOTECHA, SHLACH, KORACH, CHUKAT, BALAK, PINCHAS, MATOT_MASEI, DEVARIM, VAETCHANAN, EIKEV, REEH, SHOFTIM, KI_TEITZEI, KI_TAVO, NITZAVIM_VAYELECH},
{NOPARSHAH, HAAZINU, NOPARSHAH, NOPARSHAH, BERESHIT, NOACH, LECH_LECHA, VAYEIRA, CHAYEI_SARAH, TOLEDOT, VAYETZE, VAYISHLACH, VAYESHEV, MIKETZ, VAYIGASH, VAYECHI, SHEMOT, VAEIRA, BO, BESHALACH, YITRO, MISHPATIM, TERUMAH, TETZAVEH, KI_TISA, VAYAKHEL_PEKUDEI, VAYIKRA, TZAV, NOPARSHAH, SHEMINI, TAZRIA_METZORA, ACHAREI_MOT_KEDOSHIM, EMOR, BEHAR, BECHUKOTAI, BAMIDBAR, NASO, BEHAALOTECHA, SHLACH, KORACH, CHUKAT, BALAK, PINCHAS, MATOT_MASEI, DEVARIM, VAETCHANAN, EIKEV, REEH, SHOFTIM, KI_TEITZEI, KI_TAVO, NITZAVIM},
{NOPARSHAH, VAYELECH, HAAZINU, NOPARSHAH, BERESHIT, NOACH, LECH_LECHA, VAYEIRA, CHAYEI_SARAH, TOLEDOT, VAYETZE, VAYISHLACH, VAYESHEV, MIKETZ, VAYIGASH, VAYECHI, SHEMOT, VAEIRA, BO, BESHALACH, YITRO, MISHPATIM, TERUMAH, TETZAVEH, KI_TISA, VAYAKHEL, PEKUDEI, VAYIKRA, TZAV, SHEMINI, TAZRIA, METZORA, NOPARSHAH, ACHAREI_MOT, KEDOSHIM, EMOR, BEHAR, BECHUKOTAI, BAMIDBAR, NASO, BEHAALOTECHA, SHLACH, KORACH, CHUKAT, BALAK, PINCHAS, MATOT_MASEI, DEVARIM, VAETCHANAN, EIKEV, REEH, SHOFTIM, KI_TEITZEI, KI_TAVO, NITZAVIM_VAYELECH},
{NOPARSHAH, VAYELECH, HAAZINU, NOPARSHAH, BERESHIT, NOACH, LECH_LECHA, VAYEIRA, CHAYEI_SARAH, TOLEDOT, VAYETZE, VAYISHLACH, VAYESHEV, MIKETZ, VAYIGASH, VAYECHI, SHEMOT, VAEIRA, BO, BESHALACH, YITRO, MISHPATIM, TERUMAH, TETZAVEH, KI_TISA, VAYAKHEL, PEKUDEI, VAYIKRA, TZAV, SHEMINI, TAZRIA, METZORA, NOPARSHAH, ACHAREI_MOT, KEDOSHIM, EMOR, BEHAR, BECHUKOTAI, BAMIDBAR, NASO, BEHAALOTECHA, SHLACH, KORACH, CHUKAT, BALAK, PINCHAS, MATOT, MASEI, DEVARIM, VAETCHANAN, EIKEV, REEH, SHOFTIM, KI_TEITZEI, KI_TAVO, NITZAVIM},
{NOPARSHAH, NOPARSHAH, HAAZINU, NOPARSHAH, NOPARSHAH, BERESHIT, NOACH, LECH_LECHA, VAYEIRA, CHAYEI_SARAH, TOLEDOT, VAYETZE, VAYISHLACH, VAYESHEV, MIKETZ, VAYIGASH, VAYECHI, SHEMOT, VAEIRA, BO, BESHALACH, YITRO, MISHPATIM, TERUMAH, TETZAVEH, KI_TISA, VAYAKHEL, PEKUDEI, VAYIKRA, TZAV, SHEMINI, TAZRIA, METZORA, NOPARSHAH, ACHAREI_MOT, KEDOSHIM, EMOR, BEHAR, BECHUKOTAI, BAMIDBAR, NASO, BEHAALOTECHA, SHLACH, KORACH, CHUKAT, BALAK, PINCHAS, MATOT_MASEI, DEVARIM, VAETCHANAN, EIKEV, REEH, SHOFTIM, KI_TEITZEI, KI_TAVO, NITZAVIM_VAYELECH}};

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

hdate convertDate(struct tm date)
{
    hdate result;
    double julianDay = gregorianjulian(date);
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
	result.year = year;
	result.month = month;
	result.day = day;
	result.wday = (HebrewCalendarElapsedDays(year)+dayOfYear)%7;
	result.dayofyear = dayOfYear;
	result.leap = HebrewLeapYear(year);
	result.hour = date.tm_hour;
	result.min = date.tm_min;
	result.sec = date.tm_sec;
	return result;
}

void setEY(hdate *date, _Bool EY)
{
	date->EY = EY;
}

double hdatejulian(hdate date)
{
	double diff = 347996.5;
	long int yearstart = HebrewCalendarElapsedDays(date.year);
	return (date.dayofyear-1) + yearstart + diff;
}

struct tm hdategregorian(hdate date)
{
	struct tm result;
	double jd = hdatejulian(date)+.5;
	double A = floor((jd - 1867216.25)/36524.25);
	double B = (jd + 1525 + A - floor(A/4));
	double C = floor((B-122.1)/365.25);
	double D = floor(C*365.25);
	double E = floor((B-D)/30.6001);
	int m,y;
	if (E>13){m = E-13;}else{m = E-1;}
	if (m>2){y = C-4716;}else{y = C-4715;}
	result.tm_year = y-1900;
	result.tm_mon = m-1;
	result.tm_mday = (B - D - floor(E*30.6001));
	result.tm_hour = date.hour;
	result.tm_min = date.min;
	result.tm_sec = date.sec;
	result.tm_isdst=-1;
	mktime(&result);
	return result;
}

time_t hdatetime_t(hdate date)
{
	time_t result = (HebrewCalendarElapsedDays(date.year)+(date.dayofyear-1))-2092591;
	result = ((((((result*24)+date.hour)*60)+date.min)*60)+date.sec);
	result -= date.offset;
	return result;
}

double gregorianjulian(struct tm date)
{
	int year = date.tm_year + 1900;
	int month = date.tm_mon + 1;
	int day = date.tm_mday;
	if (month <= 2) {
		year -= 1;
		month += 12;
	}
	int A = floor(year/100);
	int B = 2 - A + floor(A/4);

	double JD = floor(365.25*(year + 4716)) + floor(30.6001*(month+1)) + day + B - 1524.5;
	return JD;
}

int hdatecompare(hdate date1, hdate date2)
{
	if (date1.year < date2.year){return 1;}
	else if (date1.year > date2.year){return -1;}
	else if (date1.dayofyear < date2.dayofyear){return 1;}
	else if (date1.dayofyear > date2.dayofyear){return -1;}
	else if (date1.hour < date2.hour){return 1;}
	else if (date1.hour > date2.hour){return -1;}
	else if (date1.min < date2.min){return 1;}
	else if (date1.min > date2.min){return -1;}
	else if (date1.sec < date2.sec){return 1;}
	else if (date1.sec > date2.sec){return -1;}
	else if (date1.msec < date2.msec){return 1;}
	else if (date1.msec > date2.msec){return -1;}
	else {return 0;}
}

void hdatesetdoy(hdate *date)
{
	int year = date->year;
	int month = date->month;
	int day = date->day;
	if (day == 30 && LastDayOfHebrewMonth(month, year) == 29){day = 29;}
	int monthcount;
    int dayOfYear;
	if (month < 7)
	{
		monthcount = 1;
		dayOfYear = nissanCount(year);
	} else {
		monthcount = 7;
		dayOfYear = 0;
	}
	while (monthcount < month)
	{
		dayOfYear += LastDayOfHebrewMonth(monthcount, year);
		monthcount++;
	}
	dayOfYear += day;
	date->dayofyear = dayOfYear;
	date->wday = (HebrewCalendarElapsedDays(year)+dayOfYear)%7;
	date->leap = HebrewLeapYear(year);
}

void hdateaddyear(hdate *date, int years)
{
	int year = date->year;
	int month = date->month;
	int leap1 = date->leap;
	year += years;
	int leap2 = HebrewLeapYear(year);
	if (leap1 != leap2)
	{
		if (leap1 && month == 13){month = 12;}
		if (!leap1 && month == 12){month = 13;}
	}
	date->year = year;
	date->month = month;
	hdatesetdoy(date);
}

void hdateaddmonth(hdate *date, int months)
{
	_Bool last = 0;
	if (date->day == 30) {last = 1;}
	int monthcount = months;
	while (monthcount > 0)
	{
		switch (date->month)
		{
			case 12:
				if (date->leap){date->month++;}
				else{date->month = 1;}
				monthcount--;
				break;
			case 13:
				date->month = 1;
				monthcount--;
				break;
			case 6:
				date->month++;
				hdateaddyear(date, 1);
				monthcount--;
				break;
			default:
				date->month++;
				monthcount--;
				break;
		 }
	}
	while (monthcount < 0)
	{
		switch (date->month)
		{
			case 1:
				if (date->leap){date->month = 13;}
				else{date->month = 12;}
				monthcount++;
				break;
			case 7:
				date->month--;
				hdateaddyear(date, -1);
				monthcount++;
				break;
			default:
				date->month--;
				monthcount++;
				break;
		 }
	}
	if (last && LastDayOfHebrewMonth(date->month, date->year) == 30){date->day = 30;}
	hdatesetdoy(date);
}

void hdateaddday(hdate *date, int days)
{
	int daycount = days;
	while (daycount > 0)
	{
		switch (date->day)
		{
			case 30:
				date->day = 1;
				hdateaddmonth(date, 1);
				daycount--;
				break;
			case 29:
				if (LastDayOfHebrewMonth(date->month, date->year) == 29)
				{
					date->day = 1;
					hdateaddmonth(date, 1);
				} else {
					date->day++;
				}
				daycount--;
				break;
			default:
				date->day++;
				daycount--;
				break;
		}
	}
	while (daycount < 0)
	{
		switch (date->day)
		{
			case 1:
				hdateaddmonth(date, -1);
				if (LastDayOfHebrewMonth(date->month, date->year) == 30)
				{
					date->day = 30;
				} else {
					date->day = 29;
				}
				daycount++;
				break;
			default:
				date->day--;
				daycount++;
				break;
		}
	}
	hdatesetdoy(date);
}

void divideandcarry(int start, int *finish, int *carry, int divisor)
{
	*finish = start%divisor;
	*carry = start/divisor;
	if (*finish < 0)
	{
		*finish +=divisor;
		--*carry;
	}
}

void hdateaddhour(hdate *date, int hours)
{
	int hour = date->hour + hours;
	int carry = 0;
	divideandcarry(hour, &date->hour, &carry, 24);
	if (carry){hdateaddday(date, carry);}
	hdatesetdoy(date);
}

void hdateaddminute(hdate *date, int minutes)
{
	int minute = date->min + minutes;
	int carry = 0;
	divideandcarry(minute, &date->min, &carry, 60);
	if (carry){hdateaddhour(date, carry);}
	hdatesetdoy(date);
}

void hdateaddsecond(hdate *date, int seconds)
{
	int second = date->sec + seconds;
	int carry = 0;
	divideandcarry(second, &date->sec, &carry, 60);
	if (carry){hdateaddminute(date, carry);}
	hdatesetdoy(date);
}

void hdateaddmsecond(hdate *date, int mseconds)
{
	int msecond = date->msec + mseconds;
	int carry = 0;
	divideandcarry(msecond, &date->msec, &carry, 1000);
	if (carry){hdateaddsecond(date, carry);}
	hdatesetdoy(date);
}

void hdateadd(hdate *date, int years, int months, int days, int hours, int minutes, int seconds, int mseconds)
{
	if (years) {hdateaddyear(date, years);}
	if (months) {hdateaddmonth(date, months);}
	if (days) {hdateaddday(date, days);}
	if (hours) {hdateaddhour(date, hours);}
	if (minutes) {hdateaddminute(date, minutes);}
	if (seconds) {hdateaddsecond(date, seconds);}
	if (mseconds) {hdateaddmsecond(date, mseconds);}
}

molad getmolad(int year, int month)
{
	hdate result ={0};
	int MonthsElapsed =
	(235 * ((year - 1) / 19))           // Months in complete cycles so far.
	+ (12 * ((year - 1) % 19))          // Regular months in this cycle.
	+ (7 * ((year - 1) % 19) + 1) / 19; // Leap months this cycle
	if(month > 6)
	{
		MonthsElapsed += (month-7);
	} else {
		MonthsElapsed += (month+5);
		if (HebrewLeapYear(year)){MonthsElapsed += 1;}
	}

	long int PartsElapsed = 204 + 793 * (MonthsElapsed % 1080);
	long int HoursElapsed =
	5 + 12 * MonthsElapsed + 793 * (MonthsElapsed  / 1080)
	+ PartsElapsed / 1080;
	long int ConjunctionDay = 29 * MonthsElapsed + (HoursElapsed) / 24;
	int ConjunctionHour =(HoursElapsed % 24);
	int ConjunctionMinute = (PartsElapsed % 1080) / 18;
	int ConjunctionParts = (PartsElapsed % 1080) % 18;
	result.year = 1;
	result.month = 7;
	result.day = 1;
	hdateaddday(&result, ConjunctionDay);
	result.hour = ConjunctionHour;
	result.min = ConjunctionMinute;
	result.sec = ConjunctionParts;
	result.offset = 8456;
	hdateaddhour(&result, -6);
	return result;
}

int getYearType(hdate date)
{
	int yearWday = (HebrewCalendarElapsedDays(date.year)+1)%7;
	if (date.leap)
	{
		switch (yearWday)
		{
		case 2:
			if (ShortKislev(date.year))
			{
				if (date.EY) { return 14;}
				return 6;
			}
			if (LongHeshvan(date.year))
			{
				if (date.EY) { return 15;}
				return 7;
			}
			break;
		case 3:
			if (date.EY) { return 15;}
			return 7;
			break;
		case 5:
			if (ShortKislev(date.year)) {return 8;}
			if (LongHeshvan(date.year)) {return 9;}
			break;
		case 0:
			if (ShortKislev(date.year)) {return 10;}
			if (LongHeshvan(date.year))
			{
				if (date.EY) { return 16;}
				return 11;
			}
			break;
		}
	} else {
		switch (yearWday)
		{
		case 2:
			if (ShortKislev(date.year)) {return 0;}
			if (LongHeshvan(date.year))
			{
				if (date.EY) { return 12;}
				return 1;
			}
			break;
		case 3:
			if (date.EY) { return 12;}
			return 1;
			break;
		case 5:
			if (LongHeshvan(date.year)) {return 3;}
			if (!ShortKislev(date.year))
			{
				if (date.EY) { return 13;}
				return 2;
			}
			break;
		case 0:
			if (ShortKislev(date.year)) {return 4;}
			if (LongHeshvan(date.year)) {return 5;}
			break;
		}
	}
	return -1;
}

parshah getparshah(hdate date)
{
	int yearType = getYearType(date);
	//optimise
	int yearWday = HebrewCalendarElapsedDays(date.year)%7;
	int day = yearWday + date.dayofyear;
	if (date.wday) {return NOPARSHAH;}
	if (yearType >= 0)
	{
		return parshahlist[yearType][day/7];
	}
	return NOPARSHAH;
}

yomtov getyomtov(hdate date)
{
	switch(date.month)
	{
		case 1:
			if(date.day == 14) {return EREV_PESACH;}
			if(date.day == 15) {return PESACH_DAY1;}
			if(date.day == 16 && date.EY) {return CHOL_HAMOED_PESACH_DAY1;}
			if(date.day == 16) {return PESACH_DAY2;}
			if(date.day == 17 && date.EY) {return CHOL_HAMOED_PESACH_DAY2;}
			if(date.day == 17) {return CHOL_HAMOED_PESACH_DAY1;}
			if(date.day == 18 && date.EY) {return CHOL_HAMOED_PESACH_DAY3;}
			if(date.day == 18) {return CHOL_HAMOED_PESACH_DAY2;}
			if(date.day == 19 && date.EY) {return CHOL_HAMOED_PESACH_DAY4;}
			if(date.day == 19) {return CHOL_HAMOED_PESACH_DAY3;}
			if(date.day == 20 && date.EY) {return CHOL_HAMOED_PESACH_DAY5;}
			if(date.day == 20) {return CHOL_HAMOED_PESACH_DAY4;}
			if(date.day == 21) {return SHVEI_SHEL_PESACH;}
			if(date.day == 22 && !date.EY) {return ACHRON_SHEL_PESACH;}
			break;
		case 2:
			if(date.day == 14) {return PESACH_SHEINI;}
			if(date.day == 18) {return LAG_BAOMER;}
			break;
		case 3:
			if(date.day == 5) {return EREV_SHAVOUS;}
			if(date.day == 6) {return SHAVOUS_DAY1;}
			if(date.day == 7 && !date.EY) {return SHAVOUS_DAY2;}
			break;
		case 4:
			if(date.day == 17 && date.wday) {return SHIVA_ASAR_BTAAMUZ;}
			if(date.day == 18 && date.wday == 1) {return SHIVA_ASAR_BTAAMUZ;}
			break;
		case 5:
			if(date.day == 9 && date.wday) {return TISHA_BAV;}
			if(date.day == 10 && date.wday == 1) {return TISHA_BAV;}
			if(date.day == 15) {return TU_BAV;}
			break;
		case 6:
			if(date.day == 29) {return EREV_ROSH_HASHANAH;}
			break;
		case 7:
			if(date.day == 1) {return ROSH_HASHANAH_DAY1;}
			if(date.day == 2) {return ROSH_HASHANAH_DAY2;}
			if(date.day == 3 && date.wday) {return TZOM_GEDALIA;}
			if(date.day == 4 && date.wday == 1) {return TZOM_GEDALIA;}
			if(date.day == 9) {return EREV_YOM_KIPPUR;}
			if(date.day == 10) {return YOM_KIPPUR;}
			if(date.day == 14) {return EREV_SUKKOS;}
			if(date.day == 15) {return SUKKOS_DAY1;}
			if(date.day == 16 && date.EY) {return CHOL_HAMOED_SUKKOS_DAY1;}
			if(date.day == 16) {return SUKKOS_DAY2;}
			if(date.day == 17 && date.EY) {return CHOL_HAMOED_SUKKOS_DAY2;}
			if(date.day == 17) {return CHOL_HAMOED_SUKKOS_DAY1;}
			if(date.day == 18 && date.EY) {return CHOL_HAMOED_SUKKOS_DAY3;}
			if(date.day == 18) {return CHOL_HAMOED_SUKKOS_DAY2;}
			if(date.day == 19 && date.EY) {return CHOL_HAMOED_SUKKOS_DAY4;}
			if(date.day == 19) {return CHOL_HAMOED_SUKKOS_DAY3;}
			if(date.day == 20 && date.EY) {return CHOL_HAMOED_SUKKOS_DAY5;}
			if(date.day == 20) {return CHOL_HAMOED_SUKKOS_DAY4;}
			if(date.day == 21) {return HOSHANA_RABBAH;}
			if(date.day == 22) {return SHMEINI_ATZERES;}
			if(date.day == 23 && !date.EY) {return SIMCHAS_TORAH;}
			break;
		case 9:
			if(date.day == 25) {return CHANUKAH_DAY1;}
			if(date.day == 26) {return CHANUKAH_DAY2;}
			if(date.day == 27) {return CHANUKAH_DAY3;}
			if(date.day == 28) {return CHANUKAH_DAY4;}
			if(date.day == 29) {return CHANUKAH_DAY5;}
			if(date.day == 30) {return CHANUKAH_DAY6;}
			break;
		case 10:
			if(date.day == 1)
			{	if(ShortKislev(date.year)) {return CHANUKAH_DAY6;}
				else {return CHANUKAH_DAY7;}}
			if(date.day == 2)
			{	if(ShortKislev(date.year)) {return CHANUKAH_DAY7;}
				else {return CHANUKAH_DAY8;}}
			if(date.day == 3 && ShortKislev(date.year)) {return CHANUKAH_DAY8;}
			if(date.day == 10) {return ASARAH_BTEVES;}
			break;
		case 11:
			if(date.day == 15) {return TU_BISHVAT;}
			break;
		case 12:
			if(!date.leap && date.day == 11 && date.wday == 5) {return TAANIS_ESTER;}
			if(!date.leap && date.day == 13 && date.wday) {return TAANIS_ESTER;}
			if(date.day == 14)
			{	if(date.leap) {return PURIM_KATAN;}
				else {return PURIM;}}
			if(date.day == 15)
			{	if(date.leap) {return SHUSHAN_PURIM_KATAN;}
				else {return SHUSHAN_PURIM;}}
			break;
		case 13:
			if(date.day == 11 && date.wday == 5) {return TAANIS_ESTER;}
			if(date.day == 13 && date.wday) {return TAANIS_ESTER;}
			if(date.day == 14) {return PURIM;}
			if(date.day == 15) {return SHUSHAN_PURIM;}
			break;
	}
	return CHOL;
}

yomtov getspecialshabbos(hdate date)
{
	if(!date.wday)
	{
		if((date.month == 11 && !date.leap) || (date.month == 12 && date.leap))
		{
			if(date.day == 25
			|| date.day == 27
			|| date.day == 29)
			{return SHKALIM;}
		}
		if((date.month == 12 && !date.leap) || date.month == 13)
		{
			if(date.day == 1) {return SHKALIM;}
			if(date.day == 8
			|| date.day == 9
			|| date.day == 11
			|| date.day == 13)
			{return ZACHOR;}
			if(date.day == 18
			|| date.day == 20
			|| date.day == 22
			|| date.day == 23)
			{return PARAH;}
			if(date.day == 25
			|| date.day == 27
			|| date.day == 29)
			{return HACHODESH;}
		}
		if(date.month == 1 && date.day == 1) {return HACHODESH;}
	}
	return CHOL;
}

yomtov getroshchodesh(hdate date)
{
	if (date.day == 30
		|| (date.day == 1 && date.month != 7))
	{return ROSH_CHODESH;}
	return CHOL;
}

yomtov getmacharchodesh(hdate date)
{
	if (date.wday) {return CHOL;}
	if (date.day == 30 || date.day == 29) {return MACHAR_CHODESH;}
	return CHOL;
}

yomtov getshabbosmevorchim(hdate date)
{
	if (date.wday) {return CHOL;}
	if (date.day >= 23 && date.day <= 29) {return SHABBOS_MEVORCHIM;}
	return CHOL;
}

int getomer(hdate date)
{
	int omer = 0;
	if (date.month == 1 && date.day >= 16) {omer = date.day - 15;}
	if (date.month == 2) {omer = date.day + 15;}
	if (date.month == 3 && date.day <= 5) {omer = date.day + 44;}
	return omer;
}

_Bool istaanis(hdate date)
{
	yomtov current = getyomtov(date);
	if (current == YOM_KIPPUR
	|| (current >= SHIVA_ASAR_BTAAMUZ && current <= TAANIS_ESTER))
	{return 1;}
	return 0;
}

_Bool isassurbemelachah(hdate date)
{
	yomtov current = getyomtov(date);
	if(!date.wday
	|| (current >= PESACH_DAY1 && current <= SIMCHAS_TORAH))
	{return 1;}
	return 0;
}

int iscandlelighting(hdate date)
{
	yomtov current = getyomtov(date);
	if((current >= EREV_PESACH && current <= EREV_SUKKOS)
	|| (current == CHOL_HAMOED_PESACH_DAY4 && !date.EY)
	|| (current == CHOL_HAMOED_PESACH_DAY5 && date.EY)
	|| current == HOSHANA_RABBAH)
	{
		if(!date.wday){return 2;}
		return 1;
	}
	if(current == PESACH_DAY1
	|| current == SHVEI_SHEL_PESACH
	|| current == SHAVOUS_DAY1
	|| current == ROSH_HASHANAH_DAY1
	|| current == SUKKOS_DAY1
	|| current == SHMEINI_ATZERES){return 2;}
	if((current == ACHRON_SHEL_PESACH
	|| current == SHAVOUS_DAY2
	|| current == ROSH_HASHANAH_DAY2
	|| current == SIMCHAS_TORAH)
	&& date.wday == 6) {return 2;}
	if(date.wday == 6) {return 1;}
	if((date.month == 9 && date.day == 24)
	|| (current >= CHANUKAH_DAY1 && current <= CHANUKAH_DAY7))
	{
		if(!date.wday){return 2;}
		return 3;
	}
	return 0;
}
