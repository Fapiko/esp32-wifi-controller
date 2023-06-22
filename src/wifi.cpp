#include "WiFi.h"

unsigned long lastWifiConnectAttempt;

void attemptConnectWifi(const char *ssid, const char *password) {
    if (WiFi.isConnected()) {
        return;
    }

    Serial.println("Attempt wifi...");

    unsigned long time = millis();

    if (lastWifiConnectAttempt == 0 || lastWifiConnectAttempt + 5000 < time) {
        WiFi.disconnect();
        WiFi.begin(ssid, password);

        if (WiFi.isConnected()) {
            Serial.print(F("Connected to "));
            Serial.println(ssid);
        } else {
            Serial.print(F("Unable to connect to wifi network "));
            Serial.print(ssid);
            Serial.println(F(" attempting to reconnect in 5 seconds..."));
        }

        lastWifiConnectAttempt = time;
    }
}