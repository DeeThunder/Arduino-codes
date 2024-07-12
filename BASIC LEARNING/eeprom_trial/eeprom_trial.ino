#include<EEPROM.h>
#include<Keypad.h>

const byte ROWS =4;
const byte COLS =4;

char mykeys [ROWS][COLS]=
{
 {'1', '2', '3', 'A'},
 {'4', '5', '6', 'B'},
 {'7', '8', '9', 'C'},
 {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {19,18,5,17}; 
byte colPins[COLS] = {13,14,15,16}; 

Keypad customKeypad = Keypad (makeKeymap(mykeys), rowPins, colPins, ROWS, COLS);

#define EEPROM_SIZE 5

int password[5]={0,1,2,3,4};

int Getkeyvalue(){
  int key = customKeypad.getKey();
  while (key ==NO_KEY){
    key= customKeypad.getKey();
  }
  return key;
}

void savedEEPROM(int data, int address)
{
  EEPROM.write(address, data);
  EEPROM.commit();
}

int readEEPROM(int address){
  return EEPROM.read(address);
  }
void setup(){
  delay(1000);
  Serial.begin(9600);
  if (!EEPROM.begin (EEPROM_SIZE))
  {
  Serial.println(" EEPROM failed");
  }
}

void loop()
{
   for(int i=0; i<5; i++){
    password[i]=Getkeyvalue()  - '0';
    Serial.print("Keypad Pressed = ");
    Serial.println(password[i]);
   savedEEPROM(password[i],i);
   Serial.print("Read Value from EEPROM = ");
   Serial.println(readEEPROM(i));
   }

   
}
