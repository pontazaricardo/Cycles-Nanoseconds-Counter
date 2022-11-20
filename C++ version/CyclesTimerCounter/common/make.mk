


CFLAGS += -Wall -Wextra -Wpedantic -Wredundant-decls \
	-Wshadow -Wno-unused-result \
	-mtune=native -mcpu=native


CC ?= g++
CPP ?= cpp
AR ?= ar
LD ?= $(CC)
OBJCOPY ?= objcopy
SIZE ?= size


