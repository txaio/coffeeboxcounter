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
void coffee_animate1();
void coffee_animate2();
void coffee_animate3();
void coffee_animate4();
void coffee_animate5();
void display_users_debug();
void display_users_totals();
void step_counter(int& cnt, int steps, bool& re, void (*function_s)());

// Counters
int anim1_cnt = 0;
int anim2_cnt = 0;
int anim3_cnt = 0;
int anim4_cnt = 0;
int anim5_cnt = 0;
int anim6_cnt = 0;
int anim7_cnt = 0;
bool reloop1, reloop2, reloop3, reloop4, reloop5, reloop6, reloop7 = true;
#define STEP 50

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
  Serial.println("#BUTTON PUSHED INTERRUPT");
  display_users_debug();
  delay(1000);
}

void loop() {
   //Serial.println("#LOOPING#");
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
  step_counter(anim1_cnt, 700, reloop1, splash_screen);
  if(reloop1){return;}
  
  //display_users_totals();
  step_counter(anim2_cnt, 800, reloop2, display_users_totals);
  if(reloop2){return;}
  //delay(3000);
  //Animate Oled Screen with HotCoffee
  step_counter(anim3_cnt, 400, reloop3, coffee_animate1);
  if(reloop3){return;}
  step_counter(anim4_cnt, 400, reloop4, coffee_animate2);
  if(reloop4){return;}
  step_counter(anim5_cnt, 400, reloop5, coffee_animate3);
  if(reloop5){return;}
  step_counter(anim6_cnt, 400, reloop6, coffee_animate4);
  if(reloop6){return;}
  step_counter(anim7_cnt, 400, reloop7, coffee_animate5);
  if(reloop7){return;}
  delay(STEP);
  
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
    for(int y = 0; y<4; y++){
      display.print(users[i].uid[y],HEX);
    }
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

void step_counter(int& cnt, int steps, bool& re, void (*function_s)()){
	if(!re){return;}
	if(cnt < steps){
		(*function_s)();
		cnt++;
    re = true;
    Serial.print("COUNTER ");
    Serial.println(cnt);
	} else {
    re = false;
		cnt = 0;
	}
  
}

void coffee_animate1(){
    display.clearDisplay();
    display.drawBitmap(0, 0, anim01, 64, 48, WHITE);
    display.display();
}
void coffee_animate2(){
    display.clearDisplay();
    display.drawBitmap(0, 0, anim02, 64, 48, WHITE);
    display.display();
}
void coffee_animate3(){
    display.clearDisplay();
    display.drawBitmap(0, 0, anim03, 64, 48, WHITE);
    display.display();
}
void coffee_animate4(){
    display.clearDisplay();
    display.drawBitmap(0, 0, anim04, 64, 48, WHITE);
    display.display();
}
void coffee_animate5(){
    display.clearDisplay();
    display.drawBitmap(0, 0, anim05, 64, 48, WHITE);
    display.display();
}
