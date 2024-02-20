#ifndef WEIGHT_MODULE_H 
#define WEIGHT_MOUDLE_H

#include <HX711_ADC.h>
#if defined(ESP8266)
#include <EEPROM.h>
#endif

#include <Arduino.h>
#include "logger_module.h"

namespace weight
{
    void init();
    bool capture_measurement(float &current_reading);

    void calibrate();
    void change_saved_cal_factor();
    bool check_tare_completed();

    void set_refresh_time();
    bool should_refresh();

    bool is_taring();
    void tare_without_delay();
}

#endif

