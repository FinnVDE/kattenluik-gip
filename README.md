# kattenluik-gip

---

# RFID Toegangscontrole met Servo en LED-indicatoren

Dit project maakt gebruik van een RFID-lezer, een servo-motor en LED-lampjes om een eenvoudige toegangscontrole te realiseren. Wanneer een geautoriseerde RFID-tag wordt gescand, wordt toegang verleend door een servo-motor te activeren en een groene LED aan te zetten. Bij een niet-geautoriseerde tag blijft de toegang gesloten en licht een rode LED op.

---

## Benodigdheden

* Arduino Uno (of compatibel bord)
* RFID-lezer (MFRC522)
* RFID-tag of kaart
* Servo-motor
* 2 Weerstanden (220Ω voor de LED's)
* 1 Rode LED
* 1 Groene LED
* Breadboard en jumper wires

---

## Beschrijving

De Arduino leest de UID van een RFID-kaart via de MFRC522-module. Als de UID overeenkomt met de geautoriseerde code in de sketch, wordt een servo-motor naar 180° gedraaid (bijv. om een deur te openen) en gaat de groene LED aan. Na 30 seconden sluit de servo automatisch. Indien de UID niet overeenkomt, gaat de rode LED 2 seconden aan.

---

## Aansluitschema

| Component    | Arduino Pin |
| ------------ | ----------- |
| MFRC522 SDA  | 10          |
| MFRC522 RST  | 9           |
| MFRC522 MOSI | 11          |
| MFRC522 MISO | 12          |
| MFRC522 SCK  | 13          |
| Servo-motor  | 6           |
| Rode LED     | 4           |
| Groene LED   | 5           |

---

## Installatie

1. Installeer de volgende bibliotheken via de Arduino IDE:

   * **MFRC522**: Voor RFID-functionaliteit.
   * **Servo**: Voor de servo-motor.

2. Upload de sketch naar je Arduino.

3. Pas indien nodig de `authorizedUID[]` aan met de UID van jouw RFID-kaart. Deze UID kun je uitlezen via de seriële monitor.

---

## Gebruik

1. Open de seriële monitor op 9600 baud.
2. Scan een RFID-kaart.
3. Controleer of toegang wordt verleend of geweigerd.
4. Observeer de beweging van de servo en de bijbehorende LED-status.

---

## Code-uitleg

* `checkUID()` vergelijkt de gescande UID met een vooraf ingestelde, geautoriseerde UID.
* Servo draait naar 180° bij succesvolle herkenning en keert na 30 seconden terug naar 0°.
* Rode of groene LED wordt geactiveerd op basis van toegang.

---


