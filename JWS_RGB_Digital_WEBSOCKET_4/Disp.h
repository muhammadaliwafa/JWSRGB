uint8_t x = 8;
uint8_t y = 35;
uint8_t x_jadwal = 62;
uint8_t y_jadwal = 19;
int8_t jumlah_beep = 0;
bool tndaBuzzer = false;

String tampil_waktu[]={"Waktu Imsyak", "Waktu Adzan", "Waktu Adzan", "Waktu Dhuha", "Waktu Adzan", "Waktu Adzan", "Waktu Adzan", "Waktu Adzan"};

uint8_t cursor_block[8][4] {
  {0, 0, 0, 0},
  {65, 13, 29, 15},
  {0, 0, 0, 0},
  {111, 13, 29, 15},
  {153, 13, 35, 15},
  {65, 30, 29, 15},
  {103, 30, 41, 15},
  {157, 29, 26, 16}
};
void buzz(int8_t n){
  time2 = millis();
  jumlah_beep=(n*2)-1;
}
void Disp_Azzan(String x, uint16_t y) {
  virtualDisp->setFont(&FreeMono9pt7b);
  //  virtualDisp->setTextSize(1);
  virtualDisp->setCursor(75, y);
  virtualDisp->print(x);
}

//void Disp_Iqmh(uint16_t y){
//  virtualDisp->setFont(&FreeMono9pt7b);
//  virtualDisp->setCursor(70, y);
//  virtualDisp->printf("Iqomah : %02d", hitung);
//  hitung--;
//  if(hitung<=0){
//    iqmh=false;
//  }
//}
int16_t textWidth(const char* text)
{
  int16_t x1, y1;
  uint16_t w, h;
  virtualDisp->getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  return w;
}


void tampilIqomah(uint16_t y, uint8_t& cycl, bool rst){
  static bool lKdp=kdp;
  static int8_t i_menit = timer_iqomah();
  static int8_t i_detik = 0;
//  static bool rst1=true;
  if(rst){
    i_menit = timer_iqomah();
    if(i_menit<=0){
      cycl--;
//      rst1=false;
      return;
    }
    i_detik = 0;
//    rst = false;
  }
  virtualDisp->setFont(&FreeMono9pt7b);
  //  virtualDisp->setTextSize(1);
  virtualDisp->setCursor(65, y);
  virtualDisp->printf("Iqomah : %02d:%02d", i_menit, i_detik);
  if(kdp)virtualDisp->fillRect(65, 49, 60, 14, 0B0000000000000000);
  if(lKdp!=kdp){
    lKdp=kdp;
    
    if(!lKdp)return;
    i_detik--;
    if(i_detik<0){
      i_menit--;
      if(i_menit<0){
        cycl++;
//        buzz(3);
        return;
      }
      i_detik=59;
    }
  }
  
}

void tekanTombol(uint8_t& cycl){
  static bool state = false;
  bool out=digitalRead(tombol);
//  Serial.println(out);
  if(out){
    state=HIGH;
  }
  if(state){
    if(!out){
      if(!iqmh){
        iqmh=true;
        cycl++;
        tampilIqomah(59, cycl, true);
        buzz(1);
      }else{
        iqmh=false;
        cycl--;
        buzz(1);
      }
      
      state=LOW;
    }
  }
}

void sebelumSholat(String msg, uint16_t y, uint8_t& cycl){
  uint32_t Tmr = millis();
  static uint32_t lsRn;
  static int16_t x = lebar;
  static bool rst=true;
  static int8_t beep_sholat;
  if(rst){
    pTeks = msg.length();
    beep_sholat = 3;
    buzz(3);
    rst=false;
  }
  if ((Tmr - lsRn) > 30) {
    lsRn = Tmr;
    x--;
    if (x < (pTeks * (-9))) {
      x = lebar;
      cycl++;
      rst=true;
      azzan = false;
      tarhim = false;
      return;
    }
  }
  virtualDisp->setFont(&FreeMono9pt7b);
  //  virtualDisp->setTextSize(1);
  virtualDisp->setCursor(x, y);
  virtualDisp->print(msg);
  virtualDisp->fillRect(0, y - 11, 64, 15, 0B0000000000000000);
  virtualDisp->fillRect(184, y - 11, 8, 15, 0B0000000000000000);
}

