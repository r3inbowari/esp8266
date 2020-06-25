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
   设备初始化Flash
*/
void config_init() {
  Store s;
  // unlock();
  if (!s.isWriteProtect()) {
    char * port = uint16_t2pchar(DEFAULT_TCP_PORT);
    char * port2 = uint16_t2pchar(DEFAULT_TCP_IOT_PORT);
    s.set(FLASH_SSID, DEFAULT_WLAN_SSID);
    s.set(FLASH_PASSWORD, DEFAULT_WLAN_PASSWORD);
    s.set(FLASH_TCP_HOST, DEFAULT_TCP_HOST);
    s.set(FLASH_TCP_PORT, port);
    s.set(FLASH_TCP_IOT_HOST, DEFAULT_TCP_IOT_HOST);
    s.set(FLASH_TCP_IOT_PORT, port2);
    s.set(FLASH_IOT_ID, DEFAULT_IOT_ID);
    s.set(FLASH_IOT_APPID, DEFAULT_IOT_APPID);
    char *a = "\x10\x00\x43";
    s.setPos(FLASH_DEVICE_VERSION, a, 3);
    free(port);
    free(port2);
    lock();
  }
}

char* getWlanPassword() {
  return store.get(FLASH_PASSWORD);
}

char* getWlanSSID() {
  return store.get(FLASH_SSID);
}

void setWlanPassword(char *src) {
  store.set(FLASH_PASSWORD, src);
}

void setWlanSSID(char *src) {
  store.set(FLASH_SSID, src);
}

void lock() {
  store.writeProtectLock();
}

void unlock() {
  store.writeProtectUnlock();
}

char* getHost() {
  return store.get(FLASH_TCP_HOST);
}

char *getPort() {
  return store.get(FLASH_TCP_PORT);
}

void setHost(char *src) {
  store.set(FLASH_TCP_HOST, src);
}

void setPort(char *src) {
  store.set(FLASH_TCP_PORT, src);
}

char* getIOTHost() {
  return store.get(FLASH_TCP_IOT_HOST);
}

char *getIOTPort() {
  return store.get(FLASH_TCP_IOT_PORT);
}

void setIOTHost(char *src) {
  store.set(FLASH_TCP_IOT_HOST, src);
}

void setIOTPort(char *src) {
  store.set(FLASH_TCP_IOT_PORT, src);
}

// ============================ BIG IOT ============================
char* getIOTID() {
  return store.get(FLASH_IOT_ID);
}

char *getIOTAppID() {
  return store.get(FLASH_IOT_APPID);
}

void setIOTID(char *src) {
  store.set(FLASH_IOT_ID, src);
}

void setIOTAppID(char *src) {
  store.set(FLASH_IOT_APPID, src);
}

// // ============================ update ============================
void setVersion(char *src) {
  store.set(FLASH_DEVICE_VERSION, src);
}

char* getVersion() {
  return store.get(FLASH_DEVICE_VERSION);
}
