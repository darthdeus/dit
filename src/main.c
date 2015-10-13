#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

__attribute__((noreturn))
void failed(const char* s) {
  perror(s);
  exit(1);
}

int main() {
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(3000);

  if (inet_aton("127.0.0.1", &addr.sin_addr) == 0) {
    failed("inet_aton()");
  }

  const char* str = "hello";

  int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sock == -1) {
    failed("socket()");
  }

  int stat = sendto(sock, str, strlen(str), 0, (struct sockaddr*) &addr, sizeof(addr));
  if (!stat) {
    failed("stat()");
  }

}
