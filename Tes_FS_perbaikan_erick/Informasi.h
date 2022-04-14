
const char *fileInfo = "/parameter_Info.json";
    
struct parameterInfo{
  String info1;
  String info2;
  String info3;
  String info4;
  String info5;
  String info6;
  String info7;
  String info8;
  String info9;
  String info10;
}; parameterInfo p_info; 
    
String p_defaultInfo(){
  String defaultInfo = "";
  defaultInfo += "info-1*";
  defaultInfo += "info_2*";
  defaultInfo += "info_3*";
  defaultInfo += "info_4*";
  defaultInfo += "info.5*";
  defaultInfo += "info_6*";
  defaultInfo += "info_7*";
  defaultInfo += "info_8*";
  defaultInfo += "info09*";
  defaultInfo += "info_10";
  Serial.println(defaultInfo);
  return defaultInfo;
}


void print_p_info(){
  Serial.println();
  Serial.println("=========== DATA PARAMETER INFO ============");
  Serial.println();
  Serial.printf("info1 \t \t : %s\n", p_info.info1);
  Serial.printf("info2 \t \t : %s\n", p_info.info2);
  Serial.printf("info3 \t \t : %s\n", p_info.info3);
  Serial.printf("info4 \t \t : %s\n", p_info.info4);
  Serial.printf("info5 \t \t : %s\n", p_info.info5);
  Serial.printf("info6 \t \t : %s\n", p_info.info6);
  Serial.printf("info7 \t \t : %s\n", p_info.info7);
  Serial.printf("info8 \t \t : %s\n", p_info.info8);
  Serial.printf("info9 \t \t : %s\n", p_info.info9);
  Serial.printf("info10 \t \t : %s\n", p_info.info10);
} 


 
void readFileInfo(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\r\n", path);
    String dataJson;

    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }
    String hasil[10];
    String pesan = file.readString();
    for(int i=0;i<10;i++){
      hasil[i] = parsing(pesan);
      Serial.println(hasil[i]);
    }
    p_info.info1            = hasil[0];
    p_info.info2            = hasil[1];
    p_info.info3            = hasil[2];
    p_info.info4            = hasil[3];
    p_info.info5            = hasil[4];
    p_info.info6            = hasil[5];
    p_info.info7            = hasil[6];
    p_info.info8            = hasil[7];
    p_info.info9            = hasil[8];
    p_info.info10           = hasil[9];
    
    file.close();
    print_p_info();
    
}
    
    
    
