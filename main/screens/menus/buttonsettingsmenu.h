#pragma once

// 3rdparty lib includes
#include <screenmanager.h>

// local includes
#include "guihelpers/menudisplay.h"

namespace bicycle::gui
{

class ButtonSettingsMenu : public BicycleMenuDisplay
{
    using Base = BicycleMenuDisplay;

public:
    ButtonSettingsMenu();

    void back() override
    {
        espgui::popScreen();
    }

    std::string title() const override;
};

} // namespace bicycle::gui