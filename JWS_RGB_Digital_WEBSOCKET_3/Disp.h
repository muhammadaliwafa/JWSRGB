uint8_t x = 8;
uint8_t y = 35;
uint8_t x_jadwal = 62;
uint8_t y_jadwal = 19;

void Disp_Azzan(String x, uint16_t y) {
  virtualDisp->setFont(&FreeMono9pt7b);
  //  virtualDisp->setTextSize(1);
  virtualDisp->setCursor(75, y);
  x = "WAKTU " + x;
  virtualDisp->print(x);
}

void Disp_Iqmh(uint16_t y){
  virtualDisp->setFont(&FreeMono9pt7b);
  virtualDisp->setCursor(70, y);
  virtualDisp->printf("Iqomah : %02d", hitung);
  hitung--;
  if(hitung<=0){
    iqmh=false;
  }
}

void Disp_Info(String msg, uint16_t y, uint8_t& cycl) {
  if(dInfo[cycl]){
    uint32_t Tmr = millis();
    static uint32_t lsRn;
    static int16_t x = lebar;
    static bool rst=true;
    if(rst){
      pTeks = msg.length();
      rst = false;
    }
    if ((Tmr - lsRn) > 30) {
      lsRn = Tmr;
      x--;
      if (x < (pTeks * (-9))) {
        x = lebar;
        cycl++;
        rst=true;
      }
    }
    virtualDisp->setFont(&FreeMono9pt7b);
    //  virtualDisp->setTextSize(1);
    virtualDisp->setCursor(x, y);
    virtualDisp->printf(msg.c_str());
    virtualDisp->fillRect(0, y - 11, 64, 15, 0B0000000000000000);
    virtualDisp->fillRect(184, y - 11, 8, 15, 0B0000000000000000);
  }else{
    cycl++;
  }
}

void cycle_info(){
  static uint8_t cycle;
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
  virtualDisp->print("Masjid Jami' Alhuda Bittaqwa");
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
