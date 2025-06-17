#include <TinyGPSPlus.h> // Library for parsing GPS data

// Define the ESP32 pins connected to the GPS module
// ESP32 has multiple hardware serial ports (UARTs).
// Using Serial1 or Serial2 is recommended for peripherals as Serial0 is used for USB communication.
// For example, using Serial1:
#define GPS_RX_PIN 16 // ESP32 pin connected to GPS module's TX (data output)
#define GPS_TX_PIN 17 // ESP32 pin connected to GPS module's RX (data input)

// Initialize the TinyGPSPlus object for processing GPS data.
TinyGPSPlus gps;

void setup() {
  // Start the main hardware serial communication for debugging output to the Serial Monitor.
  // This is typically Serial0 on ESP32, which connects to the USB port.
  Serial.begin(115200);

  // Start the hardware serial communication for the GPS module.
  // We're using Serial1 here. The baud rate for most GPS modules is 9600.
  // The `begin()` function takes baud rate, SERIAL_8N1 (8 data bits, no parity, 1 stop bit), RX_pin, TX_pin.
  Serial1.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);

  Serial.println("--- ESP32 GPS Reader Initializing ---");
  delay(1000); // Give the GPS module a moment to power up
  Serial.println("Waiting for GPS data...");
}

void loop() {
  // Process incoming data from the GPS module
  // This loop continuously reads characters from the GPS serial (Serial1)
  // and feeds them to TinyGPSPlus for parsing.
  while (Serial1.available() > 0) {
    // If gps.encode() successfully processes a complete NMEA sentence, it returns true.
    if (gps.encode(Serial1.read())) {
      // A new NMEA sentence has been successfully encoded by TinyGPSPlus.
      // Now, we can check for updated and valid GPS data.
      if (gps.location.isValid()) { // Check if the GPS has a valid fix
        if (gps.location.isUpdated()) { // Check if the location data has been updated
          Serial.println("--- GPS Data Acquired ---");
          // Print Latitude and Longitude to Serial Monitor
          Serial.print("Latitude: ");
          // gps.location.lat() returns a double, print with 6 decimal places for precision
          Serial.println(gps.location.lat(), 6);
          Serial.print("Longitude: ");
          // gps.location.lng() returns a double, print with 6 decimal places for precision
          Serial.println(gps.location.lng(), 6);

          // You can add more GPS data printing here if needed, e.g.:
          // if (gps.altitude.isValid()) {
          //   Serial.print("Altitude: "); Serial.println(gps.altitude.meters());
          // }
          // if (gps.satellites.isValid()) {
          //   Serial.print("Satellites: "); Serial.println(gps.satellites.value());
          // }
          // if (gps.speed.isValid()) {
          //   Serial.print("Speed (km/h): "); Serial.println(gps.speed.kmph());
          // }
          Serial.println("-------------------------");
        }
      } else {
        // If location is not valid, it means the GPS hasn't gotten a fix yet.
        Serial.println("No valid GPS fix yet. Waiting...");
      }
    }
  }

  // If no new GPS data is available from the serial buffer,
  // we still want to keep the loop running and checking.
  // A small delay here can prevent the ESP32 from hogging resources unnecessarily,
  // but be careful not to make it too long or you might miss GPS data.
  delay(10);
}