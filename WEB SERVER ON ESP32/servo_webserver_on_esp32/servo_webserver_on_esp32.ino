#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const char* ssid = "APITech";
const char* password = "@ApiTech";

// Static IP settings
IPAddress local_IP(192, 168, 0, 215);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

WebServer server(80);

Servo myServo;    // Create a Servo object
int servoPin = 13;  // Define the GPIO pin for the servo motor
int currentAngle = 90; // Servo starts at 90 degrees (middle position)

void setup() {
  Serial.begin(115200);

  // Attach the servo motor to the GPIO pin
  myServo.attach(servoPin);
  myServo.write(currentAngle);  // Initialize servo to 90 degrees

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

  // Serve the main webpage
  server.on("/", []() {
    String htmlPage = 
    "<!DOCTYPE html>"
    "<html>"
    "<head>"
    "  <title>ESP32 Servo Control</title>"
    "  <style>"
    "    body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; color: blue;}"
    "    .button { padding: 10px 20px; font-size: 16px; margin: 5px; color:orange; }"
    "  </style>"
    "</head>"
    "<body>"
    "  <h1>Servo Motor Control</h1>"
    "  <button class='button' onclick=\"window.location.href='/servo/up'\">Move Up</button>"
    "  <button class='button' onclick=\"window.location.href='/servo/down'\">Move Down</button>"
    "</body>"
    "</html>";

    server.send(200, "text/html", htmlPage);
  });

  // Handle the /servo/up endpoint to increase the angle
  server.on("/servo/up", []() {
    currentAngle += 10;
    if (currentAngle > 180) currentAngle = 180;  // Limit to 180 degrees
    myServo.write(currentAngle);
    server.send(200, "text/html", "<h1>Servo moved up to " + String(currentAngle) + " degrees</h1><a href='/'>Go Back</a>");
    Serial.println("Servo moved up to: " + String(currentAngle) + " degrees");
  });

  // Handle the /servo/down endpoint to decrease the angle
  server.on("/servo/down", []() {
    currentAngle -= 10;
    if (currentAngle < 0) currentAngle = 0;  // Limit to 0 degrees
    myServo.write(currentAngle);
    server.send(200, "text/html", "<h1>Servo moved down to " + String(currentAngle) + " degrees</h1><a href='/'>Go Back</a>");
    Serial.println("Servo moved down to: " + String(currentAngle) + " degrees");
  });

  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}
