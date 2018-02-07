//
// Sketch for the CoffeBoxCounter
// 2018 -
//

// Included libraries
#include <ESP8266WiFi.h>      // ESP library for all WiFi functions
#include <ArduinoOTA.h>       // Library for uploading sketch over the air (OTA)
#include <SPI.h>              // Library for hardware or software driven SPI
#include <EEPROM.h>           // Library for EEPROM functions
#include <MFRC522.h>          // Library for RFID MFRC522 module
#include <Adafruit_GFX.h>     // OLED GFX https://github.com/adafruit/Adafruit-GFX-Library
#include <Adafruit_SSD1306.h> // OLED https://github.com/adafruit/Adafruit_SSD1306

typedef struct {
		byte uid[4];             //4 Bytes
    char name[4];               // 4 Bytes
    unsigned int current_total; // 2 Bytes
    unsigned int backup_total;  // 2 Bytes
} User;                         // TOTAL 12 Bytes (42 Users in 512 B EPROM)

// RFID
#define SS_PIN 10             // RFID slave select pin
#define RST_PIN 5             // RFID reset pin
MFRC522 mfrc522(SS_PIN, RST_PIN);// instatiate a MFRC522 reader object.
// OLED
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


void setup() {
  Serial.println("### COFFE BOX COUNTER ###");
  Serial.begin(9600);        // Initialize serial communications for serial communications over USB
  SPI.begin();               // Init SPI bus
  mfrc522.PCD_Init();        // Init MFRC522 card (in case you wonder what PCD means: proximity coupling device)
  Serial.println("MFRC522 Ready");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
  Serial.println("OLED Screen Ready");
}

void loop() {

  // Detects new RFID Card
  if (mfrc522.PICC_IsNewCardPresent()) {
    Serial.println("RFID detected");
    // Read uuid form the RFID Card
    if (mfrc522.PICC_ReadCardSerial()) {
      Serial.println("ID:");
      // UUID -> Name Lookup & Counter increment

      // Visual Feedback Oled

      // Sound Feedback

      // TIMEOUT
    }
  }


  //Animate Oled Screen with HotCoffee
}
