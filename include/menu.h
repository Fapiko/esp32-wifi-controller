#ifndef ESP32_WIFI_CONTROLLER_MENU_H
#define ESP32_WIFI_CONTROLLER_MENU_H

#include "config.h"

class Menu {
private:
	Preferences preferences;
public:
	Menu(const Preferences &preferences);

	void displayMenu();

	void outputNetworkInfo();
};

#endif //ESP32_WIFI_CONTROLLER_MENU_H
