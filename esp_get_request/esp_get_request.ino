#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

 
const char* ssid = "EponWifi";
const char* password = "afsal123";
 
void setup () {
 
  Serial.begin(115200);
   pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
  WiFi.begin(ssid, password);
 Serial.println("Going to connect");
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.println("Connecting..");
 
  }
  Serial.println("Connected successfully");
 
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
    Serial.println("Wifi connection status is true");
    http.begin("http://django-smart-home-server.herokuapp.com/api/device/testdevice/");  //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
    Serial.print("Http code is: ");
    Serial.print(httpCode);
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
      const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(payload);
//      const char* name/_obj = root["data"]["status"];
      //Serial.println(typeid(name_obj).name())
      //Serial.println(name_obj);
//      Stri/ng a = *name_obj;
bool name_obj = root["data"]["status"];
      Serial.println(name_obj);
      if(name_obj ==true){
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(4, HIGH);
        }
        else{
          digitalWrite(LED_BUILTIN, HIGH);
          digitalWrite(4, LOW);
          }
 
    }
 
    http.end();   //Close connection
 
  }
 
  delay(1000);    //Send a request every 30 seconds
 
}
