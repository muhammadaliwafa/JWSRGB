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
#include "RTClib.h"
#include "Lama.h"
// placeholder for the matrix object
MatrixPanel_I2S_DMA *dma_display = nullptr;

// placeholder for the virtual display object
VirtualMatrixPanel  *virtualDisp = nullptr;

// Waktu
RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int detik, menit, jam, yo;
float mmdetik;
String waktu;

void kursor(int x){
  x=x+30;
  virtualDisp->setCursor(x,55);
}
void titikGanda(int x){
  x=x*60;
  virtualDisp->setCursor(x, 55);
}

String nol(int x){
  String hasil;
  if(x<10){
    hasil="0";
  }
  else{hasil="";}
  hasil=hasil+String(x);
  return hasil;
}



/**************************
 * Setup!
 **************************/
void setup() {

    delay(1000);
  Serial.begin(9600);
    delay(200);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

//  if (rtc.lostPower()) {
//    Serial.println("RTC lost power, let's set the time!");
//    // When time needs to be set on a new device, or after a power loss, the
//    // following line sets the RTC to the date & time this sketch was compiled
//    rtc.adjust(DateTime(F(_DATE), F(TIME_)));
//    // This line sets the RTC with an explicit date & time, for example to set
//    // January 21, 2014 at 3am you would call:
//    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    //rtc.adjust(DateTime(2021, 12, 16, 18, 12, 0));
//  }
  //rtc.adjust(DateTime(F(_DATE), F(TIME_)));
  

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
    DateTime now = rtc.now();
    start_x = virtualDisp->width();
    yo = now.second();
}

void loop() {
  DateTime now = rtc.now();
////    virtualDisp->print(now.year(), DEC);
////    virtualDisp->print('/');
////    virtualDisp->print(now.month(), DEC);
////    virtualDisp->print('/');
////    virtualDisp->print(now.day(), DEC);
////    virtualDisp->print(" (");
////    virtualDisp->print(daysOfTheWeek[now.dayOfTheWeek()]);
////    virtualDisp->print(") ");
////    virtualDisp->print(now.hour(), DEC);
////    virtualDisp->print(':');
////    virtualDisp->print(now.minute(), DEC);
////    virtualDisp->print(':');
////    virtualDisp->print(now.second(), DEC);
////    virtualDisp->println();
//
////    virtualDisp->print("Temperature: ");
////      virtualDisp->print(rtc.getTemperature());
//
//   virtualDisp->setFont(&FreeSansBold12pt7b);
//   virtualDisp->setTextColor(0B0000011111111111);
//   virtualDisp->setTextSize(1); 
//   
  detik= now.second();
  menit=now.minute();
 jam=now.hour();
// virtualDisp->flipDMABuffer();
// virtualDisp->clearScreen();
 mmdetik=detik*1.0/2.0;
// if(detik!=yo){
//    
//    Serial.print(jam);
//    Serial.print("  ");
//    Serial.print(menit);
//    Serial.print("  ");
//    Serial.println(detik);
//    yo=detik;
//    virtualDisp->setCursor(60,30);
//    virtualDisp->print("Waktu");
//    kursor(0);
//    virtualDisp->print(nol(jam));
//    titikGanda(1);
//    virtualDisp->print(" :");
//    kursor(60);
//    virtualDisp->print(nol(menit));
//    titikGanda(2);
//    virtualDisp->print(" :");
//    kursor(120);
//    virtualDisp->print(nol(detik));
//    virtualDisp->drawRect(1,1, 189, 61, 0B1111100000000000);
//    virtualDisp->drawRect(3,3, 188, 60, 0B0000011111111111);
//    
//    
//
////    virtualDisp->clearScreen();
////    virtualDisp->setCursor(60,30);
////    virtualDisp->print("Waktu");
////    kursor(0);
////    virtualDisp->print(nol(jam));
//////    titikGanda(1);
//////    virtualDisp->print(" :");
////    kursor(60);
////    virtualDisp->print(nol(menit));
//////    titikGanda(2);
//////    virtualDisp->print(" :");
////    kursor(120);
////    virtualDisp->print(nol(detik));
////    virtualDisp->drawRect(1,1, 189, 61, 0B1111100000000000);
////    virtualDisp->drawRect(3,3, 188, 60, 0B0000011111111111);
//   }
virtualDisp->flipDMABuffer();    
  //if ( !display->backbuffready() ) return;
  //display->showDMABuffer();        
  virtualDisp->clearScreen();  
    
  buffer_id ^= 1;

  // Blue square on the left is printed to BOTH buffers.
  
   virtualDisp->drawRect(1,1, 189, 61, 0B1111100000000000);
   virtualDisp->drawRect(2,2, 189, 61, 0B0000011111111111);
  start_x--;

  if (buffer_id)
  {
    virtualDisp->setCursor(60, row2+28);  
     virtualDisp->setFont(&FreeSansBold12pt7b);
     virtualDisp->setTextSize(1);  
    virtualDisp->setTextColor( 0B1111100000000000);      
    
    virtualDisp->printf("%02d %02d %02d", jam,menit,detik);
    //delay(40); // simulate slow drawing operation
  } 
  else 
  {
    virtualDisp->setCursor(68, row1+8);    
    virtualDisp->setTextColor(virtualDisp->color565(0, 200, 0));          
    virtualDisp->print("waktu");
  }
  
  
 
  if (start_x < (-1*square_size)) start_x = virtualDisp->width()+square_size;
  
  
} // end loop
