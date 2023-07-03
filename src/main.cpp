#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include "Preferences.h"
#include "menu.h"
#include "serial.h"
#include "wifi.h"
#include <Adafruit_MQTT_Client.h>
#include <SPIFFS.h>
#include "mqtt.h"
#include "files.h"
#include "preferences.h"

int LED_BUILTIN = 2;
const int RELAY_PIN = 5;

Adafruit_MQTT_Subscribe topic = Adafruit_MQTT_Subscribe(&mqttClient, "devices/dev-test", 1);

Menu *menu;
char *chain;
char *cert;
char *key;
bool otaEnabled = false;

void topicCallback(char *data, uint16_t len) {
	serialWrapper.print("Received data from mqtt: ");
	serialWrapper.println(data);
}

void setup() {
	Serial.begin(115200);

	SPIFFS.begin(true);
	cert = readFile("/cert.pem");
	key = readFile("/key.pem");
	chain = readFile("/chain.pem");

	initPreferences();

	otaEnabled = preferences.getBool("ota-enabled", false);

	menu = new Menu(preferences);

	WiFiClass::setHostname(preferences.getString("hostname", "client.dev.mqtt.webscale.me").c_str());
	WiFi.setAutoReconnect(true);

	attemptConnectWifi(
			preferences.getString(SSID, "").c_str(),
			preferences.getString(PASSWORD, "").c_str());

	if (otaEnabled) {
		const auto hostname = preferences.getString("hostname", "").c_str();
		const auto otaPwd = preferences.getString("ota-pwd", "").c_str();
		ArduinoOTA.setHostname(hostname);
		ArduinoOTA.setPassword(otaPwd);
		ArduinoOTA.begin();
	}

	wifiClient.setCACert(chain);
	wifiClient.setCertificate(cert);
	wifiClient.setPrivateKey(key);

	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(RELAY_PIN, OUTPUT);

	serialWrapper.setTopic("devices/dev-test/serial");
	topic.setCallback(topicCallback);
	mqttClient.subscribe(&topic);
}

void loop() {
	if (otaEnabled) {
		ArduinoOTA.handle();
	}
	if (Serial.available()) {
		flushBuffer();
		menu->displayMenu();
	}

	// Init WiFi
	attemptConnectWifi(preferences.getString(SSID, "").c_str(),
					   preferences.getString(PASSWORD, "").c_str());
	attemptConnectMqtt(mqttClient);
	mqttClient.processPackets(100);

	if (mqttClient.connected()) {
		mqttClient.publish("devices/dev-test", "Hello from ESP32");
	}

	digitalWrite(LED_BUILTIN, HIGH);
	delay(1000);
	digitalWrite(LED_BUILTIN, LOW);
	delay(1000);
}
