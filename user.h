/**
   user behavior header
   @author r3inbowari
   @date 2020/6/21
*/
#ifndef __USER_H
#define __USER_H

/**
   Flash 地址定义
   @addr 0 读写标志位 -> 255 未写入状态 | 240 已写入状态
   @addr 1-33 ssid 地址, 其中第一位为长度位(总长度33)
   @addr 34-66 password 地址 其中第一位为长度位(总长度33)
   @addr 67-99 host1 tcp地址1
   @addr 100-109 port1 tcp端口1, 实际上只占用2个字节
   @addr 110-142 host2 tcp地址2
   @addr 143-152 port2 tcp端口2
   @addr 153-169 device_id 设备id
   @addr 170-186 device_appid 设备appid
   当 addr 0 为 255 时, 进行第一次写入, 否正不再自动写入!
*/
#define FLASH_SSID 1
#define FLASH_PASSWORD 34
#define FLASH_TCP_HOST 67
#define FLASH_TCP_PORT 100
#define FLASH_TCP_IOT_HOST 110
#define FLASH_TCP_IOT_PORT 143
#define FLASH_IOT_ID 153
#define FLASH_IOT_APPID 170

/**
   自定义host1
*/
#define DEFAULT_TCP_PORT 1008
#define DEFAULT_TCP_HOST "172.20.10.2"


/**
   AP-Config
*/
#define DEFAULT_WLAN_SSID "r3inbowari"
#define DEFAULT_WLAN_PASSWORD "15946395951"

/**
   自定义host2
   贝壳物联网
*/
#define DEFAULT_TCP_IOT_PORT 8181
#define DEFAULT_TCP_IOT_HOST "bigiot.net"

/**
   物联网id与appid
*/
#define DEFAULT_IOT_ID "18534"
#define DEFAULT_IOT_APPID "aaaaaaaaa"

/**
   米家智能
*/

void config_init(); // 新设备初始化

char* getWlanPassword();
char* getWlanSSID();
void setWlanSSID(char *src);
void setWlanPassword(char *src);

char* getHost();
char* getPort();
void setHost(char *src);
void setPort(char *src);

char* getIOTHost();
char* getIOTPort();
void setIOTHost(char *src);
void setIOTPort(char *src);

char* getIOTID();
char* getIOTAppID();
void setIOTID(char *src);
void setIOTAppID(char *src);

void lock();
void unlock();
#endif
