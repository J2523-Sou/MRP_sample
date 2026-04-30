/*
  D2626 永瀬大地
  DCモーター（MRPドライバ使用） - Arduino版
*/

#define motor01_01 10           // 9番ピン（PWM対応）
#define motor01_02 9            // 10番ピン（PWM対応）
#define motor02_01 5            // 9番ピン（PWM対応）
#define motor02_02 6            // 10番ピン（PWM対応）
#define resistor_pin_01 A0      // 可変抵抗を接続したピン
#define resistor_pin_02 A1      // 可変抵抗を接続したピン

int wait = 25;
int maxSpeed = 255;  // 0-255の範囲で指定
int speed = 0;
int speed_up = 5;
float current_speed = 0.0;

void setup() {
  Serial.begin(9600);
  pinMode(motor01_01, OUTPUT);
  pinMode(motor01_02, OUTPUT);
  analogReadResolution(12);  // 必要なら12ビット（0-4095）に変更可能
}

void loop() {
  int val_01 = analogRead(A0);
  int target_speed = 0;

  if (val_01 > 1600) {
    target_speed = map(val_01, 1600, 2800, 0, maxSpeed);
  } else if (val_01 < 1200) {
    target_speed = map(val_01, 1200, 30, 0, -maxSpeed);
  }

  // 目標スピードとの差の「5%」だけスピードを変化させる
  // ※ 0.05 を 0.01 にすると氷の上のようにツルツル滑り、0.1 にすると機敏に動きます。
  speed = speed + (target_speed - speed) * 0.05;

  if (speed > 0) {
    analogWrite(motor01_01, speed);
    analogWrite(motor01_02, 0);
  } else if (speed < 0) {
    analogWrite(motor01_01, 0);
    analogWrite(motor01_02, -speed);
  } else {
    analogWrite(motor01_01, 0);
    analogWrite(motor01_02, 0);
  }
  delay(5);


  Serial.print("speed:");
  Serial.print(speed);
  Serial.print(", ");
  Serial.print("val_01:");
  Serial.println(val_01);
}