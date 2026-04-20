/*

  J2523 髙橋湊
  サーボモーター（ESP32・SG90使用）サンプルプログラム
  動作確認：未

*/

//サーボモータライブラリ
#include <ESP32Servo.h>

//サーボのクラスを作成する
Servo servo;

void setup() {

  //0番ピンをservoに紐づける
  servo.attach(0);

}

void loop() {

  //角度を増加させる
  for (int i = 0; i <= 180; i++) {
    servo.write(i);
  }
  //角度を減少させる
  for (int i = 180; i >= 0; i--) {
    servo.write(i);
  }

}
