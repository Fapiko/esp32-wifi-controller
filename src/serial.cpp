#include <WString.h>
#include <Arduino.h>

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
