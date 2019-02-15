/****
Copyright (c) 2018 Y Paritcher

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation version 2.1 of the License.

This library is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY; 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for more details. 
You should have received a copy of the GNU Lesser General Public License along with this library; 
if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA, 
or connect to: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html
****/

#include <stdio.h>
#include <time.h>
#include "hebrewcalendar.h"
#include "hdateformat.h"

const char* tehillimarray[] = { "קמ - ק״נ", "א - ט", "י - י״ז", "י״ח - כ״ב", "כ״ג - כ״ח", "כ״ט - ל״ד", "ל״ה - ל״ח", "ל״ט - מ״ג", "מ״ד - מ״ח", "מ״ט - נ״ד", "נ״ה - נ״ט", "ס - ס״ה", "ס״ו - ס״ח", "ס״ט - ע״א", "ע״ב - ע״ו", "ע״ז - ע״ח", "ע״ט - פ״ב", "פ״ג - פ״ז", "פ״ח - פ״ט", "צ - צ״ו", "צ״ז - ק״ג", "ק״ד - ק״ה", "ק״ו - ק״ז", "ק״ח - קי״ב", "קי״ג - קי״ח", "קי״ט אשרי - מצותך מאד", "קי״ט מה - לא שכחתי", "ק״כ - קל״ד", "קל״ה - קל״ט", "ק״מ - קמ״ד", "קמ״ה - ק״נ" };
const char* tanyaarray[] = { "0", "1" };
const char* rambamarray[] = { "", "הקדמת הרמב״ם למשנה תורה", "מצוות עשה", "מצוות לא תעשה", "תוכן החיבור", "משנה תורה - ספר המדע", "הלכות יסודי התורה - פרק רביעי", "הלכות יסודי התורה - פרק שביעי", "הלכות יסודי התורה - פרק עשירי", "הלכות דעות - פרק שלישי", "הלכות דעות - פרק ששי", "הלכות תלמוד תורה - פרק שני", "הלכות תלמוד תורה - פרק חמישי", "הלכות עבודת כוכבים וחקותיהם", "הלכות עבודת כוכבים - פרק רביעי", "הלכות עבודת כוכבים - פרק שביעי", "הלכות עבודת כוכבים - פרק עשירי", "הלכות תשובה", "הלכות תשובה - פרק רביעי", "הלכות תשובה - פרק שביעי", "הלכות תשובה - פרק עשירי", "הלכות קריאת שמע - פרק שלישי", "הלכות תפלה - פרק שני", "הלכות תפלה - פרק חמישי", "הלכות תפלה - פרק שמיני", "הלכות תפלה - פרק אחד עשר", "הלכות תפלה - פרק ארבעה עשר", "הלכות תפילין - פרק שני", "הלכות מזוזה - פרק חמישי", "הלכות ספר תורה - פרק שמיני", "הלכות ציצית", "הלכות ברכות", "הלכות ברכות - פרק רביעי", "הלכות ברכות - פרק שביעי", "הלכות ברכות - פרק עשירי", "הלכות מילה - פרק שני", "נוסח ברכות התפלה וסידורן", "נוסח ברכת המזון", "הלכות שבת - פרק שלישי", "הלכות שבת - פרק ששי", "הלכות שבת - פרק תשיעי", "הלכות שבת - פרק שנים עשר", "הלכות שבת - פרק חמשה עשר", "הלכות שבת - פרק שמנה עשר", "הלכות שבת - פרק אחד ועשרים", "הלכות שבת - פרק ארבעה ועשרים", "הלכות שבת - פרק שבעה ועשרים", "הלכות שבת - פרק שלשים", "הלכות עירובין - פרק שלישי", "הלכות עירובין - פרק ששי", "הלכות שביתת עשור", "הלכות שביתת יום טוב", "הלכות יום טוב - פרק רביעי", "הלכות יום טוב - פרק שביעי", "הלכות חמץ ומצה - פרק שני", "הלכות חמץ ומצה - פרק חמישי", "הלכות חמץ ומצה - פרק שמיני", "הלכות שופר - פרק שלישי", "הלכות סוכה - פרק ששי", "הלכות שקלים", "הלכות שקלים - פרק רביעי", "הלכות קדוש החדש - פרק שלישי", "הלכות קדוש החדש - פרק ששי", "הלכות קדוש החדש - פרק תשיעי", "הלכות קידוש החדש - פרק שנים עשר", "הלכות קידוש החדש - פרק חמשה עשר", "הלכות קידוש החדש - פרק שמנה עשר", "הלכות תענית - פרק שני", "הלכות תענית - פרק חמישי", "הלכות חנוכה - פרק שלישי", "הלכות אישות - פרק שני", "הלכות אישות - פרק חמישי", "הלכות אישות - פרק שמיני", "הלכות אישות - פרק אחד עשר", "הלכות אישות - פרק ארבעה עשר", "הלכות אישות - פרק שבעה עשר", "הלכות אישות - פרק עשרים", "הלכות אישות - פרק שלשה ועשרים", "הלכות גירושין", "הלכות גירושין - פרק רביעי", "הלכות גירושין - פרק שביעי", "הלכות גירושין - פרק עשירי", "הלכות גירושין - פרק שלשה עשר", "הלכות יבום וחליצה - פרק שלישי", "הלכות יבום וחליצה - פרק ששי", "הלכות נערה בתולה", "הלכות סוטה", "הלכות סוטה - פרק רביעי", "הלכות איסורי ביאה - פרק שלישי", "הלכות איסורי ביאה - פרק ששי", "הלכות איסורי ביאה - פרק תשיעי", "הלכות איסורי ביאה - פרק שנים עשר", "הלכות איסורי ביאה - פרק חמשה עשר", "הלכות איסורי ביאה - פרק שמנה עשר", "הלכות איסורי ביאה - פרק אחד ועשרים", "הלכות מאכלות אסורות - פרק שני", "הלכות מאכלות אסורות - פרק חמישי", "הלכות מאכלות אסורות - פרק שמיני", "הלכות מאכלות אסורות - פרק אחד עשר", "הלכות מאכלות אסורות - פרק ארבעה עשר", "הלכות מאכלות אסורות - פרק שבעה עשר", "הלכות שחיטה - פרק שלישי", "הלכות שחיטה - פרק ששי", "הלכות שחיטה - פרק תשיעי", "הלכות שחיטה - פרק שנים עשר", "משנה תורה - ספר הפלאה", "הלכות שבועות - פרק רביעי", "הלכות שבועות - פרק שביעי", "הלכות שבועות - פרק עשירי", "הלכות נדרים", "הלכות נדרים - פרק רביעי", "הלכות נדרים - פרק שביעי", "הלכות נדרים - פרק עשירי", "הלכות נדרים - פרק שלשה עשר", "הלכות נזירות - פרק שלישי", "הלכות נזירות - פרק ששי", "הלכות נזירות - פרק תשיעי", "הלכות ערכין וחרמין - פרק שני", "הלכות ערכין וחרמין - פרק חמישי", "הלכות ערכין וחרמין - פרק שמיני", "הלכות כלאים - פרק שלישי", "הלכות כלאים - פרק ששי", "הלכות כלאים - פרק תשיעי", "הלכות מתנות עניים - פרק שני", "הלכות מתנות עניים - פרק חמישי", "הלכות מתנות עניים - פרק שמיני", "הלכות תרומות", "הלכות תרומות - פרק רביעי", "הלכות תרומות - פרק שביעי", "הלכות תרומות - פרק עשירי", "הלכות תרומות - פרק שלשה עשר", "הלכות מעשר", "הלכות מעשר - פרק רביעי", "הלכות מעשר - פרק שביעי", "הלכות מעשר - פרק עשירי", "הלכות מעשר - פרק שלשה עשר", "הלכות מעשר שני ונטע רבעי - פרק שני", "הלכות מעשר שני ונטע רבעי - פרק חמישי", "הלכות מעשר שני ונטע רבעי - פרק שמיני", "הלכות מעשר שני ונטע רבעי - פרק אחד עשר", "הלכות בכורים - פרק שלישי", "הלכות בכורים - פרק ששי", "הלכות בכורים - פרק תשיעי", "הלכות בכורים - פרק שנים עשר", "הלכות שמיטה ויובל - פרק שלישי", "הלכות שמיטה ויובל - פרק ששי", "הלכות שמיטה ויובל - פרק תשיעי", "הלכות שמיטה ויובל - פרק שנים עשר", "הלכות בית הבחירה - פרק שני", "הלכות בית הבחירה - פרק חמישי", "הלכות בית הבחירה - פרק שמיני", "הלכות כלי המקדש - פרק שלישי", "הלכות כלי המקדש - פרק ששי", "הלכות כלי המקדש - פרק תשיעי", "הלכות ביאת המקדש - פרק שני", "הלכות ביאת המקדש - פרק חמישי", "הלכות ביאת המקדש - פרק שמיני", "הלכות איסורי מזבח - פרק שני", "הלכות איסורי המזבח - פרק חמישי", "הלכות מעשה הקרבנות", "הלכות מעשה הקרבנות - פרק רביעי", "הלכות מעשה הקרבנות - פרק שביעי", "הלכות מעשה הקרבנות - פרק עשירי", "הלכות מעשה הקרבנות - פרק שלשה עשר", "הלכות מעשה הקרבנות - פרק ששה עשר", "הלכות מעשה הקרבנות - פרק תשעה עשר", "הלכות תמידין ומוספין - פרק שלישי", "הלכות תמידין ומוספין - פרק ששי", "הלכות תמידין ומוספין - פרק תשיעי", "הלכות פסולי המוקדשין - פרק שני", "הלכות פסולי המוקדשין - פרק חמישי", "הלכות פסולי המוקדשין - פרק שמיני", "הלכות פסולי המוקדשין - פרק אחד עשר", "הלכות פסולי המוקדשין - פרק ארבעה עשר", "הלכות פסולי המוקדשין - פרק שבעה עשר", "הלכות עבודת יום הכפורים", "הלכות עבודת יום הכפורים - פרק רביעי", "הלכות מעילה - פרק שני", "הלכות מעילה - פרק חמישי", "הלכות מעילה - פרק שמיני", "הלכות קרבן פסח - פרק שלישי", "הלכות קרבן פסח - פרק ששי", "הלכות קרבן פסח - פרק תשיעי", "הלכות חגיגה - פרק שני", "הלכות בכורות - פרק שני", "הלכות בכורות - פרק חמישי", "הלכות בכורות - פרק שמיני", "הלכות שגגות - פרק שלישי", "הלכות שגגות - פרק ששי", "הלכות שגגות - פרק תשיעי", "הלכות שגגות - פרק שנים עשר", "הלכות שגגות - פרק חמשה עשר", "הלכות מחוסרי כפרה - פרק שלישי", "הלכות תמורה", "הלכות תמורה - פרק רביעי", "הלכות טומאת מת - פרק שלישי", "הלכות טומאת מת - פרק ששי", "הלכות טומאת מת - פרק תשיעי", "הלכות טומאת מת - פרק שנים עשר", "הלכות טומאת מת - פרק חמשה עשר", "הלכות טומאת מת - פרק שמונה עשר", "הלכות טומאת מת - פרק אחד ועשרים", "הלכות טומאת מת - פרק ארבעה ועשרים", "הלכות פרה אדומה - פרק שני", "הלכות פרה אדומה - פרק חמישי", "הלכות פרה אדומה - פרק שמיני", "הלכות פרה אדומה - פרק אחד עשר", "הלכות פרה אדומה - פרק ארבעה עשר", "הלכות טומאת צרעת - פרק שני", "הלכות טומאת צרעת - פרק חמישי", "הלכות טומאת צרעת - פרק שמיני", "הלכות טומאת צרעת - פרק אחד עשר", "הלכות טומאת צרעת - פרק ארבעה עשר", "הלכות מטמאי משכב ומושב", "הלכות מטמאי משכב ומושב - פרק רביעי", "הלכות מטמאי משכב ומושב - פרק שביעי", "הלכות מטמאי משכב ומושב - פרק עשירי", "הלכות מטמאי משכב ומושב - פרק שלשה עשר", "הלכות אבות הטומאות - פרק שלישי", "הלכות אבות הטומאות - פרק ששי", "הלכות אבות הטומאות - פרק תשיעי", "הלכות אבות הטומאות - פרק שנים עשר", "הלכות אבות הטומאות - פרק חמשה עשר", "הלכות אבות הטומאות - פרק שמונה עשר", "הלכות טומאת אוכלין", "הלכות טומאת אוכלין - פרק רביעי", "הלכות טומאת אוכלין - פרק שביעי", "הלכות טומאת אוכלין - פרק עשירי", "הלכות טומאת אוכלין - פרק שלשה עשר", "הלכות טומאת אוכלין - פרק ששה עשר", "הלכות כלים - פרק שלישי", "הלכות כלים - פרק ששי", "הלכות כלים - פרק תשיעי", "הלכות כלים - פרק שנים עשר", "הלכות כלים - פרק חמשה עשר", "הלכות כלים - פרק שמונה עשר", "הלכות כלים - פרק אחד ועשרים", "הלכות כלים - פרק ארבעה ועשרים", "הלכות כלים - פרק שבעה ועשרים", "הלכות מקואות - פרק שני", "הלכות מקואות - פרק חמישי", "הלכות מקואות - פרק שמיני", "הלכות מקואות - פרק אחד עשר", "הלכות נזקי ממון - פרק שלישי", "הלכות נזקי ממון - פרק ששי", "הלכות נזקי ממון - פרק תשיעי", "הלכות נזקי ממון - פרק שנים עשר", "הלכות גניבה", "הלכות גניבה - פרק רביעי", "הלכות גניבה - פרק שביעי", "הלכות גזלה ואבדה", "הלכות גזלה ואבדה - פרק רביעי", "הלכות גזלה ואבדה - פרק שביעי", "הלכות גזלה ואבדה - פרק עשירי", "הלכות גזלה ואבדה - פרק שלשה עשר", "הלכות גזלה ואבדה - פרק ששה עשר", "הלכות חובל ומזיק", "הלכות חובל ומזיק - פרק רביעי", "הלכות חובל ומזיק - פרק שביעי", "הלכות רוצח ושמירת נפש - פרק שני", "הלכות רוצח ושמירת נפש - פרק חמישי", "הלכות רוצח ושמירת נפש - פרק שמיני", "הלכות רוצח ושמירת נפש - פרק אחד עשר", "משנה תורה - ספר קנין", "הלכות מכירה - פרק רביעי", "הלכות מכירה - פרק שביעי", "הלכות מכירה - פרק עשירי", "הלכות מכירה - פרק שלשה עשר", "הלכות מכירה - פרק ששה עשר", "הלכות מכירה - פרק תשעה עשר", "הלכות מכירה - פרק שנים ועשרים", "הלכות מכירה - פרק חמשה ועשרים", "הלכות מכירה - פרק שמונה ועשרים", "הלכות זכיה ומתנה", "הלכות זכיה ומתנה - פרק רביעי", "הלכות זכיה ומתנה - פרק שביעי", "הלכות זכיה ומתנה - פרק עשירי", "הלכות שכנים", "הלכות שכנים - פרק רביעי", "הלכות שכנים - פרק שביעי", "הלכות שכנים - פרק עשירי", "הלכות שכנים - פרק שלשה עשר", "הלכות שלוחין ושותפים - פרק שני", "הלכות שלוחין ושותפים - פרק חמישי", "הלכות שלוחין ושותפים - פרק שמיני", "הלכות עבדים", "הלכות עבדים - פרק רביעי", "הלכות עבדים - פרק שביעי", "משנה תורה - ספר משפטים", "הלכות שכירות - פרק רביעי", "הלכות שכירות - פרק שביעי", "הלכות שכירות - פרק עשירי", "הלכות שכירות - פרק שלשה עשר", "הלכות שאלה ופקדון - פרק שלישי", "הלכות שאלה ופקדון - פרק ששי", "הלכות מלוה ולוה", "הלכות מלוה ולוה - פרק רביעי", "הלכות מלוה ולוה - פרק שביעי", "הלכות מלוה ולוה - פרק עשירי", "הלכות מלוה ולוה - פרק שלשה עשר", "הלכות מלוה ולוה - פרק ששה עשר", "הלכות מלוה ולוה - פרק תשעה עשר", "הלכות מלוה ולוה - פרק שנים ועשרים", "הלכות מלוה ולוה - פרק חמשה ועשרים", "הלכות טוען ונטען", "הלכות טוען ונטען - פרק רביעי", "הלכות טוען ונטען - פרק שביעי", "הלכות טוען ונטען - פרק עשירי", "הלכות טוען ונטען - פרק שלשה עשר", "הלכות טוען ונטען - פרק ששה עשר", "הלכות נחלות - פרק שלישי", "הלכות נחלות - פרק ששי", "הלכות נחלות - פרק תשיעי", "משנה תורה - ספר שופטים", "הלכות סנהדרין - פרק רביעי", "הלכות סנהדרין - פרק שביעי", "הלכות סנהדרין - פרק עשירי", "הלכות סנהדרין - פרק שלשה עשר", "הלכות סנהדרין - פרק ששה עשר", "הלכות סנהדרין - פרק תשעה עשר", "הלכות סנהדרין - פרק שנים ועשרים", "הלכות סנהדרין - פרק חמשה ועשרים", "הלכות עדות - פרק שני", "הלכות עדות - פרק חמישי", "הלכות עדות - פרק שמיני", "הלכות עדות - פרק אחד עשר", "הלכות עדות - פרק ארבעה עשר", "הלכות עדות - פרק שבעה עשר", "הלכות עדות - פרק עשרים", "הלכות ממרים", "הלכות ממרים - פרק רביעי", "הלכות ממרים - פרק שביעי", "הלכות אבל - פרק שלישי", "הלכות אבל - פרק ששי", "הלכות אבל - פרק תשיעי", "הלכות אבל - פרק שנים עשר", "הלכות מלכים ומלחמותיהם", "הלכות מלכים - פרק רביעי", "הלכות מלכים - פרק שביעי", "הלכות מלכים - פרק עשירי" };

