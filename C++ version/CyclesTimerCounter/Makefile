CC=/usr/bin/g++
LDFLAGS=-march=native
SOURCES = common/hal-cortexa.c Main.cpp
HEADERS = common/hal.h

MEASURETIME = nanoseconds

ifeq "$(shell uname -m)" "aarch64"
EXTRACONDITIONS = -D __aarch64__
endif

ifeq "$(shell uname -m)" "armv7l"
EXTRACONDITIONS = -mfpu=neon
endif


test: $(HEADERS) $(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(SOURCES) -g $(EXTRACONDITIONS) -lssl -lcrypto -D $(MEASURETIME)

include common/make.mk

.PHONY: clean

clean:
	-rm test

rebuild: clean
	make