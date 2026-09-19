#include "src/comm_panel.hpp"
#include "src/connection.hpp"


constexpr unsigned long SERIAL_BAUD    = 115200;
constexpr int           ENC_MIN        = -180;
constexpr int           ENC_MAX        = 180;
constexpr int           ENC_STEP_DEG   = 5;    
constexpr unsigned long LCD_REFRESH_MS = 50;
constexpr unsigned long DEBOUNCE_MS    = 50;
constexpr unsigned long DEBUG_PRINT_MS = 1000;


int  angle        = 0;
bool displayDirty = true;

//encoder
volatile int8_t  encSteps = 0;   
volatile uint8_t encState = 0;
volatile int8_t  encAccum = 0;
static const int8_t ENC_TABLE[16] = {0,-1,1,0, 1,0,0,-1, -1,0,0,1, 0,1,-1,0};

void IRAM_ATTR encoderISR() {
  encState = ((encState << 2) | (digitalRead(ENCODER_CLK) << 1) | digitalRead(ENCODER_DT)) & 0x0F;
  encAccum += ENC_TABLE[encState];
  if (encAccum >= 4)       { encSteps++; encAccum = 0; }
  else if (encAccum <= -4) { encSteps--; encAccum = 0; }
}


struct Button {
  uint8_t       pin;
  const char*   name;
  int           lastReading;   
  int           stableState;   
  unsigned long changedAt;     
};

Button buttons[] = {
  {BTN_1, "Button 1", HIGH, HIGH, 0},
  {BTN_2, "Button 2", HIGH, HIGH, 0},
};


void handleEncoder() {
  noInterrupts();
  int8_t steps = encSteps;
  encSteps = 0;
  interrupts();

  if (steps != 0) {
    angle = constrain(angle + steps * ENC_STEP_DEG, ENC_MIN, ENC_MAX);
    displayDirty = true;
  }
}

void handleDisplay() {
  static unsigned long lastRefresh = 0;
  if (displayDirty && millis() - lastRefresh >= LCD_REFRESH_MS) {
    lastRefresh = millis();
    displayDirty = false;
    updateAngleDisplay(angle);
  }
}

void handleButtons() {
  const unsigned long now = millis();

  for (Button& b : buttons) {
    int reading = digitalRead(b.pin);

    if (reading != b.lastReading) {
      b.lastReading = reading;
      b.changedAt = now;
    }

    if (reading != b.stableState && now - b.changedAt > DEBOUNCE_MS) {
      b.stableState = reading;
      if (reading == LOW) {
        onButtonPressed(b.name);
      }
    }
  }
}


void handleTelemetry() {
  static unsigned long lastSendTime = 0;
  if (millis() - lastSendTime < SEND_INTERVAL) return;
  lastSendTime = millis();

  sendTelemetry(angle, digitalRead(BTN_1), digitalRead(BTN_2));
}

// void handleDebugPrint() {
//   static unsigned long lastPrint = 0;
//   if (millis() - lastPrint < DEBUG_PRINT_MS) return;
//   lastPrint = millis();

//   Serial.print("DEBUG angle=");
//   Serial.println(angle);
// }


void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(1000);

  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);

  encState = (digitalRead(ENCODER_CLK) << 1) | digitalRead(ENCODER_DT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_DT),  encoderISR, CHANGE);

  initDisplay();
  updateAngleDisplay(angle);

  Serial.println("\nWeMos TCP telemetry client");

  connectToWiFi();
  connectToServer();
  WiFi.setSleepMode(WIFI_NONE_SLEEP); 
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi disconnected");
    connectToWiFi();
    return;
  }

  handleEncoder();
  handleDisplay();
  handleButtons();
  handleTelemetry();
  // handleDebugPrint();
}