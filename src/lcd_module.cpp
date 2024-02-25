#include "lcd_module.h"

U8G2_ST7567_ENH_DG128064I_F_SW_I2C u8g2_lcd(U8G2_R0, SCL, SDA, U8X8_PIN_NONE); // Set the LCD pins

GEM_u8g2 menu(u8g2_lcd, GEM_POINTER_DASH, 5, 10, 10, 86);

GEMPage menuPage("Ustawienia - Kurwaga v1.0");

GEMPage datePage("Data", menuPage);
GEMPage timePage("Czas", menuPage);
GEMPage offsetPage("Zakres sredniej", menuPage);
GEMPage calibratePage("Kalibracja", menuPage);

GEMItem dateItem("Data", datePage);
GEMItem timeItem("Czas", timePage);
GEMItem offsetItem("Zakres sredniej", offsetPage);
GEMItem calibrateItem("Kalibracja", calibratePage);

// Time settings page
SelectOptionByte select_hour_options[] = {
        {"0",  0},
        {"1",  1},
        {"2",  2},
        {"3",  3},
        {"4",  4},
        {"5",  5},
        {"6",  6},
        {"7",  7},
        {"8",  8},
        {"9",  9},
        {"10", 10},
        {"11", 11},
        {"12", 12},
        {"13", 13},
        {"14", 14},
        {"15", 15},
        {"16", 16},
        {"17", 17},
        {"18", 18},
        {"19", 19},
        {"20", 20},
        {"21", 21},
        {"22", 22},
        {"23", 23}
};
GEMSelect select_hour(sizeof(select_hour_options) / sizeof(SelectOptionByte), select_hour_options);

int setting_hour = 0;

void validate_hour() {
    Serial.println("Hour: " + String(setting_hour));
}

GEMItem hour_item("Godzina:", setting_hour, select_hour, validate_hour);

SelectOptionByte select_minute_second_options[] = {
        {"0",  0},
        {"1",  1},
        {"2",  2},
        {"3",  3},
        {"4",  4},
        {"5",  5},
        {"6",  6},
        {"7",  7},
        {"8",  8},
        {"9",  9},
        {"10", 10},
        {"11", 11},
        {"12", 12},
        {"13", 13},
        {"14", 14},
        {"15", 15},
        {"16", 16},
        {"17", 17},
        {"18", 18},
        {"19", 19},
        {"20", 20},
        {"21", 21},
        {"22", 22},
        {"23", 23},
        {"24", 24},
        {"25", 25},
        {"26", 26},
        {"27", 27},
        {"28", 28},
        {"29", 29},
        {"30", 30},
        {"31", 31},
        {"32", 32},
        {"33", 33},
        {"34", 34},
        {"35", 35},
        {"36", 36},
        {"37", 37},
        {"38", 38},
        {"39", 39},
        {"40", 40},
        {"41", 41},
        {"42", 42},
        {"43", 43},
        {"44", 44},
        {"45", 45},
        {"46", 46},
        {"47", 47},
        {"48", 48},
        {"49", 49},
        {"50", 50},
        {"51", 51},
        {"52", 52},
        {"53", 53},
        {"54", 54},
        {"55", 55},
        {"56", 56},
        {"57", 57},
        {"58", 58},
        {"59", 59}

};

GEMSelect select_minute(sizeof(select_minute_second_options) / sizeof(SelectOptionByte), select_minute_second_options);

int setting_minute = 0;

void validate_minute() {
    Serial.println("Minute: " + String(setting_minute));
}

GEMItem minute_item("Minuta:", setting_minute, select_minute, validate_minute);

GEMSelect select_second(sizeof(select_minute_second_options) / sizeof(SelectOptionByte), select_minute_second_options);

int setting_second = 0;

void validate_second() {
    Serial.println("Second: " + String(setting_second));
}

GEMItem second_item("Sekunda:", setting_second, select_second, validate_second);

void save_time_to_rtc() {
    Serial.println("Save time");
    menu.setMenuPageCurrent(menuPage);
}

GEMItem save_time("Zapisz", save_time_to_rtc);
// END Time settings page

// Settings date page
SelectOptionByte select_year_options[] = {
        {"2024", 24},
        {"2025", 25},
        {"2026", 26},
        {"2027", 27},
        {"2028", 28},
        {"2029", 29},
        {"2030", 30},
};

GEMSelect select_year(sizeof(select_year_options) / sizeof(SelectOptionByte), select_year_options);

int setting_year = 24;

void validate_year() {
    Serial.println("Year: " + String(setting_year));
}

GEMItem year_item("Rok:", setting_year, select_year, validate_year);

SelectOptionByte select_month_options[] = {
        {"Sty", 1},
        {"Lut", 2},
        {"Mar", 3},
        {"Kwi", 4},
        {"Maj", 5},
        {"Cze", 6},
        {"Lip", 7},
        {"Sie", 8},
        {"Wrz", 9},
        {"Paz", 10},
        {"Lis", 11},
        {"Gru", 12},
};

GEMSelect select_month(sizeof(select_month_options) / sizeof(SelectOptionByte), select_month_options);

int setting_month = 1;

void validate_month() {
    Serial.println("Month: " + String(setting_month));
}

GEMItem month_item("Miesiac:", setting_month, select_month, validate_month);

