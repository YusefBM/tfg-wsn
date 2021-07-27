#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <iWifi.h>
#include <definitions.h>

WiFiClient esp_client;
PubSubClient client(esp_client);
iWifi my_wifi(SSID, PASSWORD);

int people_counter, old_people_counter;
unsigned int s1_value, s2_value;
boolean s1_detected, s2_detected;
boolean entry, output;
unsigned long send_time;

void reconnect();
void counter_people();
void send_data();
boolean check_data();
boolean check_send_time();

void setup()
{
  people_counter = old_people_counter = 0;
  s1_detected = s2_detected = false;
  s1_value = s2_value = 0;
  send_time = 0;

  Serial.begin(BAUD_RATE);
  pinMode(PIR1_PIN, INPUT_PULLDOWN);
  pinMode(PIR2_PIN, INPUT_PULLDOWN);

  my_wifi.connect();
  client.setServer(MQTT_SERVER, MOSQUITTO_PORT);
}

void loop()
{
  if (!client.connected())
    reconnect();
  client.loop();

  counter_people();

  if (check_data() || check_send_time())
  send_data();
}

void reconnect()
{
  while (!client.connected())
  {
    if (!client.connect("door_node"))
      delay(2000);
    yield();
  }
}

void counter_people()
{
  s2_value = digitalRead(PIR2_PIN);
  //delay(150);
  s1_value = digitalRead(PIR1_PIN);
  Serial.println("S1:" + String(s1_value) + "-S2:" + String(s2_value));

  /* States Machine */
  if (s1_value == HIGH && s2_value == HIGH)
  {
    if (entry)
    {
      people_counter++;
      delay(1000);
    }
    else if (output)
    {
      people_counter > 0 ? people_counter-- : people_counter = 0;

      delay(1000);
    }
    // Reset States
    entry = false;
    output = false;
  }

  else if (s1_value == LOW && s2_value == HIGH)
  {
    entry = true;
    output = false;
  }

  else if (s1_value == HIGH && s2_value == LOW)
  {
    entry = false;
    output = true;
  }

  else
  {
    entry = false;
    output = false;
  }

  delay(250);
}

boolean check_data()
{
  if (people_counter != old_people_counter)
  {
    old_people_counter = people_counter;
    return true;
  }
  return false;
}

boolean check_send_time()
{
  return (millis() - send_time) >= MAX_SEND_TIME;
}

void send_data()
{
  client.publish(state_topic.c_str(), line_protocol(people_counter).c_str());
  client.disconnect();
  send_time = millis();
}
