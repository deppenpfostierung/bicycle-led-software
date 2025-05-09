#pragma once

// 3rdparty lib includes
#include <screenmanager.h>

// local includes
#include "guihelpers/display.h"
#include "guihelpers/widgets/statusicons.h"
#include "screens/menus/mainmenu.h"

namespace bicycle::gui
{

class StartDisplay : public BicycleDisplay
{
    using Base = BicycleDisplay;

public:
    void initScreen(espgui::TftInterface &tft) override;

    void redraw(espgui::TftInterface &tft) override;

    void update() override;

    void buttonPressed(espgui::Button button) override
    {
        espgui::pushScreen<MainMenu>();
    }

private:
    StatusIcons m_statusIcons { 10, 10 };
};

} // namespace bicycle::gui