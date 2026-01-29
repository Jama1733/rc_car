#include <WiFi.h>
#include <esp_now.h>

#define pin 12

uint8_t broadcast_address[] = {0x78, 0x42, 0x1c, 0x65, 0x7b, 0x98};

int incoming_data = 0;
// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *value, int len) {
  memcpy(&incoming_data, value, sizeof(value));
  Serial.print("Bytes received: ");
  Serial.println(len);
}

esp_now_peer_info_t peerInfo;

void setup(){
  pinMode(pin, OUTPUT);

  // Init Serial Monitor
  Serial.begin(115200);

  // Set as wifi station
  WiFi.mode(WIFI_STA);
  WiFi.STA.begin();

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // register the data reciever callback function
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));

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

void loop(){
  esp_err_t message = esp_now_send(broadcast_address, (uint8_t *) &incoming_data, sizeof(incoming_data));
  if (message = ESP_OK) {
    Serial.println("Message recieve success");
  }
  else {
    Serial.println("Message recieve failure");
  }
  if (incoming_data == 1) {digitalWrite(pin, HIGH);}
  else                    {digitalWrite(pin, LOW);}                   
}
