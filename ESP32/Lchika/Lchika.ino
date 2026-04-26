/*

  D2626 永瀬大地
  スイッチを押すとLEDが点灯するプログラム

*/

#define LED_01 4  // 4番ピンをLEDに接続
#define SWITCH 2  // 2番ピンをSWITCHに接続

void setup() {

  Serial.begin(9600);
  pinMode(SWITCH, INPUT_PULLUP);
  pinMode(LED_01, OUTPUT);
}

void loop() {
  if (digitalRead(SWITCH) == LOW) {
    Serial.println("Switch is pressed");
  digitalWrite(LED_01, HIGH);

  } else {
    Serial.println("Switch is not pressed");
    digitalWrite(LED_01, LOW);
  }
  delay(50);
}
