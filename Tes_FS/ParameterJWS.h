const char *filejws = "/parameter_JWS.json";

struct parameterJWS{
  uint8_t versi;
  uint8_t is; // iqomah subuh
  uint8_t id; 
  uint8_t ia;
  uint8_t im;
  uint8_t ii;
  uint8_t durasiAdzan;
  uint8_t f_ws;//faktor penambah waktu sholat
  uint8_t f_hjr;
  bool ringimsyak;
  bool disppuasa;
  bool dispsplash; 
  char info1[512];
  char info2[512];
  char info3[512];
  char info4[512];
  uint8_t durasikutbah;
  
}; parameterJWS p_jws;


String p_defaultJWS(){
  String defaultJWS = "{";
  defaultJWS += "\"versi\":\"1\",";
  defaultJWS += "\"is\":\"12\",";
  defaultJWS += "\"id\":\"8\",";
  defaultJWS += "\"ia\":\"6\",";
  defaultJWS += "\"im\":\"5\",";
  defaultJWS += "\"ii\":\"5\",";
  defaultJWS += "\"durasiAdzan\":\"4\",";
  defaultJWS += "\"f_ws\":\"2\",";
  defaultJWS += "\"f_hjr\":\"0\",";
  defaultJWS += "\"ringimsyak\":0,";
  defaultJWS += "\"disppuasa\":1,";
  defaultJWS += "\"dispsplash\":1,";
  defaultJWS += "\"info1\":\"Mushola Al-Furqon\",";
  defaultJWS += "\"info2\":\"Mohon Matikan Alat Komunikasi\",";
  defaultJWS += "\"info3\":\"Informasi 3\",";
  defaultJWS += "\"info4\":\"Informasi 4\",";
  defaultJWS += "\"durasikutbah\":45}";
  return defaultJWS;
}

void print_p_jws(){
  Serial.println();
  Serial.println("===================== PARAMETER JWS ==================");
  Serial.println();
  Serial.printf("versi \t\t\t : %d\n", p_jws.versi);
  Serial.printf("jeda iqomah subuh \t : %d\n", p_jws.is);
  Serial.printf("jeda iqomah dzuhur \t : %d\n", p_jws.id);
  Serial.printf("jeda iqomah ashar \t : %d\n", p_jws.ia);
  Serial.printf("jeda iqomah maghrib \t : %d\n", p_jws.im);
  Serial.printf("jeda iqomah isya' \t : %d\n", p_jws.ii);
  Serial.printf("durasi adzan \t\t : %d\n", p_jws.durasiAdzan);
  Serial.printf("faktor waktu Sholat \t : %d\n", p_jws.f_ws);
  Serial.printf("faktor Hijriah \t\t : %d\n", p_jws.f_hjr);
  Serial.printf("ring imsyak \t\t : %d\n", p_jws.ringimsyak);
  Serial.printf("display puasa \t\t : %d\n", p_jws.disppuasa);
  Serial.printf("display splash screen\t : %d\n", p_jws.dispsplash);
  Serial.printf("info 1 \t\t\t : %s\n", p_jws.info1);
  Serial.printf("info 2 \t\t\t : %s\n", p_jws.info2);
  Serial.printf("info 3 \t\t\t : %s\n", p_jws.info3);
  Serial.printf("info 4 \t\t\t : %s\n", p_jws.info4);
  Serial.printf("durasi kutbah \t\t : %d\n", p_jws.durasikutbah);  
}

void readFileJWS(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\r\n", path);
    String dataJson;

    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }
//    while(file.available()){
//        Serial.write(file.read());
//    }

    size_t size = file.size();
    std::unique_ptr<char[]> buf(new char[size]);
    file.readBytes(buf.get(), size);

    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, buf.get()); 
    char a[512];
    p_jws.versi         = doc["versi"];
    p_jws.is            = doc["is"];
    p_jws.id            = doc["id"];
    p_jws.ia            = doc["ia"];
    p_jws.im            = doc["im"];
    p_jws.ii            = doc["ii"];
    p_jws.durasiAdzan   = doc["durasiAdzan"];
    p_jws.f_ws          = doc["f_ws"];
    p_jws.f_hjr         = doc["f_hjr"];
    p_jws.ringimsyak    = doc["ringimsyak"];
    p_jws.disppuasa     = doc["disppuasa"];
    p_jws.dispsplash    = doc["dispsplash"];
    strlcpy(p_jws.info1, doc["info1"] | "", sizeof(p_jws.info1));
    strlcpy(p_jws.info2, doc["info2"] | "", sizeof(p_jws.info2));
    strlcpy(p_jws.info3, doc["info3"] | "", sizeof(p_jws.info3));
    strlcpy(p_jws.info4, doc["info4"] | "", sizeof(p_jws.info4));
    p_jws.durasikutbah  = doc["durasikutbah"];

    file.close();
    print_p_jws();
    
}
