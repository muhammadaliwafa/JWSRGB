#define PANEL_RES_X 64 // Number of pixels wide of each INDIVIDUAL panel module. 
#define PANEL_RES_Y 32 // Number of pixels tall of each INDIVIDUAL panel module.

#define NUM_ROWS 1 // Number of rows of chained INDIVIDUAL PANELS
#define NUM_COLS 6 // Number of INDIVIDUAL PANELS per ROW
#define PANEL_CHAIN NUM_ROWS*NUM_COLS    // total number of panels chained one to another

// Change this to your needs, for details on VirtualPanel pls read the PDF!
#define SERPENT false
#define TOPDOWN false

// library includes
#include <ESP32-VirtualMatrixPanel-I2S-DMA.h>
#include "Lama.h"
#include "ESPreset.h"
// placeholder for the matrix object
MatrixPanel_I2S_DMA *dma_display = nullptr;

// placeholder for the virtual display object
VirtualMatrixPanel  *virtualDisp = nullptr;

#include <Fonts/Font5x7.h>
#include <Fonts/BigNumber.h>
//#include <Fonts/FreeSerifBold9pt7b.h>
//#include <Fonts/FreeSerif9pt7b.h>
#include <Fonts/Org_01.h>
#include <Fonts/FreeSerifBoldItalic9pt7b.h>
#include <Fonts/Digital4x7.h>
#include <Fonts/FreeMono9pt7b.h>




#define f1 &Font5x78pt7b



// Waktu
#include <Arduino.h>
#include <Wire.h>
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
#include <JadwalSholat.h>
#include <WiFi.h>
//#include <WiFiClient.h>
//#include <WebServer.h>
//#include <ESPmDNS.h>
//#include <Update.h>
#include<AsyncTCP.h>
#include<ESPAsyncWebServer.h>
#include<AsyncElegantOTA.h>
#include "RTC.h"
#include "Ali.h"
#include "JWS.h"
#include "WebEsp.h"
#include "WebUpdate.h"


//const char* host = "esp32";
const char* ssid = "SII-Cikunir";
const char* password = "admin.admin";

uint8_t lebar;

uint8_t x = 8;
uint8_t y = 35;
uint8_t x_jadwal = 62;
uint8_t y_jadwal = 19; 


//bool param=true;


//WebServer server(80);
AsyncWebServer server(80);

/**************************
 * Setup!
 **************************/
void setup() {
  Serial.begin(115200);
  Serial.println("setup selesai");

  //RTC
  mulaiRTC();
  BacaRTC();
  updateJWS();
  kaka();
  

  HUB75_I2S_CFG mxconfig(
                PANEL_RES_X,   // module width
                PANEL_RES_Y,   // module height
                PANEL_CHAIN    // chain length
  );
  mxconfig.double_buff = true;
  mxconfig.clkphase = false;

  //mxconfig.driver = HUB75_I2S_CFG::FM6126A;     // in case that we use panels based on FM6126A chip, we can set it here before creating MatrixPanel_I2S_DMA object

  // Sanity checks
  if (NUM_ROWS <= 1) {
    Serial.println(F("There is no reason to use the VirtualDisplay class for a single horizontal chain and row!"));
  }

  // OK, now we can create our matrix object
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  
  // let's adjust default brightness to about 75%
  dma_display->setBrightness8(100);    // range is 0-255, 0 - 0%, 255 - 100%

  // Allocate memory and start DMA display
  if( not dma_display->begin() )
      Serial.println("** !KABOOM! I2S memory allocation failed *****");

  // create VirtualDisplay object based on our newly created dma_display object
  virtualDisp = new VirtualMatrixPanel((*dma_display), NUM_ROWS, NUM_COLS, PANEL_RES_X, PANEL_RES_Y, SERPENT, TOPDOWN);

  
    lebar = virtualDisp->width();
//    virtualDisp->setTextSize(1);
    WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  
 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200,"text/html", webpageESP);
  });
  AsyncElegantOTA.begin(&server);
  server.begin();
   
  //server.handleClient();
 //   Serial.printf("Waktu Sholat adalah : %02d:%02d",stimeInt [1][0],stimeInt[1][1]);
    for(int i=0;i<8;i++){
   Serial.println("Count"+String(i)+" = "+String(count[i]));
    }
}

