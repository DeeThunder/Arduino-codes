#include "functionDeclaration.h"  
#include "functionTab.h"
 
void setup()
{
  Serial.begin(9600);
  myservo.attach(25);
  if (!EEPROM.begin (EEPROM_SIZE))
  {
  Serial.println(" EEPROM failed");
  }
lcd.init();
lcd.backlight();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("SET ADMIN");
Serial.println("SET ADMIN");
admin();
delay(1000);
lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("1= SET USER PASSKEY");
  Serial.println("1= SET USER PASSKEY");
keyss = Getkeyvalue();
//Reset the watchdog timer to prevent a reset
esp_task_wdt_reset();
if (keyss == '1'){
  
  //Reset the watchdog timer to prevent a reset
  esp_task_wdt_reset();
  setuser();
  esp_task_wdt_reset();
  delay(1000);
}
  else {
    lcd.setCursor(0,1);
    lcd.print("USER SET");
  Serial.println("USER SET");
}
  
}

void loop()
{
//  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WELCOME HOME");
  Serial.println("WELCOME HOME");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ENTER PASSKEY");
  Serial.println("ENTER PASSKEY");
  passkeyy();

delay(2000);

}
