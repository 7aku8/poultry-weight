#include <Arduino.h>
#include "lcd_module.h"
#include "logger_module.h"
#include "weight_module.h"
#include "detector_module.h"
#include "keyboard_module.h"
#include "timer_module.h"
#include "data_persist_module.h"

keyboard::Keyboard keys(A0);
data_persist::DataPersist saver;

void setup() {
    logger::init();
    timer::init();
    lcd::init();

    weight::init();

    saver.init();
    keys.init();
}

float weight_reading = 0.0;
detector::Measurement detected_measurement(0.0, 0);
detector::Detector weight_detector;

void loop() {
    bool tare_just_completed = weight::check_tare_completed();
    if (tare_just_completed) {
        weight_detector.reset();
    }

    bool measurement_captured = weight::capture_measurement(weight_reading);

    if (measurement_captured && !weight::is_taring()) {
        weight_detector.add_measurement(weight_reading);
    }

    detector::Status detector_status = weight_detector.get_status();

    switch (detector_status) {
        case detector::DATA_READY:
            detected_measurement = weight_detector.get_detected();
            weight::tare_without_delay();
            saver.save_measurement(detected_measurement);
            break;
        case detector::REQUIRE_TARE:
            weight::tare_without_delay();
            break;
        case detector::PENDING:
            break;
    }

    if (keys.was_button_pressed()) {
        int pressed_button = keys.get_pressed_button();
        lcd::register_pressed_key(pressed_button);
    }

    // Check if the specified refresh interval has passed
    lcd::draw_page(weight_reading, weight_reading, detected_measurement.weight, 69);
}