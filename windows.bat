::####
:: Copyright (c) 2019 Y Paritcher
::####

cd "%~dp0"

rc /nologo /v windows\libzmanim.rc

IF NOT exist lib\ ( mkdir lib )

cl /nologo /O2 /LD /I include /I windows windows\stpncpy.c src\*.c /Felib\libzmanim.dll /link /DEF:windows\libzmanim.def windows\libzmanim.res

del windows\libzmanim.res

cl /nologo /O2 /I include test\test.c /Felib\test.exe /link lib\libzmanim.lib

for %%f in (.\extra\*.c) do cl /nologo /O2 /I include %%f /Felib\%%~nf.exe /link lib\libzmanim.lib

del *.obj
