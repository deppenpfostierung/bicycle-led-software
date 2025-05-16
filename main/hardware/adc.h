#pragma once

// system includes
#include <atomic>

namespace bicycle::hardware
{

extern bool adc_initialized;

namespace measure
{

extern const std::atomic<float> &battery_voltage;

extern const std::atomic<float> &battery_current;

extern const std::atomic<float> &aux_adc_0;

extern const std::atomic<float> &aux_adc_1;

} // namespace measure

void init_adc();

void update_adc();

} // namespace bicycle::hardware
