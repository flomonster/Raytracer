CC=gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
CPPFLAGS = -MMD -iquote includes -D_POSIX_C_SOURCE=200809L

vpath %.c src
OBJS = rt.o screen.o vect.o poly_solve.o svati.o trian.o ppm.o \
	color.o render.o print.o
DEPS = $(OBJS:.o=.d)

BIN = rt

all: $(BIN)
all: CFLAGS += -O2

san: CFLAGS += -fsanitize=address -fsanitize=leak -fsanitize=undefined
san: LDLIBS += -lasan -lubsan
san: debug

debug: CFLAGS += -ggdb -fstack-protector-all
debug: $(BIN)

$(BIN): LDLIBS += -lm
$(BIN): $(OBJS)

-include $(DEPS)

clean:
	rm -f $(BIN) $(OBJS)

.PHONY: clean debug all san
