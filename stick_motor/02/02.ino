/*
  D2626 永瀬大地
  DCモーター（MRPドライバ使用） - Arduino版
*/

#define PWM_01 10           // 9番ピン（PWM対応）
#define PWM_02 9          // 10番ピン（PWM対応）
#define resistor_pin_01 A0 // 可変抵抗を接続したピン
#define resistor_pin_02 A1 // 可変抵抗を接続したピン

int wait = 25;
int maxSpeed = 240; // 0-255の範囲で指定
int speed = 0;
int speed_up = 5;
float current_speed = 0.0;

void setup() {
  Serial.begin(9600);
  pinMode(PWM_01, OUTPUT);
  pinMode(PWM_02, OUTPUT);
  analogReadResolution(12); // 必要なら12ビット（0-4095）に変更可能
}

void loop() {
  int val_01 = analogRead(A0);
  int target_speed = 0; // 目標となるスピード

  // 1. スティックの倒し具合から目標スピードを計算
  if (val_01 > 1600) { 
    // 前に倒したとき（1600〜2800を、0〜maxSpeedに変換）
    target_speed = map(val_01, 1600, 2800, 0, maxSpeed);
  } else if (val_01 < 1200) { 
    // 後ろに倒したとき（1200〜30を、0〜-maxSpeedに変換）
    target_speed = map(val_01, 1200, 30, 0, -maxSpeed);
  } else {
    // スティックが真ん中付近のときは停止
    target_speed = 0;
  }

  // 2. 現在のスピードを目標スピードに少しずつ近づける
  if (speed < target_speed) {
    speed += speed_up; // 加速
    if (speed > target_speed) speed = target_speed; // 行き過ぎ防止
  } else if (speed > target_speed) {
    speed -= speed_up; // 減速
    if (speed < target_speed) speed = target_speed; // 行き過ぎ防止
  }

  // --- これ以降のモーター出力（正転・逆転・停止）は元のコードと同じ ---
  if (speed > 0) {
    analogWrite(PWM_01, speed);
    analogWrite(PWM_02, 0);
  } else if (speed < 0) {
    analogWrite(PWM_01, 0);
    analogWrite(PWM_02, -speed);
  } else {
    analogWrite(PWM_01, 0);
    analogWrite(PWM_02, 0);
  }

  delay(5);


  Serial.print("speed:");
  Serial.print(speed);
  Serial.print(", ");
  Serial.print("val_01:");
  Serial.println(val_01);
}