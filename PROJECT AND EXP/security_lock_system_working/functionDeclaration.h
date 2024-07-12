#include <Keypad.h>
#include<EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include <esp_task_wdt.h>

Servo myservo;
int pos = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);
int j;
int password[8];
int user1[8];
int user2[8];
int user3[8];
int user4[8];
int passkey[8];
int keyss;

#define EEPROM_SIZE 100

const byte rows = 4; 
const byte columns = 4; 
char hexaKeys[rows][columns] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
byte row_pins[rows] = {16,15,14,13};  
byte column_pins[columns]= {17,5,18,19}; 
Keypad keypad_key=Keypad( makeKeymap(hexaKeys),row_pins,column_pins,rows,columns);


extern char Getkeyvalue();
extern void admin();
extern void userA();
extern void userB();
extern void userC();
extern void userD();
extern int setuser();
extern void opendoor();
extern void closedoor();
extern void passkeyy();
extern bool confirm( int startAddress,int passkey[8]);
