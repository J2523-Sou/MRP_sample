#define PWM_01 10           // 9番ピン（PWM対応）
#define PWM_02 9            // 10番ピン（PWM対応）
#define resistor_pin_01 A0  // 可変抵抗を接続したピン
#define resistor_pin_02 A1  // 可変抵抗を接続したピン

int wait = 25;
int maxSpeed = 240;  // 0-255の範囲で指定
int speed = 0;
int speed_up = 5;

void setup() {
  Serial.begin(9600);
  pinMode(PWM_01, OUTPUT);
  pinMode(PWM_02, OUTPUT);
  analogReadResolution(12);  // 必要なら12ビット（0-4095）に変更可能
}

void loop() {
  int sensor_val;
  sensor_val = analogRead(A1);


  if (sensor_val < 200) {
    analogWrite(PWM_02, 100);
    analogWrite(PWM_01, 0);

  } else if (sensor_val > 1800) {
    analogWrite(PWM_02, 0);
    analogWrite(PWM_01, 100);
    
  } else {
    analogWrite(PWM_02, 0);
    analogWrite(PWM_01, 0);
  }

  Serial.print("sensor_val:");
  Serial.println(sensor_val);

  delay(5);
}