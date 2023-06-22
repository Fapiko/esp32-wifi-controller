#ifndef e32c_SERIAL_H
#define e32c_SERIAL_H

#include <WString.h>

void flushBuffer();

String awaitInput(String prompt);

#endif // e32c_SERIAL_H
