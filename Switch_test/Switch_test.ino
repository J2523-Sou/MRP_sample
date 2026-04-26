/*
  D2626 永瀬大地
  スイッチの状態が変わった時だけシリアルモニタに表示する改良版プログラム
*/

#define SW_01 6  // 6番ピンをSwitch1に接続
#define SW_02 4  // 4番ピンをSwitch2に接続
#define SW_03 5  // 5番ピンをSwitch3に接続

int pushSwitchNum = 0;
int lastSwitchNum = -1; // 前回の状態を覚えておくための新しい変数

void setup() {
  Serial.begin(9600);
  pinMode(SW_01, INPUT_PULLUP);
  pinMode(SW_02, INPUT_PULLUP);
  pinMode(SW_03, INPUT_PULLUP);
}

void loop() {
  // 1. スイッチの状態を順番に確認する（else if を使う）
  if (digitalRead(SW_01) == LOW) {
    pushSwitchNum = 1;
  } else if (digitalRead(SW_02) == LOW) {
    pushSwitchNum = 2;
  } else if (digitalRead(SW_03) == LOW) {
    pushSwitchNum = 3;
  } else {
    pushSwitchNum = 0; // どれも押されていなければ0
  }

  // 2. 前回の状態から変化があった時だけシリアルモニタに表示する
  if (pushSwitchNum != lastSwitchNum) {
    if (pushSwitchNum == 0) {
      Serial.println("Switch is released");
    } else {
      Serial.print("Switch ");
      Serial.print(pushSwitchNum);
      Serial.println(" is pressed");
    }
    
    // 今の状態を「前回の状態」として記録しておく
    lastSwitchNum = pushSwitchNum;
  }

  // 誤作動（チャタリング）防止のための少しの待ち時間
  delay(50); 
}