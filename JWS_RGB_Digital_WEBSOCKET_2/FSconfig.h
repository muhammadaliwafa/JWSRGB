void writeFile(fs::FS &fs, const char * path, const char * message);
void deleteFile(fs::FS &fs, const char * path);

//==========================================JWS===================================================

const char *filejws = "/parameter_JWS.json";

String p_defaultJWS() {
  String defaultJWS = "{";
  defaultJWS += "\"versi\":\"1\",";
  defaultJWS += "\"is\":\"12\",";
  defaultJWS += "\"id\":\"8\",";
  defaultJWS += "\"ia\":\"6\",";
  defaultJWS += "\"im\":\"5\",";
  defaultJWS += "\"ii\":\"5\",";
  defaultJWS += "\"durasikutbah\":\"45\",";
  defaultJWS += "\"f_ws\":\"2\",";
  defaultJWS += "\"durasiAdzan\":\"4\",";
  defaultJWS += "\"f_hjr\":\"0\",";
  defaultJWS += "\"dispiqmh\":\"1\",";
  defaultJWS += "\"dispimsyak\":\"1\",";
  defaultJWS += "\"ringimsyak\":1,";
  defaultJWS += "\"disppuasa\":1,";
  defaultJWS += "\"dispdhuha\":\"1\",";
  defaultJWS += "\"dispterbit\":\"1\",";
  defaultJWS += "\"dispsplash\":\"1\"}";
  return defaultJWS;
}

void print_p_jws() {
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
  Serial.printf("faktor Hijriah \t\t : %d\n", p_jws.f_hjr);
  Serial.printf("durasi kutbah \t\t : %d\n", p_jws.durasikutbah);
  Serial.printf("faktor waktu Sholat \t : %d\n", p_jws.f_ws);
  Serial.printf("display iqomah \t\t : %d\n", p_jws.dispiqmh);
  Serial.printf("display imsyak \t\t : %d\n", p_jws.dispimsyak);
  Serial.printf("ring imsyak \t\t : %d\n", p_jws.ringimsyak);
  Serial.printf("display puasa \t\t : %d\n", p_jws.disppuasa);
  Serial.printf("display dhuha \t\t : %d\n", p_jws.dispdhuha);
  Serial.printf("display terbit \t\t : %d\n", p_jws.dispterbit);
  Serial.printf("display splash screen\t : %d\n", p_jws.dispsplash);
}

void readFileJWS(fs::FS &fs, const char * path) {
  //    Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if (!file || file.isDirectory()) {
    //        Serial.println("- failed to open file for reading");
    return;
  }

  size_t size = file.size();
  std::unique_ptr<char[]> buf(new char[size]);
  file.readBytes(buf.get(), size);

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, buf.get());
  p_jws.versi         = doc["versi"];
  p_jws.is            = doc["is"];
  p_jws.id            = doc["id"];
  p_jws.ia            = doc["ia"];
  p_jws.im            = doc["im"];
  p_jws.ii            = doc["ii"];
  p_jws.durasiAdzan   = doc["durasiAdzan"];
  p_jws.f_ws          = doc["f_ws"];
  p_jws.durasikutbah  = doc["durasikutbah"];
  p_jws.f_hjr         = doc["f_hjr"];
  p_jws.dispiqmh      = doc["dispiqmh"];
  p_jws.dispimsyak    = doc["dispimsyak"];
  p_jws.ringimsyak    = doc["ringimsyak"];
  p_jws.disppuasa     = doc["disppuasa"];
  p_jws.dispdhuha     = doc["dispdhuha"];
  p_jws.dispterbit     = doc["dispterbit"];
  p_jws.dispsplash    = doc["dispsplash"];

  file.close();
      print_p_jws();

}

//=============================================ADMIN=============================================

const char *fileAdmin = "/parameter_Admin.json";

