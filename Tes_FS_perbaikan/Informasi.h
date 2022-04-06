
const char *fileInfo = "/parameter_Info.json";
    
struct parameterInfo{
  char  info1;
  char  info2;
  char  info3; 
  char info4;
  char info5;
  char info6;
  char info7;
  char info8;
  char info9;
  char info10;
}; parameterInfo p_info; 
    
String p_defaultInfo(){
  String defaultInfo = "{";
  defaultInfo += "\"info1\":\"info_1\",";
  defaultInfo += "\"info2\":\"info_2\",";
  defaultInfo += "\"info3\":\"info_3\",";
  defaultInfo += "\"info4\":\"info_4\",";
  defaultInfo += "\"info5\":\"info_5\",";
  defaultInfo += "\"info6\":\"info_6\",";
  defaultInfo += "\"info7\":\"info_7\",";
  defaultInfo += "\"info8\":\"info_8\",";
  defaultInfo += "\"info9\":\"info_9\",";
  defaultInfo += "\"info10\":\"info_10\"";
  return defaultInfo;
}


void print_p_info(){
  Serial.println();
  Serial.println("=========== DATA PARAMETER INFO ============");
  Serial.println();
  Serial.printf("info1 \t \t : %f\n", p_info.info1);
  Serial.printf("info2 \t \t : %f\n", p_info.info2);
  Serial.printf("info3 \t \t : %d\n", p_info.info3);
  Serial.printf("info4 \t \t \t : %d\n", p_info.info4);
//  Serial.printf("info5 \t \t \t : %s\n", p_info.info5);
//  Serial.printf("info6 \t \t : %s\n", p_info.info6);
//  Serial.printf("info7 \t \t : %s\n", p_info.info7);
//  Serial.printf("info8 \t : %s\n", p_info.info8);
//  Serial.printf("info9 \t \t : %d\n", p_info.info9);
//  Serial.printf("info10 \t \t : %d\n", p_info.info10);
} 


 
void readFileInfo(fs::FS &fs, const char * path){
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
    Serial.println("buff");
    Serial.println(buf.get());

    DynamicJsonDocument doc(2048);
    DeserializationError error = deserializeJson(doc, buf.get()); 
    char a[512];
    
    p_info.info1             = doc["info1"];
    p_info.info2             = doc["info2"];
    p_info.info3             = doc["info3"];
    p_info.info4             = doc["info4"];
    p_info.info5             = doc["info5"];
    p_info.info6             = doc["info6"];
    p_info.info7             = doc["info7"];
    p_info.info8             = doc["info8"];
    p_info.info9             = doc["info9"];
    p_info.info10            = doc["info10"];
  
    file.close();
    print_p_info();
    
}
    
    
    
