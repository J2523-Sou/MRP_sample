```cpp
#include <Bluepad32.h> // Bluepad32ライブラリを読み込む（Bluetoothコントローラー用）

#include <ESP32Servo.h> // ESP32用のサーボライブラリを読み込む

Servo servo_1; // 1つ目のサーボモーターのオブジェクトを作成
Servo servo_2; // 2つ目のサーボモーターのオブジェクトを作成
Servo servo_3; // 3つ目のサーボモーターのオブジェクトを作成
const unsigned int ServoPin_1 = 27; // サーボ1の信号線を27番ピンに設定
const unsigned int ServoPin_2 = 13; // サーボ2の信号線を13番ピンに設定
const unsigned int ServoPin_3 = 23; // サーボ3の信号線を23番ピンに設定
//サーボモーター信号線ピン

const unsigned int suittiP_1 = 37; // リミットスイッチ1を37番ピンに設定
const unsigned int suittiP_2 = 36; // リミットスイッチ2を36番ピンに設定
const unsigned int suittiP_3 = 33; // リミットスイッチ3を33番ピンに設定
//リミットスイッチ入力ピン

const unsigned int pwmpin = 17; // モーター速度制御（PWM）を17番ピンに設定
const unsigned int dirpin = 5;  // モーターの回転方向制御を5番ピンに設定


ControllerPtr myControllers[BP32_MAX_GAMEPADS]; // 接続されたコントローラーを保存する配列

// 新しいコントローラーが接続されたときに自動で実行される関数
void onConnectedController(ControllerPtr ctl) {
  bool foundEmptySlot = false; // 空きスロットがあるかどうかのフラグ
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) { // 最大接続数分ループして空きを探す
    if (myControllers[i] == nullptr) { // 空きスロットが見つかった場合
      Serial.printf("CALLBACK: Controller is connected, index=%d\n", i); // 接続メッセージを表示
      // コントローラーのモデル名やIDなどの情報を取得
      ControllerProperties properties = ctl->getProperties();
      Serial.printf("Controller model: %s, VID=0x%04x, PID=0x%04x\n", ctl->getModelName().c_str(), properties.vendor_id,
                    properties.product_id);
      myControllers[i] = ctl; // 配列にコントローラーを保存
      foundEmptySlot = true;  // 空きが見つかったことを記録
      break; // ループを抜ける
    }
  }
  if (!foundEmptySlot) { // 空きがなかった場合
    Serial.println("CALLBACK: Controller connected, but could not found empty slot");
  }
}

// コントローラーの接続が切れたときに自動で実行される関数
void onDisconnectedController(ControllerPtr ctl) {
  bool foundController = false; // 切断されたコントローラーを探すフラグ

  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) { // 配列の中から一致するものを探す
    if (myControllers[i] == ctl) {
      Serial.printf("CALLBACK: Controller disconnected from index=%d\n", i); // 切断メッセージを表示
      myControllers[i] = nullptr; // スロットを空にする
      foundController = true;
      break;
    }
  }

  if (!foundController) { // 見つからなかった場合
    Serial.println("CALLBACK: Controller disconnected, but not found in myControllers");
  }
}

// ゲームパッドの現在の状態（ボタンや軸）をシリアルモニタに出力する関数
void dumpGamepad(ControllerPtr ctl) {
  Serial.printf(
    "idx=%d, dpad: 0x%02x, buttons: 0x%04x, axis L: %4d, %4d, axis R: %4d, %4d, brake: %4d, throttle: %4d, "
    "misc: 0x%02x, gyro x:%6d y:%6d z:%6d, accel x:%6d y:%6d z:%6d\n",
    ctl->index(),        // インデックス
    ctl->dpad(),         // 十字キー
    ctl->buttons(),      // ボタンのビットマスク
    ctl->axisX(),        // 左スティックX軸 (-511 - 512)
    ctl->axisY(),        // 左スティックY軸
    ctl->axisRX(),       // 右スティックX軸
    ctl->axisRY(),       // 右スティックY軸
    ctl->brake(),        // ブレーキ（L2等）
    ctl->throttle(),     // スロットル（R2等）
    ctl->miscButtons(),  // その他ボタン
    ctl->gyroX(),        // ジャイロX軸
    ctl->gyroY(),        // ジャイロY軸
    ctl->gyroZ(),        // ジャイロZ軸
    ctl->accelX(),       // 加速度X軸
    ctl->accelY(),       // 加速度Y軸
    ctl->accelZ()        // 加速度Z軸
  );
}

// マウスの状態を表示する関数（今回は未使用）
void dumpMouse(ControllerPtr ctl) {
  Serial.printf("idx=%d, buttons: 0x%04x, scrollWheel=0x%04x, delta X: %4d, delta Y: %4d\n",
                ctl->index(),        ctl->buttons(),      ctl->scrollWheel(),  ctl->deltaX(),       ctl->deltaY()
  );
}

// キーボードの状態を表示する関数
void dumpKeyboard(ControllerPtr ctl) {
  static const char* key_names[] = { // キーの名前を定義
        "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V",
        "W", "X", "Y", "Z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
        "Enter", "Escape", "Backspace", "Tab", "Spacebar", "Underscore", "Equal", "OpenBracket", "CloseBracket",
        "Backslash", "Tilde", "SemiColon", "Quote", "GraveAccent", "Comma", "Dot", "Slash", "CapsLock",
        "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
        "PrintScreen", "ScrollLock", "Pause", "Insert", "Home", "PageUp", "Delete", "End", "PageDown",
        "RightArrow", "LeftArrow", "DownArrow", "UpArrow",
  };
  static const char* modifier_names[] = { // 特殊キー（Shift等）の名前
        "Left Control", "Left Shift", "Left Alt", "Left Meta",
        "Right Control", "Right Shift", "Right Alt", "Right Meta",
  };
  Serial.printf("idx=%d, Pressed keys: ", ctl->index());
  for (int key = Keyboard_A; key <= Keyboard_UpArrow; key++) { // 押されているキーを探して表示
    if (ctl->isKeyPressed(static_cast<KeyboardKey>(key))) {
      const char* keyName = key_names[key - 4];
      Serial.printf("%s,", keyName);
    }
  }
  for (int key = Keyboard_LeftControl; key <= Keyboard_RightMeta; key++) { // 押されている特殊キーを表示
    if (ctl->isKeyPressed(static_cast<KeyboardKey>(key))) {
      const char* keyName = modifier_names[key - 0xe0];
      Serial.printf("%s,", keyName);
    }
  }
  Console.printf("\n");
}

// バランスボードの状態を表示する関数（今回は未使用）
void dumpBalanceBoard(ControllerPtr ctl) {
  Serial.printf("idx=%d,  TL=%u, TR=%u, BL=%u, BR=%u, temperature=%d\n",
                ctl->index(), ctl->topLeft(), ctl->topRight(), ctl->bottomLeft(), ctl->bottomRight(), ctl->temperature()
  );
}

// ゲームパッドの入力に応じて実際の動作を行う関数
void processGamepad(ControllerPtr ctl) {
  if (ctl->a()) { // Aボタンが押された場合
    static int colorIdx = 0;
    switch (colorIdx % 3) { // LEDの色を順番に変える
      case 0: ctl->setColorLED(255, 0, 0); break; // 赤
      case 1: ctl->setColorLED(0, 255, 0); break; // 緑
      case 2: ctl->setColorLED(0, 0, 255); break; // 青
    }
    colorIdx++;
    servo_2.write(70); // サーボ2を70度の位置に動かす
  }

  if (ctl->b()) { // Bボタンが押された場合
    static int led = 0;
    led++;
    ctl->setPlayerLEDs(led & 0x0f); // プレイヤーLED（コントローラーのランプ）を光らせる

    servo_3.write(180); // サーボ3を180度の位置に動かす
  }

  if (ctl->x()) { // Xボタンが押された場合
    ctl->playDualRumble(0, 250, 0x80, 0x40); // 振動機能を動作させる

    servo_1.write(180); // サーボ1を180度の位置に動かす
  }

  if (ctl->y()) { // Yボタンが押された場合
    servo_1.write(180); // サーボ1を180度に
    servo_2.write(70);  // サーボ2を70度に
    servo_3.write(180); // サーボ3を180度に（一括操作）
  }

  if (ctl->dpad() == 0x01) { // 十字キーの上が押された場合
    digitalWrite(dirpin,0); // モーターの回転方向を設定
    ledcWrite(0,255);      // モーターをフルスピードで回す
  }

  if (ctl->dpad() == 0x00) { // 十字キーが何も押されていない場合
    digitalWrite(dirpin,0); // モーターの回転方向を設定
    ledcWrite(0,0);        // モーターを止める
  }

  dumpGamepad(ctl); // 現在の状態をシリアルに出力
}

// マウス入力の処理（今回は未使用）
void processMouse(ControllerPtr ctl) {
  if (ctl->scrollWheel() > 0) {} 
  else if (ctl->scrollWheel() < 0) {}
  dumpMouse(ctl);
}

// キーボード入力の処理
void processKeyboard(ControllerPtr ctl) {
  if (!ctl->isAnyKeyPressed()) return; // 何も押されていなければ終了

  if (ctl->isKeyPressed(Keyboard_A)) { // Aキーが押された場合
    Serial.println("Key 'A' pressed");
  }
  if (ctl->isKeyPressed(Keyboard_LeftShift)) { // 左Shiftが押された場合
    Serial.println("Key 'LEFT SHIFT' pressed");
  }
  if (ctl->isKeyPressed(Keyboard_LeftArrow)) { // 左矢印が押された場合
    Serial.println("Key 'Left Arrow' pressed");
  }
  dumpKeyboard(ctl);
}

// バランスボードの処理（今回は未使用）
void processBalanceBoard(ControllerPtr ctl) {
  if (ctl->topLeft() > 10000) {}
  dumpBalanceBoard(ctl);
}

// すべての接続済みコントローラーをチェックして処理を振り分ける関数
void processControllers() {
  for (auto myController : myControllers) { // 接続されているコントローラーを一つずつ確認
    if (myController && myController->isConnected() && myController->hasData()) { // 接続中でデータがある場合
      if (myController->isGamepad()) { // ゲームパッドなら
        processGamepad(myController);
      } else if (myController->isMouse()) { // マウスなら
        processMouse(myController);
      } else if (myController->isKeyboard()) { // キーボードなら
        processKeyboard(myController);
      } else if (myController->isBalanceBoard()) { // バランスボードなら
        processBalanceBoard(myController);
      } else {
        Serial.println("Unsupported controller");
      }
    }
  }
}

// ESP32起動時に一度だけ実行される初期設定関数
void setup() {
  Serial.begin(115200); // シリアル通信の速度を115200に設定
  Serial.printf("Firmware: %s\n", BP32.firmwareVersion()); // ファームウェアのバージョンを表示
  const uint8_t* addr = BP32.localBdAddress(); // ESP32自身のBluetoothアドレスを取得
  Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

  // Bluepad32の接続・切断時コールバック関数を登録
  BP32.setup(&onConnectedController, &onDisconnectedController);

  // 以前のペアリング情報をリセット（接続トラブル防止のため）
  BP32.forgetBluetoothKeys();

  // バーチャルデバイス機能を無効化（マウスとゲームパッドを分けたい場合以外はfalse）
  BP32.enableVirtualDevice(false);

  servo_1.setPeriodHertz(50); // サーボ1の周波数を50Hzに設定（標準的なサーボ用）
  servo_1.attach(ServoPin_1, 500, 2400); // 27番ピンを使用、最小・最大パルス幅を指定

  servo_2.setPeriodHertz(50); // サーボ2の周波数を50Hzに設定
  servo_2.attach(ServoPin_2, 500, 2400); // 13番ピンを使用

  servo_3.setPeriodHertz(50); // サーボ3の周波数を50Hzに設定
  servo_3.attach(ServoPin_3, 500, 2400); // 23番ピンを使用


  pinMode(suittiP_1, INPUT_PULLUP); // 37番ピンをプルアップ入力に設定（スイッチ用）
  pinMode(suittiP_2, INPUT_PULLUP); // 36番ピンをプルアップ入力に設定
  pinMode(suittiP_3, INPUT_PULLUP); // 33番ピンをプルアップ入力に設定

  ledcSetup(0, 5000, 8); // PWMの0番チャンネルを5kHz、8ビット(0-255)で設定
  ledcAttachPin(pwmpin, 0); // モーターのPWMピンを0番チャンネルに紐付け
  pinMode(dirpin,OUTPUT); // モーターの方向制御ピンを出力に設定
}

// 電源が入っている間、ずっと繰り返されるメインの処理
void loop() {
  // コントローラーの最新データを取得
  bool dataUpdated = BP32.update();
  if (dataUpdated) // データが更新されていたら
    processControllers(); // 各ボタンの処理を実行

  bool switchState_1 = digitalRead(suittiP_1); // スイッチ1の状態を読み取る
  bool switchState_2_real = digitalRead(suittiP_2); // スイッチ2の物理的な状態を読み取る
  bool switchState_3 = digitalRead(suittiP_3); // スイッチ3の状態を読み取る
  bool switchState_2;

  if (switchState_2_real == 0) { // スイッチ2が押された（0になった）場合
    switchState_2 = 1; // 内部変数を1にする
  } else {
    switchState_2 = 0; // 内部変数を0にする
  }

  // スイッチ1が反応した（1になった）場合
  if (switchState_1 == 1) {
    servo_1.write(75); // サーボ1をリセット位置（75度）に戻す
  }

  // スイッチ2が反応した（1になった）場合
  if (switchState_2 == 1) {
    servo_2.write(0); // サーボ2をリセット位置（0度）に戻す
  }

  // スイッチ3が反応した（1になった）場合
  if (switchState_3 == 1) {
    servo_3.write(75); // サーボ3をリセット位置（75度）に戻す
  }

  // CPUに負担をかけすぎないよう、少し待つ（ウォッチドッグタイマー対策）
  delay(15);
}

```
