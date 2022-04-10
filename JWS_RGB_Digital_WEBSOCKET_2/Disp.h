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
  if(hitung==0){
    iqmh=false;
  }
}

void Disp_Info(String msg, uint16_t y) {
  uint32_t Tmr = millis();
  static uint32_t lsRn;
  static int16_t x = lebar;
  if ((Tmr - lsRn) > 30) {
    lsRn = Tmr;
    x--;
    if (x < (pTeks * (-7))) {
      x = lebar;
    }
  }
  virtualDisp->setFont(&FreeMono9pt7b);
  //  virtualDisp->setTextSize(1);
  virtualDisp->setCursor(x, y);
  virtualDisp->printf(msg.c_str());
  virtualDisp->fillRect(0, y - 11, 64, 15, 0B0000000000000000);
  virtualDisp->fillRect(184, y - 11, 8, 15, 0B0000000000000000);
}

void Disp_Main() {
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
  virtualDisp->setCursor(18, 50);
  virtualDisp->printf(namaHari[rHar]);
}
