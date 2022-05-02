
#include <Adafruit_GFX.h>           // Core graphics library
#include <Adafruit_ST7789.h>        // Hardware-specific library for ST7789
#include <Fonts/FreeSans9pt7b.h>    // for sans-serif font
#include <Adafruit_SPIFlash.h>      // SPI / QSPI flash library

#define TFT_CS        10
#define TFT_RST        9 
#define TFT_DC         8

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

String incomingByte;

void setup(void) {
  tft.init(240, 240);               // Init ST7789 1.14" 135x240 TFT
  pinMode(2,INPUT_PULLUP); //yellow
  pinMode(3,INPUT_PULLUP); //green
  pinMode(4,INPUT_PULLUP); //white
  pinMode(5,INPUT_PULLUP); //black
  pinMode(6,INPUT_PULLUP); //grey
  pinMode(A4,OUTPUT);
  pinMode(A5,OUTPUT);

  tft.setCursor(5, 5);
  tft.fillScreen(ST77XX_BLACK);
//  delay(500);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.println("Welcome");
  tft.println("to the");
  tft.println("Flight deck");
  delay(3000);
  Serial.begin(9600);
}

void success(){
  digitalWrite(A5,HIGH);
  delay(10);
  digitalWrite(A5,LOW);
}
void failure(){
  digitalWrite(A4,HIGH);
  delay(10);
  digitalWrite(A4,LOW);
}
// For library documentation, visit:
// https://learn.adafruit.com/adafruit-gfx-graphics-library
void button(){
  int n = random(2,7); //2 green 3 blue 4 yellow 5 red
  const char *colors[5] = {"YELLOW!","GREEN!","WHITE!","BLACK!","GREY!"};
  tft.setCursor(5, 5);
  tft.fillScreen(ST77XX_YELLOW);
  tft.setTextColor(ST77XX_BLACK);
  tft.println("Activate");
  tft.println(colors[n-2]);
  float t = 0;
  while(t<4000){
    if(digitalRead(n)!=HIGH){
      tft.fillScreen(ST77XX_GREEN);
      tft.setTextColor(ST77XX_BLACK);
      tft.println("SAFE!");
      success();
      delay(2000);
      return;
    }
    t+=0.01;
  }
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_RED);
  tft.println("missed");
  failure();
  delay(2000);
  return;
}

void loop() {
  button();
}
