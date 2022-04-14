const char *fileAdmin = "/parameter_Admin.json";
struct parameterAdmin {
  float lat;
  float lon;
  int8_t z_w; //zona waktu
  uint8_t hilal;
  String ssid;
  String p_ssid;
  String ap;
  String p_ap;
  int batastombol;
}; parameterAdmin p_admin;
String p_defaultAdmin() {
  String defaultAdmin = "";
  defaultAdmin += "-7.19971*";
  defaultAdmin += "108.19076*";
  defaultAdmin += "7*";
  defaultAdmin += "2*";
  defaultAdmin += "SII-Cikunir*";
  defaultAdmin += "admin.admin*";
  defaultAdmin += "JWS_AP*";
  defaultAdmin += "jwsmasjid01*";
  defaultAdmin += "100";
  Serial.println(defaultAdmin);
  return defaultAdmin;
}

void print_p_admin() {
  Serial.println();
  Serial.println("=========== DATA PARAMETER ADMIN ============");
  Serial.println();
  Serial.printf("latitude \t \t : %f\n", p_admin.lat);
  Serial.printf("longitude \t \t : %f\n", p_admin.lon);
  Serial.printf("zona waktu \t \t : %d\n", p_admin.z_w);
  Serial.printf("hilal \t \t \t : %d\n", p_admin.hilal);
  Serial.printf("ssid \t \t \t : %s\n", p_admin.ssid);
  Serial.println(p_admin.ssid);
  Serial.printf("password ssid \t \t : %s\n", p_admin.p_ssid);
  Serial.printf("akses point \t \t : %s\n", p_admin.ap);
  Serial.printf("password akses poin \t : %s\n", p_admin.p_ap);
  Serial.printf("batas tombol \t \t : %d\n", p_admin.batastombol);
}

void readFileAdmin(fs::FS &fs, const char * path) {
  //    Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if (!file || file.isDirectory()) {
    //        Serial.println("- failed to open file for reading");
    return;
  }
  String hasil[9];
  String pesan = file.readString();
  for(int i=0;i<9;i++){
    hasil[i] = parsing(pesan);
      Serial.println(hasil[i]);
  }
  p_admin.lat             = hasil[0].toFloat();
  p_admin.lon             = hasil[1].toFloat();
  p_admin.z_w             = hasil[2].toInt();
  p_admin.hilal           = hasil[3].toInt();
  p_admin.ssid            = hasil[4];
  p_admin.p_ssid          = hasil[5];
  p_admin.ap              = hasil[6];
  p_admin.p_ap            = hasil[7];
  p_admin.batastombol     = hasil[8].toInt();
  file.close();
  
  file.close();
  print_p_admin();
}
