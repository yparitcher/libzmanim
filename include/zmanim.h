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

#ifndef ZMANIM_H
#define ZMANIM_H

#define GEOMETRIC_ZENITH 90.0
#define ZENITH_AMITIS (GEOMETRIC_ZENITH + 1.583)

#define ZENITH_26_D (GEOMETRIC_ZENITH + 26.0)
#define ZENITH_19_P_8 (GEOMETRIC_ZENITH + 19.8)
#define ZENITH_18_D (GEOMETRIC_ZENITH + 18)
#define ZENITH_16_P_9 (GEOMETRIC_ZENITH + 16.9)
#define ZENITH_16_P_1 (GEOMETRIC_ZENITH + 16.1)
#define ZENITH_13_P_24 (GEOMETRIC_ZENITH + 13.24)

#define ZENITH_11_P_5 (GEOMETRIC_ZENITH + 11.5)
#define ZENITH_11_D (GEOMETRIC_ZENITH + 11)
#define ZENITH_10_P_2 (GEOMETRIC_ZENITH + 10.2)

#define ZENITH_3_P_65 (GEOMETRIC_ZENITH + 3.65)
#define ZENITH_3_P_676 (GEOMETRIC_ZENITH + 3.676)
#define ZENITH_3_P_7 (GEOMETRIC_ZENITH + 3.7)
#define ZENITH_3_P_8 (GEOMETRIC_ZENITH + 3.8)
#define ZENITH_4_P_37 (GEOMETRIC_ZENITH + 4.37)
#define ZENITH_4_P_61 (GEOMETRIC_ZENITH + 4.61)
#define ZENITH_4_P_8 (GEOMETRIC_ZENITH + 4.8)
#define ZENITH_5_P_88 (GEOMETRIC_ZENITH + 5.88)
#define ZENITH_5_P_95 (GEOMETRIC_ZENITH + 5.95)
#define ZENITH_6_D (GEOMETRIC_ZENITH + 6)
#define ZENITH_7_P_083 (GEOMETRIC_ZENITH + 7.083)
#define ZENITH_8_P_5 (GEOMETRIC_ZENITH + 8.5)

#define MINUTES60 (60 * 60000)
#define MINUTES72 (72 * 60000)
#define MINUTES90 (90 * 60000)
#define MINUTES96 (96 * 60000)
#define MINUTES120 (120 * 60000)

#define MINUTES18 (18 * 60000)

hdate getalos(hdate date, location here);
hdate getalosbaalhatanya(hdate date, location here);
hdate getalos26degrees(hdate date, location here);
hdate getalos19p8degrees(hdate date, location here);
hdate getalos18degrees(hdate date, location here);
hdate getalos120(hdate date, location here);
hdate getalos120zmanis(hdate date, location here);
hdate getalos96(hdate date, location here);
hdate getalos96zmanis(hdate date, location here);
hdate getalos90(hdate date, location here);
hdate getalos90zmanis(hdate date, location here);
hdate getalos72(hdate date, location here);
hdate getalos72zmanis(hdate date, location here);
hdate getalos60(hdate date, location here);

hdate getmisheyakir11p5degrees(hdate date, location here);
hdate getmisheyakir11degrees(hdate date, location here);
hdate getmisheyakir10p2degrees(hdate date, location here);

hdate getsunrise(hdate date, location here);
hdate getsunrisebaalhatanya(hdate date, location here);
hdate getelevationsunrise(hdate date, location here);

hdate getshmabaalhatanya(hdate date, location here);
hdate getshmagra(hdate date, location here);
hdate getshmamga(hdate date, location here);

hdate gettefilabaalhatanya(hdate date, location here);
hdate gettefilagra(hdate date, location here);
hdate gettefilamga(hdate date, location here);

hdate getachilaschometzbaalhatanya(hdate date, location here);
hdate getachilaschometzgra(hdate date, location here);
hdate getachilaschometzmga(hdate date, location here);

hdate getbiurchometzbaalhatanya(hdate date, location here);
hdate getbiurchometzgra(hdate date, location here);
hdate getbiurchometzmga(hdate date, location here);

hdate getchatzosbaalhatanya(hdate date, location here);
hdate getchatzosgra(hdate date, location here);

hdate getminchagedolabaalhatanya(hdate date, location here);
hdate getminchagedolagra(hdate date, location here);
hdate getminchagedolamga(hdate date, location here);
hdate getminchagedolabaalhatanyag30m(hdate date, location here);
hdate getminchagedolagrag30m(hdate date, location here);
hdate getminchagedolamgag30m(hdate date, location here);

hdate getminchaketanabaalhatanya(hdate date, location here);
hdate getminchaketanagra(hdate date, location here);
hdate getminchaketanamga(hdate date, location here);

hdate getplagbaalhatanya(hdate date, location here);
hdate getplaggra(hdate date, location here);
hdate getplagmga(hdate date, location here);

hdate getcandlelighting(hdate date, location here);

hdate getsunset(hdate date, location here);
hdate getsunsetbaalhatanya(hdate date, location here);
hdate getelevationsunset(hdate date, location here);

hdate gettzaisbaalhatanya(hdate date, location here);
hdate gettzais8p5(hdate date, location here);
hdate gettzais72(hdate date, location here);

long getshaahzmanisbaalhatanya(hdate date, location here);
long getshaahzmanisgra(hdate date, location here);
long getshaahzmanismga(hdate date, location here);

#endif
