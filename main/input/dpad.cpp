#include "dpad.h"

// local includes
#include <configs.h>

namespace bicycle::buttons
{
Dpad<IN_PINS.size(), OUT_PINS.size(), IN_PINS, OUT_PINS> dpad;

void init()
{
    dpad.init();
}

void update()
{
    dpad.update();
}

bool isValidConfig()
{
    return configs.dpad.mappingUp.value() != INPUT_BUTTON_NONE && configs.dpad.mappingDown.value() != INPUT_BUTTON_NONE
           && configs.dpad.mappingLeft.value() != INPUT_BUTTON_NONE
           && configs.dpad.mappingRight.value() != INPUT_BUTTON_NONE;
}

} // namespace bicycle::buttons