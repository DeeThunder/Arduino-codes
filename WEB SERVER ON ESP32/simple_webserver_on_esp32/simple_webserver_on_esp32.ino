#include <WiFi.h>

#include <WebServer.h>



const char* ssid = "your ssid";

const char* password = "your password";



WebServer server(80);



const char* htmlPage =

"<!DOCTYPE html>"

"<html>"

"<head>"

"  <title>ESP32 Webpage</title>"

"  <​style>"

"    body { font-family: Arial, sans-serif; }"

"    .container { text-align: center; margin-top: 50px; }"

"    .button { padding: 10px 20px; font-size: 16px; }"

"  <​/style>"

"</head>"

"<body>"

"  <div class='container'>"

"    <h1>Welcome to ESP32 Webpage</h1>"

"    <button class='button' onclick​='alert(\"Button clicked!\")'>Click Me</button>"

" </div>"

"</body>"

"</html>"

;

void setup() {

  Serial.begin(115200);

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



  server.begin();

  Serial.println("Server started");

}



void loop() {

  server.handleClient();

}

