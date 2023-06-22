#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>
#include "serial.h"
#include "menu.h"

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
    Serial.println(buffer);
}

void Menu::displayMenu() {
    Serial.println("network: Get current network configuration");
    Serial.println("ssid: configure the ssid");
    Serial.println("password: configure the network password");
    Serial.println("hostname: configure the hostname");

    auto input = awaitInput(": ");

    if (input == "network") {
        outputNetworkInfo();
    } else if (input == "ssid") {
        auto ssidInput = awaitInput("ssid: ");
        preferences.putString("ssid", ssidInput);
    } else if (input == "password") {
        auto pwdInput = awaitInput("password: ");
        preferences.putString("password", pwdInput);
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
        Serial.println(buffer);
    }
}
