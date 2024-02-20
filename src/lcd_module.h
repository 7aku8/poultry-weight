#ifndef LCD_MODULE_H
#define LCD_MODULE_H

#include "U8g2lib.h"
#include <Arduino.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

namespace lcd 
{
    bool should_refresh();
    void init();
    void draw_splash_screen();
    void draw_weight(float current, float average, float latest);

    void set_refresh_time();
    bool should_refresh();
}

#endif