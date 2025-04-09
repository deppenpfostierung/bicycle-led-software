#pragma once

// 3rdparty lib includes
#include <messagepopupdisplay.h>

namespace bicycle::gui
{

class BicyclePopupDisplay : public espgui::MessagePopupDisplay
{
    using Base = espgui::MessagePopupDisplay;

public:
    using Base::Base;

    void rawButtonPressed(uint8_t button) override;
    void rawButtonReleased(uint8_t button) override;

    void buttonPressed(espgui::Button button) override;
    void buttonReleased(espgui::Button button) override;
};

} // namespace bicycle::gui