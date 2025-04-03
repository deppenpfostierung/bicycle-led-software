#include "display.h"

// local includes
#include "input/buttons.h"

namespace bicycle::gui
{
void BicycleDisplay::rawButtonPressed(uint8_t button)
{
    //Base::rawButtonPressed(button);
    if (const auto translated = translateRawButton(button))
        buttonPressed(*translated);
}

void BicycleDisplay::rawButtonReleased(uint8_t button)
{
    //Base::rawButtonReleased(button);
    if (const auto translated = translateRawButton(button))
        buttonReleased(*translated);
}

void BicycleDisplay::buttonPressed(espgui::Button button)
{
    //Base::buttonPressed(button);
    buttonPressedCommon(button);
}

void BicycleDisplay::buttonReleased(espgui::Button button)
{
    //Base::buttonReleased(button);
    buttonReleasedCommon(button);
}
} // namespace bicycle::gui