void Disp_Info(String msg, uint16_t y, uint8_t& cycl) {
//  bool a = bitRead(bit_data, cycl);
//  Serial.printf("%d  %d\n", cycl, a);
  if(!bitRead(bit_data, cycl)){
    cycl++;
    return;
  }
  uint32_t Tmr = millis();
  static uint32_t lsRn;
  static int16_t x = lebar;
  static int16_t txt_bnd;
  static bool rst=true;
  if(rst){
    pTeks = msg.length()*(-7);
    lsRn = Tmr;
    x = lebar;
//    txt_bnd = textWidth(msg.c_str());
    rst = false;
  }
  if ((Tmr - lsRn) > 15) {
    lsRn = Tmr;
    x--;
    if (x < pTeks) {
      cycl++;
      rst=true;
    }
  }
  virtualDisp->setFont(&FreeSerif9pt7b);
//    virtualDisp->setTextSize(1);
  virtualDisp->setCursor(x, y);
  virtualDisp->print(msg.c_str());
  virtualDisp->fillRect(0, y - 12, 64, 17, 0B0000000000000000);
  virtualDisp->fillRect(184, y - 12, 8, 17, 0B0000000000000000);
}

void info_puasa(uint16_t y, uint8_t& cycl){
  static String msg = "";
  uint32_t Tmr = millis();
  static uint32_t lsRn;
  static int16_t x = lebar;
  static bool rst=true;
  static uint8_t i_p;
  static int16_t s_pTeks;
  if(!p_jws.disppuasa){
    cycl++;
    return;
  }
  if(rst){
    i_p = check_puasa();
    if(i_p==0){
      cycl++;
      rst = true;
      return;
    }
    msg = String(namaPuasa[i_p-1]);
    x = lebar;
    s_pTeks = *(&namaPuasa[i_p-1] + 1) - namaPuasa[i_p-1];
    rst = false;
  }
  
  
  if ((Tmr - lsRn) > 15) {
    lsRn = Tmr;
    x--;
    if (x < (s_pTeks * (-9))) {
      cycl++;
      rst=true;
    }
  }
  virtualDisp->setFont(&FreeSerif9pt7b);
//    virtualDisp->setTextSize(1);
  virtualDisp->setCursor(x, y);
  virtualDisp->print(msg.c_str());
  virtualDisp->fillRect(0, y - 12, 64, 17, 0B0000000000000000);
  virtualDisp->fillRect(184, y - 12, 8, 17, 0B0000000000000000);
}

