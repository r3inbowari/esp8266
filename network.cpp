/**
  network content realize
  @author r3inbowari
  @date 2020/6/21
*/

#include "system.h"
#include "user.h"
#include "network.h"
#include "utils.h"

WiFiClient client;
char* host = "172.20.10.2";
uint16_t port = 10086;



void network_init() {
  char *ssid = getWlanSSID();
  char *password = getWlanPassword();
  connect_wifi(ssid, password);
  create_ap();
}

void connect_wifi(char * __ssid, char *__password) {
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(__ssid, __password);
  int count = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    count ++;
    if (count > 20) {
      break;
    }
  }
  Serial.println(WiFi.localIP());
}

void create_ap() {
  IPAddress softLocal(192, 168, 128, 1);
  IPAddress softGateway(192, 168, 128, 1);
  IPAddress softSubnet(255, 255, 255, 0);
  WiFi.softAPConfig(softLocal, softGateway, softSubnet);
  String apName = ("ESP8266_" + (String)ESP.getChipId());
  const char *softAPName = apName.c_str();
  WiFi.softAP(softAPName, "12345678");
  IPAddress myIP = WiFi.softAPIP();
}

/**
   关闭tcp
*/
void close_tcp() {
  client.stop();
}

/**
    esp 建立tcp连接
    @return 是否成功连接到服务器
*/
bool connect_tcp() {
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);
  return client.connect(host, port);
}

void tcp_init() {
  host = getHost();
  char *tempPortArr = getPort();
  port = tempPortArr[0] | uint16_t(tempPortArr[1]) << 8;
  connect_tcp();
}

void resetTCP(char *phost, uint16_t pport) {
  close_tcp();
  host = getHost();
  port = pchar2uint16_t(getPort());
  connect_tcp();
}

void check_tcp_alive() {
  // 记录最后一次超时时间
  static unsigned long timeout = millis();
  if (millis() - timeout > TCP_CONNECT_TIMEOUT && !client.connected()) {
    // 超时两分钟 && 断开, 更新timeout
    timeout = millis();
    connect_tcp();
  }
}
