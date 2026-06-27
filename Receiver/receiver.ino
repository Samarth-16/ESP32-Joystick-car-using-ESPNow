#include <esp_now.h>
#include <WiFi.h>

typedef struct {
  int x;
  int y;
  bool sw;
} Data;

Data data;

const int IN1 = 25;
const int IN2 = 26;
const int IN3 = 32;
const int IN4 = 33;
const int ENA = 14;
const int ENB = 12;

unsigned long lastReceive = 0;

void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void forward(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void reverse(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void left(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void right(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

// Updated callback signature compliant with latest ESP-NOW structures
void receiveData(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
  memcpy(&data, incomingData, sizeof(data));
  lastReceive = millis();
}

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  stopCar();

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(receiveData);
}

void loop() {
  // Failsafe: Stops the car if communication drops out for > 500ms
  if (millis() - lastReceive > 500) {
    stopCar();
    return;
  }

  int x = data.x;
  int y = data.y;

  // Added deadzone logic adjustments (Assuming joystick resting position sits ~2048)
  if (y > 3000) {
    int speed = map(y, 3000, 4095, 120, 255);
    forward(speed);
  }
  else if (y < 1000) {
    int speed = map(y, 1000, 0, 120, 255);
    reverse(speed);
  }
  else if (x > 3000) {
    int speed = map(x, 3000, 4095, 120, 255);
    right(speed);
  }
  else if (x < 1000) {
    int speed = map(x, 1000, 0, 120, 255);
    left(speed);
  }
  else {
    stopCar();
  }
}