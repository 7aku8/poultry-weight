#include "detector_module.h"
#include <cmath>

using namespace detector;

logger::Logger detector_logs("Detector Module");

const float Detector::MAX_PERCENT_WEIGHT_CHANGE = 2.0f;
const float Detector::MAX_PERCENTAGE_DIFF_BETWEEN_SAMPLES = 2.0f;

RunningMedian::RunningMedian(size_t max_size) : max_size(max_size) {}

void RunningMedian::add(float value) {
    elements.push_back(value);
    if (elements.size() > max_size) {
        elements.erase(elements.begin());
    }
    std::sort(elements.begin(), elements.end());
    last_sample = value;
}

/**
 * @brief Removes all saved values
*/
void RunningMedian::clear() {
    elements.clear();
}

/**
 * @brief Returns median
*/
float RunningMedian::get() const {
    size_t size = elements.size();
    if (size == 0) {
        return 0.0;
    }

    std::vector<float> sorted_copy(elements); // Make a copy since nth_element modifies the order
    std::nth_element(sorted_copy.begin(), sorted_copy.begin() + size / 2, sorted_copy.end());

    if (size % 2 == 0) {
        // If even number of elements, average the middle two
        return (sorted_copy[size / 2 - 1] + sorted_copy[size / 2]) / 2.0;
    }
    // If odd number of elements, return the middle one
    return sorted_copy[size / 2];
}

/**
 * @brief Returns latest added sample
*/
float RunningMedian::get_last_sample() const {
    return last_sample;
}

/**
 * @brief Returns true if actual number of elements considered in median is equal to its max size
 */
bool RunningMedian::is_full() const {
    return elements.size() == max_size;
}

Measurement::Measurement(float weight, int timestamp) : weight(weight), timestamp(timestamp) {};

Detector::Detector() : median(MEDIAN_ELEMENTS), detected_measurement(0.0, 0), status(PENDING), stable_since(0) {};

void Detector::add_measurement(float measurement) {
    // May need to be deleted, but may be useful as well, don't know yet
    if (status != PENDING) {
        detector_logs.debug("Waiting to get reading from.");
        return;
    }

    // Checking negative period
    if (measurement < -2) {
        if (negative_since == 0) {
            negative_since = millis();
            return;
        }

        unsigned int negative_diff = millis() - negative_since;

        if (negative_diff > NEGATIVE_PERIOD) {
            set_require_tare();
            return;
        }
    } else {
        negative_since = 0;
    }
    // End checking negative period

    detector_logs.debug("Adding new measurement");
    detector_logs.debug(measurement);

    float previous_sample = median.get_last_sample();
    median.add(measurement);

    if (!median.is_full()) {
        detector_logs.debug("Too few samples to detect anything.");
        return;
    }

    float diff = abs(median.get() - measurement); // Difference between median and present value

    bool diff_too_large = (diff / measurement / 100) > MAX_PERCENT_WEIGHT_CHANGE;

    if (diff_too_large) {
        detector_logs.debug("Diff too large.");

        reset();
        return;
    }

    bool is_drift_too_large =
            (abs(previous_sample - measurement) / measurement / 100) > MAX_PERCENTAGE_DIFF_BETWEEN_SAMPLES;

    if (is_drift_too_large) {
        detector_logs.debug("Drift between samples is too large.");

        reset();
        return;
    }

    if (stable_since == 0) {
        detector_logs.debug("Begin stable period.");

        stable_since = millis();
        return;
    }

    unsigned long now = millis();
    unsigned long time_diff = now - stable_since;

    bool is_time_diff = time_diff > STABLE_PERIOD;

    bool is_enough_weight = measurement > MIN_DETECTABLE_WEIGHT;

    if (is_time_diff) {
        if (!is_enough_weight) {
            detector_logs.debug("Detected measurement too low.");

            reset();
            return;
        }

        detector_logs.debug("Mesurement detected:");
        detector_logs.debug(measurement);

        set_ready(measurement);
    }
}

/**
 * @brief Returns true if detector detected measurement and is waiting to get it from itself
*/
Status Detector::get_status() const {
    return status;
}

/**
 * @brief Returns detected measurement and resets detector state
*/
Measurement Detector::get_detected() {
    Measurement saved = detected_measurement;
    reset();

    return saved;
}

/**
 * @brief Sets detector ready to get detected measurement from
 * @param detected Detected measurement
*/
void Detector::set_ready(float detected) {
    status = DATA_READY;
    detected_measurement.weight = detected;
    detected_measurement.timestamp = millis();
}

/**
 * @brief Sets status of detector - require tare
*/
void Detector::set_require_tare() {
    status = REQUIRE_TARE;
}

/**
 * @brief Makes detector not ready to get data from
*/
void Detector::reset() {
    status = PENDING;
    detected_measurement.weight = 0;
    detected_measurement.timestamp = 0;
    stable_since = 0;

    median.clear();

    detector_logs.debug("Resetting measurement.");
}
