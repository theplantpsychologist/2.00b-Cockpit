
#include <Adafruit_GFX.h>           // Core graphics library
#include <Adafruit_ST7789.h>        // Hardware-specific library for ST7789
#include <Fonts/FreeSans9pt7b.h>    // for sans-serif font
#include <Adafruit_SPIFlash.h>      // SPI / QSPI flash library

#define TFT_CS        10
#define TFT_RST        9 
#define TFT_DC         8

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

String incomingByte;
const char id = '1';
bool busy = false;

void setup(void) {
  tft.init(240, 240);               // Init ST7789 1.14" 135x240 TFT
  pinMode(2,INPUT_PULLUP); //green
  pinMode(3,INPUT_PULLUP); //blue
  pinMode(4,INPUT_PULLUP); //yellow
  pinMode(5,INPUT_PULLUP); //red
  pinMode(A0,INPUT_PULLUP); //x
  pinMode(A1,INPUT_PULLUP); //y 

  tft.setCursor(5, 5);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.println("Welcome");
  tft.println("to the");
  tft.println("Cockpit");
  delay(3000);
  Serial.begin(9600);
}

// For library documentation, visit:
// https://learn.adafruit.com/adafruit-gfx-graphics-library

void payAttention(){
  //pay attention to the serial and respond if needed
  if (Serial.available() > 0) {
    //Serial.println("Starting...");
    incomingByte = Serial.readString(); //this includes the newline (which is \r\n)
    char* output = incomingByte.c_str();
    Serial.print(output);
    char first = output[0];
    
    if (first != id){
      Serial.println("this command was not for me");
      return;
    } 
    
    tft.println(output + 1);
    busy = true;
    tft.fillScreen(ST77XX_YELLOW);
    tft.setTextColor(ST77XX_BLACK);
    tft.setTextSize(3);
    tft.setCursor(5, 5);
  }
}
void raiseHand(){
  //tell the master that you need a new command
  Serial.println("C1");
}
void failure(){
  //tell the master that the command timed out
  //success is determined by the master, failure is determined by the console
  Serial.println("FAIL");
  tft.fillScreen(ST77XX_YELLOW);
  tft.setTextColor(ST77XX_BLACK);
  tft.setTextSize(3);
  tft.setCursor(5, 5);
  tft.println("MISSED");
  delay(2000);
}
void checkControls(){
  //go through all controls and report to master what is pressed
}
void loop() {
  payAttention();
  if(not busy){
    raiseHand();
  }
  checkControls();
}
