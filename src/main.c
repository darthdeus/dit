#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

__attribute__((noreturn))
void failed(const char* s) {
  perror(s);
  exit(1);
}

void udp_bcast(int port, const char* str) {
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);

  if (inet_aton("255.255.255.255", &addr.sin_addr) == 0) {
    failed("inet_aton()");
  }

  int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sock == -1) {
    failed("socket()");
  }

  int broadcastEnable = 1;
  int ret = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
  if (ret == -1) {
    failed("setsockopt()");
  }

  int stat = sendto(sock, str, strlen(str), 0, (struct sockaddr*) &addr, sizeof(addr));
  if (!stat) {
    failed("stat()");
  }

  close(sock);
}

int main() {
  udp_bcast(3000, "hello");
  udp_bcast(3000, "worldddd");
}
