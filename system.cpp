/**
   system realize
   @author r3inbowari
   @date 2020/6/20
*/
#include "system.h"
#include "user.h"

void system_init() {
  Serial.begin(9600);
  
  char *pl = getVersion();
  Serial.println();
  Serial.print("device software version: ");
  Serial.print((int)pl[0]);
  Serial.print(".");
  Serial.print((int)pl[1]);
  Serial.print(".");
  Serial.println((int)pl[2]);

}
