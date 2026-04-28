/*

  D2626 永瀬大地
  DCモーター（MRPドライバ使用）

*/

#define PWM_01 15 // 15番ピンをPWM_01に接続
#define PWM_02 16 // 16番ピンをPWM_02に接続
int wait = 25;
int maxSpeed = 240;

void setup() {
  Serial.begin(9600);
  ledcAttachPin(PWM_01, 0); // PWM_01ピンをチャンネル0に割り当て
  ledcSetup(0, 5000, 8);    // チャンネル0を5kHz、8bit分解能で設定

  ledcAttachPin(PWM_02, 1); // PWM_02ピンをチャンネル1に割り当て
  ledcSetup(1, 5000, 8);    // チャンネル1を5kHz、8bit分解能で設定
}

void loop() {

  //正転増加
  for (int i = 0; i < maxSpeed; i++) {
    ledcWrite(0, i);
    ledcWrite(1, 0);
    Serial.println(i);
    delay(wait);
  }

  //正転減少
  for (int i = maxSpeed - 1; i > 0; i--) {
    ledcWrite(0, i);
    ledcWrite(1, 0);
    Serial.println(i);
    delay(wait);
  }

  //逆転増加
  for (int i = 0; i < maxSpeed; i++) {
    ledcWrite(0, 0);
    ledcWrite(1, i);
    Serial.println(i);
    delay(wait);
  }

  //逆転減少
  for (int i = maxSpeed - 1; i > 0; i--) {
    ledcWrite(0, 0);
    ledcWrite(1, i);
    Serial.println(i);
    delay(wait);
  }
}
