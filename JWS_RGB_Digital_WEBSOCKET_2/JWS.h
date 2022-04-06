
int8_t SholatNow = 1;

uint8_t stimeInt[8][3]={
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0}
};

char namaWaktuSholat[][8] = {"IMSYAK", "SUBUH", "TERBIT", "DHUHA", "DZUHUR", "ASHAR", "MAGHRIB", "ISYA"};

float stimeFloat[]={0,0,0,0,0,0,0,0};

char dispNJadwal[] ="";

void updateJWS(){
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
  koreksi = (float)koreksi/60;
//  sholatCal(rTah, rBul, rTgl, 7, -7.199509,108.191037, 45);
  sholatCal(rTah, rBul, rTgl, p_admin.z_w, p_admin.lat, p_admin.lon, 45);
  for(int i=0; i<=7; i++){
  float   stime   = waktuSholat(i)+koreksi;
  stimeFloat[i] = stime;
  stimeInt[i][0] = floor(stime);
  stimeInt[i][1] = floor((stime-(float)stimeInt[i][0])*60);
  stimeInt[i][2] = floor((stime-(float)stimeInt[i][0]-(float)stimeInt[i][1]/60)*3600);
  }
  for(int i=0; i<=7; i++){
    char  out[21];
//    sprintf(out, "%s,%02d:%02d:%02d", namaWaktuSholat[i], stimeInt[i][0], stimeInt[i][1], stimeInt[i][2]);
//    Serial.println(out);
  }
//  sprintf(dispNJadwal, " Shubuh %02d:%02d  Dzuhur %02d:%02d ",stimeInt[1][0], stimeInt[1][1],stimeInt[4][0], stimeInt[4][1]);
}

bool azzan = false;
bool jumat = false;

void check_azzan(){ 
//  disableAzzan();
  
  for (int i = 0; i <= 7; i++)
  {
    if(true and i==0){//optional skip imsyak
      i++;
    }
    if (i != 2 and i != 3) // bukan terbit dan bukan dhuha
    {
      if (floatnow >= stimeFloat[i])
      {
        if (!azzan and (floatnow > stimeFloat[i]) and (floatnow < (stimeFloat[i] + 0.03)))
        {
          SholatNow = i;
          if(i==6){
            //TanggalHijriah();// mengganti penanggalan hijriah
          }
          if(rHar ==5 and SholatNow==4){jumat = true;}
          azzan = true;

        }

      }
    }
  }
}

void waktuSholatNow() {
  for (int i = 7; i >= 0; i--) {
    Serial.println(waktuSholat(i));
    if (floatnow > waktuSholat(i)) {
      SholatNow = i;
      break;
    }
  }
  Serial.printf("waktu sekarang adalah %d", SholatNow);
  Serial.println();

}
