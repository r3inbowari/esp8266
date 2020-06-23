#include <ArduinoJson.h>
#include <ArduinoOTA.h>
#include "store.h"
#include "system.h"
#include "user.h"
#include "utils.h"
#include "_esp.h"
#include "network.h"
#include "web.h"

#include "tcp.h"
#include "bigiot.h"

const char *input = "{\"sensor\":\"gps\"}";

void setup() {
  system_init();
  config_init();
  web_init();
  network_init();


  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
}

void loop() {
  ArduinoOTA.handle();
  http_handle();
  // tcp_golang->Handler();
  tcp_bigiot->Handler();
}
























void __test_user_config() {
  store.writeProtectUnlock();
  config_init();

  char *gkd = store.get(FLASH_SSID);
  Serial.println(gkd);

  char *gkd2 = store.get(FLASH_PASSWORD);
  Serial.println(gkd2);

  char *gkd3 = store.get(FLASH_TCP_HOST);
  Serial.println(gkd3);

  char *gkd4 = store.get(FLASH_TCP_PORT);
  Serial.println(pchar2uint16_t(gkd4));


  delay(2000000);
}


void __test_utils_convert() {
  Serial.println("u16 -> pchar");
  uint16_t t = 2333;
  char *a = uint16_t2pchar(t);
  Serial.println(a[0], HEX);
  Serial.println(a[1], HEX);
  delay(2000);

  Serial.println("pchar -> u16");
  uint16_t b = pchar2uint16_t(a);
  Serial.println(b);
  delay(2000);
}









/**
   测试代码
*/
void __test_store() {
  delay(2000);
  __test_protect_status();
  store.writeProtectUnlock();
  __test_protect_status();

  delay(2000);
  __test_get_ssid();
  store.set(FLASH_SSID, "bilibili");
  __test_get_ssid();
  delay(2000);
  store.set(FLASH_SSID, "bilibilgggai");
  __test_get_ssid();
  delay(2000);
  store.set(FLASH_SSID, "0755");
  __test_get_ssid();
  store.writeProtectLock();
  delay(2000);

  if (!store.set(FLASH_SSID, "0755")) {
    Serial.println("protect!!!!");
  }
}

void __test_protect_status() {
  Serial.print("protect status: ");
  Serial.println(store.isWriteProtect());
}

void __test_get_ssid () {
  char *gkd = store.get(FLASH_SSID);
  Serial.println(gkd);
}
