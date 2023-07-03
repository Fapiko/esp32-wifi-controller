#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>
#include "serial.h"
#include "menu.h"
#include "preferences.h"

Menu::Menu(const Preferences &preferences) {
	this->preferences = preferences;
}

void Menu::outputNetworkInfo() {
	const auto message = "\nSSID: %s\nPassword: %s\nWiFi Status: %s";

	const char *wifiStatus = "disconnected";
	if (WiFi.isConnected()) {
		wifiStatus = "connected";
	}

	char buffer[100];
	sprintf(buffer, message,
			preferences.getString("ssid", "").c_str(),
			preferences.getString("password", "").c_str(),
			wifiStatus);
	serialWrapper.println(buffer);
}

void Menu::displayMenu() {
	serialWrapper.println("network: Get current network configuration");
	serialWrapper.println("ssid: configure the ssid");
	serialWrapper.println("password: configure the network password");
	serialWrapper.println("hostname: configure the hostname");
	serialWrapper.println("ota-enabled: configure whether ota is enabled");
	serialWrapper.println("ota-pwd: configure the ota password");
	serialWrapper.println("restart: restart the device");

	auto input = awaitInput(": ");

	if (input == "network") {
		outputNetworkInfo();
	} else if (input == SSID) {
		auto ssidInput = awaitInput("ssid: ");
		preferences.putString(SSID, ssidInput);
	} else if (input == PASSWORD) {
		auto pwdInput = awaitInput("password: ");
		preferences.putString(PASSWORD, pwdInput);
	} else if (input == "hostname") {
		auto hostnameInput = awaitInput("hostname: ");
		preferences.putString("hostname", hostnameInput);
	} else if (input == "restart") {
		ESP.restart();
	} else if (input == "ota-enabled") {
		auto otaEnabledInput = awaitInput("ota-enabled: ");
		preferences.putBool("ota-enabled", otaEnabledInput == "true");
	} else if (input == "ota-pwd") {
		auto otaPwdInput = awaitInput("ota-pwd: ");
		preferences.putString("ota-pwd", otaPwdInput);
	} else {
		char buffer[100];
		const auto message = "Input %s not expected";
		sprintf(buffer, message, input.c_str());
		serialWrapper.println(buffer);
	}
}
