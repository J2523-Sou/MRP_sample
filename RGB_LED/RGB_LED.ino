#include <Adafruit_NeoPixel.h>
#define LED_PIN 48            //  LEDのピン
Adafruit_NeoPixel pixels(1, LED_PIN, NEO_GRB + NEO_KHZ800);     //  LED初期設定
int RGB[3] = { 0, 0, 0 };
int wait = 0.2;

void display() {      
  //  色を指定して点灯させる
  pixels.setPixelColor(0, pixels.Color(RGB[0], RGB[1], RGB[2]));
  pixels.show();

  //現在の色の状態を出力する
  Serial.print("R:");
  Serial.print(RGB[0]);
  Serial.print(" G:");
  Serial.print(RGB[1]);
  Serial.print(" B:");
  Serial.println(RGB[2]);
}

void setup() {
  Serial.begin(9600);
  pixels.begin();
  RGB[0] = 255;
  display();
}

void loop() {
  // display(255, 0, 0);
  // delay(200);
  // display(0, 255, 0);
  // delay(200);
  // display(0, 0, 255);
  // delay(200);


  for (int i = 0; i < 255; i++) {
    RGB[1]++;   //緑増やす
    RGB[0]--;   //赤減らす
    display();
    delay(wait);
  }

  for (int i = 0; i < 255; i++) {
    RGB[2]++;   //青増やす
    RGB[1]--;   //緑減らす
    display();
    delay(wait);
  }

    for (int i = 0; i < 255; i++) {
    RGB[0]++;   //赤増やす
    RGB[2]--;   //青減らす
    display();
    delay(wait);
  }
}
