#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/uio.h>

#define SERVER "127.0.0.1"
#define BUFLEN 512 // max length of buffer
#define PORT 3000 // destination port

void die(const char *s) {
  perror(s);
  exit(1);
}

int main() {
  struct sockaddr_in si_other;
  int s, slen = sizeof(si_other);

  char buf[BUFLEN];

  if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
    die("socket");
  }

  memset((char*)&si_other, 0, sizeof(si_other));
  si_other.sin_family = AF_INET;
  si_other.sin_port = htons(PORT);

  if (inet_aton(SERVER, &si_other.sin_addr) == 0) {
    fprintf(stderr, "inet_aton() failed\n");
    exit(1);
  }

  while (1) {
    printf("Enter message:\n");
    const char* msg = "hello";

    if (sendto(s, msg, strlen(msg), 0, (struct sockaddr*) &si_other, slen) == -1) {
      die("sendto()");
    }

    memset(buf, '\0', BUFLEN);
    break;
  }

  close(s);
  return 0;
}
