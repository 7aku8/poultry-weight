//
// Created by Jakub on 03/03/2024.
//

#include "data_persist_module.h"

#define PIN_SPI_CS D8
#define FILE_NAME "measurements.jsonl"

File root;

void data_persist::DataPersist::init() {
    if (!SD.begin(PIN_SPI_CS)) {
        while (true);
    }

    root = SD.open("/");
}

void data_persist::DataPersist::save_measurement(const detector::Measurement measurement) {
    File file = SD.open(FILE_NAME, FILE_WRITE);

    if (file) {
        JsonDocument doc;
        doc["weight"] = measurement.weight;
        doc["timestamp"] = measurement.timestamp.timestamp();

        serializeJson(doc, file);
        file.println();

        file.close();
    }
}

int data_persist::DataPersist::fetch_history(detector::Measurement measurements[], int maxCount) {
//    File dataFile = SD.open(FILE_NAME, FILE_READ);
//
//    JsonDocument doc;
//
//    if (dataFile) {
//        int count = 0;
//        dataFile.seek(dataFile.size());
//
//        while (count < maxCount && dataFile.position() > 0) {
//            // Find the beginning of a line
//            while (dataFile.peek() != '\n' && dataFile.position() > 0) {
//                dataFile.seek(dataFile.position() - 1);
//            }
//
//            // Read and parse the JSON line
//            String jsonLine = dataFile.readStringUntil('\n');
//            deserializeJson(doc, jsonLine);
//
//            // Access the values from the JSON object
//            float weight = doc["weight"];
//            unsigned long timestamp = doc["timestamp"];
//
//            // Store the values in the Measurement struct
//            measurements[count] = detector::Measurement();
//
//            count++;
//        }
//
//        dataFile.close();
//        return count;
//    } else {
//        Serial.println("Error opening data file.");
//        return 0;
//    }
    return 0;
}
