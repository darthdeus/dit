ASAN=-fsanitize=address

INCLUDE=-Iinclude
CFLAGS=$(ASAN) -g3 -Wall -Wextra -std=gnu11 -O0 -pthread
LIB=$(ASAN) -lncurses -lpthread

SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c, obj/%.o, $(SRC))

.PHONY: dit

all: run

obj/%.o: src/%.c
	$(CC) $(CFLAGS) $(CPFLAGS) -c $< -o $@

dit:
	$(CC) $(LIB) $(OBJS) -o bin/dit

run: dit
	./bin/dit
