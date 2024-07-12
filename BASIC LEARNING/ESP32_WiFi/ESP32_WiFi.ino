
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL25WPr7Hxp"
#define BLYNK_TEMPLATE_NAME "LED ESP32"
#define BLYNK_AUTH_TOKEN "chjysrKI55H0lFCCDHR60qo83IYA6xYE"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "DeeThunder";
char pass[] = "Deetunda15";


BLYNK_WRITE(V0)
{
  int value = param.asInt();

  if (value == 1) {
    digitalWrite(2, HIGH);
    Serial.print("value =");
    Serial.println(value);
  } else {
    digitalWrite(2, LOW);
    Serial.print("value = ");
    Serial.println(value);
  }
}
BLYNK_WRITE(V1)
{
  int value = param.asInt();

  if (value == 1) {
    digitalWrite(13, HIGH);
    Serial.print("value =");
    Serial.println(value);
  } else {
    digitalWrite(13, LOW);
    Serial.print("value = ");
    Serial.println(value);
  }
}

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);
  // Debug console
  Serial.begin(9600);
  delay(100);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();
  delay(10);
  
}
