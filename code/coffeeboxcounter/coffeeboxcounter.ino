////////////////////////////////////////
// CoffeBoxCounter v0.0.1
// Feb 2018
// Copyleft
////////////////////////////////////////

// Wemos Mini D1 Pinout - ESP8266
// RST - RESET
// A0  - ADC0
// D0  - GPIO16
// D5  - GPIO14 SCK - SPI
// D6  - GPIO12 MISO - SPI
// D7  - GPIO13 MOSI - SPI
// D8  - GPIO15 SS - SPI
// 3v3 - 3.3v
// TX  - TXD
// RX  - RXD
// D1  - GPIO5 SCL
// D2  - GPIO4 SDA
// D3  - GPIO0
// D4  - GPIO2
// GND - Ground
// 5V  - 

// Included libraries
#include <ESP8266WiFi.h>      // ESP library for all WiFi functions
#include <ArduinoOTA.h>       // Library for uploading sketch over the air (OTA)
#include <SPI.h>              // Library for hardware or software driven SPI
#include <EEPROM.h>           // Library for EEPROM functions
#include <MFRC522.h>          // Library for RFID MFRC522 module
#include <Adafruit_GFX.h>     // OLED GFX https://github.com/adafruit/Adafruit-GFX-Library
#include <Adafruit_SSD1306.h> // OLED https://github.com/adafruit/Adafruit_SSD1306
// Included custom
#include "animations.h"       // Header files for screen animations

typedef struct {
		byte uid[4];             //4 Bytes
    char name[4];               // 4 Bytes
    unsigned int current_total; // 2 Bytes
    unsigned int backup_total;  // 2 Bytes
} User;                         // TOTAL 12 Bytes (42 Users in 512 B EPROM)

// RFID
//#define SS_PIN 10             // RFID slave select pin
//#define RST_PIN 5             // RFID reset pin
//MFRC522 mfrc522(SS_PIN, RST_PIN);// instatiate a MFRC522 reader object.

// OLED
// SCL GPIO5
// SDA GPIO4
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

// Push Button
#define PUSH_BTN_PIN 4

// Buzzer
#define BUZZER_PIN 2

// Functions declaration
void createEE();
void saveEE();
void coffee_animate();

void setup() {
  Serial.begin(9600);        // Initialize serial communications for serial communications over USB
  Serial.println("### COFFE BOX COUNTER ###");
  //SPI.begin();               // Init SPI bus
  //mfrc522.PCD_Init();        // Init MFRC522 card (in case you wonder what PCD means: proximity coupling device)
  //Serial.println("MFRC522 Ready");
  // OLED Setup
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  Serial.println("OLED Screen Ready");
  // Push BTN Setup
  //pinMode(PUSH_BTN_PIN, INPUT);
  // Buzzer Setup
  //pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
   Serial.println("#LOOPING#");
  // Detects new RFID Card
  //if (mfrc522.PICC_IsNewCardPresent()) {
  //  Serial.println("RFID detected");
    // Read uuid form the RFID Card
  //  if (mfrc522.PICC_ReadCardSerial()) {
  //    Serial.println("ID:");
      // UUID -> Name Lookup & Counter increment

      // Visual Feedback Oled

      // Sound Feedback

      // TIMEOUT
   // }
  //}

  // Detects if Button is pressed
    if (digitalRead(PUSH_BTN_PIN) == HIGH) {
          
    }

      //Display the table of user with current consuptions

    //3 press

      //Wait for RFID Card with UID 0x0001

        //Display Confirmation "Are you sure / Confirm with button"

          //Confirm button

             //Copy current value to backup

             //Reser current counters
  
  //Animate Oled Screen with HotCoffee
  coffee_animate();
  delay(50);
}

void createEE(){
  
}

void saveEE(){
  
}

void coffee_animate(){
  display.display();
    // Clear the buffer.
  display.clearDisplay();
 
  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("COFFEEBOX\nCOUNTER");
  display.display();
  delay(2000);
  display.clearDisplay();
  display.drawBitmap(0, 0, anim01, 64, 48, WHITE);
  display.display();
  delay(700);
  display.clearDisplay();
  display.drawBitmap(0, 0, anim02, 64, 48, WHITE);
  display.display();
  delay(700);
  display.clearDisplay();
  display.drawBitmap(0, 0, anim03, 64, 48, WHITE);
  display.display();
  for (int cnt = 0; cnt < 2; cnt++) {
  delay(700);
  display.clearDisplay();
  display.drawBitmap(0, 0, anim04, 64, 48, WHITE);
  display.display();
  delay(700);
  display.clearDisplay();
  display.drawBitmap(0, 0, anim05, 64, 48, WHITE);
  display.display();
  }
}
