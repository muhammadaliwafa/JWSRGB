const char *filejws = "/parameter_JWS.json";

struct parameterJWS {
  uint8_t versi;
  uint8_t is; // iqomah subuh
  uint8_t id;
  uint8_t ia;
  uint8_t im;
  uint8_t ii;
  uint8_t durasiAdzan;
  uint8_t f_ws;//faktor penambah waktu sholat
  uint8_t durasikutbah;
  uint8_t f_hjr;
  bool dispiqmh;
  bool dispimsyak;
  bool ringimsyak;
  bool disppuasa;
  bool dispdhuha;
  bool dispterbit;
  bool dispsplash;

}; parameterJWS p_jws;


String p_defaultJWS() {
  String defaultJWS = "";
  defaultJWS += "1*";
  defaultJWS += "12*";
  defaultJWS += "8*";
  defaultJWS += "6*";
  defaultJWS += "5*";
  defaultJWS += "5*";
  defaultJWS += "45*";
  defaultJWS += "2*";
  defaultJWS += "4*";
  defaultJWS += "0*";
  defaultJWS += "true*";
  defaultJWS += "true*";
  defaultJWS += "true*";
  defaultJWS += "true*";
  defaultJWS += "true*";
  defaultJWS += "true*";
  defaultJWS += "true";
  Serial.println(defaultJWS);
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

    String hasil[17];
  String pesan = file.readString();
  for(int i=0;i<17;i++){
    hasil[i] = parsing(pesan);
      Serial.println(hasil[i]);
  }
  p_jws.versi         = hasil[0].toInt();
  p_jws.is            = hasil[1].toInt();
  p_jws.id            = hasil[2].toInt();
  p_jws.ia            = hasil[3].toInt();
  p_jws.im            = hasil[4].toInt();
  p_jws.ii            = hasil[5].toInt();
  p_jws.durasiAdzan   = hasil[6].toInt();
  p_jws.f_ws          = hasil[7].toInt();;
  p_jws.durasikutbah  = hasil[8].toInt();;
  p_jws.f_hjr         = hasil[9].toInt();;
  p_jws.dispiqmh      = (hasil[10]=="true");
  p_jws.dispimsyak    = (hasil[11]=="true");
  p_jws.ringimsyak    = (hasil[12]=="true");
  p_jws.disppuasa     = (hasil[13]=="true");
  p_jws.dispdhuha     = (hasil[14]=="true");
  p_jws.dispterbit    = (hasil[15]=="true");
  p_jws.dispsplash    = (hasil[16]=="true");

    file.close();
    print_p_jws();
    
}
