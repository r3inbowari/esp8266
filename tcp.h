/**
   mux tcp header
   @author r3inbowari
   @date 2020/6/22
*/

#ifndef __ESP_TCP_H
#define __ESP_TCP_H

#define TCP_CONNECT_TIMEOUT 5000
#include "system.h"
#include "user.h"
#include "utils.h"

typedef char* (*pGetter)();

class ESPTCP {
  private:
    char* host;
    uint16_t port;
    WiFiClient client;
    unsigned long timeout;

  public:

    /**
       构造函数
       两个函数地址回调
       @callback1 host
       @callback2 port
    */
    ESPTCP(pGetter phost, pGetter pport);

    /**
      默认构造
    */
    ESPTCP();

    /**
      关闭tcp
    */
    void close_tcp();

    /**
      esp 建立tcp连接
      @return 是否成功连接到服务器
    */
    bool connect_tcp();

    // 重设
    void resetTCP(pGetter phost, pGetter pport);
    
    // 检查
    void check_tcp_alive();

    /**
      \r\n response end tag
    */
    void tcp_send(char *msg);

    /**
       \r response end tag
       @see bigiot.net doc
    */
    void tcp_send_r(char *msg);
};



#endif
