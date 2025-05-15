#pragma once

// 3rdparty lib includes
#include <delayedconstruction.h>
#include <screenmanager.h>

// local includes
#include "guihelpers/display.h"
#include "guihelpers/widgets/statusicons.h"
#include "runtimeicons/leftarrowicon.h"
#include "runtimeicons/rightarrowicon.h"
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

    void stop() override;

    void buttonPressed(espgui::Button button) override
    {
        espgui::pushScreen<MainMenu>();
    }

private:
    static constexpr auto ICON_SPACING = 35;

    cpputils::DelayedConstruction<StatusIcons> m_statusIcons;
    cpputils::DelayedConstruction<runtimeicons::LeftArrowIcon> m_leftArrowIcon;
    cpputils::DelayedConstruction<runtimeicons::RightArrowIcon> m_rightArrowIcon;
};

} // namespace bicycle::gui