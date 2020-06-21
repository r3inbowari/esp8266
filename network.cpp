/**
  network content realize
  @author r3inbowari
  @date 2020/6/21
*/

#include "system.h"
#include "user.h"
#include "network.h"

void network_init() {
  char *ssid = getWlanSSID();
  char *password = getWlanPassword();

  connect_wifi(ssid, password);
  // create_ap();
}

void connect_wifi(char * __ssid, char *__password) {
  Serial.println();
  Serial.print("Connecting to ");

  Serial.println(__ssid);
  Serial.println(__password);
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
  Serial.print("!");
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
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
