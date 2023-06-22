#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include "Preferences.h"
#include "wifi.h"
#include "menu.h"
#include "config.h"
#include "serial.h"

int LED_BUILTIN = 2;

Preferences preferences;
Menu *menu;

void initPreferenceStr(const char *key) {
    if (!preferences.isKey(key)) {
        preferences.putString(key, "");
    }
}

void initPreferenceBool(const char *key, const bool value = false) {
    if (!preferences.isKey(key)) {
        preferences.putBool(key, value);
    }
}

void setup() {
    Serial.begin(115200);

    preferences.begin("default", false);

    // Initialize preferences
    initPreferenceStr("ssid");
    initPreferenceStr("password");
    initPreferenceStr("hostname");
    initPreferenceBool("ota-enabled");
    initPreferenceBool("ota-pwd");

    menu = new Menu(preferences);

    const auto hostname = preferences.getString("hostname", "").c_str();
    const auto otaPwd = preferences.getString("ota-pwd", "").c_str();
    if (preferences.getBool("ota-enabled", false)) {
        ArduinoOTA.begin(WiFi.localIP(), hostname, otaPwd, InternalStorage);
    }

    WiFiClass::setHostname(preferences.getString("hostname", "").c_str());
    WiFi.setAutoReconnect(true);

    attemptConnectWifi(
            preferences.getString("ssid", "").c_str(),
            preferences.getString("password", "").c_str());

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    ArduinoOTA.poll();

    if (Serial.available()) {
        flushBuffer();
        menu->displayMenu();
    }

    // Init WiFi
    attemptConnectWifi(preferences.getString("ssid", "").c_str(),
                       preferences.getString("password", "").c_str());

    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}