#include <Arduino.h>
#include <SPIFFS.h>
#include <WiFi.h>

// WiFi credentials
const char *WIFI_SSID = "test_network";
const char *WIFI_PASS = "espresso";
  
// put function declarations here:
// int myFunction(int, int);

// ----------------------------------------------------------------------------
// SPIFFS initialization
// ----------------------------------------------------------------------------
void initSPIFFS() {
  if (!SPIFFS.begin()) {
    Serial.println("Cannot mount SPIFFS volume...");
    // while(1) digitalWrite(LED_BUILTIN, millis() % 200 < 50 ? HIGH : LOW);
  }
}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.printf("Trying to connect [%s] ", WiFi.macAddress().c_str());
  while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
  }
  Serial.printf(" %s\n", WiFi.localIP().toString().c_str());
}

void setup() {
  // put your setup code here, to run once:
  // int result = myFunction(2, 3);
  pinMode(32, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Started.");

  initSPIFFS();
  initWiFi();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(32, HIGH);
  delay(1000);
  digitalWrite(32, LOW);
  delay(500);
}

// put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }