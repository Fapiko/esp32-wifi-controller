#ifndef ESP32_WIFI_CONTROLLER_MQTT_H
#define ESP32_WIFI_CONTROLLER_MQTT_H

#include <Adafruit_MQTT_Client.h>
#include <WiFiClientSecure.h>

extern Adafruit_MQTT_Client mqttClient;
extern WiFiClientSecure wifiClient;

void attemptConnectMqtt(Adafruit_MQTT_Client client);

#endif //ESP32_WIFI_CONTROLLER_MQTT_H
