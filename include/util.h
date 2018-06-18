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

#ifndef UTIL_H
#define UTIL_H

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

typedef struct {
  struct tm tm;
  int tmz_msec;
  long int tmz_gmtoff;
} tmz;

typedef struct {
	double latitude;
	double longitude;
	double elevation;
} location;

typedef union {
	unsigned int s;
	struct t {
		unsigned int tm :1;
		unsigned int of :1;
		unsigned int la :1;
		unsigned int lo :1;
		unsigned int el :1;
	}bf;
}settings;

#define FULLSETUP 31

#endif
