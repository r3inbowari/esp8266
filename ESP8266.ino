//#include <ESP8266WiFi.h>
//#include <ESP8266mDNS.h>
//#include <WiFiClient.h>
//#include <ESP8266WebServer.h>
#include "store.h"
#include "system.h"
#include "user.h"
#include "utils.h"

Store store;

void setup() {
  system_init();



}

void loop() {
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
