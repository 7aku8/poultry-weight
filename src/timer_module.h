//
// Created by Jakub on 25/02/2024.
//

#ifndef POULTRY_WEIGHT_TIMER_MODULE_H
#define POULTRY_WEIGHT_TIMER_MODULE_H

#include <Arduino.h>
#include <RTClib.h>

namespace timer {
    void init();

    int get_year();

    int get_month();

    int get_day();

    int get_hour();

    int get_minute();

    int get_second();

    String get_time();

    String get_date();

    DateTime get_datetime();

    void set_time(int hour, int minute, int second);

    void set_date(int year, int month, int day);
}

#endif //POULTRY_WEIGHT_TIMER_MODULE_H
