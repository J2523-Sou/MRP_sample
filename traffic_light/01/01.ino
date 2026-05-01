/*
車用信号
*/

#define LED_01 4  // 4番ピンをLEDに接続　赤
#define LED_02 5  // 5番ピンをLEDに接続　黄色
#define LED_03 6  // 6番ピンをLEDに接続　青

void setup() {

  Serial.begin(9600);

  pinMode(LED_01, OUTPUT);
  pinMode(LED_02, OUTPUT);
  pinMode(LED_03, OUTPUT);


}

void loop() {
  //順番に光らせる
  digitalWrite(LED_01, HIGH); //赤
  delay(1000);
  digitalWrite(LED_01, LOW);    
  digitalWrite(LED_02, HIGH);　//黄色
  delay(500);
  digitalWrite(LED_02, LOW);
  digitalWrite(LED_03, HIGH);　//青
  delay(1000);
  digitalWrite(LED_03, LOW);
    
  
  delay(50);
}
