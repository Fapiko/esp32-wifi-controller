#include "WiFi.h"
#include "serial.h"

unsigned long lastWifiConnectAttempt;

void attemptConnectWifi(const char *ssid, const char *password) {
	if (WiFi.isConnected()) {
		return;
	}

	serialWrapper.println("Attempt wifi...");

	unsigned long time = millis();

	if (lastWifiConnectAttempt == 0 || lastWifiConnectAttempt + 5000 < time) {
		WiFi.disconnect();
		WiFi.begin(ssid, password);

		if (WiFi.isConnected()) {
			serialWrapper.print(F("Connected to "));
			serialWrapper.println(ssid);
		} else {
			serialWrapper.print(F("Unable to connect to wifi network "));
			serialWrapper.print(ssid);
			serialWrapper.println(F(" attempting to reconnect in 5 seconds..."));
		}

		lastWifiConnectAttempt = time;
	}
}