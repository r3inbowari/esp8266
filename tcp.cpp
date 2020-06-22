/**
   mux tcp realize
   @author r3inbowari
   @date 2020/6/22
*/

#include "tcp.h"

/**
   构造函数
   两个函数地址回调
   @callback1 host
   @callback2 port
*/
ESPTCP::ESPTCP(pGetter phost, pGetter pport) {

  this->host = phost();
  char *tempPortArr = pport();
  this->port = tempPortArr[0] | uint16_t(tempPortArr[1]) << 8;
  this->connect_tcp();
  this->timeout = millis();
}

/**
  默认构造
*/
ESPTCP::ESPTCP() {
  this->host = getHost();
  char *tempPortArr = getPort();
  this->port = tempPortArr[0] | uint16_t(tempPortArr[1]) << 8;
  this->connect_tcp();
  this->timeout = millis();
}

/**
  关闭tcp
*/
void ESPTCP::close_tcp() {
  client.stop();
}

/**
  esp 建立tcp连接
  @return 是否成功连接到服务器
*/
bool ESPTCP::connect_tcp() {
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);
  return this->client.connect(host, port);
}

// 重设
void ESPTCP::resetTCP(pGetter phost, pGetter pport) {
  close_tcp();
  host = phost();
  port = pchar2uint16_t(pport());
  // connect_tcp();
}

// static unsigned long timeout = millis();

// 检查
void ESPTCP::check_tcp_alive() {
  // 记录最后一次超时时间
  // static unsigned long timeout = millis();
  if (millis() - timeout > TCP_CONNECT_TIMEOUT && !this->client.connected()) {
    // 超时两分钟 && 断开, 更新timeout
    timeout = millis();
    connect_tcp();
  }
}

/**
  \r\n response end tag
*/
void ESPTCP::tcp_send(char *msg) {
  if (this->client.connected()) {
    this->client.println(msg);
  }
}

/**
   \r response end tag
   @see bigiot.net doc
*/
void ESPTCP::tcp_send_r(char *msg) {
  if (this->client.connected()) {
    this->client.print(msg);
    this->client.print('\r');
  }
}
