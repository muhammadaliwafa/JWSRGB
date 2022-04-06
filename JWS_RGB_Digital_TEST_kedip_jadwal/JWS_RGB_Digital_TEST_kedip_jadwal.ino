#define PANEL_RES_X 64 // Number of pixels wide of each INDIVIDUAL panel module. 
#define PANEL_RES_Y 32 // Number of pixels tall of each INDIVIDUAL panel module.

#define NUM_ROWS 2 // Number of rows of chained INDIVIDUAL PANELS
#define NUM_COLS 3 // Number of INDIVIDUAL PANELS per ROW
#define PANEL_CHAIN NUM_ROWS*NUM_COLS    // total number of panels chained one to another

// Change this to your needs, for details on VirtualPanel pls read the PDF!
#define SERPENT false
#define TOPDOWN false

// library includes
#include <ESP32-VirtualMatrixPanel-I2S-DMA.h>
#include "Lama.h"

// placeholder for the matrix object
MatrixPanel_I2S_DMA *dma_display = nullptr;

// placeholder for the virtual display object
VirtualMatrixPanel  *virtualDisp = nullptr;

#include <Fonts/Font5x7.h>
#include <Fonts/BigNumber.h>
#include <Fonts/FreeSerifBold9pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>





#define f1 &Font5x78pt7b



// Waktu
#include <Wire.h>
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
#include <JadwalSholat.h>

#include "RTC.h"
#include "Ali.h"
#include "JWS.h"

uint8_t lebar;

uint8_t x = 8;
uint8_t y = 35;
uint8_t x_jadwal = 62;
uint8_t y_jadwal = 19; 






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

  // So far so good, so continue
//  virtualDisp->fillScreen(virtualDisp->color444(0, 0, 0));
//  virtualDisp->drawDisplayTest(); // draw text numbering on each screen to check connectivity
//
//   virtualDisp->setFont(&FreeSansBold12pt7b);
//   virtualDisp->setTextColor(virtualDisp->color565(0, 0, 255));
//   virtualDisp->setTextSize(1); 
//   virtualDisp->setCursor(1, virtualDisp->height()-20); 
   
   // Red text inside red rect (2 pix in from edge)
//   virtualDisp->print("1234");
//   virtualDisp->drawRect(1,1, virtualDisp->width()-2, virtualDisp->height()-2, virtualDisp->color565(255,0,0));
//
//   // White line from top left to bottom right
//   virtualDisp->drawLine(0,0, virtualDisp->width()-1, virtualDisp->height()-1, virtualDisp->color565(255,255,255));

    lebar = virtualDisp->width();
//    virtualDisp->setTextSize(1);
    
   
  
}

