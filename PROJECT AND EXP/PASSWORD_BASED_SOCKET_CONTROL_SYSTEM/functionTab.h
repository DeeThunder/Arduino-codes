char Getkeyvalue(){
  int keys =  customKeypad.getKey();
  esp_task_wdt_reset();
  while (keys ==NO_KEY){
    keys=  customKeypad.getKey();
    //Reset the watchdog timer to prevent a reset
     esp_task_wdt_reset();
  }
  return keys;
}

void useron(){
    int j;
    lcd.setCursor(0,0);
    lcd.scrollDisplayRight();
    lcd.print("ENTER SWITCH ON KEY");
    Serial.println("SWITCH ON KEY");
    for(j=0; j<4; j++)
    {
    passON[j] = Getkeyvalue()  - '0';
    //Reset the watchdog timer to prevent a reset
    esp_task_wdt_reset();
    lcd.setCursor(j+1,1);
    lcd.print(passON[j]);
    Serial.println(passON[j]);
    EEPROM.write(j, passON[j]);
    EEPROM.commit();
    delay(500);
    }
    
    for(j=0;j<4;j++)
    {
      esp_task_wdt_reset();
    passON[j]=EEPROM.read(j);
    Serial.print(EEPROM.read(j));
    }
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("SAVED KEY");
    Serial.println("SAVED KEY");
}

void useroff(){
    int j;
    lcd.setCursor(0,0);
    lcd.scrollDisplayRight();
    lcd.print("ENTER SWITCH OFF KEY");
    Serial.println("SWITCH OFF KEY");
    for(j=0; j<4; j++)
    {
    passOFF[j] = Getkeyvalue()  - '0';
    //Reset the watchdog timer to prevent a reset
    esp_task_wdt_reset();
    lcd.setCursor(j+1,1);
    lcd.print(passOFF[j]);
    Serial.println(passOFF[j]);
    EEPROM.write(8+j, passOFF[j]);
    EEPROM.commit();
    delay(500);
    }
    bool passok3=confirm2(0,passOFF);
    if (passok3){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.scrollDisplayRight();
      lcd.print("SAME PASSWORD");
      delay(500);
      lcd.clear();
    useroff();
    }
    else {
      for(j=8;j<12;j++)
    {
      esp_task_wdt_reset();
    passOFF[j]=EEPROM.read(j);
    Serial.print(EEPROM.read(j));
    }
      lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("SAVED KEY");
    Serial.println("SAVED KEY");
     }
}


void onswitch(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SWITCH ON");
  Serial.print("switch on");
  
    digitalWrite(2, LOW);
}

void offswitch(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SWITCH OFF");
  Serial.print("switch off");
    digitalWrite(2,HIGH);
}

void passkeyy(){
    int j;
    for(j=0; j<4; j++)
    {
    passkey[j] = Getkeyvalue()  - '0';
    //Reset the watchdog timer to prevent a reset
    esp_task_wdt_reset();
    lcd.setCursor(j,1);
    lcd.print("*");
    Serial.println(passkey[j]);
    }
    bool passok1=confirm(0,passkey);
    bool passok2=confirm(8,passkey);
    if (passok1){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("SWITCH ON");
      onswitch();
    }
     else if (passok2){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("SWITCH OFF");
      offswitch();
     }
     else{
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("WRONG PASSWORD");
     }
}
    

bool confirm( int startAddress,int passkey[4]){
  for( int j=0;j<4; j++){
    if (EEPROM.read (j + startAddress)!=passkey[j])
      {
        return false;
      }
  }
    return true;
  }
  
  bool confirm2( int startAddress,int passOFF[4]){
  for( int j=0;j<4; j++){
    if (EEPROM.read (j + startAddress)!=passOFF[j])
      {
        return false;
      }
  }
    return true;
  }
