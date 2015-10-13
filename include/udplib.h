#ifndef UDPLIB_H
#define UDPLIB_H

void udp_listen(int port);
void udp_bcast(int port, const char* str);

#endif /* UDPLIB_H */
