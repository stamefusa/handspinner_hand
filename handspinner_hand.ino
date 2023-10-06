#include <Servo.h>

Servo hand, spinner;

int val = 0, pre_val = 0;
int threshould = 300;
int count = 0, tmp_count = 0;
unsigned long start = 0;
int state = 0;  // 0:停止 1:回転中 2:スピナー回転準備 3:手で回転させる 4:スピナー戻す 5:手戻す

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);  // SerialでのString受信のタイムアウト設定（ms）

  // サーボピン初期化
  hand.attach(7);
  spinner.attach(8);

  hand.write(10);
  spinner.write(170);

  start = millis();
}

void loop() {
  val = analogRead(A0);
  //int diff = val - pre_val;
  //Serial.println(val);
  if (val > threshould && pre_val <= threshould) {
    count++;
  }
  if (millis() - start > 1000) {
    Serial.println(count);
    if (count >= 3 && state == 0) {
      state = 1;
      Serial.println("START");
    } else if (count < 3 && state == 1) {
      state = 2;
      Serial.println("SLOW DOWN");
    } else if (state == 2) {
      state = 3;
      Serial.println("ROTATE SPINNER TO SPIN");
      spinner.write(10);
    } else if (state == 3) {
      Serial.println("ROTATE HAND TO SPIN");
      state = 4;
      hand.write(170);
    } else if (state == 4) {
      Serial.println("RETURN SPINNER");
      state = 5;
      spinner.write(170);
    } else if (state == 5) {
      Serial.println("RETURN HAND");
      state = 0;
      hand.write(10);
    }
    count = 0;
    start = millis();
  }
  pre_val = val;

  delay(1);
}