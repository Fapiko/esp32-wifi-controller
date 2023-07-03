#ifndef e32c_SERIAL_H
#define e32c_SERIAL_H

#include <WString.h>
#include "mqtt.h"

class SerialWrapper {
private:
	String buffer = "";
	const char *topic;
public:
	size_t print(const char str[]);

	size_t print(const __FlashStringHelper *str);

	size_t println(const char str[]);

	size_t println(const __FlashStringHelper *str);

	void setTopic(const char *topic);
};

extern SerialWrapper serialWrapper;

void flushBuffer();

String awaitInput(String prompt);

#endif // e32c_SERIAL_H
