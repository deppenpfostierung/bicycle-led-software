#include "popupscreen.h"

// local includes
#include "input/buttons.h"

namespace bicycle::gui
{

void BicyclePopupDisplay::rawButtonPressed(uint8_t button)
{
    if (const auto translated = translateRawButton(button))
        buttonPressed(*translated);
}

void BicyclePopupDisplay::rawButtonReleased(uint8_t button)
{
    if (const auto translated = translateRawButton(button))
        buttonReleased(*translated);
}

void BicyclePopupDisplay::buttonPressed(espgui::Button button)
{
    Base::buttonPressed(button);
    buttonPressedCommon(button);
}

void BicyclePopupDisplay::buttonReleased(espgui::Button button)
{
    // Base::buttonReleased(button);
    buttonReleasedCommon(button);
}

} // namespace bicycle::gui