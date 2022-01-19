ROOT = ../../thirdparty

CC = g++
INCLUDE = -I $(ROOT)/include
CFLAGS = -Wall -g -std=c++17 -shared -fpic $(INCLUDE)
LDFLAGS = -llua

SRC = player.cpp
TARGET = player.so
 

all: shared

shared:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SRC)
	@rm -rf *.dSYM

static:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(ROOT)/lib/liblua.a
	@rm -rf *.dSYM

test:
	lua test.lua

clean:
	@rm -f $(TARGET)