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
//#define SS_PIN 10             // RFID slave select pin
//#define RST_PIN 5             // RFID reset pin
//MFRC522 mfrc522(SS_PIN, RST_PIN);// instatiate a MFRC522 reader object.

// OLED
#define OLED_RESET 0  // GPIO0
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

void setup() {
  Serial.begin(9600);        // Initialize serial communications for serial communications over USB
  Serial.println("### COFFE BOX COUNTER ###");
  //SPI.begin();               // Init SPI bus
  //mfrc522.PCD_Init();        // Init MFRC522 card (in case you wonder what PCD means: proximity coupling device)
  //Serial.println("MFRC522 Ready");
  // OLED Setup
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  Serial.println("OLED Screen Ready");
  // Push BTN Setup - Using interrupt to
  attachInterrupt(PUSH_BTN_PIN, btn_pushed, RISING);
  // Buzzer Setup
  //pinMode(BUZZER_PIN, OUTPUT);
}

void btn_pushed(){
  Serial.println("#BUTTON LOW");
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
    

      //Display the table of user with current consuptions

      //3 press

      //Wait for RFID Card with UID 0x0001

        //Display Confirmation "Are you sure / Confirm with button"

          //Confirm button

             //Copy current value to backup

             //Reser current counters
  splash_screen();
  delay(2000);
  display_users_totals();
  delay(3000);
  //Animate Oled Screen with HotCoffee
  coffee_animate();
  delay(50);
}

void display_users_debug(){
  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  for(int i = 0; i<NUM_USERS; i++){
    display.print(users[i].name);
    display.print("    ");
    display.print(users[i].current_total);
    display.print("\n");
  }
  display.display(); 
}

void display_users_totals(){
  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  for(int i = 0; i<NUM_USERS; i++){
    display.print(users[i].name);
    display.print("    ");
    display.print(users[i].current_total);
    display.print("\n");
  }
  display.display();  
}

void createEE(){
  
}

void saveEE(){
  
}

void splash_screen(){
  display.clearDisplay();
 
  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("COFFEEBOX");
  display.println("COUNTER\n");
  display.print("Ver: b");
  display.print(VERS);
  display.display();
}

void coffee_animate(){
  //display.display();
    // Clear the buffer.
  display.clearDisplay();
  
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
