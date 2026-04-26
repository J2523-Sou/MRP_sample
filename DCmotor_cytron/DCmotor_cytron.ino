/*

  D2626
  DCモーター（サイトロン使用）o

*/

#define PWM 4   //4番ピンをPWMに接続
#define DIR 32  //32番ピンをDIRに接続
#define BTN 2   //2番ピンをBTNに接続
#define LED 16  //16番ピンをLEDに接続

int motor_speed = 0;

void setup() {
  Serial.begin(9600);
  ledcAttach(PWM, 5000, 8);
  pinMode(DIR, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
}

void loop() {
  //スイッチの状態を読み取る
  int buttonState = digitalRead(BTN);

  //ボタンが押されていて，スピードが最大未満のとき
  if (buttonState == 0 && motor_speed < 255) {
    motor_speed++;
  }

  //ボタンが押されていなくて，スピードが最小よりも大きいとき
  if (buttonState == 1 && motor_speed > 0) {
    motor_speed--;
  }

  delay(random(5, ));
  digitalWrite(LED, 1);
  Serial.println(buttonState);
}




/*

  //スイッチの状態を読み取る
  int buttonState = digitalRead(BTN);

  //ボタンが押されていて，スピードが最大未満のとき
  if (buttonState == 0 && motor_speed < 255) {
    motor_speed++;
  }

  //ボタンが押されていなくて，スピードが最小よりも大きいとき
  if (buttonState == 1 && motor_speed > 0) {
    motor_speed--;
  }

  ledcWrite(PWM, motor_speed);
  digitalWrite(DIR, 0);
  delay(10);
  Serial.println(buttonState);
  Serial.println(motor_speed);

*/