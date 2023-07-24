#include <Arduino.h>
#include <SPIFFS.h>
#include <WiFi.h>
// #include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <wifi_creds.h>   // Include WiFi Creds -> src/wifi_creds.h

#define LED_PIN 32
#define BTN_PIN 22

const uint8_t DEBOUNCE_DELAY = 10;

// ----------------------------------------------------------------------------
// Define Led
// ----------------------------------------------------------------------------
struct Led {
    uint8_t pin;
    bool    on;

    void update() {
        digitalWrite(pin, on ? HIGH : LOW);
    }
};

// ----------------------------------------------------------------------------
// Define Button
// ----------------------------------------------------------------------------
struct Button {
    uint8_t  pin;
    bool     lastReading;
    uint32_t lastDebounceTime;
    uint16_t state;

    // methods determining the logical state of the button
    bool pressed()                { return state == 1; }
    bool released()               { return state == 0xffff; }
    bool held(uint16_t count = 0) { return state > 1 + count && state < 0xffff; }

    // method for reading the physical state of the button
    void read() {
        // reads the voltage on the pin connected to the button
        bool reading = digitalRead(pin);

        // if the logic level has changed since the last reading...
        // we reset the timer which counts down the necessary time
        // beyond which we can consider that the bouncing effect
        // has passed.
        if (reading != lastReading) {
            lastDebounceTime = millis();
        }

        // from the moment we're out of the bouncing phase...
        // the actual status of the button can be determined
        if (millis() - lastDebounceTime > DEBOUNCE_DELAY) {
            // don't forget that the read pin is pulled-up
            bool pressed = reading == LOW;
            if (pressed) {
                if (state  < 0xfffe) state++;
                else if (state == 0xfffe) state = 2;
            } else if (state) {
                state = state == 0xffff ? 0 : 0xffff;
            }
        }

        // finally, each new reading is saved
        lastReading = reading;
    }
};

// ----------------------------------------------------------------------------
// WebServer/Socket Helpers 
// ----------------------------------------------------------------------------
Led led =       {LED_PIN, false};
Button button = {BTN_PIN, HIGH, 0, 0};

// ----------------------------------------------------------------------------
// WebServer/Socket Helpers 
// ----------------------------------------------------------------------------
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

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
    // return String("testing");
    return String(var == "STATE" && led.on ? "on" : "off");
}

// SPIFFS Filesystem Setup
void initSPIFFS() {
  if (!SPIFFS.begin()) {
    Serial.println("Error mounting SPIFFS volume.");
  }else{
    Serial.println("Mounted SPIFFS volume successfully.");
  }
}

// Request: Root Handler
void onRootRequest(AsyncWebServerRequest *request) {
  Serial.println("/index.html requested.");
  request->send(SPIFFS, "/index.html", "text/html", false, processor);
}

// Server Init/Routing
void initWebServer() {
  server.on("/", onRootRequest);
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
  // pinMode(32, OUTPUT);
  pinMode(led.pin,    OUTPUT);
  pinMode(button.pin, INPUT);
  
  Serial.begin(115200); delay(1000);
  Serial.println("welcome to flavortown. 🌭");
  Serial.println("did you update the filesystem?");

  initSPIFFS();
  initWiFi();
  // delay(1000);
  initWebSocket();
  initWebServer();
}

void loop() {
  ws.cleanupClients();
    
  button.read();
  if (button.pressed()) led.on = !led.on;
  
  led.update();

  // digitalWrite(32, HIGH);
  // delay(1000);
  // digitalWrite(32, LOW);
  // delay(500);
  // notifyClients();   
}