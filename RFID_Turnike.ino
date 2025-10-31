#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 2
#define RST_PIN 4
#define GREEN_LED 25
#define RED_LED 26
#define BUZZER 27

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();

  lcd.begin();
  lcd.backlight();

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.println("RFID Turnike Sistemi hazir!");
  lcd.setCursor(0, 0);
  lcd.print("Turnike Hazir...");
  delay(1500);
  lcd.clear();
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  Serial.print("Kart UID: ");
  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
  }
  uid.toUpperCase();
  Serial.println(uid);

  String isim = "";
  if (uid == "F0FD9A7C") isim = "Eda Erden";
  else if (uid == "20641C24") isim = "Gizem Ozbek";
  else if (uid == "5330AD32") isim = "Onur Mese";
  else if (uid == "F7594A39") isim = "Beyza Demirtas";
  else if (uid == "873B5CED") isim = "Gulsum Sahin";
  else if (uid == "53134132") isim = "Ahmet Kahraman";
  else if (uid == "2D9C73A1") isim = "Ebrar Kilic"; // ✅ yeni ekleme
  else isim = "";

  lcd.clear();
  if (isim != "") {
    Serial.print("Hosgeldiniz ");
    Serial.println(isim);
    lcd.setCursor(0, 0);
    lcd.print("Hosgeldiniz");
    lcd.setCursor(0, 1);
    lcd.print(isim);

    digitalWrite(GREEN_LED, HIGH);
    tone(BUZZER, 1000, 200);
    delay(1000);
    digitalWrite(GREEN_LED, LOW);
  } else {
    Serial.println("Erisim reddedildi!");
    lcd.setCursor(0, 0);
    lcd.print("Erisim reddedildi!");
    lcd.setCursor(0, 1);
    lcd.print("Yetkisiz kart!");
    digitalWrite(RED_LED, HIGH);
    tone(BUZZER, 600, 500);
    delay(1000);
    digitalWrite(RED_LED, LOW);
  }

  rfid.PICC_HaltA();
  delay(1500);
  lcd.clear();
}
