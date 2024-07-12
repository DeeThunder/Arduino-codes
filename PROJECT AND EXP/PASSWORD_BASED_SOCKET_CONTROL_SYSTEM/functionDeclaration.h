#include <Keypad.h>
#include<EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <esp_task_wdt.h>



LiquidCrystal_I2C lcd(0x27, 16, 2);
int j;
int passON[8];
int passOFF[8];
int passkey[8];
int keyss;

#define EEPROM_SIZE 20

const byte ROWS = 4; /* four rows */
const byte COLS = 4; /* four columns */
/* define the symbols on the buttons of the keypads */
char hexaKeys[ROWS][COLS] = {
 {'1', '4', '7', '*'},
 {'2', '5', '8', '0'},
 {'3', '6', '9', '#'},
 {'A', 'B', 'C', 'D'}
};

byte rowPins[ROWS] = {14,27,26,25}; /* connect to the row pinouts of the keypad */
byte colPins[COLS] = {33,32,19,23};
/* initialize an instance of class NewKeypad */
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

extern char Getkeyvalue();
extern void useron();
extern void useroff();
extern void onswitch();
extern void offswitch();
extern void passkeyy();
extern bool confirm( int startAddress,int passkey[8]);
extern bool confirm2( int startAddress,int passOFF[8]);
