/*
  D2626 永瀬大地
  可変抵抗 - Arduino版
*/

#define pin_01 A0  // 可変抵抗を接続したピン
#define pin_02 A1  // 可変抵抗を接続したピン

void setup() {
  Serial.begin(9600);      // シリアル通信の開始
  analogReadResolution(12);  // 必要なら12ビット（0-4095）に変更可能
}

void loop() {
  int val_01 = analogRead(A0);  // 電圧を読み取る（0〜1023）
  int val_02 = analogRead(A1);  // 電圧を読み取る（0〜1023）
  Serial.print(val_01);         // 値を表示
  Serial.print(",");            // 値を表示
  Serial.println(val_02);       // 値を表示
  delay(100);                   // 少し待つ
}