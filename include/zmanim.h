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

hdate getalos(hdate *date, location *here);
hdate getalosbaalhatanya(hdate *date, location *here);
hdate getalos26degrees(hdate *date, location *here);
hdate getalos19p8degrees(hdate *date, location *here);
hdate getalos18degrees(hdate *date, location *here);
hdate getalos120(hdate *date, location *here);
hdate getalos120zmanis(hdate *date, location *here);
hdate getalos96(hdate *date, location *here);
hdate getalos96zmanis(hdate *date, location *here);
hdate getalos90(hdate *date, location *here);
hdate getalos90zmanis(hdate *date, location *here);
hdate getalos72(hdate *date, location *here);
hdate getalos72zmanis(hdate *date, location *here);
hdate getalos60(hdate *date, location *here);

hdate getmisheyakir11p5degrees(hdate *date, location *here);
hdate getmisheyakir11degrees(hdate *date, location *here);
hdate getmisheyakir10p2degrees(hdate *date, location *here);

hdate getsunrise(hdate *date, location *here);
hdate getsunrisebaalhatanya(hdate *date, location *here);
hdate getelevationsunrise(hdate *date, location *here);

hdate getshmabaalhatanya(hdate *date, location *here);
hdate getshmagra(hdate *date, location *here);
hdate getshmamga(hdate *date, location *here);

hdate gettefilabaalhatanya(hdate *date, location *here);
hdate gettefilagra(hdate *date, location *here);
hdate gettefilamga(hdate *date, location *here);

hdate getachilaschometzbaalhatanya(hdate *date, location *here);
hdate getachilaschometzgra(hdate *date, location *here);
hdate getachilaschometzmga(hdate *date, location *here);

hdate getbiurchometzbaalhatanya(hdate *date, location *here);
hdate getbiurchometzgra(hdate *date, location *here);
hdate getbiurchometzmga(hdate *date, location *here);

hdate getchatzosbaalhatanya(hdate *date, location *here);
hdate getchatzosgra(hdate *date, location *here);

hdate getminchagedolabaalhatanya(hdate *date, location *here);
hdate getminchagedolagra(hdate *date, location *here);
hdate getminchagedolamga(hdate *date, location *here);
hdate getminchagedolabaalhatanyag30m(hdate *date, location *here);
hdate getminchagedolagrag30m(hdate *date, location *here);
hdate getminchagedolamgag30m(hdate *date, location *here);

hdate getminchaketanabaalhatanya(hdate *date, location *here);
hdate getminchaketanagra(hdate *date, location *here);
hdate getminchaketanamga(hdate *date, location *here);

hdate getplagbaalhatanya(hdate *date, location *here);
hdate getplaggra(hdate *date, location *here);
hdate getplagmga(hdate *date, location *here);

hdate getcandlelighting(hdate *date, location *here);

hdate getsunset(hdate *date, location *here);
hdate getsunsetbaalhatanya(hdate *date, location *here);
hdate getelevationsunset(hdate *date, location *here);

hdate gettzaisbaalhatanya(hdate *date, location *here);
hdate gettzais8p5(hdate *date, location *here);
hdate gettzais72(hdate *date, location *here);

long getshaahzmanisbaalhatanya(hdate *date, location *here);
long getshaahzmanisgra(hdate *date, location *here);
long getshaahzmanismga(hdate *date, location *here);

#endif
