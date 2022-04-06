const char *fileAdmin = "/paranter_Admin.json";

struct parameterAdmin{
  double lat;
  double lon;
  int8_t z_w; //zona waktu
  uint8_t hilal;
  char ssid[20];
  char p_ssid[20];
  char ap[16];
  char p_ap[8];
  int batastombol;
}; parameterAdmin p_admin;

String p_defaultAdmin(){
  String defaultAdmin = "{";
  defaultAdmin += "\"lat\":\"-6.2631969\",";
  defaultAdmin += "\"lon\":\"106.9615763\",";
  defaultAdmin += "\"z_w\":\"7\",";
  defaultAdmin += "\"hilal\":\"2\",";
  defaultAdmin += "\"ssid\":\"JWS\",";
  defaultAdmin += "\"p_ssid\":\"12345678\",";
  defaultAdmin += "\"ap\":\"JWS_AP\",";
  defaultAdmin += "\"p_ap\":\"12345678ap\",";
  defaultAdmin += "\"batastombol\":\"100\"";
  defaultAdmin += "}";
  return defaultAdmin;
}

void print_p_admin(){
  Serial.println();
  Serial.println("=========== DATA PARAMETER ADMIN ============");
  Serial.println();
  Serial.printf("latitude \t \t : %f\n", p_admin.lat);
  Serial.printf("longitude \t \t : %f\n", p_admin.lon);
  Serial.printf("zona waktu \t \t : %d\n", p_admin.z_w);
  Serial.printf("hilal \t \t \t : %d\n", p_admin.hilal);
  Serial.printf("ssid \t \t \t : %s\n", p_admin.ssid);
  Serial.printf("password ssid \t \t : %s\n", p_admin.p_ssid);
  Serial.printf("akses point \t \t : %s\n", p_admin.ap);
  Serial.printf("password akses poin \t : %s\n", p_admin.p_ap);
  Serial.printf("batas tombol \t \t : %d\n", p_admin.batastombol);
}


void readFileAdmin(fs::FS &fs, const char * path){
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

    DynamicJsonDocument doc(2048);
    DeserializationError error = deserializeJson(doc, buf.get()); 
    char a[512];
    p_admin.lat             = doc["lat"];
    p_admin.lon             = doc["lon"];
    p_admin.z_w             = doc["z_w"];
    p_admin.hilal           = doc["hilal"];
    strlcpy(p_admin.ssid, doc["ssid"] | "", sizeof(p_admin.ssid));
    strlcpy(p_admin.p_ssid, doc["p_ssid"] | "", sizeof(p_admin.p_ssid));
    strlcpy(p_admin.ap, doc["ap"] | "", sizeof(p_admin.ap));
    strlcpy(p_admin.p_ap, doc["p_ap"] | "", sizeof(p_admin.p_ap));
    p_admin.batastombol     = doc["batastombol"];

   
    file.close();
    print_p_admin();
    
}
