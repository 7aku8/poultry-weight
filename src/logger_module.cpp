#include "logger_module.h"

unsigned long baudRate = 57600;

void logger::init()
{
    delay(500);
    Serial.begin(baudRate);

    while (!Serial)
    {
        delay(100);
    }
}

logger::Logger::Logger(const char *name)
{
    this->name = name;
}

void logger::Logger::debug(const char *message)
{
    Serial.print("{DBG}[");
    Serial.print(this->name);
    Serial.print("]: ");
    Serial.println(message);
}

void logger::Logger::debug(float number)
{
    char buffer[10];
    dtostrf(number, 5, 2, buffer);

    Serial.print("{DBG}[");
    Serial.print(this->name);
    Serial.print("]: ");
    Serial.println(String(buffer)); 
}

void logger::Logger::log(const char *message)
{
    Serial.print("{LOG}[");
    Serial.print(this->name);
    Serial.print("]: ");
    Serial.println(message);
}

void logger::Logger::log(float number)
{
    char buffer[10];
    dtostrf(number, 5, 2, buffer);

    Serial.print("{LOG}[");
    Serial.print(this->name);
    Serial.print("]: ");
    Serial.println(String(buffer)); 
}
