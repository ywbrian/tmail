CC = gcc
CFLAGS = -std=gnu99 -Wall -pedantic -Wextra

LIBS = -lcurl -lssl -lcrypto

SRC = tmail.c commands.c utils.c session.c email.c
OBJ = $(SRC:.c=.o)
OUT = tmail

TARGET = all

.PHONY: all debug clean

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUT) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += -g
debug: clean all

clean:
	rm -f $(OUT) $(OBJ)
