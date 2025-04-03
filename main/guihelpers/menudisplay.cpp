#include "menudisplay.h"

// local includes
#include "input/buttons.h"

namespace bicycle::gui
{

void BicycleMenuDisplay::rawButtonPressed(uint8_t button)
{
    //Base::rawButtonPressed(button);
    if (const auto translated = translateRawButton(button))
        buttonPressed(*translated);
}

void BicycleMenuDisplay::rawButtonReleased(uint8_t button)
{
    //Base::rawButtonReleased(button);
    if (const auto translated = translateRawButton(button))
        buttonReleased(*translated);
}

void BicycleMenuDisplay::buttonPressed(espgui::Button button)
{
    Base::buttonPressed(button);
    buttonPressedCommon(button);
}

void BicycleMenuDisplay::buttonReleased(espgui::Button button)
{
    //Base::buttonReleased(button);
    buttonReleasedCommon(button);
}

} // namespace bicycle::gui