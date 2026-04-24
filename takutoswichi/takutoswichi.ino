/*
スイッチを押したらLEDがつくプログラム
熊谷航一
*/

// 1. ピン番号の名前決め
#define LED_01 2
#define SWITCH 18

void setup() {
  pinMode(LED_01, OUTPUT);        // LED：電気を出す設定
  pinMode(SWITCH, INPUT_PULLUP);  // スイッチ：電気を読む設定
}

void loop() {
  // 2. もしスイッチが押されたら（LOWになったら）
  if(digitalRead(SWITCH) == LOW){
    digitalWrite(LED_01, HIGH);   // LEDをつける
  }
  // 3. そうじゃない時（離している時）
  else{
    digitalWrite(LED_01, LOW);    // LEDを消す
  }
}