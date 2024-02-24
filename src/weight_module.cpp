#include "weight_module.h"

const int HX711_DOUT = D3;
const int HX711_SCK = D4;

const int samples = 2;

const int gain = 64;
unsigned long stabilizingtime = 600; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
boolean _tare = true;                 // set this to false if you don't want tare to be performed in the next step

HX711_ADC LoadCell(HX711_DOUT, HX711_SCK);
logger::Logger logs("Weight Module");

const int calVal_eepromAdress = 0;
const int tareOffsetVal_eepromAdress = 4;

const int SAMPLES_PER_SECOND = 10;

unsigned long previous_measurement_time = 0;

bool _is_taring = false;

void weight::set_refresh_time() {
    previous_measurement_time = millis();
}

bool weight::should_refresh() {
    unsigned long current_time = millis();
    return current_time - previous_measurement_time >= 1000.0 / SAMPLES_PER_SECOND;
}

void weight::init() {
    LoadCell.begin(gain);

#if defined(ESP8266) || defined(ESP32)
    EEPROM.begin(512);
#endif

    float calibrationValue = 0;
    EEPROM.get(calVal_eepromAdress,
               calibrationValue); // uncomment this if you want to fetch the calibration value from eeprom
    LoadCell.setCalFactor(calibrationValue);

    LoadCell.start(stabilizingtime, _tare);
    if (LoadCell.getTareTimeoutFlag() || LoadCell.getSignalTimeoutFlag()) {
        logs.debug("Timeout, check MCU>HX711 wiring and pin designations");
        while (1);
    } else {
        LoadCell.setCalFactor(calibrationValue);
        LoadCell.setSamplesInUse(samples);
        logs.debug("Startup is complete");
    }
    while (!LoadCell.update());
}

/**
 * @brief Captures measurement and saves weight value to passed parameter
 * @param current_reading Variable to save measurement to
 * @returns True if measurement captured, otherwise false
*/
bool weight::capture_measurement(float &current_reading) {
    bool should_capture = weight::should_refresh();
    uint8_t should_update = LoadCell.update();

    if (should_capture && should_update == 1) {
        current_reading = LoadCell.getData();
        weight::set_refresh_time();
    }

    return should_capture;
}

void weight::calibrate() {
    logs.log("***");
    logs.log("Start calibration:");
    logs.log("Place the load cell an a level stable surface.");
    logs.log("Remove any load applied to the load cell.");
    logs.log("Send 't' from serial monitor to set the tare offset.");

    boolean _resume = false;
    while (!_resume) {
        LoadCell.update();
        if (Serial.available() > 0) {
            if (Serial.available() > 0) {
                char inByte = Serial.read();
                if (inByte == 't')
                    LoadCell.tareNoDelay();
            }
        }
        if (LoadCell.getTareStatus()) {
            logs.log("Tare complete");
            _resume = true;
        }
    }

    logs.log("Now, place your known mass on the loadcell.");
    logs.log("Then send the weight of this mass (i.e. 100.0) from serial monitor.");

    float known_mass = 0;
    _resume = false;
    while (_resume == false) {
        LoadCell.update();
        if (Serial.available() > 0) {
            known_mass = Serial.parseFloat();
            if (known_mass != 0) {
                logs.log("Known mass is: ");
                logs.log(known_mass);
                _resume = true;
            }
        }
    }

    LoadCell.refreshDataSet();                                          // refresh the dataset to be sure that the known mass is measured correct
    float newCalibrationValue = LoadCell.getNewCalibration(known_mass); // get the new calibration value

    logs.log("New calibration value has been set to: ");
    logs.log(newCalibrationValue);
    logs.log(", use this as calibration value (calFactor) in your project sketch.");
    logs.log("Save this value to EEPROM adress ");
    logs.log(calVal_eepromAdress);
    logs.log("? y/n");

    _resume = false;
    while (!_resume) {
        if (Serial.available() > 0) {
            char inByte = Serial.read();
            if (inByte == 'y') {
#if defined(ESP8266) || defined(ESP32)
                EEPROM.begin(512);
#endif
                EEPROM.put(calVal_eepromAdress, newCalibrationValue);
#if defined(ESP8266) || defined(ESP32)
                EEPROM.commit();
#endif
                EEPROM.get(calVal_eepromAdress, newCalibrationValue);
                logs.log("Value ");
                logs.log(newCalibrationValue);
                logs.log(" saved to EEPROM address: ");
                logs.log(calVal_eepromAdress);
                _resume = true;
            } else if (inByte == 'n') {
                logs.log("Value not saved to EEPROM");
                _resume = true;
            }
        }
    }

    logs.log("End calibration");
    logs.log("***");
    logs.log("To re-calibrate, send 'r' from serial monitor.");
    logs.log("For manual edit of the calibration value, send 'c' from serial monitor.");
    logs.log("***");
}

