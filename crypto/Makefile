CC := gcc
AR := ar
ARFLAGS := -crs
CFLAGS := -Wno-deprecated-declarations -Wall -Wextra -Werror -pedantic
DEPEND := -lssl -lcrypto
PROJECT := hblk_crypto
STATIC_LIB := lib$(PROJECT).a
SRC_FILES := $(wildcard *.c)
OBJ_FILES := $(patsubst %.c, %.o, $(SRC_FILES))

.PHONY: all clean

all: $(STATIC_LIB)

$(STATIC_LIB): $(OBJ_FILES)
	$(AR) $(ARFLAGS) $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(DEPEND)

clean:
	rm -f $(STATIC_LIB) *.o
