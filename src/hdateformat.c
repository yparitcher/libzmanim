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

#include <string.h>
#include <stdio.h>
#include "hebrewcalendar.h"
#include "hdateformat.h"
#ifdef _WIN32
#include "stpncpy.h"
#endif

const char* hchar[]={ "׆", "א", "ב", "ג", "ד", "ה", "ו", "ז", "ח", "ט", "י", "כ", "ל", "מ", "נ", "ס", "ע", "פ", "צ", "ק", "ר", "ש", "ת", "״", "׳"};
const char* hmonth[]={ "אדר א׳", "ניסן", "אייר", "סיון", "תמוז", "אב", "אלול", "תשרי", "חשון", "כסלו", "טבת", "שבט", "אדר", "אדר ב׳"};
const char* hwday[]={ "שביעי", "ראשון", "שני", "שלישי", "רביעי", "חמישי", "שישי", "שבת"};
const char* parshahchar[]={"\0", "בראשית", "נח", "לך לך", "וירא", "חיי שרה", "תולדות", "ויצא", "וישלח", "וישב", "מקץ", "ויגש", "ויחי", "שמות", "וארא", "בא", "בשלח", "יתרו", "משפטים", "תרומה", "תצוה", "כי תשא", "ויקהל", "פקודי", "ויקרא", "צו", "שמיני", "תזריע", "מצורע", "אחרי מות", "קדושים", "אמור", "בהר", "בחוקותי", "במדבר", "נשא", "בהעלותך", "שלח", "קרח", "חקת", "בלק", "פינחס", "מטות", "מסעי", "דברים", "ואתחנן", "עקב", "ראה", "שופטים", "כי תצא", "כי תבוא", "נצבים", "וילך", "האזינו", "וזאת הברכה", "ויקהל - פקודי", "תזריע - מצורע", "אחרי מות - קדושים", "בהר - בחוקותי", "חקת - בלק", "מטות - מסעי", "נצבים - וילך"};

const char* gethchar(int num)
{
	const char* hchar1 = NULL;
	switch(num)
	{
		case 1:
			hchar1 = hchar[1];
			break;
		case 2:
			hchar1 = hchar[2];
			break;
		case 3:
			hchar1 = hchar[3];
			break;
		case 4:
			hchar1 = hchar[4];
			break;
		case 5:
			hchar1 = hchar[5];
			break;
		case 6:
			hchar1 = hchar[6];
			break;
		case 7:
			hchar1 = hchar[7];
			break;
		case 8:
			hchar1 = hchar[8];
			break;
		case 9:
			hchar1 = hchar[9];
			break;
		case 10:
			hchar1 = hchar[10];
			break;
		case 20:
			hchar1 = hchar[11];
			break;
		case 30:
			hchar1 = hchar[12];
			break;
		case 40:
			hchar1 = hchar[13];
			break;
		case 50:
			hchar1 = hchar[14];
			break;
		case 60:
			hchar1 = hchar[15];
			break;
		case 70:
			hchar1 = hchar[16];
			break;
		case 80:
			hchar1 = hchar[17];
			break;
		case 90:
			hchar1 = hchar[18];
			break;
		case 100:
			hchar1 = hchar[19];
			break;
		case 200:
			hchar1 = hchar[20];
			break;
		case 300:
			hchar1 = hchar[21];
			break;
		case 400:
			hchar1 = hchar[22];
			break;
		case 99:
			hchar1 = hchar[23];
			break;
		case 999:
			hchar1 = hchar[24];
			break;
		default:
			hchar1 = hchar[0];
	}
	return hchar1;
}

char* addchar(char* year, int charnum, int *num, size_t *counter, size_t limit)
{
			int charvalue = charnum;
			if (charvalue == 99 || charvalue == 999){ charvalue = 0;}
			size_t len = limit-*counter;
			char* end = stpncpy(year, gethchar(charnum), len);
			*counter += len > 2 ? 2 : len;
			*num -= charvalue;
			return end;
}

int numtohchar(char* buf, size_t limit, int innum)
{
	int num = innum;
	char* year = buf;
	size_t counter = 0;
	if(num >= 1000 && num <= 10000 && num%1000 == 0)
	{
		year = addchar(year, num/1000, &num, &counter, limit);
		year = addchar(year, 999, &num, &counter, limit);
		return counter;
	}
	if(num >= 1000 && num <= 10000){ num=num%1000; }
	while (num > 0 && counter < 13)
	{
		if (num==15 || num==16)
		{
			year = addchar(year, 9, &num, &counter, limit);
			year = addchar(year, 99, &num, &counter, limit);
			year = addchar(year, num, &num, &counter, limit);
			return counter;
		}
		else if(num<10
		|| (num < 100 && num%10 == 0)
		|| (num < 500 && num%100 == 0))
		{
			if (counter!=0){ year = addchar(year, 99, &num, &counter, limit);}
			year = addchar(year, num, &num, &counter, limit);
			return counter;
		}
		else if (num > 400)
		{
			year = addchar(year, 400, &num, &counter, limit);
			continue;
		}
		else if (num > 300)
		{
			year = addchar(year, 300, &num, &counter, limit);
			continue;
		}
		else if (num > 200)
		{
			year = addchar(year, 200, &num, &counter, limit);
			continue;
		}
		else if (num > 100)
		{
			year = addchar(year, 100, &num, &counter, limit);
			continue;
		}
		else if (num/10 > 0)
		{
			year = addchar(year, num-(num%10), &num, &counter, limit);
			continue;
		}
	}
	return counter;
}

