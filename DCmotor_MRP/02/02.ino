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
  for (int i = 0; i <= 100; i++) {
    // まず、iを 0.00 〜 1.00 の小数（パーセント）にします
    float t = i / 100.0;
    
    // 【ここが魔法の数式！】
    // コサイン波を使って、S字カーブ（0.0 〜 1.0）を作ります
    // PI（円周率）をかけることで、波の「半分」だけを使っています
    float curve = (1.0 - cos(t * PI)) / 2.0;
    
    // カーブの割合（0.0〜1.0）にMAXスピードを掛け算して最終的なスピードを決定
    int speed = curve * maxSpeed;

    ledcWrite(0, speed);
    ledcWrite(1, 0);
    delay(wait);
  }

  delay(3000);

  // 【2. 前進の減速】
  for (int i = 100; i >= 0; i--) {
    float t = i / 100.0;
    // 減速の時も同じS字カーブの計算を使います
    // これにより、急ブレーキではなく「ジワッと止まる」リアルな動きになります
    float curve = (1.0 - cos(t * PI)) / 2.0;
    int speed = curve * maxSpeed;

    ledcWrite(0, speed);
    ledcWrite(1, 0);
    delay(wait);
  }

  delay(200);

  // 【3. 後退の加速】
  for (int i = 0; i <= 100; i++) {
    float t = i / 100.0;
    float curve = (1.0 - cos(t * PI)) / 2.0;
    int speed = curve * maxSpeed;

    ledcWrite(0, 0);
    ledcWrite(1, speed); // 後退なのでチャンネル1
    delay(wait);
  }

  delay(3000);

  // 【4. 後退の減速】
  for (int i = 100; i >= 0; i--) {
    float t = i / 100.0;
    float curve = (1.0 - cos(t * PI)) / 2.0;
    int speed = curve * maxSpeed;

    ledcWrite(0, 0);
    ledcWrite(1, speed);
    delay(wait);
  }

  delay(200);
}