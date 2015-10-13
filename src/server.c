#include "udplib.h"

#ifdef BUILD_SERVER

int main() {
  udp_listen(3000);
}

#endif
