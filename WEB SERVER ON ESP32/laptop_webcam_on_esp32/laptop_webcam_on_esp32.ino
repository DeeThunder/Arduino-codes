#include <WiFi.h>
#include <WebServer.h>

// WiFi Credentials
const char* ssid = "DeeThunder";
const char* password = "Deetunda@20";

// Laptop Webcam Stream URL (Change IP to your laptop's)
const char* webcamURL = "http://192.168.50.238:8080/?action=stream";

// ESP32 Web Server
WebServer server(80);

void handleRoot()
{
    String page = "<html><body><h2>ESP32 Live Webcam Stream</h2>";
    page += "<img src='" + String(webcamURL) + "' width='640' height='480'/>";
    page += "<p>Streaming from Laptop Webcam</p>";
    page += "</body></html>";
    server.send(200, "text/html", page);
}

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println("\nConnected!");

    server.on("/", handleRoot);
    server.begin();
    Serial.println("ESP32 Web Server Started.");
}

void loop()
{
    server.handleClient();
}
