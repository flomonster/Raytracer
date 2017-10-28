CC=gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
CPPFLAGS = -MMD -iquote includes -D_POSIX_C_SOURCE=200809L

vpath %.c src
OBJS = rt.o screen.o vect.o poly_solve.o svati.o trian.o ppm.o \
	color.o render.o print.o
DEPS = $(OBJS:.o=.d)
PROFS = $(OBJS:.o=.gcda)

BIN = rt

all: lto

lto: CFLAGS += -flto
lto: LDFLAGS += -flto
lto: release


release: $(BIN)
release: CFLAGS += -O3


prof_gen: lto
prof_gen: LDLIBS += -lgcov
prof_gen: CFLAGS += -fprofile-generate


prof_use: lto
prof_use: CFLAGS += -fprofile-use


san: CFLAGS += -fsanitize=address -fsanitize=leak -fsanitize=undefined
san: LDLIBS += -lasan -lubsan
san: debug


debug: CFLAGS += -ggdb -fstack-protector-all
debug: $(BIN)


$(BIN): LDLIBS += -lm
$(BIN): $(OBJS)


-include $(DEPS)


base_clean:
	rm -f $(BIN) $(OBJS)

clean: base_clean
	rm -f $(PROFS)

.PHONY: base_clean clean debug all san release lto prof_gen prof_use
