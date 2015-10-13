ASAN=-fsanitize=address
ASAN=

ifeq ($(TARGET),server)
	TARGET=BUILD_SERVER
else
	TARGET=BUILD_CLIENT
endif



INCLUDE=-isystem include
CFLAGS=$(ASAN) -g3 -Wall -Wextra -std=gnu11 -O0 -pthread -D$(TARGET)
LIB=$(ASAN) -lncurses -lpthread
LIB=

SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c, obj/%.o, $(SRC))

.PHONY: dit

all: run

obj/%.o: src/%.c
	$(CC) $(INCLUDE) $(CFLAGS) $(CPFLAGS) -c $< -o $@

dit: $(OBJ)
	$(CC) $(LIB) $(OBJ) -o bin/dit

valgrind:
	valgrind --log-file=tmp/valgrind.txt ./bin/dit

run: dit
	./bin/dit

clean:
	rm -rf -- obj/* bin/* tmp/*

tcpdump:
	sudo tcpdump -n udp -v dst port 3000

socat:
	echo "foobar" | socat - udp-datagram:127.0.0.1:3000,broadcast
