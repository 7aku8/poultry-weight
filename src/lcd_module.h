#ifndef LCD_MODULE_H
#define LCD_MODULE_H

#include "U8g2lib.h"
#include <Arduino.h>
#include <GEM.h>
#include <TimeLib.h>
#include "GEMPage.h"
#include "GEM_u8g2.h"
#include "images/logo.xbm"

#ifdef U8X8_HAVE_HW_SPI

#include <SPI.h>

#endif
#ifdef U8X8_HAVE_HW_I2C

#include <Wire.h>

#endif

namespace lcd {
    bool should_refresh();

    void init();

    void draw_splash_screen();

    void draw_weight(float current, float average, float latest, int measurements_number);

    void open_menu();

    void set_refresh_time();

    void register_pressed_key(int key);
}

#endif