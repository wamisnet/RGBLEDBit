#include <Adafruit_NeoPixel.h>

// RGBLEDに出力するピン番号
#define RGBLED_OUTPIN    1
// Arduinoにぶら下がっているRGBLEDの個数
#define NUMRGBLED        30
int RGBlednum = 30;
// RGBLEDのライブラリを生成する(色指定はRGBの並びで行う、LEDの速度は800KHzとする)
Adafruit_NeoPixel RGBLED = Adafruit_NeoPixel(RGBlednum, RGBLED_OUTPIN, NEO_GRB);
int getMaster(int max) {
  int val = analogRead(A3) / 10;
  return map(val, 0, 100, 0, max);
}
int getSub(int max) {
  int val = analogRead(A2) / 10;
  return map(val, 0, 100, 0, max);
}
void setup()
{
  Serial.begin(115200);
  Serial.println("RGBbits");
  RGBLED.begin() ;                   // RGBLEDのライブラリを初期化する
  RGBLED.setBrightness(50) ;         // 明るさの指定(0-255)を行う
  RGBLED.setPixelColor(0, 0, 150, 0) ; // 適度に明るい緑の色。(R=0,G=150,B=0)
  RGBLED.show() ;                    // LEDにデータを送り出す
}
void ColorSelect() {
  //色がどんどん変わっていく
  Serial.println("ColorSelect");
  int mas = getMaster(255);
  int sub = getSub(100);
  if (sub < 10)sub = 50;
  for (int i = 0; i < RGBlednum; i++) {
    RGBLED.setBrightness(sub);
    RGBLED.setPixelColor(i, mas, mas, mas) ;
  }
  RGBLED.show();
}
void Equalizer() {
  Serial.println("Equalizer");
  //一定以上になると赤色が光る
  int mas = getMaster(RGBlednum);
  int sub = getSub(100);
  if (sub < 10)sub = 50;
  for (int i = 0; i < RGBlednum; i++) {
    RGBLED.setBrightness(sub);
    RGBLED.setPixelColor(i, 0, 150, 50) ;
    if ((RGBlednum - RGBlednum / 6) < i)RGBLED.setPixelColor(i, 150, 50, 0) ;
  }
  RGBLED.show();
}
int colorWavePos[4] = {0, 0, 0, 12};
void ColorWave() {
  if (colorWavePos[0] < 12) {
    colorWavePos[3]--;
    colorWavePos[1]++;
  } else if (colorWavePos[0] < 24) {
    colorWavePos[1]--;
    colorWavePos[2]++;
  } else if (colorWavePos[0] < 36) {
    colorWavePos[2]--;
    colorWavePos[3]++;
  }

  for (int i = 1; i < 4; i++) {
    if (colorWavePos[i] < 0)colorWavePos[i] = 0;
  }
  colorWavePos[0]++;
  if (colorWavePos[0] > 36) {
    colorWavePos[0] = 0;
  }
  Serial.println("ColorWave");
  for (int i = 0; i < 4; i++) {
    Serial.print(colorWavePos[i]);
    Serial.print(":");
  }
}
void Rainbow() {
  //色がどんどん変わっていく
  Serial.println("Rainbow");
  ColorWave();
  int mas = getMaster(100);
  int sub = getSub(100);
  if (sub < 10)sub = 50;
  for (int i = 0; i < RGBlednum; i++) {
    RGBLED.setBrightness(sub);
    RGBLED.setPixelColor(i, colorWavePos[1] * 10, colorWavePos[2] * 10, colorWavePos[3] * 10);
  }
  RGBLED.show();
  delay(mas);
}
void RainbowCycle() {
  //色がどんどん変わっていく
  Serial.println("RainbowCycle");
  int mas = getMaster(100);
  int sub = getSub(100);
  if (sub < 10)sub = 50;
  for (int i = 0; i < RGBlednum; i++) {
    ColorWave();
    RGBLED.setBrightness(sub);
    RGBLED.setPixelColor(i, colorWavePos[1] * 10, colorWavePos[2] * 10, colorWavePos[3] * 10);
  }
  RGBLED.show();
  delay(mas);
}

void Nightrider() {
  //光る場所がアナログ値によって変わる
  Serial.println("Nightrider");
  int mas = getMaster(RGBlednum);
  int sub = getSub(255);
  if (sub < 10)sub = 50;
  for (int i = 0; i < RGBlednum; i++) {
    RGBLED.setBrightness(0);
    RGBLED.setPixelColor(i, 0, 0, 0);
  }
  RGBLED.setBrightness(50);
  RGBLED.setPixelColor(mas, sub, sub, sub);

  RGBLED.show();
  delay(10);
}
int ligCount = 0;
void Counter() {
  Serial.println("Counter");
  //カウントアップしていく
  int mas = getMaster(100);
  int sub = getSub(250);
  if (sub < 10)sub = 50;
  if (mas > 50) {
    for (int i = 0; i < RGBlednum; i++) {
      RGBLED.setBrightness(0);
      RGBLED.setPixelColor(i, 0, 0, 0) ;
    }
    if (ligCount > RGBlednum) {
      ligCount = 0;
    }
    RGBLED.setBrightness(50);
    RGBLED.setPixelColor(ligCount, sub, sub, sub);
    ligCount++;
  }
  RGBLED.show();
}
void CounterExtended() {
  Serial.println("CounterExtended");
  //カウントアップしていく+消えない
  int mas = getMaster(100);
  int sub = getSub(250);
  if (sub < 10)sub = 50;
  if (mas > 50) {

    if (ligCount > RGBlednum) {
      for (int i = 0; i < RGBlednum; i++) {
        RGBLED.setBrightness(0);
        RGBLED.setPixelColor(i, 0, 0, 0) ;
      }
      ligCount = 0;
    }
    RGBLED.setBrightness(50);
    RGBLED.setPixelColor(ligCount, sub, sub, sub);
    ligCount++;
  }
  RGBLED.show();
}

void loop()
{


  delay(10);
}
