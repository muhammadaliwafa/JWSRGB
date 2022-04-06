#include <Arduino.h>
#include "FS.h"
#include <LITTLEFS.h>
#include <ArduinoJson.h>
#include "FSConfig.h"

void setup() {
  Serial.begin(115200);
  Serial.println();
  if(!LITTLEFS.begin(FORMAT_LITTLEFS_IF_FAILED)){
      Serial.println("LITTLEFS Mount Failed");
      return;
  }
  Serial.println( "SPIFFS-like write file to new path and delete it w/folders" );

  writeFile(LITTLEFS, filejws,p_defaultJWS().c_str());
  writeFile(LITTLEFS, fileAdmin,p_defaultAdmin().c_str());
  writeFile(LITTLEFS, fileInfo,p_defaultInfo().c_str());
  listDir(LITTLEFS, "/", 1);
  readFileJWS(LITTLEFS, filejws);
  readFileAdmin(LITTLEFS, fileAdmin);
  readFileInfo(LITTLEFS, fileInfo);
  listDir(LITTLEFS, "/", 1);
  deleteFile(LITTLEFS, filejws);
  deleteFile(LITTLEFS, fileAdmin);
  deleteFile(LITTLEFS, fileInfo);
  listDir(LITTLEFS, "/", 1);
}

void loop() {
  
}
