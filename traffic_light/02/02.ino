/*
歩行者用信号
*/

#define LED_red 4  // 4番ピンをLEDに接続　赤

#define LED_green 6  // 6番ピンをLEDに接続　青

void setup() {

  Serial.begin(9600);

  pinMode(LED_red, OUTPUT);

  pinMode(LED_green, OUTPUT);
}

void loop() {
  digitalWrite(LED_red, HIGH);
  delay(2000);
  digitalWrite(LED_red, LOW);
  digitalWrite(LED_green, HIGH);
  delay(2000);
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_green, LOW);
    delay(280);
    digitalWrite(LED_green, HIGH);
    delay(280);
  }
  digitalWrite(LED_green, LOW);
  delay(50);
}
