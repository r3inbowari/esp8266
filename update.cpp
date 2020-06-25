/**
   server update realize
   @author r3inbowari
   @date 2020/6/24
*/
#include "update.h"
#include "user.h"
#include "store.h"

char *result_ret;

void check_update(char *result) {
  int serverChk = result[0] * 100 + result[1] * 10 + result[2] * 1;
  // const char *pl = ver.c_str();
  char *pl = getVersion();
  int localChk = pl[0] * 100 + pl[1] * 10 + pl[2] * 1;

  //  Serial.println(serverChk);
  //  Serial.println(localChk);

  if (serverChk > localChk) {
    Serial.println("found new software version...");

    // server 1.2.3
    // local  1.2.1
    // local  0.3.1
    result_ret = result;
    Serial.print("updating software version from ");
    Serial.print((int)pl[0]);
    Serial.print(".");
    Serial.print((int)pl[1]);
    Serial.print(".");
    Serial.print((int)pl[2]);
    Serial.print(" to ");

    Serial.print((int)result[0]);
    Serial.print(".");
    Serial.print((int)result[1]);
    Serial.print(".");
    Serial.print((int)result[2]);
    Serial.println("!");
    int a = (int)result[0];
    int b = (int)result[1];
    int c = (int)result[2];
    String fly = "_";
    String path = a + fly + b + fly + c;
    __esp_update(path);
  } else {
    Serial.println("no sofeware update!");
  }
}

void __esp_update(String updatePath) {
  WiFiClient client;
  ESPhttpUpdate.setLedPin(LED_BUILTIN, LOW);
  ESPhttpUpdate.onStart(update_started);
  ESPhttpUpdate.onEnd(update_finished);
  ESPhttpUpdate.onProgress(update_progress);
  ESPhttpUpdate.onError(update_error);

  String uu = UPDATE_URL;
  String uf = UPDATE_FILENAME;
  Serial.println("redirect to " + uu + updatePath + uf);
  t_httpUpdate_return ret = ESPhttpUpdate.update(client, uu + updatePath + uf);

  switch (ret) {
    case HTTP_UPDATE_FAILED:
      Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
      break;

    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("HTTP_UPDATE_NO_UPDATES");
      break;

    case HTTP_UPDATE_OK:
      Serial.println("HTTP_UPDATE_OK");
      break;
  }
}

void update_started() {
  Serial.println("CALLBACK:  HTTP update process started");
}

void update_finished() {
  Store tempDa;
  unlock();
  tempDa.setPos(FLASH_DEVICE_VERSION, result_ret, 3);
  lock();
  Serial.println("CALLBACK:  HTTP update process finished");
}

void update_progress(int cur, int total) {
  Serial.printf("CALLBACK:  HTTP update process at %d of %d bytes...\n", cur, total);
}

void update_error(int err) {
  Serial.printf("CALLBACK:  HTTP update fatal error code %d\n", err);
}