int chumash(hdate date, char* buffer)
{
	parshah current = NOPARSHAH;
	hdate shabbos = date;
	int st = shabbos.EY ? 22 : 23;
	for (hdateaddday(&shabbos, 7-shabbos.wday); (current = getparshah(shabbos)) == NOPARSHAH; hdateaddday(&shabbos, 7)){}
	if (current == BERESHIT)
	{
		if (date.day < st) {current = VZOT_HABERACHAH;}
		else if  (date.day == st){
			if (date.wday == 1){
				return sprintf(buffer, "פרשת %s %s עם פירש״י", parshahformat(BERESHIT), numtowday(date, 0));
			}else if (date.wday == 7){
				return sprintf(buffer, "פרשת %s %s עם פירש״י", parshahformat(VZOT_HABERACHAH), numtowday(date, 0));
			}else{
				return sprintf(buffer, "פרשת %s %s - שביעי, %s ראשון - %s עם פירש״י", parshahformat(VZOT_HABERACHAH), numtowday(date, 0), parshahformat(BERESHIT), numtowday(date, 0));
			}
		}
	}
	return sprintf(buffer, "פרשת %s %s עם פירש״י", parshahformat(current), numtowday(date, 0));
}

int tehillim(hdate date, char* buffer)
{
	int current = date.day;
	if (current == 29 && LastDayOfHebrewMonth(date.month, date.year) == 30) {current = 0;}
	return sprintf(buffer, "%s %s", "תהלים", tehillimarray[current]);
}

int rambam(hdate date, char* buffer)
{
	int current = ((HebrewCalendarElapsedDays(date.year)+date.dayofyear)- (2097823)) % 339;
	return sprintf(buffer, "%s %s", "רמב״ם", rambamarray[current]);
}