void weight::change_saved_cal_factor() {
    float oldCalibrationValue = LoadCell.getCalFactor();
    boolean _resume = false;
    logs.log("***");
    logs.log("Current value is: ");
    logs.log(oldCalibrationValue);
    logs.log("Now, send the new value from serial monitor, i.e. 696.0");
    float newCalibrationValue;
    while (!_resume) {
        if (Serial.available() > 0) {
            newCalibrationValue = Serial.parseFloat();
            if (newCalibrationValue != 0) {
                logs.log("New calibration value is: ");
                logs.log(newCalibrationValue);
                LoadCell.setCalFactor(newCalibrationValue);
                _resume = true;
            }
        }
    }
    _resume = false;
    logs.log("Save this value to EEPROM adress ");
    logs.log(calVal_eepromAdress);
    logs.log("? y/n");
    while (!_resume) {
        if (Serial.available() > 0) {
            char inByte = Serial.read();
            if (inByte == 'y') {
#if defined(ESP8266) || defined(ESP32)
                EEPROM.begin(512);
#endif
                EEPROM.put(calVal_eepromAdress, newCalibrationValue);
#if defined(ESP8266) || defined(ESP32)
                EEPROM.commit();
#endif
                EEPROM.get(calVal_eepromAdress, newCalibrationValue);
                logs.log("Value ");
                logs.log(newCalibrationValue);
                logs.log(" saved to EEPROM address: ");
                logs.log(calVal_eepromAdress);
                _resume = true;
            } else if (inByte == 'n') {
                logs.log("Value not saved to EEPROM");
                _resume = true;
            }
        }
    }
    logs.log("End change calibration value");
    logs.log("***");
}

// zero offset value (tare), calculate and save to EEprom:
void refresh_offset_value_and_save_to_eeprom() {
    long _offset = 0;
    logs.log("Calculating tare offset value...");
    LoadCell.tare();                                 // calculate the new tare / zero offset value (blocking)
    _offset = LoadCell.getTareOffset();              // get the new tare / zero offset value
    EEPROM.put(tareOffsetVal_eepromAdress, _offset); // save the new tare / zero offset value to EEprom
#if defined(ESP8266) || defined(ESP32)
    EEPROM.commit();
#endif
    LoadCell.setTareOffset(_offset); // set value as library parameter (next restart it will be read from EEprom)
    logs.log("New tare offset value:");
    logs.log(_offset);
    logs.log(", saved to EEprom adr:");
    logs.log(tareOffsetVal_eepromAdress);
}

/**
 * @brief Simply checks if async tare has been completed, logs to serial monitor if yes
 */
bool weight::check_tare_completed() {
    if (LoadCell.getTareStatus()) {
        _is_taring = false;
        return true;
    }

    return false;
}

void weight::tare_without_delay() {
    if (_is_taring) {
        return;
    }

    _is_taring = true;
    LoadCell.tareNoDelay();
}

bool weight::is_taring() {
    return _is_taring;
}