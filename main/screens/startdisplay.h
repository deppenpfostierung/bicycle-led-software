#pragma once

// 3rdparty lib includes
#include <screenmanager.h>

// local includes
#include "guihelpers/display.h"
#include "screens/menus/mainmenu.h"

namespace bicycle::gui
{

class StartDisplay : public BicycleDisplay
{
    using Base = BicycleDisplay;

    void buttonPressed(espgui::Button button) override
    {
        espgui::pushScreen<MainMenu>();
    }
};

} // namespace bicycle::gui