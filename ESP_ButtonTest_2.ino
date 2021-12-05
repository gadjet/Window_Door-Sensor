
#include<ESP8266WiFi.h>
#include<espnow.h>

uint8_t bridgeAddress[] = {0x2C, 0xF4, 0x32, 0x77, 0x5B, 0x73};   //please update this with the MAC address of your ESP-NOW TO MQTT brigde

// Set your Board ID (ESP32 Sender #1 = BOARD_ID 1, ESP32 Sender #2 = BOARD_ID 2, etc)
#define BOARD_ID 1

const int reedSwitch = 13;

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  int id;
  char state[7];
  int vBatt;
} struct_message;

// Create a struct_message called test to store variables to be sent
struct_message myData;

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  /* Serial.print("\r\nLast Packet Send Status: ");
    if (sendStatus == 0){
     Serial.println("Delivery success");
    }
    else{
     Serial.println("Delivery fail");
    }
  */
}

void setup() {
  // Init Serial Monitor
  //Serial.begin(115200);
  // initialize the reed switch pin as an input:
  pinMode(reedSwitch, INPUT);
  // initialize the wakeup pin as an input:
  pinMode(D0, WAKEUP_PULLUP);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    //Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Set ESP-NOW role
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);

  // Once ESPNow is successfully init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  esp_now_add_peer(bridgeAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
  // Set values to send
  myData.id = BOARD_ID;
  // Read the state of the reed switch and send open or closed
  if (digitalRead(reedSwitch) == HIGH) {
    strcpy(myData.state, "Closed");
  }
  else {
    strcpy(myData.state, "Open");
  }

  myData.vBatt = analogRead(A0) * 4.2 * 10 / 1023;
  // Send message via ESP-NOW
  esp_now_send(0, (uint8_t *) &myData, sizeof(myData));
  ESP.deepSleep(0);
  delay(200);
}
