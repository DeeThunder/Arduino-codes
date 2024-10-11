#include <WiFi.h>
#include <WebServer.h>
#include <HCSR04.h>

const char* ssid = "your ssid";
const char* password = "your password";

// Static IP settings
IPAddress local_IP(192, 168, 0, 215);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

WebServer server(80);

// Ultrasonic sensor pins
const int trigPin = 5;  // Trigger pin for the sensor
const int echoPin = 18;  // Echo pin for the sensor

// Function to get the distance from the ultrasonic sensor
long getDistance() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Trigger the sensor by setting the trigPin high for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the time it takes for the pulse to return
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance (in cm) based on the time duration
  long distance = duration * 0.034 / 2; // Speed of sound wave divided by 2

  return distance;
}

void setup() {
  Serial.begin(115200);

  // Set up the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Configure static IP
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA failed to configure");
  }

  // Initialize WiFi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());

  // Serve the main webpage with the sensor data
  server.on("/", []() {
    String htmlPage = 
    "<!DOCTYPE html>"
    "<html>"
    "<head>"
    "  <title>ESP32 Ultrasonic Sensor</title>"
    "  <style>"
    "    body { font-family: Arial, sans-serif; }"
    "    .container { text-align: center; margin-top: 50px; }"
    "  </style>"
    "  <script>"
    "    function getData() {"
    "      fetch('/distance').then(response => response.text()).then(data => {"
    "        document.getElementById('distance').innerHTML = data + ' cm';"
    "      });"
    "    }"
    "    setInterval(getData, 1000); // Update every 1 second"
    "  </script>"
    "</head>"
    "<body>"
    "  <div class='container'>"
    "    <h1>ESP32 Ultrasonic Sensor</h1>"
    "    <p>Distance: <span id='distance'>Loading...</span></p>"  // Placeholder for dynamic data
    "  </div>"
    "</body>"
    "</html>";
    
    server.send(200, "text/html", htmlPage);
  });

  // Handle the /distance endpoint to send sensor data
  server.on("/distance", []() {
    long distance = getDistance(); // Get the ultrasonic sensor reading
    server.send(200, "text/plain", String(distance));  // Send distance as plain text
    Serial.println(distance);
  });

  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}
