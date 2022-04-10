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
// DFPlayer
#include <DFRobotDFPlayerMini.h>
DFRobotDFPlayerMini myDFPlayer;

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LITTLEFS.h>
#include <ArduinoJson.h>

const char* ssid = "SII-Cikunir";
const char* password = "admin.admin";
String textJln;
int pTeks;
uint32_t time1, time2;
uint8_t lebar;
uint8_t buzzer = 32;
uint8_t tombol = 34;

uint8_t hitung;
int hIqmh=0;


//LittleFS
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

struct parameterAdmin {
  double lat;
  double lon;
  int8_t z_w; //zona waktu
  uint8_t hilal;
  char ssid[20];
  char p_ssid[20];
  char ap[16];
  char p_ap[8];
  int batastombol;
}; parameterAdmin p_admin;

struct parameterInfo {
  char info1[512];
  char info2[512];
  char info3[512];
  char info4[512];
  char info5[512];
  char info6[512];
  char info7[512];
  char info8[512];
  char info9[512];
  char info10[512];
}; parameterInfo p_info;

struct parameterAtur {
  uint8_t cerah;
  uint8_t volume;
}; parameterAtur p_atur;

#include "Config.h"
#include "DF.h"
#include "RTC.h"
#include "Ali.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
#include "FSconfig.h"
#include "JWS.h"
#include "WebPage.h"
#include "WebSocket.h"
#include "Disp.h"

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

void setup() {
  Serial.begin(9600);
    Serial.println("setup selesai");
  pinMode(buzzer, OUTPUT);
  pinMode(tombol, INPUT);
  if (!LITTLEFS.begin(FORMAT_LITTLEFS_IF_FAILED)) {
    //    Serial.println("LITTLEFS Mount Failed");
    return;
  }
//    DataDefault();
  //  deleteFile(LITTLEFS, filejws);
  //  writeFile(LITTLEFS, filejws,p_defaultJWS().c_str());
//  writeFile(LITTLEFS, fileAtur, p_defaultAtur().c_str());
  readFileJWS(LITTLEFS, filejws);
  readFileAdmin(LITTLEFS, fileAdmin);
  readFileInfo(LITTLEFS, fileInfo);
  readFileAtur(LITTLEFS, fileAtur);
  textJln = String(p_info.info1);
  pTeks = textJln.length();
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
  dma_display->setBrightness8((p_atur.cerah)-'0');
  if ( not dma_display->begin() )
        Serial.println("** !KABOOM! I2S memory allocation failed *****");

    virtualDisp = new VirtualMatrixPanel((*dma_display), NUM_ROWS, NUM_COLS, PANEL_RES_X, PANEL_RES_Y, SERPENT, TOPDOWN);
  lebar = virtualDisp->width();

  setDF();

  setup_websocket();
  lsKdp = kdp;
  virtualDisp->setTextColor(0B1111111111111111);
}

void loop() {
  Serial.println("loop bagin");
  ws.cleanupClients();
  //tanda terima data dari web
  if (tndaBuzzer) {
    digitalWrite(buzzer, HIGH);
    if (millis() - time2 >= 500) {
      tndaBuzzer = false;
      digitalWrite(buzzer, LOW);
    }
  }
  BacaRTC();
  kedip();
  virtualDisp->flipDMABuffer();
  virtualDisp->clearScreen();
  if (!jumat or blynk) {
    Disp_Main();
    if (!blynk) {
      Disp_Info(textJln, 59);
    }
    if (kdp && blynk) {
      //      virtualDisp->fillRect(cursor_block[iSholatNow[0],cursor_block[SholatNow][1], cursor_block[SholatNow][2], cursor_block[SholatNow][3], 0B1111111111111111);//isya'
      virtualDisp->fillRect(cursor_block[SholatNow][0], cursor_block[SholatNow][1], cursor_block[SholatNow][2], cursor_block[SholatNow][3], 0B0000000000000000); //isya'
      digitalWrite(buzzer, LOW);
    } else if (!kdp && blynk) {
      switch (SholatNow) {
        case 0:
          Disp_Azzan("Imsyak", 59);
          break;
        case 2:
          Disp_Azzan("Terbit", 59);
          break;
        case 3:
          Disp_Azzan("Dhuha", 59);
          break;
        default:
          Disp_Azzan("ADZAN", 59);
          break;
      }
      digitalWrite(buzzer, HIGH);
    } else if(iqmh & kdp){
        Disp_Iqmh(59);
        digitalWrite(buzzer, LOW);
    }else {
      digitalWrite(buzzer, LOW);
    }
  } else {
    digitalWrite(buzzer, LOW);
  }
  
  if(hIqmh>0){
    digitalRead(tombol);
    if(tombol){
      hIqmh=0;
      iqmh=true;
    }
    if(kdp){
      hIqmh--;
    }
  }
  
  Disp_Jam();
  if (lsKdp != kdp) {
    lsKdp = kdp;
    check_azzan();

  }
  aturBlynk();
  //  Serial.print(azzan);
  //  Serial.println(blynk);
  //kirim waktu websocket
  if (LDet != rDet) {
    LDet = rDet;
    char z[8];
    sprintf(z, "%02d:%02d:%02d", rJam, rMen, rDet);
    notifyClients(String(z), "1");
  }
}
