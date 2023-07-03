#include <Arduino.h>
#include <WiFiClientSecure.h>
#include "Adafruit_MQTT_Client.h"
#include "mqtt.h"
#include "serial.h"

unsigned long lastMqttConnectAttempt;

WiFiClientSecure wifiClient;
Adafruit_MQTT_Client mqttClient(&wifiClient, "dev.mqtt.int.facepalmer.net", 8883, "dev-test-1", "", "");

void attemptConnectMqtt(Adafruit_MQTT_Client mqttClient) {
	if (mqttClient.connected()) {
		return;
	}

	unsigned long time = millis();

	if (lastMqttConnectAttempt == 0 || lastMqttConnectAttempt + 5000 < time) {
		serialWrapper.println(F("Connecting to MQTT..."));

		int8_t ret = mqttClient.connect();
		if (ret == 0) {
			serialWrapper.println(F("MQTT Connected!"));
		} else {
			lastMqttConnectAttempt = time;
			serialWrapper.println(mqttClient.connectErrorString(ret));
			serialWrapper.println(F("Retrying MQTT connection in 5 seconds..."));
			mqttClient.disconnect();
		}
	}
}