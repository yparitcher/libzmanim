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

time_t gettime();
double getoffset();
double getlatitude();
double getlongitude();
double getelevation();

ltime getsunrise();
ltime getsunrisebaalhatanya();
ltime getelevationsunrise();
ltime getsunset();
ltime getsunsetbaalhatanya();
ltime getelevationsunset();

ltime getalos();
ltime getalosbaalhatanya();
ltime getalos120();
ltime getalos72();

ltime getmisheyakir10point2degrees();

ltime getshmabaalhatanya();
ltime getshmagra();
ltime getshmamga();

ltime gettzais72();

#endif
