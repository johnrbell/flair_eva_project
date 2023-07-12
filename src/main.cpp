#include <Arduino.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <wifi_creds.h>   // Include WiFi Creds -> src/wifi_creds.h

// ----------------------------------------------------------------------------
// Helpers
// ----------------------------------------------------------------------------

// Web Server & Socket Setup
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// SPIFFS Setup
void initSPIFFS() {
  if (!SPIFFS.begin()) {
    Serial.println("Error mounting SPIFFS volume.");
  }else{
    Serial.println("Mounted SPIFFS volume successfully.");
  }
}

// WiFI Setup
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

// Rendering Template "Engine"
String processor(const String &var) {
    return String("testing");
}

// Request Root Handler
void onRootRequest(AsyncWebServerRequest *request) {
  Serial.println("/index requested.");
  request->send(SPIFFS, "/index.html", "text/html", false, processor);
}

// Server Init/Routing
void initWebServer() {
  server.on("/", onRootRequest);

  // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  //     Serial.println("TESTING.");
  //     request->send(200, "text/plain", "Hello World");
  // });

  server.serveStatic("/", SPIFFS, "/");
  server.begin();
}

// WebSocket Event Handler
void onEvent(AsyncWebSocket       *server,
             AsyncWebSocketClient *client,
             AwsEventType          type,
             void                 *arg,
             uint8_t              *data,
             size_t                len) 
{
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

// WebSocket Init
void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

// ----------------------------------------------------------------------------
// Sending Data to WebSocket Clients
// ----------------------------------------------------------------------------
void notifyClients() {
    ws.textAll("led blinked.");
    // ws.textAll(led.on ? "on" : "off");
}

// ----------------------------------------------------------------------------
// Main Sketch
// ----------------------------------------------------------------------------
void setup() {
  pinMode(32, OUTPUT);
  
  Serial.begin(115200); delay(500);
  Serial.println("welcome to flavortown.");

  initSPIFFS();
  initWiFi();
  delay(1000);
  initWebSocket();
  initWebServer();
}

void loop() {
  ws.cleanupClients();
  
  digitalWrite(32, HIGH);
  delay(1000);
  digitalWrite(32, LOW);
  delay(500);
  notifyClients();   
}