SelectOptionByte select_day_options[] = {
        {"1",  1},
        {"2",  2},
        {"3",  3},
        {"4",  4},
        {"5",  5},
        {"6",  6},
        {"7",  7},
        {"8",  8},
        {"9",  9},
        {"10", 10},
        {"11", 11},
        {"12", 12},
        {"13", 13},
        {"14", 14},
        {"15", 15},
        {"16", 16},
        {"17", 17},
        {"18", 18},
        {"19", 19},
        {"20", 20},
        {"21", 21},
        {"22", 22},
        {"23", 23},
        {"24", 24},
        {"25", 25},
        {"26", 26},
        {"27", 27},
        {"28", 28},
        {"29", 29},
        {"30", 30},
        {"31", 31},
};

GEMSelect select_day(sizeof(select_day_options) / sizeof(SelectOptionByte), select_day_options);

int setting_day = 1;

void validate_day() {
    Serial.println("Day: " + String(setting_day));
}

GEMItem day_item("Dzien:", setting_day, select_day, validate_day);

void save_date_to_rtc() {
    Serial.println("Save date");
    menu.setMenuPageCurrent(menuPage);
}

GEMItem save_date("Zapisz", save_date_to_rtc);
// END Settings date page

// Offset hours settings page
SelectOptionByte select_offset_options[] = {
        {"1h",  1},
        {"2h",  2},
        {"3h",  3},
        {"4h",  4},
        {"6h",  6},
        {"12h", 12},
        {"24h", 24},
};

GEMSelect select_offset(sizeof(select_offset_options) / sizeof(SelectOptionByte), select_offset_options);

int setting_offset = 1;

void validate_offset() {
    Serial.println("Offset: " + String(setting_offset));
}

GEMItem offset_item("Zakres:", setting_offset, select_offset, validate_offset);
// END Offset hours settings page

// Calibration settings page
void calibrate() {
    Serial.println("Calibrate");
    menu.setMenuPageCurrent(menuPage);
}

void tare() {
    Serial.println("Tare");
    menu.setMenuPageCurrent(menuPage);
}

GEMItem calibrate_item("Kalibracja", calibrate);
GEMItem tare_item("Taruj", tare);
// END Calibration settings page

void setupMenu() {
    // Time settings page
    timePage.addMenuItem(hour_item);
    timePage.addMenuItem(minute_item);
    timePage.addMenuItem(second_item);
    timePage.addMenuItem(save_time);
    // end time settings page

    // Settings date page
    datePage.addMenuItem(year_item);
    datePage.addMenuItem(month_item);
    datePage.addMenuItem(day_item);
    datePage.addMenuItem(save_date);
    // end settings date page

    // Offset hours settings page
    offsetPage.addMenuItem(offset_item);
    // end offset hours settings page

    // Calibration settings page
    calibratePage.addMenuItem(calibrate_item);
    calibratePage.addMenuItem(tare_item);
    // end calibration settings page

    // Add menu items to menu page
    menuPage.addMenuItem(dateItem);
    menuPage.addMenuItem(timeItem);
    menuPage.addMenuItem(offsetItem);
    menuPage.addMenuItem(calibrateItem);

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

    // Sets splash screen
    menu.setSplash(logo_width, logo_height, logo_bits);
    menu.hideVersion();

    menu.init();
    setupMenu();
}

enum Page {
    MAIN = 0,
    DETAILS = 1,
    HISTORY = 2,
    SETTINGS = 3
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
    time_t timestamp;
};

// Assuming you have an array to store measurements
Measurement measurements[10]; // Adjust the size based on your needs

// Variable to keep track of the number of measurements
int numMeasurements = 0;

void generateMockData() {
    // Generate mock data for demonstration
    for (int i = 0; i < 10; ++i) {
        measurements[i].weight = rand() % 1000 + 500.0; // Random weight between 50.0 and 149.9 grams
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

            dtostrf(measurements[i].weight, 4, 1, weightBuffer);

            struct tm *tm_info = localtime(&measurements[i].timestamp);

            u8g2_lcd.setCursor(2, 12 + i * 10);
            u8g2_lcd.print("W: ");
            u8g2_lcd.print(weightBuffer);
            u8g2_lcd.print("g");

            u8g2_lcd.setCursor(64, 12 + i * 10);
            u8g2_lcd.print("C: ");
            u8g2_lcd.println(String(tm_info->tm_hour) + ":" + String(tm_info->tm_min) + ":" + String(tm_info->tm_sec));
        }

    } while (u8g2_lcd.nextPage());
}

void settings_page() {
    menu.drawMenu();
}

Page pages[] = {MAIN, DETAILS, HISTORY};

void lcd::register_pressed_key(int key) {
//    Serial.print("Key: ");
//    switch (key) {
//        case GEM_KEY_RIGHT:
//            Serial.println("Right");
//            break;
//        case GEM_KEY_LEFT:
//            Serial.println("Left");
//            break;
//        case GEM_KEY_OK:
//            Serial.println("OK");
//            break;
//        case GEM_KEY_CANCEL:
//            Serial.println("Cancel");
//            break;
//        case GEM_KEY_UP:
//            Serial.println("Up");
//            break;
//        case GEM_KEY_DOWN:
//            Serial.println("Down");
//            break;
//    }

    if (current_page != SETTINGS) {
        if (key == GEM_KEY_RIGHT && current_page < 2) {
            current_page = pages[current_page + 1];
        } else if (key == GEM_KEY_LEFT && current_page > 0) {
            current_page = pages[current_page - 1];
        } else if (key == GEM_KEY_OK) {
            current_page = SETTINGS;
        }
    } else if (menu.readyForKey()) {
        if (menu.getCurrentMenuPage() == &menuPage && key == GEM_KEY_CANCEL) {
            current_page = MAIN;
        } else {
            menu.registerKeyPress(key);
        }
    }
}

void lcd::draw_page(float current, float average, float latest, int measurements_number) {
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
}