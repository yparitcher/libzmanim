#include "ffi-cdecl.h"
#include <time.h>
#include "hebrewcalendar.h"
#include "zmanim.h"
#include "hdateformat.h"
#include "shuir.h"

cdecl_type(location)
cdecl_type(parshah)
cdecl_type(yomtov)
cdecl_type(hdate)
cdecl_c99_type(molad, hdate)

cdecl_func(LastDayOfHebrewMonth)
cdecl_func(HebrewLeapYear)
cdecl_func(HebrewCalendarElapsedDays)
cdecl_func(convertDate)
cdecl_func(setEY)

cdecl_func(hdatejulian)
cdecl_func(hdategregorian)
cdecl_func(gregorianjulian)
cdecl_func(hdatetime_t)

cdecl_func(hdatecompare)
cdecl_func(hdateaddyear)
cdecl_func(hdateaddmonth)
cdecl_func(hdateaddday)
cdecl_func(hdateaddhour)
cdecl_func(hdateaddminute)
cdecl_func(hdateaddsecond)
cdecl_func(hdateaddmsecond)
cdecl_func(hdateadd)

cdecl_func(getmolad)
cdecl_func(getparshah)
cdecl_func(getyomtov)
cdecl_func(getspecialshabbos)
cdecl_func(getroshchodesh)
cdecl_func(getmacharchodesh)
cdecl_func(getshabbosmevorchim)
cdecl_func(getomer)
cdecl_func(getavos)
cdecl_func(istaanis)
cdecl_func(isassurbemelachah)
cdecl_func(iscandlelighting)
cdecl_func(isbirchashachama)
cdecl_func(isbirchashashanim)
cdecl_func(getbirchashashanim)

cdecl_func(getalos)
cdecl_func(getalosbaalhatanya)
cdecl_func(getalos26degrees)
cdecl_func(getalos19p8degrees)
cdecl_func(getalos18degrees)
cdecl_func(getalos120)
cdecl_func(getalos120zmanis)
cdecl_func(getalos96)
cdecl_func(getalos96zmanis)
cdecl_func(getalos90)
cdecl_func(getalos90zmanis)
cdecl_func(getalos72)
cdecl_func(getalos72zmanis)
cdecl_func(getalos60)
cdecl_func(getmisheyakir11p5degrees)
cdecl_func(getmisheyakir11degrees)
cdecl_func(getmisheyakir10p2degrees)
cdecl_func(getsunrise)
cdecl_func(getsunrisebaalhatanya)
cdecl_func(getelevationsunrise)
cdecl_func(getshmabaalhatanya)
cdecl_func(getshmagra)
cdecl_func(getshmamga)
cdecl_func(gettefilabaalhatanya)
cdecl_func(gettefilagra)
cdecl_func(gettefilamga)
cdecl_func(getachilaschometzbaalhatanya)
cdecl_func(getachilaschometzgra)
cdecl_func(getachilaschometzmga)
cdecl_func(getbiurchometzbaalhatanya)
cdecl_func(getbiurchometzgra)
cdecl_func(getbiurchometzmga)
cdecl_func(getchatzosbaalhatanya)
cdecl_func(getchatzosgra)
cdecl_func(getminchagedolabaalhatanya)
cdecl_func(getminchagedolagra)
cdecl_func(getminchagedolamga)
cdecl_func(getminchagedolabaalhatanyag30m)
cdecl_func(getminchagedolagrag30m)
cdecl_func(getminchagedolamgag30m)
cdecl_func(getminchaketanabaalhatanya)
cdecl_func(getminchaketanagra)
cdecl_func(getminchaketanamga)
cdecl_func(getplagbaalhatanya)
cdecl_func(getplaggra)
cdecl_func(getplagmga)
cdecl_func(getcandlelighting)
cdecl_func(getsunset)
cdecl_func(getsunsetbaalhatanya)
cdecl_func(getelevationsunset)
cdecl_func(gettzaisbaalhatanya)
cdecl_func(gettzais8p5)
cdecl_func(gettzais72)
cdecl_func(getmolad7days)
cdecl_func(getmoladhalfmonth)
cdecl_func(getmolad15days)
cdecl_func(getshaahzmanisbaalhatanya)
cdecl_func(getshaahzmanisgra)
cdecl_func(getshaahzmanismga)

cdecl_func(numtohchar)
cdecl_func(numtohmonth)
cdecl_func(numtowday)
cdecl_func(hdateformat)
cdecl_func(parshahformat)
cdecl_func(yomtovformat)
cdecl_func(avosformat)


cdecl_func(chumash)
cdecl_func(tehillim)
cdecl_func(tanya)
cdecl_func(rambam)