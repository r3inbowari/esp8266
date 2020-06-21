/**
  web content realize
  @author r3inbowari
  @date 2020/6/21
*/

#include "system.h"
#include "rest.h"

/**
 * web server
 */
void web_init() {
  if (MDNS.begin("esp8266")) {
  }
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.on("/changeWlan", handleWlan); // 修改 WLAN 的 SSID 和 PASSWORD
  server.on("/changeHost", handleHost); // 修改 后台服务器访问地址
  server.begin();
}
