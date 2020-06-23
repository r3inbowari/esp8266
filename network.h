/**
  network content header
  @author r3inbowari
  @date 2020/6/21
*/

#ifndef __NET_H
#define __NET_H

#include "system.h"
#include "user.h"
#include "tcp.h"
#include "utils.h"
#include "bigiot.h"

#define TCP_CONNECT_TIMEOUT 5000

extern ESPTCP *tcp_golang;
extern BigIOT *tcp_bigiot;

void connect_wifi(char * __ssid, char *__password);
void network_init();
void create_ap();

extern char* host;
extern uint16_t port;

#endif
