/**
  web rest content realize
  @author r3inbowari
  @date 2020/6/21
*/

#include "rest.h"
#include "utils.h"
#include "system.h"

/**
 * Home
 */
void handleRoot() {
  server.send(200, "text/plain", "It is a RESTful Web created by ESP8266");
}

/**
 * 404 NOT FOUND
 */
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

/**
 * WLAN修改
 * @rest ip:port/changeWlan?ssid=[ssid]&password=[password]
 */
void handleWlan() {
  if (server.hasArg("ssid") && server.hasArg("password")) {
    String arg0 = server.arg("ssid");
    String arg1 = server.arg("password");
    writeProtectUnlock();
    flash_write((char*)arg0.c_str(), FLASH_SSID);
    flash_write((char*)arg1.c_str(), FLASH_PASSWORD);
    writeProtectLock();
    WiFi.disconnect();
    WiFi.begin(arg0, arg1);
    server.send(200, "text/plain", "wlan params: " + arg0 + ", " + arg1);
  } else {
    server.send(200, "text/plain", "error or less query params.");
  }
}

/**
 * TCP Host 修改
 * @rest ip:port/changeHost?host=[host]&port=[port]
 */
void handleHost() {
  if (server.hasArg("host") && server.hasArg("port")) {
    String arg0 = server.arg("host");
    String arg1 = server.arg("port");

    char *a = (char*)arg1.c_str();

    
    uint16_t __port = 0;
    double j = 0;
    for (int i = strlen(a) - 1; i >= 0; i--) {
      __port += (a[i] - '0') * (uint16_t)pow(10, j++);
    }
    // 套接字中port的处理方法(uint16_t2char*)
    char *convertPort = (char*)malloc(2);
    // 低八位
    convertPort[0] = __port & 0xFF;
    // 高八位
    convertPort[1] = __port >> 8;
    writeProtectUnlock();
    flash_write((char*)arg0.c_str(), FLASH_TCP_HOST);
    flash_write(convertPort, FLASH_TCP_PORT);
    free(convertPort);
    writeProtectLock();
    close_tcp();
    free(host);
    load_host_flash();
    connect_tcp();
    server.send(200, "text/plain", "host params: " + arg0 + ", " + arg1);
  } else {
    server.send(200, "text/plain", "error or less query params.");
  }
}
