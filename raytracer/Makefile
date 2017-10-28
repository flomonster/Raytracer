CC=gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
CPPFLAGS = -iquote includes -D_POSIX_C_SOURCE=200809L

vpath %.c src
OBJS = rt.o screen.o vect.o poly_solve.o svati.o trian.o ppm.o color.o
BIN = rt

all: $(BIN)
all: CFLAGS += -O2

debug: LDLIBS += -lasan
debug: CFLAGS += -ggdb -fstack-protector-all -fsanitize=address
debug: $(BIN)

$(BIN): LDLIBS += -lm
$(BIN): $(OBJS)

clean:
	rm -f $(BIN) $(OBJS)

.PHONY: clean debug all
