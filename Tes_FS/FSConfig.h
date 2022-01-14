#include <Arduino.h>
#include "FS.h"
#include <LITTLEFS.h>


#define FORMAT_LITTLEFS_IF_FAILED true

const char *fileconfigjws = "/configjws.json";

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("- failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println(" - not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\r\n", path);

    
  
//    DynamicJsonDocument doc(1024);
//    DeserializationError error = deserializeJson(doc, message);


    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- failed to open file for writing");
        return;
    }

    if(file.print(message)){
        Serial.println("- file written");
    } else {
        Serial.println("- write failed");
    }
    file.close();

//    serializeJson(doc, file);
//    if (error) {
//    
//      Serial.print(F("deserializeJson() gagal kode sebagai berikut: "));
//      Serial.println(error.c_str());
//      return;
//      
//    } else {
//      
//      file.close();
//      Serial.println("Berhasil membuat data awal file configjws.json");
//    
//    }  
    
}

void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\r\n", path);
    if(fs.remove(path)){
        Serial.println("- file deleted");
    } else {
        Serial.println("- delete failed");
    }
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\r\n", path);
    String dataJson;

    File file = fs.open(path);
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
}
