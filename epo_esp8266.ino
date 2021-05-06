#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;
unsigned long delayTime;
const char* ssid = "ESP8266";
const char* password = "12345678";
IPAddress local_ip(10,0,0,1);
IPAddress gateway(10,0,0,1);
IPAddress subnet(255,255,255,0);
ESP8266WebServer server(80);

void setup() {  
   Serial.begin(9600);
   bool status;  
  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Senzor nebyl nalezen");
    while (1);
  }
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  server.on("/", handle_index);
  server.on("/data", handle_data);
  server.onNotFound(handle_notfound);
  server.begin();
  Serial.println("Server spusten");
}

void loop() {
  server.handleClient();
}

void handle_index(){
  String data = "<!DOCTYPE html><html><head><meta charset='utf-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><title>Počasí</title><meta name='viewport' content='width=device-width, initial-scale=1'><style>body{text-align: center;}</style></head><body><h1>Teplota</h1><div id=\"teplota\"></div><h1>Vlhkost</h1><div id=\"vlhkost\"></div><h1>Tlak</h1><div id=\"tlak\"></div><script>function loadData(){var xhttp = new XMLHttpRequest();xhttp.onreadystatechange=function(){if(this.readyState==4&&this.status==200){let text = this.responseText.split(\"#\");document.getElementById(\"teplota\").innerHTML = text[0] + \" °C\";document.getElementById(\"tlak\").innerHTML = Math.round(text[1]/100,2) + \" hPa\";document.getElementById(\"vlhkost\").innerHTML = text[2] + \" %\";}};xhttp.open(\"GET\", \"data\", true);xhttp.send();}loadData();setInterval(loadData, 1000)</script></body></html>";
  server.send(200, "text/html", data);
}

void handle_data(){ 
  String data = "<html>";
  data+= bme.readTemperature();
  data += "#";
  data += bme.readPressure();
  data += "#"; 
  data += bme.readHumidity();
  data += "</html>";
  server.send(200, "text/html", data);
}

void handle_notfound(){
  server.send(404, "text/plain", "Not found");
}
