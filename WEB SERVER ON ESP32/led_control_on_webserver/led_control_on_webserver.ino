#include <WiFi.h>
#include <WebServer.h>
// #include <WiFiNINA.h>

const char* ssid = "Your-SSID";
const char* password = "Your-Password";

IPAddress local_IP(192,168,0,215);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
IPAddress primaryDNS(8,8,8,8);
IPAddress secondaryDNS(8,8,4,4);

WebServer server(80);

const char* htmlPage =
"<!DOCTYPE html>"
"<html>"
"<head>"
"  <title>ESP32 Webpage</title>"
"  <style>"
"    body { font-family: Arial, sans-serif; justify-content: center; align-items: center;}"
"    h1{color: #333; font-size: 24px; padding-top: 5px; }"
"    .container {  justify-content: center; align-content: center; background-color: #ffcc66; width: 300px;height: 200px; text-align: center; margin-top: 10px; border-radius: 10px;}"
"    button { background-color: #fda45f; color: #fff;  width: fit-content;padding: 10px 20px; font-size: 16px; }"
"  </style>"
"</head>"
"<body>"
"  <div class='container'>"
"    <h1>Welcome to ESP32 Webpage</h1>"
"    <button class='button' onclick=\"window.location.href='/gpio/on'\"> ON </button>"
"    <button class='button' onclick=\"window.location.href='/gpio/off'\"> OFF </button>"
" </div>"
"</body>"
"</html>"
;
void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT); // setup GPIO pin2 as an output

if(!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)){
  Serial.println("STA failed to configure");
}
  //initalize wifi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());  //Debugging line to check IP

  server.on("/", []() {
    server.send(200, "text/html", htmlPage);
  });

  server.on("/gpio/on", [](){
    digitalWrite(2,HIGH);
    server.send(200, "text/html", "<h1> GPIO 2 is ON </h1><a href='/'> Go Back </a>");
    Serial.println("GPIO 2 turned ON");
  });

  server.on("/gpio/off", [](){
    digitalWrite(2,LOW);
    server.send(200, "text/html", "<h1> GPIO 2 is OFF </h1><a href='/'> Go Back </a>");
    Serial.println("GPIO 2 turned OFF");
  });


  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}
