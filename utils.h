/**
  utils tool behavior header
  @author r3inbowari
  @date 2020/6/21
*/

#ifndef __UTILS_H
#define __UTILS_H

typedef void (*pFunc)();

#include "system.h"

char* uint16_t2pchar(uint16_t src);
uint16_t pchar2uint16_t(char *src);

/**
   程序定时器
*/
class FuncTimer {
  public:
    unsigned long timeout;
    pFunc innerfunc;
    unsigned long interval;
    void setInterval(pFunc func, int interval);
    void check();
};

#endif
