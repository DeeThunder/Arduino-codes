#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile


RH_ASK rf_driver(2000,21, 22);


void setup()
{
    delay(3000);
    Serial.begin(9600);  // Debugging only
    Serial.println(" message receiving");
    if (!rf_driver.init())
        Serial.println("init failed");
}

void loop()
{
    uint8_t buf[12]={0};
    uint8_t buflen = sizeof(buf);
    if (rf_driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;
      // Message with a good checksum received, dump it.
      Serial.print("Message: ");
      Serial.println((char*)buf);       
    }
}
