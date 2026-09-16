#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
#define SERVO_PIN A1

MFRC522 rfid(SS_PIN, RST_PIN);
Servo lockServo;

// البطاقات المسموحة
byte card1[4] = {0x07, 0xFB, 0xCC, 0x31};
byte card2[4] = {0x8D, 0xA5, 0xD2, 0x3E};

void setup() {
  Serial.begin(9600);

  SPI.begin();
  rfid.PCD_Init();

  lockServo.attach(SERVO_PIN);

  // الباب مقفل
  lockServo.write(0);

  Serial.println("Smart Door Ready");
}

// التحقق من البطاقة
bool checkCard(byte *card) {
  for (byte i = 0; i < 4; i++) {
    if (rfid.uid.uidByte[i] != card[i]) {
      return false;
    }
  }
  return true;
}

// فتح الباب
void openLock() {
  Serial.println("Access Granted");

  lockServo.write(90);

  delay(3000);

  lockServo.write(0);

  Serial.println("Door Locked");
}

void loop() {
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {

    if (checkCard(card1) || checkCard(card2)) {
      openLock();
    } else {
      Serial.println("Access Denied");
    }

    rfid.PICC_HaltA();
  }
}
