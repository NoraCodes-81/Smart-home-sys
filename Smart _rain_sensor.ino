#include <Servo.h>

Servo myservo;
int isClosed = false;

void setup() {
  pinMode(A0, INPUT);
  myservo.attach(9);
  myservo.write(0);
}

void loop() {
  int rain = analogRead(A0);

  if (rain < 800) {
    if (!isClosed) {
      myservo.write(90);
      isClosed = true;
    }
  } else {
    if (isClosed) {
      myservo.write(0);
      isClosed = false;
    }
  }
  delay(500);
}
