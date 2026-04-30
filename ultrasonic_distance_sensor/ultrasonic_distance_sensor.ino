/*
 * 超音波距離センサ（HC-SR04）サンプルプログラム
 * 対象ボード: Arduino UNO R4 WiFi
 * 
 * このプログラムは、超音波センサを使用して対象物までの距離を測定し、
 * シリアルモニタに結果を表示します。
 * 
 * 接続例:
 * VCC -> 5V
 * Trig -> 9番ピン
 * Echo -> 10番ピン
 * GND -> GND
 */

// ピン番号の定義（snake_caseを使用）
const int trig_pin = 9;  // 超音波を発信するピン
const int echo_pin = 10; // 跳ね返ってきた超音波を受信するピン

// 距離計算用の変数
float duration = 0; // 受信までの時間（マイクロ秒）
float distance = 0; // 計算された距離（センチメートル）

void setup() {
  // シリアル通信の開始（PCとの通信）
  Serial.begin(9600);

  // ピンモードの設定
  pinMode(trig_pin, OUTPUT); // Trigは出力
  pinMode(echo_pin, INPUT);  // Echoは入力

  // 初期のTrigピンをLOWにしておく
  digitalWrite(trig_pin, LOW);
  
  Serial.println("超音波距離センサ 測定開始");
}

void loop() {
  // 超音波を発生させるためのトリガーパルス送信
  // 1. Trigを一度LOWにする
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  
  // 2. TrigをHIGHにして10マイクロ秒待機（超音波の発射指示）
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  
  // 3. TrigをLOWに戻す
  digitalWrite(trig_pin, LOW);

  // EchoピンがHIGHになっている時間を測定（音速に基づいた往復時間）
  duration = pulseIn(echo_pin, HIGH);

  if (duration > 0) {
    // 距離を計算（音速 340m/s = 0.034cm/us を使用）
    // 往復の時間なので2で割る
    distance = (duration * 0.034) / 2;

    // 測定結果をシリアルモニタに表示
    Serial.print("距離: ");
    Serial.print(distance);
    Serial.println(" cm");
  } else {
    // 測定不能な場合
    Serial.println("測定範囲外、またはエラーです");
  }

  // 読み取りやすくするために少し待機（高頻度の測定による干渉を防ぐ）
  delay(500);
}
