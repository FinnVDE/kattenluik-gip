#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

#define GREEN_LED 5   // Pin for Green LED
#define RED_LED 4     // Pin for Red LED

// Define the authorized UID (replace with your card's UID)
byte authorizedUID[] = {0xA2, 0xA6, 0xA8, 0x1C}; // Example UID

void setup() {
  Serial.begin(9600);   // Initialize serial communications
  SPI.begin();          // Initialize SPI bus
  mfrc522.PCD_Init();   // Initialize RFID reader
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  Serial.println("Scan an RFID tag...");
}

void loop() {
  // Look for a new card
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Show the UID on the serial monitor
  Serial.print("UID tag: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Compare scanned UID with authorized UID
  if (checkUID(authorizedUID, mfrc522.uid.uidByte)) {
    Serial.println("Access Granted");
    digitalWrite(GREEN_LED, HIGH);  // Turn on green LED
    digitalWrite(RED_LED, LOW);     // Ensure red LED is off
    delay(2000);                    // Keep LED on for 2 seconds
    digitalWrite(GREEN_LED, LOW);   // Turn off green LED
  } else {
    Serial.println("Access Denied");
    digitalWrite(RED_LED, HIGH);    // Turn on red LED
    digitalWrite(GREEN_LED, LOW);   // Ensure green LED is off
    delay(2000);                    // Keep LED on for 2 seconds
    digitalWrite(RED_LED, LOW);     // Turn off red LED
  }

  mfrc522.PICC_HaltA();  // Halt PICC
  mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
}

// Function to compare two UIDs
bool checkUID(byte *uid1, byte *uid2) {
  for (byte i = 0; i < 4; i++) {
    if (uid1[i] != uid2[i]) {
      return false;
    }
  }
  return true;
}
