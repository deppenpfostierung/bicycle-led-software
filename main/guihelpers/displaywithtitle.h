#pragma once

// 3rdparty lib includes
#include <displaywithtitle.h>

namespace bicycle::gui
{

class BicycleDisplayWithTitle : public espgui::DisplayWithTitle
{
    using Base = espgui::DisplayWithTitle;

public:
    void rawButtonPressed(uint8_t button) override;
    void rawButtonReleased(uint8_t button) override;

    void buttonPressed(espgui::Button button) override;
    void buttonReleased(espgui::Button button) override;
};
} // namespace bicycle::gui