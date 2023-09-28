int val = 0, pre_val = 0;
int threshould = 300;
int count = 0;
unsigned long start = 0;

void setup() {
  Serial.begin(9600);
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
    count = 0;
    start = millis();
  }
  pre_val = val;
  delay(1);
}