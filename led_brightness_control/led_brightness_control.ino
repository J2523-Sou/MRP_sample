#define pin_01 32
#define pin_02 33

#define LED_01 18
#define LED_02 19


void setup() {
  ledcAttach(LED_01, 5000, 8);
  ledcAttach(LED_02, 5000, 8);


  Serial.begin(9600);       // シリアル通信の開始
  analogReadResolution(8);  // 8bitに変更（maxが255になる）
}


void loop() {
  int val_01 = analogRead(pin_01);  // 電圧を読み取る
  int val_02 = analogRead(pin_02);  // 電圧を読み取る

  ledcWrite(LED_01, val_01);  //LEDの値に読み取った値を書き込む
  ledcWrite(LED_02, val_02);  //LEDの値に読み取った値を書き込む


  Serial.print(val_01);    // 値を表示
  Serial.print(",");       // 値を表示
  Serial.println(val_02);  // 値を表示
  delay(10);               // 少し待つ
}
