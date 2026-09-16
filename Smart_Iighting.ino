int soundSensor = 2;
int LED = 3;
boolean LEDStatus = false;

void setup() {
  pinMode(soundSensor, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop() {
  int SensorData = digitalRead(soundSensor);
  
  if (SensorData == HIGH) {
    if (LEDStatus == false) {
      LEDStatus = true;
      digitalWrite(LED, HIGH);
    } else {
      LEDStatus = false;
      digitalWrite(LED, LOW);
    }
    delay(500); // لمنع التكرار السريع عند التقاط الصوت
  }
}
