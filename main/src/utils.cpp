/*
 * utils.cpp
 * Implementations for utility helpers if needed.
 */

#include "utils.h"
#include "api.h"

struct PneumaticValue {
    std::atomic<bool>& piston;
    std::function<void(bool)> onChange;

    PneumaticValue(std::atomic<bool>& p, std::function<void(bool)> cb = {})
        : piston(p), onChange(cb) {}

    PneumaticValue& operator=(bool v) {
        piston.store(v);
        if (onChange) onChange(v);
        return *this;
    }

    operator bool() const { return piston.load(); }
};

std::atomic<bool> score_mid_piston_value{false};
std::atomic<bool> score_long_piston_value{false};
std::atomic<bool> park_piston_value{false};

PneumaticValue score_mid_value{
    score_mid_piston_value,
    [](bool v){
        std::cerr << "[Pneumatic] score_mid_piston -> " << (v ? "TRUE" : "FALSE") << '\n';
    }
};
PneumaticValue score_high_value{
    score_long_piston_value,
    [](bool v){
        std::cerr << "[Pneumatic] score_long_piston ->" << (v ? "TRUE" : "FALSE") << '\n';
    }
};
PneumaticValue park_value{
    park_piston_value,
    [](bool v){
        std::cerr << "[Pneumatic] park ->" << (v ? "TRUE" : "FALSE") << '\n';
    }
};