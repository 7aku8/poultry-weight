//
// Created by Jakub on 03/03/2024.
//

#ifndef POULTRY_WEIGHT_DATA_PERSIST_MODULE_H
#define POULTRY_WEIGHT_DATA_PERSIST_MODULE_H

#include <Arduino.h>
#include <SD.h>
#include <ArduinoJson.h>
#include "detector_module.h"

namespace data_persist {
    class DataPersist {
    public:
        void init();

        void save_measurement(const detector::Measurement measurement);

        int fetch_history(detector::Measurement measurements[], int maxCount);
    };
}

#endif //POULTRY_WEIGHT_DATA_PERSIST_MODULE_H