void loop() {
  BacaRTC();
  kedip();
  virtualDisp->flipDMABuffer();    
  //if ( !display->backbuffready() ) return;
  //display->showDMABuffer();        
  virtualDisp->clearScreen(); 
  virtualDisp->setTextSize(1);
   
  info("Created by PT Solusi Intek Indonesia on Tytyan Kencana", 59);
  virtualDisp->fillRect(0,40, 64, 61, 0B0000000000000000);
  virtualDisp->fillRect(184,40, 64, 30, 0B0000000000000000);
  
  
  virtualDisp->drawCircle(31,32,31,0B0000011111100000);
  virtualDisp->drawCircle(31,32,30,0B0000011111100000);
  virtualDisp->drawCircle(31,32,28,0B0000011111100000);

  virtualDisp->drawLine(8,23,54,23,0B1111111111111111);
  virtualDisp->drawLine(8,40,54,40,0B1111111111111111);


  virtualDisp->setTextColor( 0B0000011111100000);
//  virtualDisp->drawRect(1,1, 189, 61, 0B1111100000000000);
//  virtualDisp->drawRect(2,2, 189, 61, 0B0000011111111111);
   
   
  
  

   
  
  virtualDisp->setFont(&BigNumber7pt7b); 
//  virtualDisp->setTextSize(1);
  virtualDisp->setTextColor( 0B1111111111111111); 
//  virtualDisp->setCursor(x_jadwal+20, 11);
//  virtualDisp->print("Masjid Jami' Alhuda Bittaqwa");
  
  virtualDisp->setCursor(x, y); 
  virtualDisp->printf("%02d %02d %02d", rJam, rMen, rDet);
  if (kdp) {
//    virtualDisp->setTextColor(0B1111111111111111);
    virtualDisp->setCursor(x+13, y); 
    virtualDisp->printf(":");
    virtualDisp->setCursor(x+30, y); 
    virtualDisp->printf(":");
  }  
  
//  jamAnalog();
//  virtualDisp->fillRect(8,40, 47, 2, 0B1111111111111111);
  
  
  

//  
  
//  virtualDisp->setTextColor(0B1111100000000000);
//  
  
  
  virtualDisp->setFont(&Font5x78pt7b);
//  virtualDisp->setTextColor( 0B1111111111111111);
  virtualDisp->setCursor(26, 13);
  virtualDisp->printf("%02d", rTgl);
  virtualDisp->setCursor(23, 21);
  virtualDisp->printf(namaBulan[rBul]);
  virtualDisp->setCursor(18, 50);
  virtualDisp->printf(namaHari[rHar]);
  
  virtualDisp->setCursor(x_jadwal+3, y_jadwal); 
//  virtualDisp->setTextColor( 0B0000011111100000);

  
  
   
  virtualDisp->print("SUBUH    DHUHA   DZUHUR");
//  virtualDisp->setCursor(x_jadwal+47, y_jadwal);
//  virtualDisp->print("SUBUH");
//  virtualDisp->setCursor(x_jadwal+47+40, y_jadwal);
//  virtualDisp->print("DZUHUR");

  virtualDisp->setCursor(x_jadwal+3, y_jadwal+17);  
  virtualDisp->print("ASHAR  MAGHRIB   ISYA'");
//  virtualDisp->setCursor(x_jadwal+41, y_jadwal+17);
//  virtualDisp->print("MAGHRIB");
//  virtualDisp->setCursor(x_jadwal+47+45, y_jadwal+17);
//  virtualDisp->print("ISYA'");
  
  
//  virtualDisp->setTextColor( 0B0000011111111111); 
  virtualDisp->setCursor(x_jadwal+4, y_jadwal+8);
  virtualDisp->printf("%02d:%02d    %02d:%02d    %02d:%02d", stimeInt[1][0], stimeInt[1][1], stimeInt[3][0], stimeInt[3][1], stimeInt[4][0], stimeInt[4][1]);
//  virtualDisp->setCursor(x_jadwal+47, y_jadwal+8);
//  virtualDisp->printf("%02d:%02d", 8, 8);
//  virtualDisp->setCursor(x_jadwal+91, y_jadwal+8);
//  virtualDisp->printf("%02d:%02d", 8, 8);

//  virtualDisp->setCursor(18, 50);
//  virtualDisp->printf(namaHari[rHar]);

  virtualDisp->setCursor(x_jadwal+4, y_jadwal+25);
  virtualDisp->printf("%02d:%02d    %02d:%02d    %02d:%02d", stimeInt[5][0], stimeInt[5][1], stimeInt[6][0], stimeInt[6][1], stimeInt[7][0], stimeInt[7][1]);

  virtualDisp->setTextColor(0B0000011111100000);
  virtualDisp->setCursor(x_jadwal-7, 8);
  virtualDisp->print("Masjid Jami' Alhuda Bittaqwa");
//  virtualDisp->setCursor(x_jadwal+47, y_jadwal+25);
//  virtualDisp->printf("%02d:%02d", 8, 8);
//  virtualDisp->setCursor(x_jadwal+91, y_jadwal+25);
//  virtualDisp->printf("%02d:%02d", 8, 8);
  
//  if(kdp){
//    virtualDisp->fillRect(149,12, 39, 16, 0B0000000000000000);//dzuhur
//    virtualDisp->fillRect(96,12, 44, 16, 0B0000000000000000);//dhuha
//    virtualDisp->fillRect(65,12, 44, 16, 0B0000000000000000);//subuh
//    virtualDisp->fillRect(65,30, 33, 16, 0B0000000000000000);//ashar
//    virtualDisp->fillRect(148,29, 40, 17, 0B0000000000000000);//isya'
//    virtualDisp->fillRect(101,29, 44, 17, 0B0000000000000000);//maghrib
//  }

  

//  virtualDisp->setFont(&BigNumber7pt7b);
  

  
  
}

void info(String msg, uint16_t y){
  uint32_t Tmr = millis();
  static String pesan;
  static uint32_t lsRn;
  static int16_t x=lebar;
  if((Tmr-lsRn)>30){
    lsRn = Tmr;
    x--;
    if(x<(54*-5)){
      x=lebar;
    }
  }
  virtualDisp->setFont(&FreeSerif9pt7b);
//  virtualDisp->setTextSize(1);
  virtualDisp->setCursor(x, y); 
  virtualDisp->setTextColor( 0B0000011111100000);
  virtualDisp->printf(msg.c_str());
}
