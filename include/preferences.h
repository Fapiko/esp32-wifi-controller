#ifndef ESP32_WIFI_CONTROLLER_PREFERENCES_H
#define ESP32_WIFI_CONTROLLER_PREFERENCES_H

extern Preferences preferences;
extern const char *PASSWORD;
extern const char *SSID;

void initPreferences();

void initPreferenceStr(const char *key, const char *value = "");

void initPreferenceBool(const char *key, bool value = false);

#endif //ESP32_WIFI_CONTROLLER_PREFERENCES_H
