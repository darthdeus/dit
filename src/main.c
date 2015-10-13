#include "udplib.h"

int main() {
  udp_bcast(3000, "hello");
  udp_bcast(3000, "worldddd");
}
