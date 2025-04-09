#pragma once

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
    }

    std::string title() const override;
};

} // namespace bicycle::gui