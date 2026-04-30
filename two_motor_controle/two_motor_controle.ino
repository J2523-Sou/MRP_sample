/*
  D2626 永瀬大地
  DCモーター（MRPドライバ使用） - Arduino版
*/

#define motor01_01 9  // 1つ目のモーターを9番ピンに接続
#define motor01_02 10 // 1つ目のモーターを10番ピンに接続
#define motor02_01 5  // 2つ目のモーターを5番ピンに接続
#define motor02_02 6  // 2つ目のモーターを6番ピンに接続

#define resistor_pin_01 A0 // 可変抵抗を接続したピン
#define resistor_pin_02 A1 // 可変抵抗を接続したピン
int wait = 25;
int maxSpeed = 240; // 0-255の範囲で指定
int speed = 230;
int speed_up = 5;

void setup() {
  Serial.begin(9600);
  pinMode(motor01_01, OUTPUT);
  pinMode(motor01_02, OUTPUT);
  analogReadResolution(12); // 必要なら12ビット（0-4095）に変更可能
}

void loop() {
  int val_01 = analogRead(A0); // 電圧を読み取る（0〜1023）
  int val_02 = analogRead(A1); // 電圧を読み取る（0〜1023）

  if (val_01 > 2700) { //  前に倒されている
    go();
  } else if (val_01 < 50) { //  後ろに倒されている
    back();
  } else if (val_02 > 2700) {
    turn_left();
  } else if (val_02 < 50) {
    turn_right();
  } else {
    stop();
  }

  Serial.print("speed:");
  Serial.print(speed);
  Serial.print(", ");
  Serial.print("val_01:");
  Serial.println(val_01);
  delay(5);
}

void go() {
  analogWrite(motor01_01, speed);
  analogWrite(motor01_02, 0);
  analogWrite(motor02_01, speed);
  analogWrite(motor02_02, 0);
}

void back() {
  analogWrite(motor01_01, 0);
  analogWrite(motor01_02, speed);
  analogWrite(motor02_01, 0);
  analogWrite(motor02_02, speed);
}

void turn_left() {
  analogWrite(motor01_01, speed);
  analogWrite(motor01_02, 0);
  analogWrite(motor02_01, 0);
  analogWrite(motor02_02, speed);
}

void turn_right() {
  analogWrite(motor01_01, 0);
  analogWrite(motor01_02, speed);
  analogWrite(motor02_01, speed);
  analogWrite(motor02_02, 0);
}

void stop() {
  analogWrite(motor01_01, 0);
  analogWrite(motor01_02, 0);
  analogWrite(motor02_01, 0);
  analogWrite(motor02_02, 0);
}