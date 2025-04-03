#pragma once

// system includes
#include <optional>

// 3rdparty lib includes
#include <buttonsinterface.h>

namespace bicycle
{
enum BicycleButton
{
    Custom1 = espgui::Button::ButtonMax + 1,
    Custom2,
    Custom3,
    Custom4,
    Custom5,
    Custom6,
    Custom7,
    Custom8,
    Custom9,
    Custom10,
    Custom11,
    Custom12,
    Confirm = espgui::Button::Right,
    Back = espgui::Button::Left,
    ButtonMax = Back
};

[[nodiscard]] std::optional<espgui::Button> translateRawButton(uint8_t button);
void buttonPressedCommon(espgui::Button button);
void buttonReleasedCommon(espgui::Button button);

class BicycleButtons : public virtual espgui::ButtonsInterface
{
public:
    void rawButtonPressed(uint8_t button) override;
    void rawButtonReleased(uint8_t button) override;

    void buttonPressed(espgui::Button button) override;
    void buttonReleased(espgui::Button button) override;
};
} // namespace bicycle