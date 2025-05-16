#pragma once

// 3rdparty lib includes
#include <menudisplay.h>

namespace bicycle::gui
{
class BicycleMenuDisplay : public espgui::MenuDisplay
{
    using Base = espgui::MenuDisplay;

public:
    void rawButtonPressed(uint8_t button) override;
    void rawButtonReleased(uint8_t button) override;

    void buttonPressed(espgui::Button button) override;
    void buttonReleased(espgui::Button button) override;
};
} // namespace bicycle::gui