void cycle_info(){
  static uint8_t cycle=0;
  static int8_t n_beep=10;
  if (lsKdp != kdp) {
    lsKdp = kdp;
    check_azzan(cycle, n_beep);
    
  }
  switch(cycle){
    case 0://menampilkan nama penceramah
      Disp_Info(String(p_info.info1), 59, cycle);
      break;
    case 1:
      Disp_Info(String(p_info.info2), 59, cycle);
      break;
    case 2:
      Disp_Info(String(p_info.info3), 59, cycle);
      break;
    case 3:
      Disp_Info(String(p_info.info4), 59, cycle);
      break;
    case 4:
      Disp_Info(String(p_info.info5), 59, cycle);
      break;
    case 5:
      Disp_Info(String(p_info.info6), 59, cycle);
      break;
    case 6:
      Disp_Info(String(p_info.info7), 59, cycle);
      break;
    case 7:
      Disp_Info(String(p_info.info8), 59, cycle);
      break;
    case 8:
      Disp_Info(String(p_info.info9), 59, cycle);
      break;
    case 9:
      Disp_Info(String(p_info.info10), 59, cycle);
      break;
    case 10:
      Serial.println("dieksekusi");
      info_puasa(59, cycle);
//      Disp_Info(String(namaPuasa[4]), 59, cycle);
//      cycle++;
      break;
    case 50:
      static bool lKdp=kdp;
      tekanTombol(cycle);
      disableAzzan(cycle);
      if(jumat)return;
      !kdp ? Disp_Azzan(tampil_waktu[SholatNow], 59) : virtualDisp->fillRect(cursor_block[SholatNow][0], cursor_block[SholatNow][1], cursor_block[SholatNow][2], cursor_block[SholatNow][3], 0B0000000000000000);
      if(lKdp!=kdp){
        lKdp=kdp;
        if(n_beep>0){
          n_beep--;
          digitalWrite(buzzer, !kdp);
        }else{
          digitalWrite(buzzer, LOW);
          if (rHar == 5 and SholatNow == 4) {
            jumat = true;
          }
        }
      }
      break;
    case 51:
      tekanTombol(cycle);
      tampilIqomah(59, cycle, false);
      break;
    case 52:
      sebelumSholat("Lurus dan Rapatkan Shaf Demi Kesempurnaan Sholat Berjamaah", 59,  cycle);
      break;
    case 100:
      virtualDisp->setFont(&FreeMono9pt7b);
  //  virtualDisp->setTextSize(1);
      virtualDisp->setCursor(65, 59);
      virtualDisp->printf("Iqomah : %02d:%02d", 5, 5);
      virtualDisp->fillRect(65, 49, 60, 14, 0B1111111111111111);
      break;
    default:
      cycle = 0;
      break;
      
  }
  
}

void Disp_Main() {
//  if(jumat) return;
  virtualDisp->setCursor(x_jadwal + 3, y_jadwal);
  virtualDisp->print("SUBUH    DHUHA   DZUHUR");
  virtualDisp->setCursor(x_jadwal + 3, y_jadwal + 17);
  virtualDisp->print("ASHAR  MAGHRIB   ISYA'");
  virtualDisp->setCursor(x_jadwal + 4, y_jadwal + 8);
  virtualDisp->printf("%02d:%02d    %02d:%02d    %02d:%02d", stimeInt[1][0], stimeInt[1][1], stimeInt[3][0], stimeInt[3][1], stimeInt[4][0], stimeInt[4][1]);
  virtualDisp->setCursor(x_jadwal + 4, y_jadwal + 25);
  virtualDisp->printf("%02d:%02d    %02d:%02d    %02d:%02d", stimeInt[5][0], stimeInt[5][1], stimeInt[6][0], stimeInt[6][1], stimeInt[7][0], stimeInt[7][1]);
  virtualDisp->setTextColor(0B0000011111100000);
  virtualDisp->setCursor(x_jadwal - 7, 8);
  virtualDisp->print("Musholla Al-Muhajirin");
}

void tengah(int x, String y){
  int tngh = (lebar/3-(y.length())*6)/2;
  virtualDisp->setCursor(tngh, x);
  virtualDisp->print(namaHari[rHar]);
}


void Disp_Jam() {
  virtualDisp->drawCircle(31, 32, 31, 0B0000011111100000);
  virtualDisp->drawCircle(31, 32, 30, 0B0000011111100000);
  virtualDisp->drawCircle(31, 32, 28, 0B0000011111100000);
  virtualDisp->drawLine(8, 23, 54, 23, 0B1111111111111111);
  virtualDisp->drawLine(8, 40, 54, 40, 0B1111111111111111);
  virtualDisp->setFont(&BigNumber7pt7b);
  if (kdp) {
    virtualDisp->setCursor(x + 13, y);
    virtualDisp->printf(":");
    virtualDisp->setCursor(x + 30, y);
    virtualDisp->printf(":");
  }
  virtualDisp->setTextColor( 0B1111111111111111);
  virtualDisp->setCursor(x, y);
  virtualDisp->printf("%02d %02d %02d", rJam, rMen, rDet);
  virtualDisp->setFont(&Font5x78pt7b);
  virtualDisp->setCursor(26, 13);
  virtualDisp->printf("%02d", rTgl);
  virtualDisp->setCursor(23, 21);
  virtualDisp->printf(namaBulan[rBul]);
  tengah(50, String(namaHari[rHar]));
}
