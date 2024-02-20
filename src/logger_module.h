#ifndef LOGGER_MODULE_H
#define LOGGER_MODULE_H

#include <Arduino.h>

namespace logger
{
    void init();

    class Logger
    {
        const char *name;

    public:
        explicit Logger(const char *name);
        void debug(const char *message);
        void debug(float number);
        void log(const char *message);
        void log(float number);
    };
}

#endif
