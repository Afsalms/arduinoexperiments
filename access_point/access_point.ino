#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

const char *ssid = "ITEAD-1000000000";
const char *password = "12345678";

ESP8266WebServer server(80);
IPAddress    apIP(10, 10, 7, 1);

void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}

void deviceDetails() {
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["deviceid"] = "1000000000";
  root["apikey"] = "xxxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx";
  root["accept"] = "post";
  String json;
  root.prettyPrintTo(json);
  server.send(200, "application/json" , json);
}

void postDetails(){
  
  Serial.println(server.arg("plain"));
  server.send(200, "text/html", "<h1>Success </h1>") ; 
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/device", deviceDetails);
  server.on("/ap", postDetails);
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
