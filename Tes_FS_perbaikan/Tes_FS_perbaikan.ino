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
  




//  Serial.printf("Reading file: %s\r\n", filejws);
//  String dataJson;
//
//  File file = LITTLEFS.open(filejws);
//  if(!file || file.isDirectory()){
//      Serial.println("- failed to open file for reading");
//      return;
//  }
//
//  size_t size = file.size();
//  std::unique_ptr<char[]> buf(new char[size]);
//  file.readBytes(buf.get(), size);
//
//  DynamicJsonDocument doc(1024);
//  DeserializationError error = deserializeJson(doc, buf.get()); 
//  char a[512];
//  
//  strlcpy(a, doc["info1"] | "", sizeof(a));
//  Serial.println(a);
//  file.close();

  

  deleteFile(LITTLEFS, filejws);
  deleteFile(LITTLEFS, fileAdmin);
  deleteFile(LITTLEFS, fileInfo);
  listDir(LITTLEFS, "/", 1);
  
//  DynamicJsonDocument doc(1024);
//  DeserializationError error = deserializeJson(doc, dataawal);
//  File file = fs.open("test.json", FILE_WRITE);
//  if(!file){
//      Serial.println("- failed to open file for writing");
//      return;
//  }
}

void loop() {
  
}
