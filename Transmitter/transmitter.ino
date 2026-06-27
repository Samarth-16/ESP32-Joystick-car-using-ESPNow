#include <esp_now.h>
#include <WiFi.h>

// Update this with your actual printed MAC Address
uint8_t receiverAddress[] = {0xFC, 0xE8, 0xC0, 0x00, 0x00, 0x00}; 

typedef struct {
  int x;
  int y;
  bool sw;
} Data;

Data data;

// Send Callback
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  // Can be left empty or used for debugging
}

void setup() {
  Serial.begin(115200);
  pinMode(27, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESPNow Init Error");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  data.x = analogRead(34);
  data.y = analogRead(35);
  data.sw = !digitalRead(27); // Invert because of INPUT_PULLUP

  esp_now_send(receiverAddress, (uint8_t *) &data, sizeof(data));

  delay(20); // 50Hz Refresh Rate
}