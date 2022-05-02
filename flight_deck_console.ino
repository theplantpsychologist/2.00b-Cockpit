
#include <Adafruit_GFX.h>           // Core graphics library
#include <Adafruit_ST7789.h>        // Hardware-specific library for ST7789
#include <Fonts/FreeSans9pt7b.h>    // for sans-serif font
#include <Adafruit_SPIFlash.h>      // SPI / QSPI flash library

#define TFT_CS        10
#define TFT_RST        9 
#define TFT_DC         8

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

//String incomingByte;

void setup(void) {
  tft.init(240, 240);               // Init ST7789 1.14" 135x240 TFT
  pinMode(2,INPUT_PULLUP); //blue
  pinMode(3,INPUT_PULLUP); //red
//  pinMode(4,INPUT_PULLUP); //yellow
//  pinMode(5,INPUT_PULLUP); //red
  pinMode(A0,INPUT_PULLUP); //x
  pinMode(A1,INPUT_PULLUP); //y 

  pinMode(A4,OUTPUT); //failure
  pinMode(A5,OUTPUT); //success

  tft.setCursor(5, 5);
  tft.fillScreen(ST77XX_BLACK);
//  delay(500);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.println("Welcome");
  tft.println("to the");
  tft.println("Flight Deck");
  delay(3000);
  Serial.begin(9600);
}

// For library documentation, visit:
// https://learn.adafruit.com/adafruit-gfx-graphics-library
void success(){
  digitalWrite(A4,HIGH);
  delay(10);
  digitalWrite(A4,LOW);
}
void failure(){
  digitalWrite(A5,HIGH);
  delay(10);
  digitalWrite(A5,LOW);
}

void button(){
  int n = random(2,4); 
  const char *colors[2] = {"BLUE!","RED!"};
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
void joystick(){
  int n = random(0,4); //0 right 1 up 2 left 3 down
  const char *directions[4] = {"RIGHT!","UP!","LEFT!","DOWN!"};
  tft.setCursor(5, 5);
  tft.fillScreen(ST77XX_YELLOW);
  tft.setTextColor(ST77XX_BLACK);
  tft.println("Joystick");
  //tft.println("to the");
  tft.println(directions[n]);
  float t = 0;
  while(t<1000){
    if( (n==0 && analogRead(A1)>800)||
        (n==1 && analogRead(A0)>800)||
        (n==2 && analogRead(A1)<200)||
        (n==3 && analogRead(A0)<200)
      ){
      tft.fillScreen(ST77XX_GREEN);
      tft.setTextColor(ST77XX_BLACK);
      tft.println("SAFE!");
      success();
      delay(2000);
      return;
    }
    t+= 0.01;
  }
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_RED);
  tft.println("missed");
  failure();
  delay(2000);
  return;
}

void loop() {
  int n = random(0,2);
  if(n==0){
    button();
  } else{
    joystick();
  }  
}
