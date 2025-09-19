CC = gcc
CFLAGS = -std=gnu99 -Wall -pedantic -Wextra

INCLUDEDIR = /opt/homebrew/opt/openssl/include
CFLAGS += -I$(INCLUDEDIR)

LIBDIR = /opt/homebrew/opt/openssl/lib
LDFLAGS = -L$(LIBDIR)

LIBS = -lcurl -lssl -lcrypto

SRC = tmail.c
OUT = tmail

TARGET = all

.PHONY: all debug clean

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS) $(LIBS)

debug: CFLAGS += -g
debug: clean all

clean:
	rm -f $(OUT)
