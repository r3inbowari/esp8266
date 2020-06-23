/**
  network content realize
  @author r3inbowari
  @date 2020/6/21
  @update 2020/6/22
*/

#include "network.h"


WiFiClient client;
char* host = "172.20.10.2";
uint16_t port = 10086;

ESPTCP *tcp_golang;
BigIOT *tcp_bigiot;

void network_init() {
  create_ap();
  char *ssid = getWlanSSID();
  char *password = getWlanPassword();
  connect_wifi(ssid, password);

  // tcp_golang = new ESPTCP(getHost, getPort);
  tcp_bigiot = new BigIOT(getIOTHost, getIOTPort);
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
