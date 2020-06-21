//#include <ESP8266WiFi.h>
//#include <ESP8266mDNS.h>
//#include <WiFiClient.h>
//#include <ESP8266WebServer.h>
#include "store.h"
#include "system.h"
#include "user.h"

Store store;

void setup() {
  system_init();
  
}

void loop() {
  
}


















/**
 * 测试代码
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
