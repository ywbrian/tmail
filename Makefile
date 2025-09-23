CC = gcc
CFLAGS = -std=gnu99 -Wall -pedantic -Wextra

# Directory structure
SRCDIR = src
INCDIR = include
BUILDDIR = build

# Add include directory to compilation flags
CFLAGS += -I$(INCDIR)

# Uncomment if using homebrew
INCLUDEDIR = /opt/homebrew/opt/openssl/include
CFLAGS += -I$(INCLUDEDIR)

LIBDIR = /opt/homebrew/opt/openssl/lib
LIBS = -L$(LIBDIR) -lcurl -lssl -lcrypto

# Uncomment if using Linux base
# LIBS = -lcurl -lssl -lcrypto

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

TARGET = tmail

.PHONY: all debug clean

all: $(TARGET)

# Create build directory if it doesn't exist
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(TARGET): $(BUILDDIR) $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

# Pattern rule to compile .c files from src/ to .o files in build/
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += -g
debug: clean all

clean:
	rm -f $(TARGET)
	rm -rf $(BUILDDIR)
