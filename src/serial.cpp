#include <WString.h>
#include <Arduino.h>
#include "serial.h"
#include "mqtt.h"

SerialWrapper serialWrapper = SerialWrapper();

size_t SerialWrapper::print(const char str[]) {
	this->buffer.concat(str);
	return Serial.print(str);
}

size_t SerialWrapper::println(const char *str) {
	this->buffer.concat(str);

	if (mqttClient.connected()) {
		mqttClient.publish(topic, this->buffer.c_str());
		this->buffer = "";
	} else {
		this->buffer += "\n";
	}

	return Serial.println(str);
}

void SerialWrapper::setTopic(const char *topic) {
	this->topic = topic;
}

size_t SerialWrapper::println(const __FlashStringHelper *str) {
	return this->println((const char *) str);
}

size_t SerialWrapper::print(const __FlashStringHelper *str) {
	return this->print((const char *) str);
}

void flushBuffer() {
	while (Serial.available()) {
		Serial.read();
	}
}

String awaitInput(const String prompt) {
	Serial.print(prompt);

	String input = "";
	while (true) {
		while (!Serial.available()) {
			delay(10);
		}

		char i = char(Serial.read());
		if (i == '\n' || i == '\r') {
			// Clear the input buffer - i.e. \r\n will leave trailing \n
			while (Serial.available()) {
				Serial.read();
			}
			break;
		}

		input += i;
		Serial.print(i);
	}

	Serial.print("\n\n");

	return input;
}
