#include "functionDeclaration.h"  
#include "functionTab.h"
 
void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  if (!EEPROM.begin (EEPROM_SIZE))
  {
  Serial.println(" EEPROM failed");
  }
delay(1000);
lcd.init();
lcd.backlight();
if (digitalRead(2)== LOW){
  digitalWrite(2,HIGH);
}
else{
  digitalWrite(2,HIGH);
}
lcd.clear();
lcd.setCursor(0,0);
lcd.print("*=SWITCH  PASSKEY");
lcd.setCursor(0,1);
lcd.print("PRESS ANY KEY TO CONTINUE");
Serial.println("*= SWITCH PASSKEY");
keyss = Getkeyvalue();
//Reset the watchdog timer to prevent a reset
esp_task_wdt_reset();
Serial.print(keyss);
if (keyss == '*'){
    //Reset the watchdog timer to prevent a reset
    esp_task_wdt_reset();
    lcd.clear();
    useron();
    esp_task_wdt_reset();
    lcd.clear();
    useroff();
    esp_task_wdt_reset();
    delay(1000);
}
  else {
    lcd.setCursor(0,1);
    lcd.print("SWITCH SET");
  Serial.println("SWITCH SET");
}
  
}

void loop()
{
//  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SMART SOCKET");
  Serial.println("WELCOME HOME");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ENTER PASSKEY");
  Serial.println("ENTER PASSKEY");
  passkeyy();
  esp_task_wdt_reset();
delay(2000);

}
