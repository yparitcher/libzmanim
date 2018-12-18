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

int settime(time_t *time);
int setoffset(double offset);
int setlatitude(double latitude);
int setlongitude(double longitude);
int setelevation(double elevation);
int setall(time_t *time, double offset, double latitude, double longitude, double elevation);
unsigned int  checksetup();

time_t gettime();
double getoffset();
double getlatitude();
double getlongitude();
double getelevation();

hdate getalos(hdate *date);
hdate getalosbaalhatanya(hdate *date);
hdate getalos26degrees(hdate *date);
hdate getalos19p8degrees(hdate *date);
hdate getalos18degrees(hdate *date);
hdate getalos120(hdate *date);
hdate getalos120zmanis(hdate *date);
hdate getalos96(hdate *date);
hdate getalos96zmanis(hdate *date);
hdate getalos90(hdate *date);
hdate getalos90zmanis(hdate *date);
hdate getalos72(hdate *date);
hdate getalos72zmanis(hdate *date);
hdate getalos60(hdate *date);

hdate getmisheyakir11p5degrees(hdate *date);
hdate getmisheyakir11degrees(hdate *date);
hdate getmisheyakir10p2degrees(hdate *date);

hdate getsunrise(hdate *date);
hdate getsunrisebaalhatanya(hdate *date);
hdate getelevationsunrise(hdate *date);

hdate getshmabaalhatanya(hdate *date);
hdate getshmagra(hdate *date);
hdate getshmamga(hdate *date);

hdate gettefilabaalhatanya(hdate *date);
hdate gettefilagra(hdate *date);
hdate gettefilamga(hdate *date);

hdate getachilaschometzbaalhatanya(hdate *date);
hdate getachilaschometzgra(hdate *date);
hdate getachilaschometzmga(hdate *date);

hdate getbiurchometzbaalhatanya(hdate *date);
hdate getbiurchometzgra(hdate *date);
hdate getbiurchometzmga(hdate *date);

hdate getchatzosbaalhatanya(hdate *date);
hdate getchatzosgra(hdate *date);

hdate getminchagedolabaalhatanya(hdate *date);
hdate getminchagedolagra(hdate *date);
hdate getminchagedolamga(hdate *date);
hdate getminchagedolabaalhatanyag30m(hdate *date);
hdate getminchagedolagrag30m(hdate *date);
hdate getminchagedolamgag30m(hdate *date);

hdate getminchaketanabaalhatanya(hdate *date);
hdate getminchaketanagra(hdate *date);
hdate getminchaketanamga(hdate *date);

hdate getplagbaalhatanya(hdate *date);
hdate getplaggra(hdate *date);
hdate getplagmga(hdate *date);

hdate getcandlelighting(hdate *date);

hdate getsunset(hdate *date);
hdate getsunsetbaalhatanya(hdate *date);
hdate getelevationsunset(hdate *date);

hdate gettzaisbaalhatanya(hdate *date);
hdate gettzais8p5(hdate *date);
hdate gettzais72(hdate *date);

long getshaahzmanisbaalhatanya(hdate *date);
long getshaahzmanisgra(hdate *date);
long getshaahzmanismga(hdate *date);

#endif
