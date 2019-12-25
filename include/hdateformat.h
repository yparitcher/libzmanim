/****
Copyright (c) 2018 Y Paritcher

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; 
either version 2.1 of the License, or (at your option)any later version.

This library is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY; 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for more details. 
You should have received a copy of the GNU Lesser General Public License along with this library; 
if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA, 
or connect to: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html
****/

#ifndef HDATE_FORMAT_H
#define HDATE_FORMAT_H

//convert an int to a Hebrew char based representation. 5779 becomes תשע״ט
int numtohchar(char* buf, size_t limit, int innum);
// convert int based Hebrew month (hdate.month) to char based representation.
const char* numtohmonth(int month, int leap);
// convert int based Hebrew weekday (hdate.wday) to char based representation.
// second argument is a booean if to use שבת (true) or שביעי (false)
const char* numtowday(hdate date, _Bool shabbos);
// convert hdate to char based representation.
int hdateformat(char* buf, size_t buflen, hdate date);

// convert parshah enum to char based representation.
const char* parshahformat(parshah current);
// convert yomtov enum to char based representation.
const char* yomtovformat(yomtov current);
// convert avos int to char based representation.
const char* avosformat(int avos);

#endif
