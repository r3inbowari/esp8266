/**
   user behavior header
   @author r3inbowari
   @date 2020/6/21
*/
#ifndef __USER_H
#define __USER_H

#define FLASH_SSID 1
#define FLASH_PASSWORD 34
#define FLASH_TCP_HOST 67
#define FLASH_TCP_PORT 100

#define DEFAULT_TCP_PORT 1008
#define DEFAULT_TCP_HOST "172.20.10.2"
#define DEFAULT_WLAN_SSID "r3inbowari"
#define DEFAULT_WLAN_PASSWORD "15946395951"



void config_init(); // 新设备初始化

char* getWlanPassword();
char* getWlanSSID();
#endif
