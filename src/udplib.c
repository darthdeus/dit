#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "udplib.h"

__attribute__((noreturn)) static void failed(const char* s) {
  perror(s);
  exit(1);
}

void udp_listen(int port) {
  struct sockaddr_in addr_server, addr_client;

  int sock;
  if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
    failed("socket()");
  }

  memset((char*)&addr_server, 0, sizeof(addr_server));
  addr_server.sin_family = AF_INET;
  addr_server.sin_port = htons(port);
  addr_server.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(sock, (struct sockaddr*)&addr_server, sizeof(addr_server)) == -1) {
    failed("bind()");
  }

#define N 512
  char buf[N];

  socklen_t clen = sizeof(addr_client);
  if (recvfrom(sock, buf, N, 0, (struct sockaddr*)&addr_client, &clen) == -1) {
    failed("recvfrom()");
  }
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
  int ret = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable,
                       sizeof(broadcastEnable));
  if (ret == -1) {
    failed("setsockopt()");
  }

  int stat =
      sendto(sock, str, strlen(str), 0, (struct sockaddr*)&addr, sizeof(addr));
  if (!stat) {
    failed("stat()");
  }

  close(sock);
}
