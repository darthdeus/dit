ASAN=-fsanitize=address
ASAN=

ifeq ($(TARGET),server)
	TARGET=BUILD_SERVER
else
	TARGET=BUILD_CLIENT
endif

INCLUDE=-isystem include
CFLAGS=$(ASAN) -g3 -Wall -Wextra -std=gnu11 -O0 -D$(TARGET)
CXXFLAGS=$(ASAN) -g3 -Wall -Wextra -std=c++11 -O0 -D$(TARGET)
LIB=$(ASAN) -lncurses

SRC=$(wildcard src/*.c src/*.cpp)
TMPOBJ=$(patsubst src/%.c, obj/%.o, $(SRC))
OBJ=$(patsubst src/%.cpp, obj/%.o, $(TMPOBJ))

.PHONY: dit

all: run

obj/%.o: src/%.c
	$(CC) $(INCLUDE) $(CFLAGS) $(CPFLAGS) -c $< -o $@

obj/%.o: src/%.cpp
	$(CXX) $(INCLUDE) $(CXXFLAGS) $(CPFLAGS) -c $< -o $@

dit: $(OBJ)
	$(CC) $(LIB) $(OBJ) -o bin/dit

valgrind:
	valgrind --log-file=tmp/valgrind.txt ./bin/dit

run: dit
	./bin/dit

clean:
	rm -rf -- obj/* bin/* tmp/*

tcpdump:
	sudo tcpdump -n udp -v dst port 3000 -X

socat:
	echo foobar | socat - udp-datagram:255.255.255.255:3000,broadcast
