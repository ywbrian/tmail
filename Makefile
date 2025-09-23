CC = gcc
CFLAGS = -std=gnu99 -Wall -pedantic -Wextra

# Uncomment if using homebrew
INCLUDEDIR = /opt/homebrew/opt/openssl/include
CFLAGS += -I$(INCLUDEDIR)

LIBDIR = /opt/homebrew/opt/openssl/lib
LIBS = -L$(LIBDIR) -lcurl -lssl -lcrypto

# Uncomment if using Linux base
# LIBS = -lcurl -lssl -lcrypto

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

TARGET = tmail

.PHONY: all debug clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += -g
debug: clean all

clean:
	rm -f $(TARGET) $(OBJ)
