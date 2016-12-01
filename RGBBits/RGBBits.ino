#include <Adafruit_NeoPixel.h>

// RGBLEDに出力するピン番号
#define RGBLED_OUTPIN    1
// Arduinoにぶら下がっているRGBLEDの個数
#define NUMRGBLED        30

// RGBLEDのライブラリを生成する(色指定はRGBの並びで行う、LEDの速度は800KHzとする)
Adafruit_NeoPixel RGBLED = Adafruit_NeoPixel(NUMRGBLED, RGBLED_OUTPIN,NEO_GRB);

void setup()
{

     RGBLED.begin() ;                   // RGBLEDのライブラリを初期化する
     RGBLED.setBrightness(50) ;         // 明るさの指定(0-255)を行う
     RGBLED.setPixelColor(0, 0,150,0) ; // 適度に明るい緑の色。(R=0,G=150,B=0)
     RGBLED.show() ;                    // LEDにデータを送り出す
}
void loop()
{
  int val = analogRead(A3);
  int val2 = analogRead(A2);

for (int i=0;i<30;i++)
  RGBLED.setPixelColor(i,0,0,0) ; // 適度に明るい緑の色。(R=0,G=150,B=0)
for (int i=0;i<map(val, 0, 1023, 0, 30);i++){
RGBLED.setBrightness(50) ;         // 明るさの指定(0-255)を行う
     RGBLED.setPixelColor(i, map(val2, 0, 1023, 0, 255),map(val2, 0, 1023, 0, 255),0) ; // 適度に明るい緑の色。(R=0,G=150,B=0)
  
}
RGBLED.show() ;                    // LEDにデータを送り出す
delay(10);
}
