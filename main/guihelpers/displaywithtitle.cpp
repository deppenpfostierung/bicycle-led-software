#include "displaywithtitle.h"

// local includes
#include "input/buttons.h"

namespace bicycle::gui
{

void BicycleDisplayWithTitle::rawButtonPressed(uint8_t button)
{
    // Base::rawButtonPressed(button);
    if (const auto translated = translateRawButton(button))
        buttonPressed(*translated);
}

void BicycleDisplayWithTitle::rawButtonReleased(uint8_t button)
{
    // Base::rawButtonReleased(button);
    if (const auto translated = translateRawButton(button))
        buttonReleased(*translated);
}

void BicycleDisplayWithTitle::buttonPressed(espgui::Button button)
{
    // Base::buttonPressed(button);
    buttonPressedCommon(button);
}

void BicycleDisplayWithTitle::buttonReleased(espgui::Button button)
{
    // Base::buttonReleased(button);
    buttonReleasedCommon(button);
}

} // namespace bicycle::gui
