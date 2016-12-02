#include <Adafruit_NeoPixel.h>

// RGBLEDに出力するピン番号
#define RGBLED_OUTPIN    1

int RGBlednum = 30;
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
  RGBLED.setBrightness(sub);
  for (int i = 0; i < RGBlednum; i++) {
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
  RGBLED.setBrightness(sub);
  for (int i = 0; i < RGBlednum; i++) {
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
  RGBLED.setBrightness(sub);
  for (int i = 0; i < RGBlednum; i++) {
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
  RGBLED.setBrightness(sub);
  for (int i = 0; i < RGBlednum; i++) {
    ColorWave();
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

bool onoff = true;
void Theater() {
  //色がどんどん変わっていく
  Serial.println("Theater");
  int mas = getMaster(100);
  int sub = getSub(255);
  if (sub < 10)sub = 50;
  RGBLED.setBrightness(50);
  for (int i = 0; i < RGBlednum / 2; i++) {
    if (onoff) {
      RGBLED.setPixelColor(i, 0, 0, 0) ;
      RGBLED.setPixelColor(i + 1, sub, sub, sub) ;
    } else {
      RGBLED.setPixelColor(i, sub, sub, sub) ;
      RGBLED.setPixelColor(i + 1, 0, 0, 0) ;
    }
  }
  onoff = !onoff;
  RGBLED.show();
  delay(10 * mas);
}

void WhiteColor() {
  //白色点灯
  Serial.println("WhiteColor");
  int mas = getMaster(100);
  int sub = getSub(RGBlednum);
  if(sub<1)sub=RGBlednum;
  RGBLED.setBrightness(mas);
  for (int i = 0; i < sub; i++) {
    RGBLED.setPixelColor(i, 255, 255, 255) ;
  }
  RGBLED.show();
}

int modechange = 0;
void loop()
{
  switch (modechange/10) {
    case 0:
      ColorSelect();
      break;
    case 1:
      Rainbow();
      break;
    case 2:
      RainbowCycle();
      break;
    case 3:
      Nightrider();
      break;
    case 4:
      Counter();
      break;
    case 5:
      CounterExtended();
      break;
    case 6:
      Equalizer();
      break;
    case 7:
      Theater();
      break;
    case 8:
      Theater();
      break;
  }
modechange++;
if(modechange/10>8){
  modechange=0;
}
  delay(10);
}