void loop() {
  
  //server.handleClient();
  BacaRTC();
  kedip();
  waktuS();
  lebih (iterated);
  //Serial.println("Waktu sekarang adalah iterasi ke- "+String (iterated));
 // Serial.println ("Waktu Sekarang adalah : "+String (rJam)+":"+String (rMen));
  virtualDisp->flipDMABuffer();    
  //if ( !display->backbuffready() ) return;
  //display->showDMABuffer();        
  virtualDisp->clearScreen(); 
  virtualDisp->setTextSize(2);

 // info ("PT. SOLUSI INTEK INDONESIA",24);
 // virtualDisp->fillRect(0,0,92,32,virtualDisp->color565(0,0,0));
//   virtualDisp->setFont(&Org_01);
//   virtualDisp->setCursor(x+58,y-10);
//   virtualDisp->setTextColor( 0B1111111111111111); 
//   virtualDisp->setTextSize(2);
//   virtualDisp->print(waktu1);
//   virtualDisp->setFont(&BigNumber7pt7b); 

//  virtualDisp->setTextColor( 0B1111111111111111); 
//   virtualDisp->setTextSize(2);
//   virtualDisp->setCursor(x-5,y-13);
//   virtualDisp->printf("%02d %02d",rJam,rMen);
//  virtualDisp->fillRect(89,2,30,30,virtualDisp->color565(0,0,0));


  

 // if (kdp) {
////   virtualDisp->setTextColor(0B1111111111111111);
////   virtualDisp->setCursor(x+20, y-13); 
////   virtualDisp->printf(":");
//////    virtualDisp->setCursor(x+30, y); 
//////    virtualDisp->printf(":");
//     virtualDisp->fillRect(x_jadwal+20,0,65,32,virtualDisp->color565(0,0,0));
//Serial.println("Waktu sekarang adalah iterasi ke- "+String (iterated));
// }  
  
//  jamAnalog();
//  virtualDisp->fillRect(8,40, 47, 2, 0B1111111111111111);
  
  
  

//  
  
  virtualDisp->setTextColor(0B1111100000000000); 
  virtualDisp->setFont(f1);
  virtualDisp->setTextColor( 0B1111111111111111);
  virtualDisp->setTextSize(2);
  virtualDisp->setCursor(x-5, 13);
  virtualDisp->print(namaHari[rHar]);
  virtualDisp->setTextSize(1);
  virtualDisp->setCursor(x-5, 27);
  virtualDisp->printf("%02d-%02d-%02d",rTgl,rBul,rTah);


   virtualDisp->setFont(&BigNumber7pt7b); 
   virtualDisp->setCursor(x_jadwal+20, y_jadwal-8); 
   virtualDisp->setTextColor( 0B0000011111100000);
   virtualDisp->print("SUBUH    DHUHA    DZUHUR");// DHUHA DZUHUR");
   virtualDisp->setCursor(x_jadwal+168, y_jadwal-8);
   virtualDisp->print("ASHAR    MAGHRIB    ISYA'");

  
  
////  virtualDisp->setTextColor( 0B0000011111111111); 
  virtualDisp->setTextColor( 0B1111111111111111); 
  virtualDisp->setCursor(x_jadwal+20, y_jadwal+8);
  virtualDisp->printf("%02d:%02d    %02d:%02d     %02d:%02d", stimeInt[1][0], stimeInt[1][1], stimeInt[3][0], stimeInt[3][1], stimeInt[4][0], stimeInt[4][1]);

 
//
//
//
//
  virtualDisp->setCursor(x_jadwal+168, y_jadwal+8);
  virtualDisp->printf("%02d:%02d      %02d:%02d      %02d:%02d", stimeInt[5][0], stimeInt[5][1], stimeInt[6][0], stimeInt[6][1], stimeInt[7][0], stimeInt[7][1]);
if (kdp) {
         switch (iterated){
          case 1:
          if(zenius){
          virtualDisp->fillRect(x_jadwal+20,0,45,32,virtualDisp->color565(0,0,0)); //SUBUH  
          }
          break;
          case 3:
          if(zenius){ 
          virtualDisp->fillRect(x_jadwal+73,0,45,32,virtualDisp->color565(0,0,0)); //DHUHA 
          }
          case 4:
          if (zenius){
          virtualDisp->fillRect(x_jadwal+112,0,45,32,virtualDisp->color565(0,0,0)); //DZUHUR
          }
          break;
          case 5:
          if (zenius){
          virtualDisp->fillRect(x_jadwal+160,0,45,32,virtualDisp->color565(0,0,0)); //ASHAR
          }
          break;
          case 6:
          if (zenius){
          virtualDisp->fillRect(x_jadwal+215,0,55,32,virtualDisp->color565(0,0,0));  //MAGHRIB
          }
          break;
          case 7:
          if (zenius){
          virtualDisp->fillRect(x_jadwal+272,0,55,32,virtualDisp->color565(0,0,0)); //ISYA
          }
          break;
          default:
          Serial.println("Salah Waktu Shalatnya");
          break;
         }
} 
 
} 
 
  
  
