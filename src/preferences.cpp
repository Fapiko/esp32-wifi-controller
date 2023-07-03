#include <Preferences.h>
#include "preferences.h"

Preferences preferences;
const char *PASSWORD = "password";
const char *SSID = "ssid";

void initPreferences() {
	preferences.begin("default", false);

	// Initialize preferences
	initPreferenceStr(SSID);
	initPreferenceStr("password");
	initPreferenceStr("hostname");
	initPreferenceStr("mqtt-host", "dev.mqtt.int.facepalmer.net");
	initPreferenceBool("ota-enabled");
	initPreferenceBool("ota-pwd");
}

void initPreferenceStr(const char *key, const char *value) {
	if (!preferences.isKey(key)) {
		preferences.putString(key, "");
	}
}

void initPreferenceBool(const char *key, const bool value) {
	if (!preferences.isKey(key)) {
		preferences.putBool(key, value);
	}
}