#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>

__attribute__((noreturn))
void failed(const char* s) {
  perror(s);
  exit(1);
}

int main() {
  int s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (s == -1) {
    failed("socket()");
  }
}
