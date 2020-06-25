/**
   mux tcp header
   @author r3inbowari
   @date 2020/6/24
*/

#ifndef __ESP_UPDATE_H
#define __ESP_UPDATE_H

#include "system.h"

void check_update(char *result);
void __esp_update(String updatePath);

void update_finished();
void update_started();
void update_progress(int cur, int total);
void update_error(int err);

#endif
