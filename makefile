#####
# Copyright (c) 2018 Y Paritcher
#####

PREFIX=$$HOME/x-tools/arm-unknown-linux-gnueabi/bin/arm-unknown-linux-gnueabi-
CC=gcc
AR=ar
RANLIB=ranlib
CFLAGS=-Wall -Wextra -O2 -std=c99 -pedantic $(INC_DIR:%=-I%)
LDLIBS=-lm

INC_DIR = include
STATICDIR=build/static/
SHAREDDIR=build/shared/
LIBDIR=lib/
SRCDIR=src/
sharedobjects := $(patsubst $(SRCDIR)%.c,$(SHAREDDIR)%.o,$(wildcard $(SRCDIR)*.c))
staticobjects := $(patsubst $(SRCDIR)%.c,$(STATICDIR)%.o,$(wildcard $(SRCDIR)*.c))

TESTDIR=test/
TESTLDFLAGS=-L$(LIBDIR)
TESTLDLIBS=-lzmanim
testobjects := $(patsubst %.c,%.o,$(wildcard $(TESTDIR)*.c))

VPATH = src $(INC_DIR)

.PHONY: clean cleaner all shared static test teststatic testshared kindle fresh

all:
	$(MAKE) shared static
	$(MAKE) test

kindle: CC = $(PREFIX)gcc
kindle: AR = $(PREFIX)ar
kindle: RANLIB = $(PREFIX)ranlib
kindle: all

shared: $(LIBDIR)libzmanim.so

static: $(LIBDIR)libzmanim.a

test: teststatic testshared

teststatic: static $(TESTDIR)teststatic

testshared: shared $(TESTDIR)testshared

$(LIBDIR)libzmanim.so: $(sharedobjects)
	$(CC) -shared $(LDFLAGS) $^ $(LDLIBS) -o $@

$(LIBDIR)libzmanim.a: $(staticobjects)
	$(AR) rc $@ $^
	$(RANLIB) $@

$(SHAREDDIR)%.o: $(SRCDIR)%.c
	$(CC) -fPIC -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(STATICDIR)%.o: $(SRCDIR)%.c
	$(CC) -static -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(TESTDIR)%.o: $(TESTDIR)%.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(TESTDIR)teststatic: $(testobjects)
	$(CC) -static $(TESTLDFLAGS) $^ $(TESTLDLIBS) -lm -o $@

$(TESTDIR)testshared: $(testobjects)
		$(CC) $(TESTLDFLAGS) $^ $(TESTLDLIBS) -o $@

testobjects: shared static

clean:
	rm -f $(SHAREDDIR)*.o $(STATICDIR)*.o $(TESTDIR)test.o

cleaner: clean
	rm -f $(LIBDIR)libzmanim.so $(LIBDIR)libzmanim.a $(TESTDIR)testshared $(TESTDIR)teststatic

fresh:
	$(MAKE) cleaner
	$(MAKE) all