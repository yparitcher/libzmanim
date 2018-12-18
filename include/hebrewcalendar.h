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

#ifndef HEBREW_CALENDAR_H
#define HEBREW_CALENDAR_H

// location struct used to calculate zmanim
typedef struct {
	double latitude;
	double longitude;
	double elevation;
} location;

// enum of parshahs
typedef enum {NONE, BERESHIT, NOACH, LECH_LECHA, VAYEIRA, CHAYEI_SARAH, TOLEDOT, VAYETZE, VAYISHLACH, VAYESHEV, MIKETZ, VAYIGASH, VAYECHI, SHEMOT, VAEIRA, BO, BESHALACH, YITRO, MISHPATIM, TERUMAH, TETZAVEH, KI_TISA, VAYAKHEL, PEKUDEI, VAYIKRA, TZAV, SHEMINI, TAZRIA, METZORA, ACHAREI_MOT, KEDOSHIM, EMOR, BEHAR, BECHUKOTAI, BAMIDBAR, NASO, BEHAALOTECHA, SHLACH, KORACH, CHUKAT, BALAK, PINCHAS, MATOT, MASEI, DEVARIM, VAETCHANAN, EIKEV, REEH, SHOFTIM, KI_TEITZEI, KI_TAVO, NITZAVIM, VAYELECH, HAAZINU, VZOT_HABERACHAH, VAYAKHEL_PEKUDEI, TAZRIA_METZORA, ACHAREI_MOT_KEDOSHIM, BEHAR_BECHUKOTAI, CHUKAT_BALAK, MATOT_MASEI, NITZAVIM_VAYELECH} parshah;

// enum of yomtovs
typedef enum {CHOL, PESACH_DAY1, PESACH_DAY2, SHVEI_SHEL_PESACH, ACHRON_SHEL_PESACH, SHAVOUS_DAY1, SHAVOUS_DAY2, ROSH_HASHANAH_DAY1, ROSH_HASHANAH_DAY2, YOM_KIPPUR, SUKKOS_DAY1, SUKKOS_DAY2, SHMEINI_ATZERES, SIMCHAS_TORAH, CHOL_HAMOED_PESACH_DAY1, CHOL_HAMOED_PESACH_DAY2, CHOL_HAMOED_PESACH_DAY3, CHOL_HAMOED_PESACH_DAY4, CHOL_HAMOED_PESACH_DAY5, CHOL_HAMOED_SUKKOS_DAY1, CHOL_HAMOED_SUKKOS_DAY2, CHOL_HAMOED_SUKKOS_DAY3, CHOL_HAMOED_SUKKOS_DAY4, CHOL_HAMOED_SUKKOS_DAY5, HOSHANA_RABBAH, PESACH_SHEINI, LAG_BAOMER, TU_BAV, CHANUKAH_DAY1, CHANUKAH_DAY2, CHANUKAH_DAY3, CHANUKAH_DAY4, CHANUKAH_DAY5, CHANUKAH_DAY6, CHANUKAH_DAY7, CHANUKAH_DAY8, TU_BISHVAT, PURIM_KATAN, SHUSHAN_PURIM_KATAN, PURIM, SHUSHAN_PURIM, SHIVA_ASAR_BTAAMUZ, TISHA_BAV, TZOM_GEDALIA, ASARAH_BTEVES, TAANIS_ESTER, EREV_PESACH, EREV_SHAVOUS, EREV_ROSH_HASHANAH, EREV_YOM_KIPPUR, EREV_SUKKOS, SHKALIM, ZACHOR, PARAH, HACHODESH, ROSH_CHODESH, MACHAR_CHODESH, SHABBOS_MEVORCHIM} yomtov;

//array of parshah year types
extern const parshah parshahlist[17][56];

// hdate struct
typedef struct {
	int year;
	int month; // starts from nissan
	int day;
	int hour;
	int min;
	int sec;
	int msec;
	int wday; // weekday
	int dayofyear;
	long int offset; // timezone offset in milliseconds
	_Bool leap; // if leap year
	_Bool EY; // if Eretz Yisroel (for yomtov & parshah)
} hdate;

// day from molad tohu until Rosh Hashana
long int HebrewCalendarElapsedDays(int year);
// convert struct tm to hdate
hdate convertDate(struct tm *date);
void setEY(hdate *date, _Bool EY);
// convert a hdate to julian day
double hdatejulian(hdate *date);
// convert a hdate to gregorian date
void hdategregorian(hdate *date, struct tm *result);
// convert a gregorian date to julian day
double gregorianjulian(struct tm *date);
// convert a hdate to a time_t
time_t hdatetime_t(hdate *date);

// functions to add or subtract from a hdate field and then normalize the result
void hdateaddyear(hdate *date, int years);
void hdateaddmonth(hdate *date, int months);
void hdateaddday(hdate *date, int days);
void hdateaddhour(hdate *date, int hours);
void hdateaddminute(hdate *date, int minutes);
void hdateaddsecond(hdate *date, int seconds);
void hdateaddmsecond(hdate *date, int mseconds);
void hdateadd(hdate *date, int years, int months, int days, int hours, int minutes, int seconds, int mseconds);

// if Shabbos get the current parshah otherwise return 0
parshah getparshah(hdate *date);
// if yomtov get the current yomtov otherwise return 0
yomtov getyomtov(hdate *date);
// if Shabbos get the current special parshah otherwise return 0
yomtov getspecialshabbos(hdate *date);
// if rosh chodesh return rosh chodesh otherwise return 0
yomtov getroshchodesh(hdate *date);
// if machar chodesh return machar chodesh otherwise return 0
yomtov getmacharchodesh(hdate *date);
// if shabbos mevorchim return shabbos mevorchim otherwise return 0
yomtov getshabbosmevorchim(hdate *date);

_Bool istaanis(hdate *date);
_Bool isassurbemelachah(hdate *date);
// return 1 if cadlelighting regular, 2 if at nightfall, 3 if chanukah, or 0 if none
int iscandlelighting(hdate *date);

#endif
