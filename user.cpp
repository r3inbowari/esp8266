/**
   user realize
   @author r3inbowari
   @date 2020/6/20
*/
#include "user.h"
#include "store.h"

/**
 * 设备初始化
 */
void init_config() {
  Store s;
  s.set(FLASH_SSID, "r3inbowari");
  s.set(FLASH_PASSWORD, "15946395951");
  s.set(FLASH_TCP_HOST, "172.20.10.2");
  s.set(FLASH_TCP_PORT, );
}