const char* numtowday(hdate date, _Bool shabbos)
{
	if (shabbos && (!date.wday)) {return hwday[7];}
	return hwday[date.wday];
}

const char* numtohmonth(int month, int leap)
{
	if (leap)
	{
		if (month == 12){ return hmonth[0];}
		if (month == 13){ return hmonth[month];}
	}
	if (month > 0 && month < 13){ return hmonth[month];}
	return "\0";
}

int hdateformat(char* buf, size_t buflen, hdate date)
{
	char day[7] = {'\0'};
	char year[13] = {'\0'};
	numtohchar(day, 6, date.day);
	const char* month = numtohmonth(date.month, date.leap);
	numtohchar(year, 12, date.year);
	return snprintf(buf, buflen, "%s %s %s", day, month, year);
}

const char* parshahformat(parshah current)
{
	return parshahchar[current];
}

const char* yomtovformat(yomtov current)
{
	switch(current)
	{
		case CHOL:
			break;
		case PESACH_DAY1:
		case PESACH_DAY2:
			return "פסח";
		case SHVEI_SHEL_PESACH:
			return "שביעי של פסח";
		case ACHRON_SHEL_PESACH:
			return "אחרון של פסח";
		case SHAVOUS_DAY1:
		case SHAVOUS_DAY2:
			return "שבועות";
		case ROSH_HASHANAH_DAY1:
		case ROSH_HASHANAH_DAY2:
			return "ראש השנה";
		case YOM_KIPPUR:
			return "יום כיפור";
		case SUKKOS_DAY1:
		case SUKKOS_DAY2:
			return "סוכות";
		case SHMEINI_ATZERES:
			return "שמיני עצרת";
		case SIMCHAS_TORAH:
			return "שמחת תורה";
		case CHOL_HAMOED_PESACH_DAY1:
		case CHOL_HAMOED_PESACH_DAY2:
		case CHOL_HAMOED_PESACH_DAY3:
		case CHOL_HAMOED_PESACH_DAY4:
		case CHOL_HAMOED_PESACH_DAY5:
			return "חול המועד פסח";
		case CHOL_HAMOED_SUKKOS_DAY1:
		case CHOL_HAMOED_SUKKOS_DAY2:
		case CHOL_HAMOED_SUKKOS_DAY3:
		case CHOL_HAMOED_SUKKOS_DAY4:
		case CHOL_HAMOED_SUKKOS_DAY5:
			return "חול המועד סוכות";
		case HOSHANA_RABBAH:
			return "הושענא רבה";
		case PESACH_SHEINI:
			return "פסח שני";
		case LAG_BAOMER:
			return "ל״ג בעומר";
		case TU_BAV:
			return "ט״ו באב";
		case CHANUKAH_DAY1:
		case CHANUKAH_DAY2:
		case CHANUKAH_DAY3:
		case CHANUKAH_DAY4:
		case CHANUKAH_DAY5:
		case CHANUKAH_DAY6:
		case CHANUKAH_DAY7:
		case CHANUKAH_DAY8:
			return "חנוכה";
		case TU_BISHVAT:
			return "ט״ו בשבט";
		case PURIM_KATAN:
			return "פורים קטן";
		case SHUSHAN_PURIM_KATAN:
			return "שושן פורים קטן";
		case PURIM:
			return "פורים";
		case SHUSHAN_PURIM:
			return "שושן פורים";
		case SHIVA_ASAR_BTAAMUZ:
			return "שבעה עשר בתמוז";
		case TISHA_BAV:
			return "ט׳ באב";
		case TZOM_GEDALIA:
			return "צום גדליה";
		case ASARAH_BTEVES:
			return "עשרה בטבת";
		case TAANIS_ESTER:
			return "תענית אסתר";
		case EREV_PESACH:
			return "ערב פסח";
		case EREV_SHAVOUS:
			return "ערב שבועות";
		case EREV_ROSH_HASHANAH:
			return "ערב ראש השנה";
		case EREV_YOM_KIPPUR:
			return "ערב יום כיפור";
		case EREV_SUKKOS:
			return "ערב סוכות";
		case SHKALIM:
			return "שקלים";
		case ZACHOR:
			return "זכור";
		case PARAH:
			return "פרה";
		case HACHODESH:
			return "החודש";
		case ROSH_CHODESH:
			return "ראש חודש";
		case MACHAR_CHODESH:
			return "מחר חודש";
		case SHABBOS_MEVORCHIM:
			return "שבת מברכים";
	}
	return "\0";
}

const char* avosformat(int avos)
{
	switch(avos)
	{
		case 1:
			return "א";
		case 2:
			return "ב";
		case 3:
			return "ג";
		case 4:
			return "ד";
		case 5:
			return "ה";
		case 6:
			return "ו";
		case 12:
			return "א-ב";
		case 34:
			return "ג-ד";
		case 56:
			return "ה-ו";
		default:
			return "\0";
	}
}
