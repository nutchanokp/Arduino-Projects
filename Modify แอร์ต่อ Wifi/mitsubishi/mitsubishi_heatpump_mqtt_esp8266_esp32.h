
//#define ESP32
//#define OTA
//const char* ota_password = "<YOUR OTA PASSWORD GOES HERE>";

// wifi settings
const char* ssid     = "Puttakun";
const char* password = "10683524";

// mqtt server settings
const char* mqtt_server   = "192.168.1.13";
const int mqtt_port       = 1883;
const char* mqtt_username = "mqtttest";
const char* mqtt_password = "10683524";

// mqtt client settings
// Note PubSubClient.h has a MQTT_MAX_PACKET_SIZE of 128 defined, so either raise it to 256 or use short topics
const char* client_id                   = "heatpump"; // Must be unique on the MQTT network
const char* heatpump_topic              = "heatpump";
const char* heatpump_set_topic          = "heatpump/set";
const char* heatpump_status_topic       = "heatpump/status";
const char* heatpump_timers_topic       = "heatpump/timers";

const char* heatpump_debug_topic        = "heatpump/debug";
const char* heatpump_debug_set_topic    = "heatpump/debug/set";

// pinouts
const int redLedPin  = 0; // Onboard LED = digital pin 0 (red LED on adafruit ESP8266 huzzah)
const int blueLedPin = 2; // Onboard LED = digital pin 0 (blue LED on adafruit ESP8266 huzzah)

// sketch settings
const unsigned int SEND_ROOM_TEMP_INTERVAL_MS = 60000;
