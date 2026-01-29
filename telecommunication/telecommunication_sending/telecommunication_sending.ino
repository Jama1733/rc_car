#include <WiFi.h>
#include <esp_now.h>

const int pin = 32;
const int light = 23;

uint8_t broadcast_address[] = {0x3c, 0x8a, 0x1f, 0xa3, 0x7d, 0x18};

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

esp_now_peer_info_t peerInfo;

void setup(){
  // Init Serial Monitor
  Serial.begin(115200);

  pinMode(pin, INPUT);
  pinMode(light, OUTPUT);

  // Set as wifi station
  WiFi.mode(WIFI_STA);
  WiFi.STA.begin();
  WiFi.begin();

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // register the data sent callback function
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcast_address, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

int data = 0;
void loop(){
  if (digitalRead(pin) == HIGH) {data = 1; digitalWrite(light, HIGH);}
  else {data = 0; digitalWrite(light, LOW);}
  esp_err_t message = esp_now_send(broadcast_address, (uint8_t *) &data, sizeof(data));
  if (message == ESP_OK) {
    Serial.println("Message send success");
  }
  else {
    Serial.println("Message send failure");
  }
}
