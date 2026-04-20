/*

  D2626 永瀬大地
  フォトインタラプタ（ESP32・CNZ1023使用）サンプルコード


*/

#define sensorPin 14;

void setup() {
  // パソコンに結果を表示するための準備（通信速度：115200）
  Serial.begin(115200);

  // センサーのピンを「信号を読み取る（入力）」モードに設定
  pinMode(sensorPin, INPUT);
}

void loop() {
  // センサーの現在の状態を読み取る（HIGH または LOW）
  int sensorValue = digitalRead(sensorPin);

  // センサーの間に物があるかどうかの判定
  if (sensorValue == LOW) {
    // 物が光を遮っているとき
    Serial.println("遮断されています！");
  } else {
    // 光がそのまま通っているとき
    Serial.println("光が通っています。");
  }

  delay(50);
}