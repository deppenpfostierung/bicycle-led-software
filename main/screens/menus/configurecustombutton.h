#pragma once

// 3rdparty lib includes
#include <screenmanager.h>

// local includes
#include "configs.h"
#include "guihelpers/menudisplay.h"

namespace bicycle::gui
{

class ConfigureCustomButtonMenu : public BicycleMenuDisplay
{
    using Base = BicycleMenuDisplay;

public:
    explicit ConfigureCustomButtonMenu(DpadConfig *buttonCfg);

    void back() override
    {
        espgui::popScreen();
    }

    std::string title() const override;

    DpadConfig *buttonCfg;

    enum class MenuMode
    {
        DEFAULT,
        CALIBRATE,
    } menuMode;

    void rawButtonPressed(uint8_t button) override;

    std::optional<std::string> error_string;
};

} // namespace bicycle::gui