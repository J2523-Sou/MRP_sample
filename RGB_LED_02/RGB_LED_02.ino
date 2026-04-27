#include <Adafruit_NeoPixel.h>
#define LED_PIN 48            //  LEDのピン
#define SW_01 4
#define SW_02 5
#define SW_03 6



Adafruit_NeoPixel pixels(1, LED_PIN, NEO_GRB + NEO_KHZ800);     //  LED初期設定
int RGB[3] = { 0, 0, 0 };     //左からRed,Green,Blue
int wait = 0.2;

void display(int R,int G,int B) {      
  //  色を指定して点灯させる
  pixels.setPixelColor(0, pixels.Color(R, G, B));
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
  display();
  pinMode(SW_01, INPUT_PULLUP);
  pinMode(SW_02, INPUT_PULLUP);
  pinMode(SW_03, INPUT_PULLUP);
}

void loop() {
  display(255, 0, 0);

}
