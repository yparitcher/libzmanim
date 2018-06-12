PREFIX=$$HOME/x-tools/arm-unknown-linux-gnueabi/bin/arm-unknown-linux-gnueabi-
CC=gcc
AR=ar
RANLIB=ranlib
CFLAGS=-Wall -Wextra -std=c99 -pedantic $(INC_DIR:%=-I%)
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

VPATH = src $(INC_DIR)

.PHONY: clean cleaner all

all: $(LIBDIR)libzmanim.so $(LIBDIR)libzmanim.a $(TESTDIR)main

kindle: CC = $(PREFIX)gcc
kindle: AR = $(PREFIX)ar
kindle: RANLIB = $(PREFIX)ranlib
kindle: $(LIBDIR)libzmanim.so $(LIBDIR)libzmanim.a $(TESTDIR)main


$(LIBDIR)libzmanim.so: $(sharedobjects) # $(addprefix $(SHAREDDIR),$(wildcard *.o))
	$(CC) -shared $(LDFLAGS) $^ $(LDLIBS) -o $@

$(LIBDIR)libzmanim.a: $(staticobjects) # $(addprefix $(STATICDIR),$(wildcard *.o))
	$(AR) rc $@ $^
	$(RANLIB) $@

$(SHAREDDIR)%.o: $(SRCDIR)%.c
	$(CC) -fPIC -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(STATICDIR)%.o: $(SRCDIR)%.c
	$(CC) -static -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(TESTDIR)main: $(TESTDIR)main.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $(TESTDIR)main.c -o $(TESTDIR)main.o
	$(CC) -static $(TESTLDFLAGS) $(TESTDIR)main.o $(TESTLDLIBS) -lm -o $@static
	$(CC) $(TESTLDFLAGS) $(TESTDIR)main.o $(TESTLDLIBS) -o $@shared


clean:
	rm -f $(SHAREDDIR)*.o $(STATICDIR)*.o $(TESTDIR)main.o

cleaner: clean
	rm -f $(LIBDIR)libzmanim.so $(LIBDIR)libzmanim.a $(TESTDIR)mainshared $(TESTDIR)mainstatic
