#ifndef DETECTOR_MODULE_H
#define DETECTOR_MODULE_H

#include "logger_module.h"
#include <vector>

// For running median
#include <algorithm>
#include <queue>

namespace detector {
    class RunningMedian {
    private:
        float last_sample{};
        std::vector<float> elements;
        const size_t max_size;

    public:
        explicit RunningMedian(size_t max_size);

        void add(float value);

        void clear();

        [[nodiscard]] float get() const;

        [[nodiscard]] float get_last_sample() const;

        [[nodiscard]] bool is_full() const;
    };

    struct Measurement {
        float weight;
        int timestamp;

    public:
        Measurement(float weight, int timestamp);
    };

    enum Status {
        PENDING,
        DATA_READY,
        REQUIRE_TARE
    };

    class Detector {
    private:
        // Defines max elements count in running median
        static const int MEDIAN_ELEMENTS = 20;

        // Defines min weight [g] that can be detecteds
        static const int MIN_DETECTABLE_WEIGHT = 50;

        // If percentage change between measurements is greater - stability threshold resets
        static const float MAX_PERCENT_WEIGHT_CHANGE;

        // If percentage change between last sample and actual sample is larger, reset measurement
        static const float MAX_PERCENTAGE_DIFF_BETWEEN_SAMPLES;

        // Time [ms] for weight to be stable to detect measurement
        static const int STABLE_PERIOD = 3500;

        // Time [ms] for weight to show negative value before being tared
        static const int NEGATIVE_PERIOD = 2000;

        RunningMedian median;

        // Stores latest detected measurement
        Measurement detected_measurement;

        // Defines whether detector has detected measurement waiting to be captured;
        Status status;

        // Contains time when weight started to be stable
        unsigned long stable_since;

        // Contains time when weight started to show negative value
        unsigned long negative_since{};

        void set_ready(float detected);

        void set_require_tare();

    public:
        Detector();                              // Constructor
        void add_measurement(float measurement); // Updated function
        [[nodiscard]] Status get_status() const;

        Measurement get_detected();              // Updated function
        void reset();
    };
}

#endif // DETECTOR_MODULE_H
