/**
   mux tcp realize
   @author r3inbowari
   @date 2020/6/22
*/

#include "tcp.h"
#include "_esp.h"
#include "update.h"

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
  // this->timeout = millis();
}

/**
  默认构造
*/
ESPTCP::ESPTCP() {
  this->host = getHost();
  char *tempPortArr = getPort();
  this->port = tempPortArr[0] | uint16_t(tempPortArr[1]) << 8;
  this->connect_tcp();
  // this->timeout = millis();
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

// 检查
bool ESPTCP::is_alive() {
  return this->client.connected();
}

// 重连
void ESPTCP::Handler() {
  static unsigned long timeout = millis();
  if (!is_alive()) {
    if (millis() - timeout > TCP_CONNECT_TIMEOUT) {
      timeout = millis();
      connect_tcp();
    }
  }


  if (client.available()) {
    char ch = static_cast<char>(client.read());
    if (ch == 0xfa) { // 更新命令
      char len = client.read();
      char *result = (char*)malloc(len + 1);

      for (int i = 0; i < len; i ++) {
        result[i] = static_cast<char>(client.read());
      }
      *(result + len) = '\0';
      check_update(result);
    } else if (ch == 0xfe) { // DHT11 传感器示例
      char len = client.read();
      char *result = (char*)malloc(len + 1);
      for (int i = 0; i < len; i ++) {
        result[i] = static_cast<char>(client.read());
      }
      *(result + len) = '\0';
      dht_order_send(result);
    }
  }
}

/**
   传感器(测试用)
*/
void ESPTCP::dht_order_send(char *order) {
  static String inputString = "";
  if (order[0] == 0xbb) {
    if (client.connected()) {
      if (inputString.length() > 0) {
        client.print(inputString);
      }
    }
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

String ESPTCP::read() {
  while (client.available()) {
    return client.readStringUntil('\n');
  }
  return "";
}
