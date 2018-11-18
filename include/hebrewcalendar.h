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

#ifndef HEBREW_CALENDAR_H
#define HEBREW_CALENDAR_H

typedef struct {
  int year;
  int month;
  int day;
  int dayofyear;
  _Bool leap;
} hdate;

typedef enum {NONE, BERESHIT, NOACH, LECH_LECHA, VAYEIRA, CHAYEI_SARAH, TOLEDOT, VAYETZE, VAYISHLACH, VAYESHEV, MIKETZ, VAYIGASH, VAYECHI, SHEMOT, VAEIRA, BO, BESHALACH, YITRO, MISHPATIM, TERUMAH, TETZAVEH, KI_TISA, VAYAKHEL, PEKUDEI, VAYIKRA, TZAV, SHEMINI, TAZRIA, METZORA, ACHAREI_MOT, KEDOSHIM, EMOR, BEHAR, BECHUKOTAI, BAMIDBAR, NASO, BEHAALOTECHA, SHLACH, KORACH, CHUKAT, BALAK, PINCHAS, MATOT, MASEI, DEVARIM, VAETCHANAN, EIKEV, REEH, SHOFTIM, KI_TEITZEI, KI_TAVO, NITZAVIM, VAYELECH, HAAZINU, VZOT_HABERACHAH, VAYAKHEL_PEKUDEI, TAZRIA_METZORA, ACHAREI_MOT_KEDOSHIM, BEHAR_BECHUKOTAI, CHUKAT_BALAK, MATOT_MASEI, NITZAVIM_VAYELECH} parshah;

extern const parshah parshahlist[][56];

void convertDate(struct tm *date, hdate *result);

parshah getparshah(hdate *date);
parshah getparshahEY(hdate *date);

#endif
