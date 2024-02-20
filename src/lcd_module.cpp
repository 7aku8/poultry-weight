#include "lcd_module.h"
#include "images/logo.xbm"

U8G2_ST7567_ENH_DG128064I_F_SW_I2C u8g2_lcd(U8G2_R0, SCL, SDA, U8X8_PIN_NONE); // Set the LCD pins

const unsigned long REFRESH_INTERVAL = 500; // 1000 milliseconds = 1 second

unsigned long previous_refresh_time = 0;

void lcd::set_refresh_time() {
    previous_refresh_time = millis();
}


bool lcd::should_refresh() {
    unsigned long current_time = millis();
    return current_time - previous_refresh_time >= REFRESH_INTERVAL;
}

void lcd::init() {
    u8g2_lcd.setI2CAddress(0x3F * 2);
    u8g2_lcd.begin();
    u8g2_lcd.clearBuffer();
    u8g2_lcd.setFont(u8g2_font_ncenB08_tr);

    u8g2_lcd.setDisplayRotation(U8G2_R2);
}

void lcd::draw_splash_screen() {
    u8g2_lcd.clearBuffer();
    u8g2_lcd.setFont(u8g2_font_ncenB08_tr); // Choose a font (change it as needed)

    // Draw the "Kurwaga v1.0" text
    u8g2_lcd.drawStr(30, 20, "Kurwaga v1.0");

    // Draw the chicken logo
    u8g2_lcd.drawXBM(45, 25, logo_width, logo_height, logo_bits);

    u8g2_lcd.sendBuffer();
}

void lcd::draw_weight(float current, float average, float latest) {
    if (!lcd::should_refresh()) {
        return;
    }

    u8g2_lcd.clearBuffer();
    u8g2_lcd.setFont(u8g2_font_ncenB08_tr);

    char buffer[3][20];

    dtostrf(current, 6, 2, buffer[0]);
    const char *currentStr = buffer[0];

    dtostrf(average, 6, 2, buffer[1]);
    const char *averageStr = buffer[1];

    dtostrf(latest, 6, 2, buffer[2]);
    const char *latestStr = buffer[2];

    u8g2_lcd.drawStr(10, 20, "CUR:");
    u8g2_lcd.drawStr(50, 20, currentStr);

    u8g2_lcd.drawStr(10, 34, "AVG:");
    u8g2_lcd.drawStr(50, 34, averageStr);

    u8g2_lcd.drawStr(10, 52, "LST:");

    if (latest > 50) {
        u8g2_lcd.drawStr(50, 52, latestStr);
    } else {
        u8g2_lcd.drawStr(50, 52, "-");
    }

    u8g2_lcd.drawFrame(5, 5, 118, 54);
    u8g2_lcd.sendBuffer();

    lcd::set_refresh_time();
}