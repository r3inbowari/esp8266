/**
   store realize
   @author r3inbowari
   @date 2020/6/20
*/
#include "store.h"

Store::Store() {
  EEPROM.begin(512);
}

void Store::__write_(char addr, char value) {
  EEPROM.write(addr, value);
  EEPROM.commit();
};

void Store::writeProtectLock() {
  __write_(WRITE_PROTECT_ADDR, WRITE_PROTECT_STATUS_LOCKED);

}

void Store::writeProtectUnlock() {
  __write_(WRITE_PROTECT_ADDR, WRITE_PROTECT_STATUS_UNLOCKED);
}

bool Store::isWriteProtect() {
  return EEPROM.read(WRITE_PROTECT_ADDR) == WRITE_PROTECT_STATUS_LOCKED;
}

char* Store::get(int addr) {
  int len = EEPROM.read(addr++);
  char *ret = (char*)malloc(len + 1);
  for (int i = 0; i < len; i++) {
    ret[i] = EEPROM.read(addr++);
  }
  *(ret + len) = '\0';
  return ret;
}

bool Store::set(int addr, char *str) {
  if (!isWriteProtect()) {
    int len = strlen(str);
    EEPROM.write(addr++, len);
    for (int i = 0; i < len; i++) {
      EEPROM.write(addr++, str[i]);
    }
    EEPROM.commit();
    return true;
  }
  return false;
}
