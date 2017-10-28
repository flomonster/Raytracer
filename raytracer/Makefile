CC=gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
CPPFLAGS = -Iincludes -D_POSIX_C_SOURCE=200809L

vpath %.c src
OBJS = rt.o screen.o vect.o poly_solve.o svati.o
BIN = rt


all: $(BIN)
all: CFLAGS += -O2

debug: $(BIN)
debug: CFLAGS += -ggdb -fstack-protector-all -fsanitize=address
debug: LDLIBS += -lasan

$(BIN): $(OBJS)

clean:
	rm -f $(BIN) $(OBJS)
