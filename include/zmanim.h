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

typedef long long int ltime;

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

ltime getalos();
ltime getalosbaalhatanya();
ltime getalos26degrees();
ltime getalos19p8degrees();
ltime getalos18degrees();
ltime getalos120();
ltime getalos120zmanis();
ltime getalos96();
ltime getalos96zmanis();
ltime getalos90();
ltime getalos90zmanis();
ltime getalos72();
ltime getalos72zmanis();
ltime getalos60();

ltime getmisheyakir11p5degrees();
ltime getmisheyakir11degrees();
ltime getmisheyakir10p2degrees();

ltime getsunrise();
ltime getsunrisebaalhatanya();
ltime getelevationsunrise();

ltime getshmabaalhatanya();
ltime getshmagra();
ltime getshmamga();

ltime gettefilabaalhatanya();
ltime gettefilagra();
ltime gettefilamga();

ltime getachilaschometzbaalhatanya();
ltime getachilaschometzgra();
ltime getachilaschometzmga();

ltime getbiurchometzbaalhatanya();
ltime getbiurchometzgra();
ltime getbiurchometzmga();

ltime getchatzosbaalhatanya();
ltime getchatzosgra();

ltime getminchagedolabaalhatanya();
ltime getminchagedolagra();
ltime getminchagedolamga();
ltime getminchagedolabaalhatanyag30m();
ltime getminchagedolagrag30m();
ltime getminchagedolamgag30m();

ltime getminchaketanabaalhatanya();
ltime getminchaketanagra();
ltime getminchaketanamga();

ltime getplagbaalhatanya();
ltime getplaggra();
ltime getplagmga();

ltime getcandlelighting();

ltime getsunset();
ltime getsunsetbaalhatanya();
ltime getelevationsunset();

ltime gettzaisbaalhatanya();
ltime gettzais8p5();
ltime gettzais72();

long getshaahzmanisbaalhatanya();
long getshaahzmanisgra();
long getshaahzmanismga();

#endif
