#pragma once

// local includes
#include "guihelpers/displaywithtitle.h"

namespace bicycle::gui
{

class ConfigureBasicButtonDisplay : public BicycleDisplayWithTitle
{
    using Base = BicycleDisplayWithTitle;

public:
    void start() override;

    void initScreen(espgui::TftInterface &tft) override;

    void update() override;

    void redraw(espgui::TftInterface &tft) override;

    std::string title() const override;
};

} // namespace bicycle::gui