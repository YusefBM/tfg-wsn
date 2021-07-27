#include <Arduino.h>

#define BAUD_RATE 115200

/* Network´s values */
#define MOSQUITTO_PORT 1883
#define CLIENT_NAME "scan_node_1"
const char *SSID = "Home";
const char *PASSWORD = "2+5+26+28=cumples";
const char *MQTT_SERVER_VM = "192.168.1.188";
const char *MQTT_SERVER = "192.168.2.106";

/* Promiscuous mode */
#define OFFLINE 0
#define ONLINE  1
#define LAST_CHANNEL 13
#define MAX_SEND_TIME 30000

/* CO2 configurations */
#define CO2_PIN 35
#define MAX_CO2_VALUE 2500
#define MIN_CO2_VALUE 100

/* BLE mode */
#define SCAN_TIME 10

/* MQTT Topics */
String ROOM_ID = "3";
String state_topic = "room/" + ROOM_ID + "/state";

