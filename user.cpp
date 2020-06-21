/**
   user realize
   @author r3inbowari
   @date 2020/6/20
*/
#include "user.h"
#include "store.h"
#include "utils.h"
#include "_esp.h"

Store store;
/**
 * 设备初始化Flash
 */
void config_init() {
  Store s;
  char * port = uint16_t2pchar(DEFAULT_TCP_PORT);
  s.set(FLASH_SSID, DEFAULT_WLAN_SSID);
  s.set(FLASH_PASSWORD, DEFAULT_WLAN_PASSWORD);
  s.set(FLASH_TCP_HOST, DEFAULT_TCP_HOST);
  s.set(FLASH_TCP_PORT, port);
  free(port);
}

char* getWlanPassword() {
  return store.get(FLASH_PASSWORD);
}

char* getWlanSSID() {
  return store.get(FLASH_SSID);
}
