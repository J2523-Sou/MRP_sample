#include <Adafruit_NeoPixel.h>
#define LED_PIN 48
Adafruit_NeoPixel pixels(1, LED_PIN, NEO_GRB + NEO_KHZ800);
int RGB[3] = { 0, 0, 0 };
int wait = 2;

void display() {
  pixels.setPixelColor(0, pixels.Color(RGB[0], RGB[1], RGB[2]));
  Serial.print("R:");
  Serial.print(RGB[0]);
  Serial.print(" G:");
  Serial.print(RGB[1]);
  Serial.print(" B:");
  Serial.println(RGB[2]);
  pixels.show();
}

void setup() {
  Serial.begin(9600);
  pixels.begin();
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
    RGB[0]++;
    RGB[2]--;//
    display();
    delay(wait);
  }

  for (int i = 0; i < 255; i++) {
    RGB[1]++;
    RGB[0]--;//
    display();
    delay(wait);
  }

  for (int i = 0; i < 255; i++) {
    RGB[2]++;
    RGB[1]--;//
    display();
    delay(wait);
  }
}
