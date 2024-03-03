//
// Created by Jakub on 25/02/2024.
//

#include "timer_module.h"

RTC_DS1307 rtc;

void timer::init() {
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
    }

    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

int timer::get_year() {
    return rtc.now().year() - 2000;
}

int timer::get_month() {
    return rtc.now().month();
}

int timer::get_day() {
    return rtc.now().day();
}

int timer::get_hour() {
    return rtc.now().hour();
}

int timer::get_minute() {
    return rtc.now().minute();
}

int timer::get_second() {
    return rtc.now().second();
}

void timer::set_time(int hour, int minute, int second) {
    rtc.adjust(DateTime(rtc.now().year(), rtc.now().month(), rtc.now().day(), hour, minute, second));
}

void timer::set_date(int year, int month, int day) {
    rtc.adjust(DateTime(year, month, day, rtc.now().hour(), rtc.now().minute(), rtc.now().second()));
}

DateTime timer::get_datetime() {
    return rtc.now();
}

String timer::get_time() {
    return rtc.now().timestamp(DateTime::TIMESTAMP_TIME);
}

String timer::get_date() {
    return rtc.now().timestamp(DateTime::TIMESTAMP_DATE);
}