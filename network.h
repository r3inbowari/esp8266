/**
  network content header
  @author r3inbowari
  @date 2020/6/21
*/

#ifndef __NET_H
#define __NET_H

#define TCP_CONNECT_TIMEOUT 5000

void connect_wifi(char * __ssid, char *__password);
void network_init();
void create_ap();

void tcp_init();
void close_tcp();
bool connect_tcp();
void resetTCP(char *phost, uint16_t pport);
void check_tcp_alive();

extern char* host;
extern uint16_t port;

#endif
