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

// Waktu
#include <Wire.h>
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
#include <JadwalSholat.h>

#include "RTC.h"
#include "Ali.h"






/**************************
 * Setup!
 **************************/
void setup() {
  Serial.begin(115200);

  //RTC
  mulaiRTC();

  

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
  dma_display->setBrightness8(72);    // range is 0-255, 0 - 0%, 255 - 100%

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

    start_x = virtualDisp->width();
    Serial.println("setup selesai");
}

void loop() {
  BacaRTC();
  kedip();
  virtualDisp->flipDMABuffer();    
  //if ( !display->backbuffready() ) return;
  //display->showDMABuffer();        
  virtualDisp->clearScreen();  
    
  
   virtualDisp->drawRect(1,1, 189, 61, 0B1111100000000000);
   virtualDisp->drawRect(2,2, 189, 61, 0B0000011111111111);
     
  virtualDisp->setFont(&FreeSansBold12pt7b);
  virtualDisp->setTextSize(1);  
  virtualDisp->setTextColor( 0B1111100000000000); 
  virtualDisp->setCursor(60, 20); 
  virtualDisp->printf("%02d %02d %02d", rJam, rMen, rDet);
  if (!kdp) {
    virtualDisp->setCursor(60, 18); 
    virtualDisp->printf("    :    :    ");
  }   

  
  
} // end loop
