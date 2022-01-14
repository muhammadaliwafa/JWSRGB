#include <Arduino.h>
#include "FS.h"
#include <LITTLEFS.h>
#include <ArduinoJson.h>
#include "FSConfig.h"
//fs::FS &fs;
void setup() {
  Serial.begin(115200);
  Serial.println();
  if(!LITTLEFS.begin(FORMAT_LITTLEFS_IF_FAILED)){
      Serial.println("LITTLEFS Mount Failed");
      return;
  }
  Serial.println( "SPIFFS-like write file to new path and delete it w/folders" );

  
  

  String dataawal = "{\"dispiqomah\":0,\"iqmhs\":\"12\",\"iqmhd\":\"8\",\"iqmha\":\"6\",\"iqmhm\":\"5\",\"iqmhi\":\"5\",\"durasiadzan\":\"4\",\"ihti\":\"2\",\"koreksihjr\":\"0\",\"dispimsyak\":0,\"ringimsyak\":0,\"disppuasa\":1,\"dispiden\":1,\"dispdhuha\":0,\"namamasjid\":\"Mushola Al-Furqon\",\"informasi\":\"Mohon Matikan Alat Komunikasi\",\"durasikutbah\":45}";
  writeFile(LITTLEFS, fileconfigjws,dataawal.c_str());
  listDir(LITTLEFS, "/", 1);
//  readFile(LITTLEFS, fileconfigjws);


  Serial.printf("Reading file: %s\r\n", fileconfigjws);
  String dataJson;

  File file = LITTLEFS.open(fileconfigjws);
  if(!file || file.isDirectory()){
      Serial.println("- failed to open file for reading");
      return;
  }

  size_t size = file.size();
  std::unique_ptr<char[]> buf(new char[size]);
  file.readBytes(buf.get(), size);

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, buf.get()); 
  char a[512];
  
  strlcpy(a, doc["informasi"] | "", sizeof(a));
  Serial.println(a);
  file.close();

  

  deleteFile(LITTLEFS, "/configjws.json");
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
