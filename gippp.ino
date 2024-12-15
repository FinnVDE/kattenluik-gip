#include <MFRC522.h>
#include <Servo.h>  // Servo bibliotheek toevoegen

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Maak een MFRC522 instantie.

#define GREEN_LED 5   // Pin voor groene LED
#define RED_LED 4     // Pin voor rode LED

Servo motor;          // Servo-motor instantie maken
#define MOTOR_PIN 6   // Pin waar de servo is aangesloten

// Gedefinieerde toegestane UID (vervang door jouw kaart-ID)
byte authorizedUID[] = {0xA2, 0xA6, 0xA8, 0x1C}; // Voorbeeld UID

void setup() {
  Serial.begin(9600);   // Start seriële communicatie
  SPI.begin();          // Start SPI-bus
  mfrc522.PCD_Init();   // Initialiseer RFID-lezer

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

  motor.attach(MOTOR_PIN); // Verbind de servo met de motor pin
  motor.write(0);          // Zet de servo in de rustpositie (0 graden)

  Serial.println("Scan een RFID-tag...");
}

void loop() {
  // Zoek naar een nieuwe kaart
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Toon de UID op de seriële monitor
  Serial.print("UID tag: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Vergelijk de gescande UID met de toegestane UID
  if (checkUID(authorizedUID, mfrc522.uid.uidByte)) {
    Serial.println("Toegang verleend");
    digitalWrite(GREEN_LED, HIGH);  // Zet groene LED aan
    digitalWrite(RED_LED, LOW);     // Zorg dat rode LED uit is

    motor.write(180);               // Draai de motor naar 180 graden
    delay(30000);                    // Houd positie 30 seconden vast
    motor.write(0);                 // Zet de motor terug naar 0 graden
    digitalWrite(GREEN_LED, LOW);   // Zet groene LED uit
  } else {
    Serial.println("Toegang geweigerd");
    digitalWrite(RED_LED, HIGH);    // Zet rode LED aan
    digitalWrite(GREEN_LED, LOW);   // Zorg dat groene LED uit is

    motor.write(0);                 // Houd de motor stil op 0 graden
    delay(2000);                    // Houd status 2 seconden vast
    digitalWrite(RED_LED, LOW);     // Zet rode LED uit
  }

  mfrc522.PICC_HaltA();         // Stop PICC
  mfrc522.PCD_StopCrypto1();    // Stop encryptie op PCD
}

// Functie om twee UIDs te vergelijken
bool checkUID(byte *uid1, byte *uid2) {
  for (byte i = 0; i < 4; i++) {
    if (uid1[i] != uid2[i]) {
      return false;
    }
  }
  return true;
}

