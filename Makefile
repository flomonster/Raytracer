CC=gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
CPPFLAGS = -Iraytracer/includes -D_POSIX_C_SOURCE=200809L

vpath %.c raytracer
OBJS = raytracer.o
BIN = rt


all: $(BIN)
all: CFLAGS += -O2

debug: $(BIN)
debug: CFLAGS += -g -fstack-protector-all -fsanitize=address
debug: LDLIBS += -lasan

$(BIN): $(OBJS)

clean:
	rm -f $(BIN) $(OBJS)