String p_defaultAdmin() {
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

void print_p_admin() {
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

void readFileAdmin(fs::FS &fs, const char * path) {
  //    Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if (!file || file.isDirectory()) {
    //        Serial.println("- failed to open file for reading");
    return;
  }
  size_t size = file.size();
  std::unique_ptr<char[]> buf(new char[size]);
  file.readBytes(buf.get(), size);

  DynamicJsonDocument doc(2048);
  DeserializationError error = deserializeJson(doc, buf.get());
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

//============================================INFO================================================


const char *fileInfo = "/parameter_Info.json";

String p_defaultInfo() {
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
  defaultInfo += "}";
  return defaultInfo;
}


void print_p_info() {
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



void readFileInfo(fs::FS &fs, const char * path) {
  //    Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if (!file || file.isDirectory()) {
    //        Serial.println("- failed to open file for reading");
    return;
  }
  size_t size = file.size();
  std::unique_ptr<char[]> buf(new char[size]);
  file.readBytes(buf.get(), size);

  DynamicJsonDocument doc(2048);
  DeserializationError error = deserializeJson(doc, buf.get());
  strlcpy(p_info.info1, doc["info1"] | "", sizeof(p_info.info1));
  strlcpy(p_info.info2, doc["info2"] | "", sizeof(p_info.info2));
  strlcpy(p_info.info3, doc["info3"] | "", sizeof(p_info.info3));
  strlcpy(p_info.info4, doc["info4"] | "", sizeof(p_info.info4));
  strlcpy(p_info.info5, doc["info5"] | "", sizeof(p_info.info5));
  strlcpy(p_info.info6, doc["info6"] | "", sizeof(p_info.info6));
  strlcpy(p_info.info7, doc["info7"] | "", sizeof(p_info.info7));
  strlcpy(p_info.info8, doc["info8"] | "", sizeof(p_info.info8));
  strlcpy(p_info.info9, doc["info9"] | "", sizeof(p_info.info9));
  strlcpy(p_info.info10, doc["info10"] | "", sizeof(p_info.info10));
  file.close();
  //    print_p_info();
}

void gantiInfo(fs::FS &fs, const char * path, String x) {
  //    Serial.printf("Reading file: %s\r\n", path);
  String a = x.substring(0, 1);
  int b = a.toInt();
  b = b + 1;
  String c = x.substring(1);
  File file = fs.open(path);
  if (!file || file.isDirectory()) {
    //        Serial.println("- failed to open file for reading");
    return;
  }
  size_t size = file.size();
  std::unique_ptr<char[]> buf(new char[size]);
  file.readBytes(buf.get(), size);

  DynamicJsonDocument doc(2048);
  DeserializationError error = deserializeJson(doc, buf.get());
  switch (b) {
    case 1:
      doc["info1"] = c;
      break;
    case 2:
      doc["info2"] = c;
      break;
    case 3:
      doc["info3"] = c;
      break;
    case 4:
      doc["info4"] = c;
      break;
    case 5:
      doc["info5"] = c;
      break;
    case 6:
      doc["info6"] = c;
      break;
    case 7:
      doc["info7"] = c;
      break;
    case 8:
      doc["info8"] = c;
      break;
    case 9:
      doc["info9"] = c;
      break;
    case 10:
      doc["info10"] = c;
      break;
  }
  String pesan;
  serializeJson(doc, pesan);
  file.close();
  deleteFile(LITTLEFS, fileInfo);
  writeFile(LITTLEFS, fileInfo, pesan.c_str());
  readFileInfo(LITTLEFS, fileInfo);
}

//======================================Cerah & Volume============================================
const char *fileAtur = "/parameter_Atur.json";

String p_defaultAtur() {
  String defaultAtur = "";
  defaultAtur += "\"cerah\":\"100\",";
  defaultAtur += "\"volume\":\"10\",";
  return defaultAtur;
}

void readFileAtur(fs::FS &fs, const char * path) {
  //    Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if (!file || file.isDirectory()) {
    //        Serial.println("- failed to open file for reading");
    return;
  }
  size_t size = file.size();
  std::unique_ptr<char[]> buf(new char[size]);
  file.readBytes(buf.get(), size);

  DynamicJsonDocument doc(2048);
  DeserializationError error = deserializeJson(doc, buf.get());
  p_atur.cerah             = doc["cerah"];
  p_atur.volume             = doc["volume"];
  file.close();
}

//=========================================CONFIG================================================

#define FORMAT_LITTLEFS_IF_FAILED true

const char *fileDisplay = "/parameter_Display.json";

struct parameterDisplay {
  uint8_t keccerahan;
}; parameterDisplay p_d;


void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
  //    Serial.printf("Listing directory: %s\r\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    //        Serial.println("- failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    //        Serial.println(" - not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      //            Serial.print("  DIR : ");
      //            Serial.println(file.name());
      if (levels) {
        listDir(fs, file.name(), levels - 1);
      }
    } else {
      //            Serial.print("  FILE: ");
      //            Serial.print(file.name());
      //            Serial.print("\tSIZE: ");
      //            Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    //        Serial.println("- failed to open file for writing");
    return;
  }

  if (file.print(message)) {
    //        Serial.println("- file written");
  } else {
    //        Serial.println("- write failed");
  }
  file.close();

}

void deleteFile(fs::FS &fs, const char * path) {
  //    Serial.printf("Deleting file: %s\r\n", path);
  if (fs.remove(path)) {
    //        Serial.println("- file deleted");
  } else {
    //        Serial.println("- delete failed");
  }
}

void DataDefault() {
  deleteFile(LITTLEFS, filejws);
  deleteFile(LITTLEFS, fileAdmin);
  deleteFile(LITTLEFS, fileInfo);
  deleteFile(LITTLEFS, fileAtur);
  writeFile(LITTLEFS, filejws, p_defaultJWS().c_str());
  writeFile(LITTLEFS, fileAdmin, p_defaultAdmin().c_str());
  writeFile(LITTLEFS, fileInfo, p_defaultInfo().c_str());
  writeFile(LITTLEFS, fileAtur, p_defaultAtur().c_str());
}
