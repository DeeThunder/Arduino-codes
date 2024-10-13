#include <WiFi.h>
#include <WebServer.h>

// green vcc, blue gnd, black signal

const char* ssid = "APITech";
const char* password = "@ApiTech";

IPAddress local_IP(192,168,0,215);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
IPAddress primaryDNS(8,8,8,8);
IPAddress secondaryDNS(8,8,4,4);

WebServer server(80);

const char* htmlPage =
"<!DOCTYPE html>"
"<html lang='en'>"
"<head>"
"    <meta charset=\"UTF-8\">"
"    <meta name='viewport' content=\"width=device-width, initial-scale=1.0\">"
"    <title>Relay Module on Webserver</title>"
"    <style>"
"        body{background-color: #ffd232; font-family: serif;}"
"        h1{color: black;}"
"        .container{ font-size: 16px; text-align: center; margin-top: 50px;}"
"        .button{background-color: grey;color: blue;font-size: 16px; padding: 10px 20px; }"
"    </style>"
"</head>"
"<body>"
"    <div  class='container'>"
"        <h1>Online Socket</h1>"
"       <p>This is a soket powered using a relay module on the esp32 and controlled on a webpage</p>"
"    <button class='button' onclick=\"window.location.href='/gpio/off'\"> ON </button>"
"    <button class='button' onclick=\"window.location.href='/gpio/on'\"> OFF </button>"
"    </div>"
"</body>"
"</html>"
;

void setup(){
  
  Serial.begin(115200);
  pinMode(25, OUTPUT);

if(!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)){
  Serial.println("STA failed to configure");
}
  //initalize wifi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to APITech...");
  }

   Serial.println("Connected to APITech");
  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());  //Debugging line to check IP

  server.on("/", []() {
    server.send(200, "text/html", htmlPage);
  });

  server.on("/gpio/off", []() {
    
    digitalWrite(25, LOW);
    server.send(200, "text/html", htmlPage);
    Serial.println("Switch ON");
  });

  server.on("/gpio/on", []() {
    
    digitalWrite(25, HIGH);
    server.send(200, "text/html", htmlPage);
    Serial.println("Switch OFF");
  });

  server.begin();
  Serial.println("Server Started");
}

void loop(){
  server.handleClient();
}