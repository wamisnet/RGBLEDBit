#include <Adafruit_NeoPixel.h>

// RGBLEDに出力するピン番号
#define RGBLED_OUTPIN    1

int RGBlednum = 60;


Adafruit_NeoPixel RGBLED = Adafruit_NeoPixel(RGBlednum, RGBLED_OUTPIN, NEO_GRB);
int getMaster(int max) {
  int val = analogRead(A3) / 10;
  return map(val, 0, 102, 0, max);
}
int getSub(int max) {
  int val = analogRead(A2) / 10;
  return map(val, 0, 102, 0, max);
}

void setup()
{
  //  Serial.begin(115200);
  //  Serial.println("RGBbits");
  RGBLED.begin() ;                   // RGBLEDのライブラリを初期化する
  pinMode(0, INPUT_PULLUP);
}
void ColorSelect() {
  //色がどんどん変わっていく
  //Serial.println("ColorSelect");
  int mas = getMaster(1023);
  int sub = getSub(50);
  if (sub < 10)sub = 20;
  RGBLED.setBrightness(sub);
  byte r = mas, g = mas >> 1, b = mas >> 2;

  for (int i = 0; i < RGBlednum; i++) {
    RGBLED.setPixelColor(i, r, g, b) ;
  }
  RGBLED.show();
  delay(50);
}
void Equalizer() {
  //  Serial.println("Equalizer");
  //一定以上になると赤色が光る
  int mas = getMaster(RGBlednum);
  int sub = getSub(50);
  if (sub < 10)sub = 20;
  RGBLED.setBrightness(sub);
  for (int i = 0; i < RGBlednum; i++) {
    if (i < mas) {
      RGBLED.setPixelColor(i, 0, 150, 50) ;
      if ((RGBlednum - RGBlednum / 5) <= i)RGBLED.setPixelColor(i, 150, 50, 0) ;
    } else {
      RGBLED.setPixelColor(i, 0, 0, 0) ;
    }
  }
  RGBLED.show();
  delay(50);
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
  // Serial.println("ColorWave");
  for (int i = 0; i < 4; i++) {
    //   Serial.print(colorWavePos[i]);
    //   Serial.print(":");
  }
}
void Rainbow() {
  //色がどんどん変わっていく
  //Serial.println("Rainbow");
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
  // Serial.println("RainbowCycle");
  int mas = getMaster(100);
  int sub = getSub(100);
  if (sub < 10)sub = 50;
  RGBLED.setBrightness(sub);
  for (int i = 0; i < RGBlednum; i++) {
    ColorWave();
    RGBLED.setPixelColor(i, colorWavePos[1] * 10, colorWavePos[2] * 10, colorWavePos[3] * 10);
  }
  RGBLED.show();
  delay(50 + mas);
}

void Nightrider() {
  //光る場所がアナログ値によって変わる
  //Serial.println("Nightrider");
  int mas = getMaster(RGBlednum - 1);
  int sub = getSub(1023);
  if (sub < 10)sub = 1023;
  byte r = sub, g = sub >> 1, b = sub >> 2;
  for (int i = 0; i < RGBlednum; i++) {
    RGBLED.setPixelColor(i, 0, 0, 0);
  }
  RGBLED.setBrightness(30);
  RGBLED.setPixelColor(mas, r, g, b);

  RGBLED.show();
  delay(10);
}
int ligCount = 0;
bool HorL = LOW;
void Counter() {
  //Serial.println("Counter");
  //カウントアップしていく
  int mas = getMaster(100);
  int sub = getSub(1023);
  if (sub < 50)sub = 1023;
  byte r = sub, g = sub >> 1, b = sub >> 2;
  if (mas > 50) {
    if (HorL == LOW) {
      HorL = HIGH;
      for (int i = 0; i < RGBlednum; i++) {
        RGBLED.setPixelColor(i, 0, 0, 0) ;
      }
      if (ligCount >= RGBlednum) {
        ligCount = 0;
      }
      RGBLED.setBrightness(30);
      RGBLED.setPixelColor(ligCount, r, g, b);
      ligCount++;
    }
  } else {
    HorL = LOW;
  }
  RGBLED.show();
  delay(50);
}
void CounterExtended() {
  // Serial.println("CounterExtended");
  //カウントアップしていく+消えない
  int mas = getMaster(100);
  int sub = getSub(1023);
  if (sub < 50)sub =1023;
  byte r = sub, g = sub >> 1, b = sub >> 2;
  if (mas > 50) {
    if (HorL == LOW) {
      HorL = HIGH;
      if (ligCount >= RGBlednum) {
        for (int i = 0; i < RGBlednum; i++) {
          RGBLED.setPixelColor(i, 0, 0, 0) ;
        }
        ligCount = 0;
      }
      RGBLED.setBrightness(30);
      RGBLED.setPixelColor(ligCount, r, g, b);
      ligCount++;
    }
  } else {
    HorL = LOW;
  }
  RGBLED.show();
  delay(50);
}

bool onoff = true;
void Theater() {
  //色がどんどん変わっていく
  //  Serial.println("Theater");
  int mas = getMaster(100);
  int sub = getSub(1023);
  if (sub < 50)sub = 1023;
  byte r = sub, g = sub >> 1, b = sub >> 2;
  RGBLED.setBrightness(30);
  for (int i = 0; i < RGBlednum; i += 2) {
    if (onoff) {
      RGBLED.setPixelColor(i, 0, 0, 0) ;
      RGBLED.setPixelColor(i + 1, r, g, b) ;
    } else {
      RGBLED.setPixelColor(i, r, g, b) ;
      RGBLED.setPixelColor(i + 1, 0, 0, 0) ;
    }
  }
  onoff = !onoff;
  RGBLED.show();
  delay(10 * mas);
}

void WhiteColor() {
  //白色点灯
  //  Serial.println("WhiteColor");
  int mas = getMaster(50);
  int sub = getSub(RGBlednum);
  if (sub < 1)sub = RGBlednum;
  RGBLED.setBrightness(mas);
  for (int i = 0; i < RGBlednum; i++) {
    if (i < sub) {
      RGBLED.setPixelColor(i, 255, 255, 255) ;
    } else {
      RGBLED.setPixelColor(i, 0, 0, 0) ;
    }
  }
  RGBLED.show();
  delay(50);
}

int modechange = 0;
bool pushSW() {
  if (digitalRead(0) == LOW) {
    delay(500);
    return true;
  }
  return false;
}
void loop()
{
  switch (modechange) {
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
      WhiteColor();
      break;
  }

if(pushSW())modechange++;
  if (modechange >8) {
    modechange = 0;
  }
  delay(10);
}
