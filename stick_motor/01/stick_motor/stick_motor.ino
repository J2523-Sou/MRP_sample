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

void setup() {
  Serial.begin(9600);
  pinMode(PWM_01, OUTPUT);
  pinMode(PWM_02, OUTPUT);
  analogReadResolution(12); // 必要なら12ビット（0-4095）に変更可能
}

void loop() {
  int val_01 = analogRead(A0); // 電圧を読み取る（0〜1023）
  int val_02 = analogRead(A1); // 電圧を読み取る（0〜1023）

  if (val_01 > 2700 && speed <= maxSpeed) { //  前に倒されている
    speed += speed_up;
  } else if (val_01 < 50 && speed >= -maxSpeed) { //  後ろに倒されている
    speed -= speed_up;
  } else {
    // スピードを0に近づける
    if (speed > 0) {
      speed -= 1;
    } else if (speed < 0) {
      speed += 1;
    }
  }

  if (speed > 0) {
    // 正転
    analogWrite(PWM_01, speed);
    analogWrite(PWM_02, 0);
  } else if (speed < 0) {
    // 逆転
    analogWrite(PWM_01, 0);
    analogWrite(PWM_02, -speed);
  } else {
    // 停止
    analogWrite(PWM_01, 0);
    analogWrite(PWM_02, 0);
  }

  Serial.print("speed:");
  Serial.print(speed);
  Serial.print(", ");
  Serial.print("val_01:");
  Serial.println(val_01);
  delay(5);
}