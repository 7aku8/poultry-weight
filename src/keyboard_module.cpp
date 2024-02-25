#include "keyboard_module.h"

//
// Created by Jakub on 25/02/2024.
//
keyboard::Keyboard::Keyboard(int input_pin) : buttons{
        Button(912, GEM_KEY_LEFT),
        Button(823, GEM_KEY_RIGHT),
        Button(554, GEM_KEY_UP),
        Button(876, GEM_KEY_DOWN),
        Button(735, GEM_KEY_CANCEL),
        Button(12, GEM_KEY_OK)
}, pressed_button(nullptr) {
    this->input_pin = input_pin;
}

void keyboard::Keyboard::init() {
    pinMode(input_pin, INPUT);
}


keyboard::Button::Button(int activation_value, int press_value) : pressed_since(0) {
    this->activation_value_ = activation_value;
    this->press_value_ = press_value;
}

bool keyboard::Button::is_pressed(int input_value) {
    bool is_active = abs(input_value - activation_value_) < RELATIVE_ERROR;

    if (pressed_since == 0 && is_active) {
        pressed_since = millis();
    }

    time_t now = millis();

    if (pressed_since != 0 && now - pressed_since > PRESS_TIME_THRESHOLD) {
        pressed_since = 0;
        return true;
    }

    return false;
}

bool keyboard::Keyboard::was_button_pressed() {
    int key_value = analogRead(input_pin);

    for (int i = 0; i < 6; i++) {
        if (buttons[i].is_pressed(key_value)) {
            pressed_button = &buttons[i];
            return true;
        }
    }

    return false;
}

int keyboard::Keyboard::get_pressed_button() {
    int pressed_value = pressed_button->get_press_value();

    pressed_button = nullptr;

    return pressed_value;
}

int keyboard::Button::get_press_value() {
    return press_value_;
}
