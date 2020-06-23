/**
  bigiot base on tcp content header
  @author r3inbowari
  @date 2020/6/22
*/

#ifndef __BIGIOT_H
#define __BIGIOT_H

#include <ArduinoJson.h>

//#define MSG_WELCOME "{\"M\":\"WELCOME TO BIGIOT\"}"
#define MSG_WELCOME "WELCOME TO BIGIOT"
#define MSG_CHECKINOK "checkinok"

#define SEND_HEARTBEAT "{\"M\":\"b\"}\n"
#define SEND_LOGIN "{\"M\":\"checkin\",\"ID\":\"18534\",\"K\":\"a06527c61\"}\n"

#define BIGIOT_PLAY "play"
#define BIGIOT_STOP "stop"

#define HEARTBEAT_TIMER 40000

class BigIOT : public ESPTCP {
  public:
    // timeout tag
    
    bool login_status = false;
    // BigIOT(pGetter phost, pGetter pport):ESPTCP(phost, pport){}
    BigIOT(pGetter phost, pGetter pport);
    // 登录
    void iot_check();
    void Login();
    void Handler();
    void heartbeat();
};

#endif
