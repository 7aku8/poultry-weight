#include "lcd_module.h"
#include "GEMPage.h"
#include "GEM_u8g2.h"

U8G2_ST7567_ENH_DG128064I_F_SW_I2C u8g2_lcd(U8G2_R0, SCL, SDA, U8X8_PIN_NONE); // Set the LCD pins

GEMPage menuPage("Kurwaga v1.0");
GEMPage settingsPage("Ustawienia", menuPage);
GEMItem settingItem("Ustawienia", settingsPage);

GEM_u8g2 menu(u8g2_lcd, GEM_POINTER_DASH, 5, 10, 10, 86);


const unsigned long REFRESH_INTERVAL = 500; // 1000 milliseconds = 1 second

unsigned long previous_refresh_time = 0;

void lcd::set_refresh_time() {
    previous_refresh_time = millis();
}


bool lcd::should_refresh() {
    unsigned long current_time = millis();
    return current_time - previous_refresh_time >= REFRESH_INTERVAL;
}

void setupMenu() {
    // Add menu items to menu page
    menuPage.addMenuItem(settingItem);

    // Add menu page to menu and set it as current
    menu.setMenuPageCurrent(menuPage);
}

void lcd::init() {
    u8g2_lcd.setI2CAddress(0x3F * 2);
    u8g2_lcd.begin();
    u8g2_lcd.clearBuffer();
    u8g2_lcd.setFont(u8g2_font_ncenB08_tr);

    u8g2_lcd.setDisplayRotation(U8G2_R2);
    u8g2_lcd.setFontMode(0);

    menu.init();
    setupMenu();
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

enum Page {
    MAIN,
    SETTINGS,
    DETAILS,
    HISTORY
};

Page current_page = MAIN;

void main_page(float current, float average, float latest, int measurements_number) {
    u8g2_lcd.firstPage();
    do {
        // Display "Średnia waga" with larger font
        u8g2_lcd.setFont(u8g2_font_profont12_tf);
        u8g2_lcd.setCursor(2, 0);
        u8g2_lcd.print("Sr. waga: ");
        u8g2_lcd.setFont(u8g2_font_DigitalDisco_tr);
        // Display the average weight
        u8g2_lcd.setCursor(2, 15);
        u8g2_lcd.print(average, 2);

        u8g2_lcd.println("g");

        u8g2_lcd.setFont(u8g2_font_profont12_tf);

        // Display "Liczba pomiarów"
        u8g2_lcd.setCursor(2, 35);
        u8g2_lcd.print("Pomiary: ");
        u8g2_lcd.println(measurements_number);

        // Display "Ostatni pomiar"
        u8g2_lcd.setCursor(2, 50);
        u8g2_lcd.print("Ostatni: ");
        u8g2_lcd.print(latest, 2);
        u8g2_lcd.println("g");

        u8g2_lcd.setFont(u8g2_font_unifont_t_75);
        u8g2_lcd.setCursor(5, 5);
        u8g2_lcd.print(9648);
        u8g2_lcd.setCursor(5, 60);
        u8g2_lcd.print(0x27b6);
    } while (u8g2_lcd.nextPage());
}

void details_page(float sensor_reading) {
    u8g2_lcd.firstPage();
    do {
        u8g2_lcd.setFont(u8g2_font_profont10_tf);
        u8g2_lcd.setCursor(2, 0);
        u8g2_lcd.print("Szczegoly");

        u8g2_lcd.drawLine(0, 8, 127, 8);

        // Display time offset options
        u8g2_lcd.setCursor(2, 12);
        u8g2_lcd.print("Zakres liczenia sredniej:");
        u8g2_lcd.setCursor(2, 20);
        u8g2_lcd.setFont(u8g2_font_pxplustandynewtv_t_all);
        u8g2_lcd.print("12h");

        // Get actual time and date
        time_t t = now();  // Replace with your actual time retrieval method
        struct tm *tm_info = localtime(&t);

        // Display actual time
        u8g2_lcd.setCursor(2, 32);
        u8g2_lcd.setFont(u8g2_font_profont10_tf);
        u8g2_lcd.print("Czas: ");
        u8g2_lcd.setFont(u8g2_font_pxplustandynewtv_t_all);
        u8g2_lcd.println(String(tm_info->tm_hour) + ":" + String(tm_info->tm_min) + ":" + String(tm_info->tm_sec));

        // Display actual date
        u8g2_lcd.setCursor(2, 42);
        u8g2_lcd.setFont(u8g2_font_profont10_tf);
        u8g2_lcd.print("Data: ");
        u8g2_lcd.setFont(u8g2_font_pxplustandynewtv_t_all);
        u8g2_lcd.println(
                String(tm_info->tm_mday) + "." + String(tm_info->tm_mon + 1) + "." + String(tm_info->tm_year + 1900));

        // Display sensor reading
        u8g2_lcd.setCursor(2, 52);
        u8g2_lcd.setFont(u8g2_font_profont10_tf);
        u8g2_lcd.print("Odczyt: ");
        u8g2_lcd.setFont(u8g2_font_pxplustandynewtv_t_all);
        u8g2_lcd.print(sensor_reading);
        u8g2_lcd.println("g");
    } while (u8g2_lcd.nextPage());
}

// TO be dETELECD
// Assuming you have a struct to represent a measurement
struct Measurement {
    float weight;
    unsigned long timestamp;
};

// Assuming you have an array to store measurements
Measurement measurements[10]; // Adjust the size based on your needs

// Variable to keep track of the number of measurements
int numMeasurements = 0;

void generateMockData() {
    // Generate mock data for demonstration
    for (int i = 0; i < 10; ++i) {
        measurements[i].weight = rand() % 100 + 50.0; // Random weight between 50.0 and 149.9 grams
        measurements[i].timestamp = millis(); // Using current millis as a timestamp
        numMeasurements++;
    }
}
// END TO BE DETELD

void history_page() {
    generateMockData();
    u8g2_lcd.firstPage();
    do {
        u8g2_lcd.setFont(u8g2_font_profont10_tf);
        u8g2_lcd.setCursor(2, 0);
        u8g2_lcd.print("Historia");

        u8g2_lcd.drawLine(0, 8, 127, 8);

        // Display the last 5 measurements
        int displayCount = min(5, numMeasurements);
        for (int i = 0; i < displayCount; ++i) {
            char weightBuffer[20];
            char timestampBuffer[20];

            dtostrf(measurements[i].weight, 4, 1, weightBuffer);
            ltoa(measurements[i].timestamp, timestampBuffer, 10);

            u8g2_lcd.setCursor(2, 12 + i * 10);
            u8g2_lcd.print("W: ");
            u8g2_lcd.print(weightBuffer);
            u8g2_lcd.print("g");

            u8g2_lcd.setCursor(64, 12 + i * 10);
            u8g2_lcd.print("C: ");
            u8g2_lcd.print(timestampBuffer);
        }

    } while (u8g2_lcd.nextPage());
}

void settings_page() {
    menu.drawMenu();
}

void lcd::draw_weight(float current, float average, float latest, int measurements_number) {
    if (Serial.available() > 0) {
        char inByte = Serial.read();

        if (inByte == 'm') {
            current_page = SETTINGS;
        } else if (inByte == 'z') {
            current_page = MAIN;
        } else if (inByte == 'x') {
            current_page = DETAILS;
        } else if (inByte == 'c') {
            current_page = HISTORY;
        }
    }

    switch (current_page) {
        case MAIN:
            main_page(current, average, latest, measurements_number);
            break;
        case SETTINGS:
            settings_page();
            break;
        case DETAILS:
            details_page(current);
            break;
        case HISTORY:
            history_page();
            break;
    }
//    if (!lcd::should_refresh()) {
//        return;
//    }
//
//    u8g2_lcd.clearBuffer();
//    u8g2_lcd.setFont(u8g2_font_ncenB08_tr);
//
//    char buffer[3][20];
//
//    dtostrf(current, 6, 2, buffer[0]);
//    const char *currentStr = buffer[0];
//
//    dtostrf(average, 6, 2, buffer[1]);
//    const char *averageStr = buffer[1];
//
//    dtostrf(latest, 6, 2, buffer[2]);
//    const char *latestStr = buffer[2];
//
//    u8g2_lcd.drawStr(10, 20, "CUR:");
//    u8g2_lcd.drawStr(50, 20, currentStr);
//
//    u8g2_lcd.drawStr(10, 34, "AVG:");
//    u8g2_lcd.drawStr(50, 34, averageStr);
//
//    u8g2_lcd.drawStr(10, 52, "LST:");
//
//    if (latest > 50) {
//        u8g2_lcd.drawStr(50, 52, latestStr);
//    } else {
//        u8g2_lcd.drawStr(50, 52, "-");
//    }
//
//    u8g2_lcd.drawFrame(5, 5, 118, 54);
//
//    u8g2_lcd.sendBuffer();
//
//    lcd::set_refresh_time();
}