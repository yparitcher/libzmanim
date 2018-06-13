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

.PHONY: clean cleaner all

all: shared static test

kindle: CC = $(PREFIX)gcc
kindle: AR = $(PREFIX)ar
kindle: RANLIB = $(PREFIX)ranlib
kindle: shared static test

shared: $(LIBDIR)libzmanim.so

static: $(LIBDIR)libzmanim.a

test: $(TESTDIR)mainstatic $(TESTDIR)mainshared

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

$(TESTDIR)mainstatic: $(testobjects)
	$(CC) -static $(TESTLDFLAGS) $^ $(TESTLDLIBS) -lm -o $@

$(TESTDIR)mainshared: $(testobjects)
		$(CC) $(TESTLDFLAGS) $^ $(TESTLDLIBS) -o $@

clean:
	rm -f $(SHAREDDIR)*.o $(STATICDIR)*.o $(TESTDIR)main.o

cleaner: clean
	rm -f $(LIBDIR)libzmanim.so $(LIBDIR)libzmanim.a $(TESTDIR)mainshared $(TESTDIR)mainstatic
