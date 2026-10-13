/* Run: cc -Iinclude src/*.c test/regression/luach_fixes.c -lm -o /tmp/libzmanim-luach-fixes && /tmp/libzmanim-luach-fixes */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "hebrewcalendar.h"
#include "shuir.h"

extern const char* rambamarray[];

int main(void)
{
    assert(HebrewLeapYear(5784) && !HebrewLeapYear(5786));
    for (int year = 5784; year <= 5786; year += 2) {
        hdate tishrei = hdatenew(year, 7, 7, 0, 0, 0, 0, 0);
        hdate cheshvan = hdatenew(year, 8, 7, 0, 0, 0, 0, 0);
        setEY(&tishrei, 1);
        setEY(&cheshvan, 1);
        assert(!isbirchashashanim(tishrei));
        assert(isbirchashashanim(cheshvan));
        int found_elul_shabbos = 0;
        int found_av_shabbos = 0;
        for (int day = 23; day <= 29; day++) {
            hdate elul = hdatenew(year, 6, day, 0, 0, 0, 0, 0);
            hdate av = hdatenew(year, 5, day, 0, 0, 0, 0, 0);
            if (!elul.wday) {
                found_elul_shabbos = 1;
                assert(getshabbosmevorchim(elul) == CHOL);
            }
            if (!av.wday) {
                found_av_shabbos = 1;
                assert(getshabbosmevorchim(av) == SHABBOS_MEVORCHIM);
            }
        }
        assert(found_elul_shabbos && found_av_shabbos);
    }

    hdate early = hdatenew(5700, 7, 1, 0, 0, 0, 0, 0);
    int elapsed = HebrewCalendarElapsedDays(early.year) + early.dayofyear;
    int index = (elapsed - 2097823) % 339;
    if (index < 0) index += 339;
    assert(elapsed < 2097823);
    assert(rambamarray[index] && rambamarray[index][0]);
    char buffer[256];
    rambam(early, buffer);
    assert(strstr(buffer, rambamarray[index]) != NULL);
    puts("luach fixes: ok");
    return 0;
}
