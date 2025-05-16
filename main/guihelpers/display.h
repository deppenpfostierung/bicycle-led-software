#pragma once

// 3rdparty lib includes
#include <display.h>

namespace bicycle::gui
{

class BicycleDisplay : public espgui::Display
{
    using Base = espgui::Display;

public:
    void rawButtonPressed(uint8_t button) override;
    void rawButtonReleased(uint8_t button) override;

    void buttonPressed(espgui::Button button) override;
    void buttonReleased(espgui::Button button) override;
};

} // namespace bicycle::gui
