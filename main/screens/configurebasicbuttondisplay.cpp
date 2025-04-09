#include "configurebasicbuttondisplay.h"

namespace bicycle::gui
{

void ConfigureBasicButtonDisplay::start()
{
    Base::start();
}

void ConfigureBasicButtonDisplay::initScreen(espgui::TftInterface &tft)
{
    Base::initScreen(tft);
}

void ConfigureBasicButtonDisplay::update()
{
    Base::update();
}

void ConfigureBasicButtonDisplay::redraw(espgui::TftInterface &tft)
{
    Base::redraw(tft);
}

std::string ConfigureBasicButtonDisplay::title() const
{
    return "Configure basic buttons";
}

} // namespace bicycle::gui