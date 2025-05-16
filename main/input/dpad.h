#pragma once

#include <sdkconfig.h>

// local includes
#include "dpadimpl.h"

namespace bicycle::buttons
{

constexpr std::array<pin_t, 2> OUT_PINS = { CONFIG_BICYCLE_PIN_BUTTON_OUT_1, CONFIG_BICYCLE_PIN_BUTTON_OUT_2 };

constexpr std::array<pin_t, 4> IN_PINS = { CONFIG_BICYCLE_PIN_BUTTON_IN_1,
                                           CONFIG_BICYCLE_PIN_BUTTON_IN_2,
                                           CONFIG_BICYCLE_PIN_BUTTON_IN_3,
                                           CONFIG_BICYCLE_PIN_BUTTON_IN_4 };

extern Dpad<IN_PINS.size(), OUT_PINS.size(), IN_PINS, OUT_PINS> dpad;

void init();
void update();

bool isValidConfig();

} // namespace bicycle::buttons
