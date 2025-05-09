#include "startdisplay.h"

namespace bicycle::gui
{

void StartDisplay::initScreen(espgui::TftInterface &tft)
{
    Base::initScreen(tft);

    m_statusIcons.init(tft);
}

void StartDisplay::update()
{
    Base::update();

    m_statusIcons.update();
}

void StartDisplay::redraw(espgui::TftInterface &tft)
{
    Base::redraw(tft);

    m_statusIcons.redraw(tft);
}

} // namespace bicycle::gui