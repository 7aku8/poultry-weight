//
// Created by Jakub on 25/02/2024.
//

#ifndef POULTRY_WEIGHT_KEYBOARD_MODULE_H
#define POULTRY_WEIGHT_KEYBOARD_MODULE_H

#include <Arduino.h>
#include <GEM_u8g2.h>

namespace keyboard {
    class Button {
        static const int RELATIVE_ERROR = 10;
        static const int PRESS_TIME_THRESHOLD = 50; // 50ms - press time required to activate the button

        int activation_value_;
        int press_value_;
        time_t pressed_since;


    public:
        Button(int activation_value, int press_value);

        bool is_pressed(int input_value);

        int get_press_value();
    };

    class Keyboard {
        Button buttons[6];
        int input_pin;
        Button *pressed_button;

    public:
        explicit Keyboard(int input_pin);

        void init();

        bool was_button_pressed();

        int get_pressed_button();
    };

}

#endif //POULTRY_WEIGHT_KEYBOARD_MODULE_H
