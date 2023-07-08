#include <Arduino.h>
#include <SPIFFS.h>
#include <WiFi.h>
// #include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// SPIFFS initialization
void initSPIFFS() {
  if (!SPIFFS.begin()) {
    Serial.println("Error mounting SPIFFS volume.");
  }else{
    Serial.println("Mounted SPIFFS volume successfully.");
  }
}

// WiFi credentials & init
const char *WIFI_SSID = "Fios-mVd9B";
const char *WIFI_PASS = "had43oasis28jet";

void initWiFi() {
  Serial.println("WTF");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.println("WTF2");
  Serial.printf("Trying to connect [%s] ", WiFi.macAddress().c_str());
  Serial.println("WTF3");
  while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
  }
  Serial.println("WTF4");
  Serial.printf(" %s\n", WiFi.localIP().toString().c_str());
}

// Web Server Setup
AsyncWebServer server(80);

// Web Server Initilization
String processor(const String &var) {
    return String("testing");
}

void onRootRequest(AsyncWebServerRequest *request) {
  Serial.println("/index requested.");
  request->send(SPIFFS, "/index.html", "text/html", false, processor);
}

void initWebServer() {
    server.on("/", onRootRequest);

//     server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
//         Serial.println("TESTING.");
//         request->send(200, "text/plain", "Hello World");
//     });

    server.serveStatic("/", SPIFFS, "/");
    server.begin();
}


// Sketch Functions
void setup() {
  pinMode(32, OUTPUT);
  
  Serial.begin(115200); delay(500);
  Serial.println("Started.");

  initSPIFFS();
  initWiFi();
  delay(5000);
  initWebServer();
}
void loop() {
  digitalWrite(32, HIGH);
  delay(1000);
  digitalWrite(32, LOW);
  delay(500);
}
