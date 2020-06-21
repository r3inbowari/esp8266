/**
  utils tool behavior realize
  @author r3inbowari
  @date 2020/6/21
*/
#include "system.h"
/**
   uint16_t 2 char
   @param a uint_16 parameter
   @return 2 byte char
*/
char* uint16_t2pchar(uint16_t src) {
  char *convertRet = (char*)malloc(2);
  // LB
  convertRet[0] = src & 0xFF;
  // HB
  convertRet[1] = src >> 8;
  return convertRet;
}

/**
 * char 2 uint_16
 * @param 
 * @return
 */
uint16_t pchar2uint16_t(char *src) {
  return src[0] | uint16_t(src[1]) << 8;
}
