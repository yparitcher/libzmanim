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
  int wday;
  int dayofyear;
  _Bool leap;
  _Bool EY;
} hdate;

typedef enum {NONE, BERESHIT, NOACH, LECH_LECHA, VAYEIRA, CHAYEI_SARAH, TOLEDOT, VAYETZE, VAYISHLACH, VAYESHEV, MIKETZ, VAYIGASH, VAYECHI, SHEMOT, VAEIRA, BO, BESHALACH, YITRO, MISHPATIM, TERUMAH, TETZAVEH, KI_TISA, VAYAKHEL, PEKUDEI, VAYIKRA, TZAV, SHEMINI, TAZRIA, METZORA, ACHAREI_MOT, KEDOSHIM, EMOR, BEHAR, BECHUKOTAI, BAMIDBAR, NASO, BEHAALOTECHA, SHLACH, KORACH, CHUKAT, BALAK, PINCHAS, MATOT, MASEI, DEVARIM, VAETCHANAN, EIKEV, REEH, SHOFTIM, KI_TEITZEI, KI_TAVO, NITZAVIM, VAYELECH, HAAZINU, VZOT_HABERACHAH, VAYAKHEL_PEKUDEI, TAZRIA_METZORA, ACHAREI_MOT_KEDOSHIM, BEHAR_BECHUKOTAI, CHUKAT_BALAK, MATOT_MASEI, NITZAVIM_VAYELECH} parshah;

typedef enum {CHOL, PESACH_DAY1, PESACH_DAY2, SHVEI_SHEL_PESACH, ACHRON_SHEL_PESACH, SHAVOUS_DAY1, SHAVOUS_DAY2, ROSH_HASHANAH_DAY1, ROSH_HASHANAH_DAY2, YOM_KIPPUR, SUKKOS_DAY1, SUKKOS_DAY2, SHMEINI_ATZERES, SIMCHAS_TORAH, CHOL_HAMOED_PESACH_DAY1, CHOL_HAMOED_PESACH_DAY2, CHOL_HAMOED_PESACH_DAY3, CHOL_HAMOED_PESACH_DAY4, CHOL_HAMOED_PESACH_DAY5, CHOL_HAMOED_SUKKOS_DAY1, CHOL_HAMOED_SUKKOS_DAY2, CHOL_HAMOED_SUKKOS_DAY3, CHOL_HAMOED_SUKKOS_DAY4, CHOL_HAMOED_SUKKOS_DAY5, HOSHANA_RABBAH, PESACH_SHEINI, LAG_BAOMER, TU_BAV, CHANUKAH_DAY1, CHANUKAH_DAY2, CHANUKAH_DAY3, CHANUKAH_DAY4, CHANUKAH_DAY5, CHANUKAH_DAY6, CHANUKAH_DAY7, CHANUKAH_DAY8, TU_BISHVAT, PURIM_KATAN, SHUSHAN_PURIM_KATAN, PURIM, SHUSHAN_PURIM, SHIVA_ASAR_BTAAMUZ, TISHA_BAV, TZOM_GEDALIA, ASARAH_BTEVES, TAANIS_ESTER, EREV_PESACH, EREV_SHAVOUS, EREV_ROSH_HASHANAH, EREV_YOM_KIPPUR, EREV_SUKKOS, SHKALIM, ZACHOR, PARAH, HACHODESH, ROSH_CHODESH, MACHAR_CHODESH, SHABBOS_MEVORCHIM} yomtov;

extern const parshah parshahlist[17][56];

void convertDate(struct tm *date, hdate *result);
void setEY(hdate *date, _Bool EY);

parshah getparshah(hdate *date);
yomtov getyomtov(hdate *date);
yomtov getspecialshabbos(hdate *date);
yomtov getroshchodesh(hdate *date);
yomtov getmacharchodesh(hdate *date);
yomtov getshabbosmevorchim(hdate *date);

_Bool istaanis(hdate *date);
_Bool isassurbemelachah(hdate *date);
int iscandlelighting(hdate *date);

#endif
