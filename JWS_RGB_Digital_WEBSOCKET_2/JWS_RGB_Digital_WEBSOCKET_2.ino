#define PANEL_RES_X 64
#define PANEL_RES_Y 32
#define NUM_ROWS 2
#define NUM_COLS 3
#define PANEL_CHAIN NUM_ROWS*NUM_COLS
#define SERPENT false
#define TOPDOWN false
#include <ESP32-VirtualMatrixPanel-I2S-DMA.h>
const byte row0 = 2 + 0 * 11;
const byte row1 = 2 + 1 * 11;
const byte row2 = 2 + 2 * 11;
int start_x   = 0;
int buffer_id = 0;
const int square_size = 16;
MatrixPanel_I2S_DMA *dma_display = nullptr;
VirtualMatrixPanel  *virtualDisp = nullptr;
#include <Fonts/Font5x7.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/BigNumber.h>
#include <Fonts/FreeSerifBold9pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>
#define f1 &Font5x78pt7b

// Waktu
#include <Wire.h>
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
#include <JadwalSholat.h>
#include <WiFi.h>
#include <AsyncTCP.h>

#include <ESPAsyncWebServer.h>
#include "FS.h"
#include <LITTLEFS.h>
#include <ArduinoJson.h>

const char* ssid = "SII-Cikunir";
const char* password = "admin.admin";
String textJln;
int pTeks;

#include "Config.h"
#include "RTC.h"
#include "Ali.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
#include "FSconfig.h"
#include "JWS.h"
#include "WebPage.h"
#include "WebSocket.h"

uint8_t lebar;

uint8_t x = 8;
uint8_t y = 35;
uint8_t x_jadwal = 62;
uint8_t y_jadwal = 19;

void setup() {
  Serial.begin(9600);
  Serial.println("setup selesai");

  if (!LITTLEFS.begin(FORMAT_LITTLEFS_IF_FAILED)) {
    Serial.println("LITTLEFS Mount Failed");
    return;
  }
  //  DataDefault();
  readFileJWS(LITTLEFS, filejws);
  readFileAdmin(LITTLEFS, fileAdmin);
  readFileInfo(LITTLEFS, fileInfo);
  textJln = String(p_info.info1);
  mulaiRTC();
  BacaRTC();
  updateJWS();

  HUB75_I2S_CFG mxconfig(
    PANEL_RES_X,   // module width
    PANEL_RES_Y,   // module height
    PANEL_CHAIN    // chain length
  );
  mxconfig.double_buff = true;
  mxconfig.clkphase = false;
  if (NUM_ROWS <= 1) {
    Serial.println(F("There is no reason to use the VirtualDisplay class for a single horizontal chain and row!"));
  }
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  dma_display->setBrightness8(100);
  if ( not dma_display->begin() )
    Serial.println("** !KABOOM! I2S memory allocation failed *****");

  virtualDisp = new VirtualMatrixPanel((*dma_display), NUM_ROWS, NUM_COLS, PANEL_RES_X, PANEL_RES_Y, SERPENT, TOPDOWN);
  lebar = virtualDisp->width();

  setup_websocket();
}
uint8_t cursor_block[6][4] {
  {65, 13, 29, 15},
  {111, 13, 29, 15},
  {153, 13, 35, 15},
  {65, 30, 29, 15},
  {103, 30, 41, 15},
  {157, 29, 26, 16}
};



void loop() {
  ws.cleanupClients();
  BacaRTC();
  kedip();
  virtualDisp->flipDMABuffer();
  virtualDisp->clearScreen();
  info(textJln, 59);
  Disp_Main();
  
  if(kdp&&azzan){
//    virtualDisp->fillRect(cursor_block[iSholatNow[0],cursor_block[SholatNow][1], cursor_block[SholatNow][2], cursor_block[SholatNow][3], 0B1111111111111111);//isya'
    virtualDisp->fillRect(cursor_block[SholatNow][0],cursor_block[SholatNow][1], cursor_block[SholatNow][2], cursor_block[SholatNow][3], 0B0000000000000000);//isya'
  }
  static bool lsKdp = kdp;
  if (lsKdp != kdp) {
    lsKdp = kdp;
    //    Serial.println("cek adzan");
    check_azzan();
  }
  //kirim waktu websocket
  if(LDet!=rDet){
    LDet=rDet;
    char z[8];
    sprintf(z, "%02d:%02d:%02d", rJam, rMen, rDet);
    notifyClients(String(z), "0");
  }
}

void info(String msg, uint16_t y) {
  uint32_t Tmr = millis();
  static String pesan;
  static uint32_t lsRn;
  static int16_t x = lebar;
  if ((Tmr - lsRn) > 30) {
    lsRn = Tmr;
    x--;
    if (x < (15 * (-5))) {
      x = lebar;
    }
  }
  virtualDisp->setFont(&FreeMono9pt7b);
  //  virtualDisp->setTextSize(1);
  virtualDisp->setCursor(x, y);
  virtualDisp->setTextColor( 0B0000011111100000);
  virtualDisp->printf(msg.c_str());
}

void Disp_Main() {
  virtualDisp->fillRect(0, 40, 64, 61, 0B0000000000000000);
  virtualDisp->fillRect(184, 40, 64, 30, 0B0000000000000000);
  virtualDisp->drawCircle(31, 32, 31, 0B0000011111100000);
  virtualDisp->drawCircle(31, 32, 30, 0B0000011111100000);
  virtualDisp->drawCircle(31, 32, 28, 0B0000011111100000);
  virtualDisp->drawLine(8, 23, 54, 23, 0B1111111111111111);
  virtualDisp->drawLine(8, 40, 54, 40, 0B1111111111111111);
  virtualDisp->setTextColor( 0B0000011111100000);
  virtualDisp->setFont(&BigNumber7pt7b);
  virtualDisp->setTextColor( 0B1111111111111111);
  virtualDisp->setCursor(x, y);
  virtualDisp->printf("%02d %02d %02d", rJam, rMen, rDet);
  virtualDisp->setTextColor(0B0000011111100000);
  if (kdp) {
    virtualDisp->setCursor(x + 13, y);
    virtualDisp->printf(":");
    virtualDisp->setCursor(x + 30, y);
    virtualDisp->printf(":");
  }
  virtualDisp->setTextColor( 0B1111111111111111);
  virtualDisp->setFont(&Font5x78pt7b);
  virtualDisp->setCursor(26, 13);
  virtualDisp->printf("%02d", rTgl);
  virtualDisp->setCursor(23, 21);
  virtualDisp->printf(namaBulan[rBul]);
  virtualDisp->setCursor(18, 50);
  virtualDisp->printf(namaHari[rHar]);
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
