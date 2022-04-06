bool zenius;
int8_t SholatNow = -1;
uint8_t count [8];
//int8_t kedipJad;
uint8_t iterated;
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


float stimeFloat[]={0,0,0,0,0,0,0,0};

char dispNJadwal[] ="";

void updateJWS(){
//  int Tahun = 2020, 
//      Bulan = 12,
//      Tgl =  30;
  float ZonaWaktu = 7, 
        Latitude = -6.261392, //jakarta
        Longitude = 106.960972, 
        Altitude = 45;
//  
  sholatCal(rTah, rBul, rTgl, ZonaWaktu, Latitude, Longitude, Altitude); 
  float koreksi = 2;
  koreksi = (float)koreksi/60;
  //sholatCal(rTah, rBul, rTgl, 7, -7.199509,108.191037, 45);
  for(int i=0; i<=7; i++){
  float   stime   = waktuSholat(i)+koreksi;
  stimeFloat[i] = stime;
  stimeInt[i][0] = floor(stime);
  stimeInt[i][1] = floor((stime-(float)stimeInt[i][0])*60);
  stimeInt[i][2] = floor((stime-(float)stimeInt[i][0]-(float)stimeInt[i][1]/60)*3600);
  }
 
  //char  out[21];
//    sprintf(out, "sholat %01d %02d : %02d : %02d", i, stimeInt[i][0], stimeInt[i][1], stimeInt[i][2]);
//    Serial.println(out);
    
  }
//  void kedipSholat(){
//   for(int i=0; i<=7; i++){
//    kedipJad = stimeInt[i][0]-sekarang.Hour();
//      if (kedipJad == 1){
//        if(((stimeInt[i][1]+60)-rMen)<=10){
//          count = i;
//          }
//          else{
//            count = 8;
//            }
//        }
//        else if (kedipJad==0){
//          if(stimeInt[i][1]>=10){
//            if (abs(rMen-stimeInt[i][1])<10){
//            count=i;
//            }
//            else{
//              count =8;
//               }
//            }
//           if (stimeInt[i][1]<10){
//            if (rMen <= stimeInt[i][1]){
//              count = i;
//              }
//              else{
//                count=8;
//                }
//            }
//          }
//      
//      }
//      }
//  sprintf(dispNJadwal, " Shubuh %02d:%02d  Dzuhur %02d:%02d ",stimeInt[1][0], stimeInt[1][1],stimeInt[4][0], stimeInt[4][1]);
//}

void kaka (){
for (int i=0; i<8;i++){
  if (stimeInt[i][1]<10){
    count [i] = 1;
    }
    else{
      count [i] =0; 
      }
  }
}
void waktuS(){
  if (rJam<=stimeInt[1][0]){
      iterated = 1;
    }
  else if (rJam<=stimeInt[3][0]){
    iterated = 3;
    }
    else if (rJam<=stimeInt[4][0]){
      iterated = 4;
      }
      else if (rJam<=stimeInt[5][0]){
        iterated =5;
        }
        else if(rJam<=stimeInt[6][0]){
          iterated=6;
          }
          else if(rJam<=stimeInt[7][0]){
            iterated =7;
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
void lebih(uint8_t i){
      if (count [i] !=1){
        if (rJam==stimeInt[i][0]){
          if(abs(rMen-stimeInt[i][1])<=10){
          zenius = true;
          }
          else
          {
            zenius =false;
            }
        }
        else {
          zenius =false;
          }
      }
      else if (count [i]=1){
        if (rJam ==(stimeInt[i][0]-1)){
          if (((60+stimeInt[i][1])-rMen)<=10){
          zenius = true;
            }
            else{
              zenius =false;}
          }
       else if (rJam==stimeInt[i][0]) {
          if(rMen<=(stimeInt[i][1]+10)){
           zenius = true;
          }
          else{
            zenius =false;
            }
          }
         else {
          zenius = false;
          }
        }

}
