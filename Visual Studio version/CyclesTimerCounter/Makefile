CC=/usr/bin/g++
LDFLAGS=-march=native
SOURCES = common/hal-cortexa.c Main.cpp
HEADERS = common/hal.h

MEASURETIME = nanoseconds

ifeq "$(shell uname -m)" "aarch64"
CPUTOUSE = -D __aarch64__
endif

ifeq "$(shell uname -m)" "armv7l"
EXTRACONDITIONS = -mfpu=neon
CPUTOUSE = -D __armv7l__
endif

ifeq "$(shell uname -m)" "x86_64"
CPUTOUSE = -D __x8664__
MEASURETIME = nanoseconds
endif


test: $(HEADERS) $(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(SOURCES) -g $(EXTRACONDITIONS) $(CPUTOUSE) -lssl -lcrypto -D $(MEASURETIME) -Wno-unknown-pragmas

include common/make.mk

.PHONY: clean

clean:
	-rm test

rebuild: clean
	make