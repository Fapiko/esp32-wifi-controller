#include <Arduino.h>
#include <SPIFFS.h>
#include "serial.h"

char *readFile(const char *filename) {
	File file = SPIFFS.open(filename, "r");
	if (!file) {
		serialWrapper.println("Failed to open file for reading");
		return nullptr;
	}

	char *returnFile = (char *) malloc(file.size());

	file.readBytes(returnFile, file.size());
	file.close();

	return returnFile;
}