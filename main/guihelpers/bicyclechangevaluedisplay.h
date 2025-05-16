#pragma once

// 3rdparty lib includes
#include <changevaluedisplay.h>

// local includes
#include "errorhandler.h"
#include "input/buttons.h"

namespace bicycle::gui
{
template <typename Tvalue>
class BicycleChangeValueDisplay : public espgui::ChangeValueDisplay<Tvalue>, public virtual BicycleErrorHandler
{
    using Base = espgui::ChangeValueDisplay<Tvalue>;

public:
    void rawButtonPressed(uint8_t button) override;
    void rawButtonReleased(uint8_t button) override;

    void buttonPressed(espgui::Button button) override;
    void buttonReleased(espgui::Button button) override;
};

template <typename Tvalue> void BicycleChangeValueDisplay<Tvalue>::rawButtonPressed(uint8_t button)
{
    if (const auto translated = translateRawButton(button))
        buttonPressed(*translated);
}

template <typename Tvalue> void BicycleChangeValueDisplay<Tvalue>::rawButtonReleased(uint8_t button)
{
    if (const auto translated = translateRawButton(button))
        buttonReleased(*translated);
}

template <typename Tvalue> void BicycleChangeValueDisplay<Tvalue>::buttonPressed(espgui::Button button)
{
    Base::buttonPressed(button);
    buttonPressedCommon(button);
}

template <typename Tvalue> void BicycleChangeValueDisplay<Tvalue>::buttonReleased(espgui::Button button)
{
    Base::buttonReleased(button);
    buttonReleasedCommon(button);
}
} // namespace bicycle::gui