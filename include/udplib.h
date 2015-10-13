#ifndef UDPLIB_H
#define UDPLIB_H

__attribute__((noreturn)) void failed(const char* s);
void udp_listen(int port);
void udp_bcast(int port, const char* str);

#endif /* UDPLIB_H */
