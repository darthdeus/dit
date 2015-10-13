#include "udplib.h"

#ifndef BUILD_SERVER

int main() {
  udp_bcast(3000, "hello");
  udp_bcast(3000, "worldddd");
}

#endif
