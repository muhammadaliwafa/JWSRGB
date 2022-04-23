
int8_t SholatNow = 1;

uint8_t stimeInt[8][3] = {
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
};

char namaWaktuSholat[][8] = {"IMSYAK", "SUBUH", "TERBIT", "DHUHA", "DZUHUR", "ASHAR", "MAGHRIB", "ISYA"};

float stimeFloat[] = {0, 0, 0, 0, 0, 0, 0, 0};

char dispNJadwal[] = "";


// UPDATE HISAB TANGGAL

F1kM_Hisab HisabTanggal;

int Hjr_Date, Hjr_Month, Hjr_Year;
uint8_t Hjr_Hari;



void waktuSholatNow() {
  for (int i = 7; i >= 0; i--) {
    //    Serial.println(waktuSholat(i));
    if (floatnow > waktuSholat(i)) {
      SholatNow = i;
      break;
    }
  }
  Serial.printf("waktu sekarang adalah %d", SholatNow);
  Serial.println();

}

void updateJWS() {
  //  int Tahun = 2020,
  //      Bulan = 12,
  //      Tgl =  30;
  //  float ZonaWaktu = 7,
  //        Latitude = -6.2311, //jakarta
  //        Longitude = 106.7791,
  //        Altitude = 45;
  //
  //  sholatCal(Tahun, Bulan, Tgl, ZonaWaktu, Latitude, Longitude, Altitude);
  float koreksi = 2;
  koreksi = (float)koreksi / 60;
  //  sholatCal(rTah, rBul, rTgl, 7, -7.199509,108.191037, 45);
  sholatCal(rTah, rBul, rTgl, p_admin.z_w, p_admin.lat, p_admin.lon, 45);
  for (int i = 0; i <= 7; i++) {
    float   stime   = waktuSholat(i) + koreksi;
    stimeFloat[i] = stime;
    stimeInt[i][0] = floor(stime);
    stimeInt[i][1] = floor((stime - (float)stimeInt[i][0]) * 60);
    stimeInt[i][2] = floor((stime - (float)stimeInt[i][0] - (float)stimeInt[i][1] / 60) * 3600);
  }
  for (int i = 0; i <= 7; i++) {
    char  out[21];
    sprintf(out, "%s\t%02d:%02d:%02d", namaWaktuSholat[i], stimeInt[i][0], stimeInt[i][1], stimeInt[i][2]);
    Serial.println(out);
  }
  waktuSholatNow();
  //  sprintf(dispNJadwal, " Shubuh %02d:%02d  Dzuhur %02d:%02d ",stimeInt[1][0], stimeInt[1][1],stimeInt[4][0], stimeInt[4][1]);
}


void TanggalHijriah() {
  HisabTanggal.setLocationOnEarth(p_admin.lat, p_admin.lon); //Latitude Longitude TANGERANG
  HisabTanggal.setHilalVisibilityFactor(p_admin.hilal);
  uint8_t tgl2H=rTgl;
  uint8_t bulan2H=rBul;
  uint16_t tahun2H=rTah;
  uint8_t Day2H=rHar;
  
//  Serial.println(Hjr_Day);
  
  if(floatnow>stimeFloat[6]){
    //Serial.println("masuk");
    nextDay(rJam,tgl2H,bulan2H,tahun2H,tgl2H,bulan2H,tahun2H,Day2H);
    HisabTanggal.Greg2HijrDate(tgl2H,bulan2H,tahun2H,Hjr_Date,Hjr_Month,Hjr_Year);
    Hjr_Hari = Day2H;
  }else{
    HisabTanggal.Greg2HijrDate(tgl2H,bulan2H,tahun2H,Hjr_Date,Hjr_Month,Hjr_Year);
    Hjr_Hari = rHar + 1;
  }
//  Serial.println(Hjr_Day);
  
  

}

void UpdateWaktu(){
  static uint8_t lastTgl;  
  BacaRTC();
  if(lastTgl!=rTgl){
    updateJWS();
    TanggalHijriah();
    lastTgl=rTgl;
  }
  
}

bool azzan = false;
bool jumat = false;
bool blynk = false;
bool iqmh = false;

void aturBlynk() {
  if (!azzan) {
    time1 = millis();
    blynk = false;
  }
  if (blynk and ((millis() - time1) / 1000 >= p_jws.durasiAdzan)) {
    blynk = false;
  }
}

uint8_t timer_iqomah(){
  int x=0;
  switch (SholatNow) {
    case 1:
      x = p_jws.is;
      break;
    case 4:
      x = p_jws.id;
      break;
    case 5:
      x = p_jws.ia;
      break;
    case 6:
      x = p_jws.im;
      break;
    case 7:
      x = p_jws.ii;
      break;
    default:
      break;
  }
  return x;
}

void disableAzzan(uint8_t& cycl) {
  if (azzan) {
    float durasiazz = p_jws.durasiAdzan;
    durasiazz = durasiazz / 60;
    if (floatnow > (stimeFloat[SholatNow] + durasiazz)) {
      azzan = false;
      tarhim = false;
      if(!jumat)cycl=0;
      Serial.println("adzan false");
    }
  }
  if (jumat) {
    float durasiktbh = p_jws.durasikutbah;
    durasiktbh = durasiktbh / 60;

    if (floatnow > (stimeFloat[SholatNow] + durasiktbh)) {
      jumat = false;
      cycl=0;
    }
  }

}
void check_azzan(uint8_t& cycl, int8_t& n_b) {
//  disableAzzan(cycl);
  for (int i = 0; i <= 7; i++) {
    if (!p_jws.dispimsyak and i == 0) { //optional skip imsyak
      i++;
    }
    if (!p_jws.dispterbit and i == 2) { //optional skip terbit
      i++;
    }
    if (!p_jws.dispdhuha and i == 3) { //optional skip dhuha
      i++;
    }
//    if (floatnow >= stimeFloat[i]) {
      float selisih = floatnow-stimeFloat[i];
//      Serial.println(selisih);
      if (!azzan and (selisih >= 0) and (selisih <= 0.02)) {
        SholatNow = i;
        if (i == 6) {
          TanggalHijriah();// mengganti penanggalan hijriah
        }
//        if (rHar == 5 and SholatNow == 4) {
//          jumat = true;
//        }
        blynk = true;
        azzan = true;
        n_b=10;
        cycl = 50;
//        hitung=hmundur();
      }else if (!azzan && (selisih >= -0.083) && (selisih < 0)&&(i!=0)&&(i!=2)&&(i!=3)) {
        runtarhim();
//        digitalWrite(buzzer, HIGH);
      }

//    }
  }
}


void resetJumat(){
  String a = "Khutbah Jumat --";
  gantiInfo(LITTLEFS, fileInfo, a);
}
