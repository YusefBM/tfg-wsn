#include <Arduino.h>
#include <vector>

#define BAUD_RATE 115200
#define MIN_CO2_LEVEL 300.00

/* Network´s values */
#define MOSQUITTO_PORT 1883
const char *SSID = "Home";
const char *PASSWORD = "2+5+26+28=cumples";
const char *MQTT_SERVER_VM = "192.168.1.188";
const char *MQTT_SERVER = "192.168.1.140";

#define MAX_SEND_TIME 10000

/* PIR values */
#define PIR1_PIN 15
#define PIR2_PIN 4

/* MQTT Topics */
String ROOM_ID = "1";
String state_topic = "room/" + ROOM_ID + "/state";


/* Line protocol format */
String line_protocol(int people)
{
  return "state people=" + String(people);
}
