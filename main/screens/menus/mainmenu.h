#pragma once

// 3rdparty lib includes
#include <screenmanager.h>

// local includes
#include "guihelpers/menudisplay.h"

namespace bicycle::gui
{

class MainMenu : public BicycleMenuDisplay
{
    using Base = BicycleMenuDisplay;

public:
    MainMenu();

    void back() override
    {
        espgui::popScreen();
    }

    std::string title() const override;
};

} // namespace bicycle::gui
