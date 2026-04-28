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
  // 【1. 前進の加速】
  // iを0から100まで変化させます（0%から100%のイメージ）
  for (int i = 0; i <= 100; i++) {
    // iを2乗して、後からグッと数値が大きくなるように計算します
    // i=10なら100、i=50なら2500、i=100なら10000になります
    // それを10000で割ることで、0.0〜1.0の割合を作っています
    int speed = (i * i * maxSpeed) / 10000; 
    
    ledcWrite(0, speed); // 計算したスピードをモーターに送る
    ledcWrite(1, 0);
    delay(wait);
  }

  delay(3000); // MAXスピードで3秒キープ

  // 【2. 前進の減速】
  // 今度は100から0に減らしていきます
  for (int i = 100; i >= 0; i--) {
    // 加速と同じ計算をすることで、最初は一気にスピードが落ちて、最後はゆっくり止まります
    int speed = (i * i * maxSpeed) / 10000;
    
    ledcWrite(0, speed);
    ledcWrite(1, 0);
    delay(wait);
  }

  delay(200); // 少し休む

  // 【3. 後退の加速】（計算の仕組みは前進と同じです）
  for (int i = 0; i <= 100; i++) {
    int speed = (i * i * maxSpeed) / 10000;
    
    ledcWrite(0, 0);
    ledcWrite(1, speed); // 今度はチャンネル1（PWM_02）を動かす
    delay(wait);
  }

  delay(3000);

  // 【4. 後退の減速】
  for (int i = 100; i >= 0; i--) {
    int speed = (i * i * maxSpeed) / 10000;
    
    ledcWrite(0, 0);
    ledcWrite(1, speed);
    delay(wait);
  }

  delay(200);
}