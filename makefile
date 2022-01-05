#####
# Copyright (c) 2018 Y Paritcher
#####

PREFIX=$$HOME/x-tools/arm-unknown-linux-gnueabi/bin/arm-unknown-linux-gnueabi-
PREFIXKT4=arm-kindlepw2-linux-gnueabi-
CC=gcc
AR=ar
RANLIB=ranlib
CFLAGS=-Wall -Wextra -Wno-format-truncation -O2 -flto -pedantic $(INC_DIR:%=-I%)
LDLIBS=-lm

INC_DIR = include
STATICDIR=build/static
SHAREDDIR=build/shared
LIBDIR=lib
SRCDIR=src/
EXTRADIR=extra/
sharedobjects := $(patsubst $(SRCDIR)%.c,$(SHAREDDIR)/%.o,$(wildcard $(SRCDIR)*.c))
staticobjects := $(patsubst $(SRCDIR)%.c,$(STATICDIR)/%.o,$(wildcard $(SRCDIR)*.c))
extraexecs := $(patsubst %.c, %, $(wildcard $(EXTRADIR)*.c))

TESTDIR=test/
TESTLDFLAGS=-L$(LIBDIR)
TESTLDLIBS=-lzmanim
TESTLDLIB=-l:libzmanim.a
testobjects := $(patsubst %.c,%.o,$(wildcard $(TESTDIR)*.c))

VPATH = src $(INC_DIR)

.PHONY: clean cleaner all shared static test directories teststatic testshared teststandard kindle KT4 fresh extra wasm

all:
	$(MAKE) directories
	$(MAKE) shared static
	$(MAKE) test extra

kindle: CC = $(PREFIX)gcc
kindle: AR = $(PREFIX)ar
kindle: RANLIB = $(PREFIX)ranlib
kindle: directories shared static test

KT4: CC = $(PREFIXKT4)gcc
KT4: AR = $(PREFIXKT4)gcc-ar
KT4: RANLIB = $(PREFIXKT4)gcc-ranlib
KT4: directories shared static test

wasm: CC = clang
wasm: CFLAGS= -DNOSTDLIB -Wall -Wextra --target=wasm32 -nostdlib -Wl,--no-entry -Wl,--export-all $(INC_DIR:%=-I%)
wasm: $(LIBDIR)/libzmanim.wasm

directories: | $(SHAREDDIR) $(STATICDIR) $(LIBDIR)

shared: $(LIBDIR)/libzmanim.so

static: $(LIBDIR)/libzmanim.a

test: teststatic testshared teststandard

teststatic: static $(TESTDIR)teststatic

testshared: shared $(TESTDIR)testshared

teststandard: static $(TESTDIR)test

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(STATICDIR):
	mkdir -p $(STATICDIR)

$(SHAREDDIR):
	mkdir -p $(SHAREDDIR)

$(LIBDIR)/libzmanim.so: $(sharedobjects)
	$(CC) -shared $(LDFLAGS) $^ $(LDLIBS) -o $@

$(LIBDIR)/libzmanim.a: $(staticobjects)
	$(AR) rc $@ $^
	$(RANLIB) $@

$(LIBDIR)/libzmanim.wasm: $(wildcard $(SRCDIR)hebrewcalendar.c)
	$(CC) $(CFLAGS) -o $@ $^

$(SHAREDDIR)/%.o: $(SRCDIR)%.c
	$(CC) -fPIC -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(STATICDIR)/%.o: $(SRCDIR)%.c
	$(CC) -static -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(TESTDIR)%.o: $(TESTDIR)%.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(TESTDIR)teststatic: $(testobjects)
	$(CC) -static $(TESTLDFLAGS) $^ $(TESTLDLIBS) -lm -o $@

$(TESTDIR)testshared: $(testobjects)
	$(CC) $(TESTLDFLAGS) $^ $(TESTLDLIBS) -o $@

$(TESTDIR)test: $(testobjects)
	$(CC) $(TESTLDFLAGS) $^ $(TESTLDLIB) $(LDLIBS) -o $@

testobjects: shared static

extra: static $(extraexecs)

$(extraexecs): %: %.c
	$(CC) $(CFLAGS) $(TESTLDFLAGS) $^ $(TESTLDLIB) $(LDLIBS) -o $@

clean:
	rm -f $(SHAREDDIR)/*.o $(STATICDIR)/*.o $(TESTDIR)test.o

cleaner: clean
	rm -f $(LIBDIR)/libzmanim.so $(LIBDIR)/libzmanim.a $(TESTDIR)testshared $(TESTDIR)teststatic $(TESTDIR)test $(extraexecs) $(LIBDIR)/libzmanim.wasm

fresh:
	$(MAKE) cleaner
	$(MAKE) all
