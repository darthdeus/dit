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

dit: $(OBJ)
	$(CC) $(LIB) $(OBJ) -o bin/dit

valgrind:
	valgrind --log-file=tmp/valgrind.txt ./bin/dit

run: dit
	./bin/dit

clean:
	rm -rf -- obj/* bin/* tmp/*
