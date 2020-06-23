/**
  bigiot base on tcp content realize
  @author r3inbowari
  @date 2020/6/22
*/

// 注意继承时, 头文件引入先后顺序..
#include "tcp.h"
#include "bigiot.h"

BigIOT::BigIOT(pGetter phost, pGetter pport) : ESPTCP(phost, pport) {

}

void BigIOT::Login() {

}

void BigIOT::heartbeat() {
  static unsigned long heartbeat_time_record = millis();
  if (millis() - heartbeat_time_record > HEARTBEAT_TIMER && this->client.connected() && this->login_status) {
    // 40秒一次 && client 开启, 发送心跳, client 断开时, 不发心跳
    heartbeat_time_record = millis();
    this->client.print(SEND_HEARTBEAT);
    Serial.println("HEARTBEAT OK");
  }
}

/**
   传感器状态检测
*/
void BigIOT::iot_check() {
  static unsigned long timeout = millis();
  // tcp 存活检测
  if (!is_alive()) {
    if (millis() - timeout > TCP_CONNECT_TIMEOUT) {
      timeout = millis();
      this->login_status = false;
      Serial.println("reconnect1");
      connect_tcp();
      return;
    }
  }
  if (!this->login_status) {
    if (millis() - timeout > TCP_CONNECT_TIMEOUT) {
      timeout = millis();
      this->login_status = false;
      Serial.println("reconnect2");
      close_tcp();
      connect_tcp();
    }
  }
}

/**
   消息处理程
   重写处理器
*/
void BigIOT::Handler() {



  // 心跳检测, 未连接状态退出
  this->heartbeat();

  String msg = this->read();

  if (msg == "") {
    iot_check();
    return;
  }

  DynamicJsonDocument doc(1024);
  deserializeJson(doc, msg);
  String MSG = doc["M"];
  String CONTENT = doc["C"];
  Serial.println(MSG);

  if (MSG == "WELCOME TO BIGIOT") {
    Serial.println("send ok");
    client.print(SEND_LOGIN);
    return;
  }

  if (MSG == MSG_CHECKINOK) {
    Serial.println("LOGIN OK");
    this->login_status = true;
    return;
  }

  if (CONTENT == BIGIOT_PLAY) {
    Serial.println("\xa1\xf1\x83\x55\x90");
    return;
  }

  if (CONTENT == BIGIOT_STOP) {
    Serial.println("\xa1\xf1\x83\x55\x90");
    return;
  }

}
