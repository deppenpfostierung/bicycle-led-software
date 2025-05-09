#include "startdisplay.h"

namespace bicycle::gui
{

void StartDisplay::initScreen(espgui::TftInterface &tft)
{
    Base::initScreen(tft);

    if (!m_statusIcons.constructed())
    {
        m_statusIcons.construct(static_cast<uint16_t>(tft.width() / 2), static_cast<uint16_t>(0), true);
    }

    if (m_statusIcons.constructed())
        m_statusIcons->init(tft);
}

void StartDisplay::redraw(espgui::TftInterface &tft)
{
    Base::redraw(tft);

    if (m_statusIcons.constructed())
        m_statusIcons->redraw(tft);
}

void StartDisplay::update()
{
    Base::update();

    if (m_statusIcons.constructed())
        m_statusIcons->update();
}

void StartDisplay::stop()
{
    Base::stop();

    if (m_statusIcons.constructed())
    {
        m_statusIcons->stop();
        m_statusIcons.destruct();
    }
}

} // namespace bicycle::gui