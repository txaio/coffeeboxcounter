////////////////////////////////////////
// CoffeBoxCounter v0.0.1
// Feb 2018
// Copyleft
////////////////////////////////////////

// Wemos Mini D1 Pinout - ESP8266
// RST	- RESET		-
// A0		- ADC0		-
// D0		- GPIO16 - 16
// D5		- GPIO14 SCK - SPI - 14
// D6		- GPIO12 MISO - SPI - 12
// D7		- GPIO13 MOSI - SPI - 13
// D8		- GPIO15 SS - SPI - 15
#define SS_PIN 15                 // RFID slave select pin
// 3v3	- 3.3V
// TX		- TXD
// RX		- RXD
// D1		- GPIO5 SCL - 5
// D2		- GPIO4 SDA - 4
// D3		- GPIO0 SPI RST - 0
#define RST_PIN 0                 // RFID reset pin
#define OLED_RESET 0  // GPIO0
// D4		- GPIO2	-	PIN - 2
// GND	- Ground
// 5V		-

// Included libraries
#include <ESP8266WiFi.h>      // ESP library for all WiFi functions
#include <ArduinoOTA.h>       // Library for uploading sketch over the air (OTA)
#include <SPI.h>              // Library for hardware or software driven SPI
#include <EEPROM.h>           // Library for EEPROM functions
#include <MFRC522.h>          // Library for RFID MFRC522 module
#include <Adafruit_GFX.h>     // OLED GFX https://github.com/adafruit/Adafruit-GFX-Library
#include <Adafruit_SSD1306.h> // OLED https://github.com/adafruit/Adafruit_SSD1306

// Local Included
#include "animations.h"       // Header files for screen animations

// Version
#define VERS 1.0

// USERS
#define NUM_USERS 5
// Struct to define user structure
typedef struct {
		byte uid[4];             //4 Bytes - UID to compare RFID respons
    char name[4];               // 4 Bytes - User abreviation i.e: David - DAV
    unsigned int current_total; // 2 Bytes - Current user's coffee consumed
    unsigned int backup_total;  // 2 Bytes - Backup of the user's cofee consumption before last reset
} user; // TOTAL 12 Bytes (42 Users in 512 B EPROM)

//user users [X]; X Max 42 Users

// Test Users
user users [NUM_USERS] = {
  {{0xFF,0xFF,0xEE,0x00},"THI",11,10},
  {{0xAA,0xBB,0xCC,0x0A},"MAR",2,98},
  {{0xCC,0xEE,0xDD,0xDD},"MAN",121,221},
  {{0x01,0x22,0x33,0xFF},"ERI",59,300},
  {{0x01,0x22,0x33,0xFF},"ROB",333,109}
};

// RFID

MFRC522 mfrc522(SS_PIN, RST_PIN); // instatiate a MFRC522 reader object.
MFRC522::MIFARE_Key key;					// A|B Key Structure
int block;
byte readbackblock[18];
byte blockcontent[16] = {"PUTINPYTHONPUTI"};

// OLED
Adafruit_SSD1306 display(OLED_RESET);

// Push Button
#define PUSH_BTN_PIN D4

// Buzzer
//#define BUZZER_PIN 2

// Functions declaration
void btn_pushed();
void createEE();
void saveEE();
void splash_screen();
void coffee_animate();
void display_users_debug();
void display_users_totals();
void step_counter();

void setup() {
  Serial.begin(9600);        // Initialize serial communications for serial communications over USB
  Serial.println("### COFFE BOX COUNTER ###");
  SPI.begin();               // Init SPI bus
  mfrc522.PCD_Init();        // Init MFRC522 card (in case you wonder what PCD means: proximity coupling device)
  Serial.println("MFRC522 Ready");
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;//keyByte is defined in the "MIFARE_Key" 'struct' definition in the .h file of the library
  }
  block=2;//this is the block number we will write into and then read. Do not write into 'sector trailer' block, since this can make the block unusable.
  //mfrc522.PCD_DumpVersionToSerial();
  //byte blockcontent[16] = {"makecourse_____"};//an array with 16 bytes to be written into one of the 64 card blocks is defined
    //blockcontent[16] = {"PUTINPYTHONPUTI"};//an array with 16 bytes to be written into one of the 64 card blocks is defined
  //byte blockcontent[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//all zeros. This can be used to delete a block.
  //This array is used for reading out a block. The MIFARE_Read method requires a buffer that is at least 18 bytes to hold the 16 bytes of a block.

  // OLED Setup
  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  //Serial.println("OLED Screen Ready");
  // Push BTN Setup - Using interrupt to
  //attachInterrupt(PUSH_BTN_PIN, btn_pushed, RISING);
  // Buzzer Setup
  //pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
   //Serial.println("#LOOPING#");
  //Detects new RFID Card
  if ( ! mfrc522.PICC_IsNewCardPresent()) {//if PICC_IsNewCardPresent returns 1, a new card has been found and we continue
    return;//if it did not find a new card is returns a '0' and we return to the start of the loop
  }
  Serial.println("RFID detected");
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {//if PICC_ReadCardSerial returns 1, the "uid" struct (see MFRC522.h lines 238-45)) contains the ID of the read card.
    return;//if it returns a '0' something went wrong and we return to the start of the loop
  }

  //writeBlock(block, blockcontent);

  readBlock(block, readbackblock);
  Serial.print("read block: ");
      for (int j=0 ; j<16 ; j++){
        Serial.write (readbackblock[j]);//Serial.write() transmits the ASCII numbers as human readable characters to serial monitor
      }
  Serial.println("");
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  // Detects if Button is pressed


      //Display the table of user with current consuptions

      //3 press

      //Wait for RFID Card with UID 0x0001

        //Display Confirmation "Are you sure / Confirm with button"

          //Confirm button

             //Copy current value to backup

             //Reser current counters
  //splash_screen();
  //delay(2000);
  //display_users_totals();
  //delay(3000);
  //Animate Oled Screen with HotCoffee
  //coffee_animate();
  delay(50);
}
