/**
   store header
   @author r3inbowari
   @date 2020/6/20
*/
#ifndef __STORE_H
#define __STORE_H

#include "system.h"

#define WRITE_PROTECT_ADDR 0x00
#define WRITE_PROTECT_STATUS_LOCKED 0xf0
#define WRITE_PROTECT_STATUS_UNLOCKED 0xff

class Store {
  private:
    void __write_(char addr, char value);
  public:
    Store();
    void writeProtectLock();
    void writeProtectUnlock();
    bool isWriteProtect();

    bool set(int addr, char *str);
    char* get(int addr);
    bool setPos(int addr, char *str, int len);

    // unit test
    void __test_protect_status();
    void __test_get_ssid();
};

#endif
