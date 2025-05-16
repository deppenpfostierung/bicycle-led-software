#include "startdisplay.h"

namespace bicycle::gui
{

void StartDisplay::initScreen(espgui::TftInterface &tft)
{
    Base::initScreen(tft);

    const uint16_t baseX = tft.width() / 2;
    constexpr uint16_t baseY = 0;

    if (!m_statusIcons)
    {
        m_statusIcons.construct(baseX, baseY, true);
    }

    if (m_statusIcons)
        m_statusIcons->init(tft);

    const uint16_t leftArrowX = baseX - m_statusIcons->getWidth() / 2 - ICON_SPACING - 10;
    const uint16_t rightArrowX = baseX + m_statusIcons->getWidth() / 2 + ICON_SPACING - 10;

    const uint16_t arrowY = baseY + m_statusIcons->getHeight() / 2 - 10;

    if (!m_leftArrowIcon)
    {
        m_leftArrowIcon.construct(leftArrowX, arrowY);
    }

    if (m_leftArrowIcon)
        m_leftArrowIcon->init(tft);

    if (!m_rightArrowIcon)
    {
        m_rightArrowIcon.construct(rightArrowX, arrowY);
    }

    if (m_rightArrowIcon)
        m_rightArrowIcon->init(tft);
}

void StartDisplay::redraw(espgui::TftInterface &tft)
{
    Base::redraw(tft);

    if (m_statusIcons)
        m_statusIcons->redraw(tft);

    if (m_leftArrowIcon)
        m_leftArrowIcon->redraw(tft);

    if (m_rightArrowIcon)
        m_rightArrowIcon->redraw(tft);
}

void StartDisplay::update()
{
    Base::update();

    if (m_statusIcons)
        m_statusIcons->update();

    if (m_leftArrowIcon)
        m_leftArrowIcon->update();

    if (m_rightArrowIcon)
        m_rightArrowIcon->update();
}

void StartDisplay::stop()
{
    Base::stop();

    if (m_statusIcons)
    {
        m_statusIcons->stop();
        m_statusIcons.destruct();
    }

    if (m_leftArrowIcon)
    {
        m_leftArrowIcon.destruct();
    }

    if (m_rightArrowIcon)
    {
        m_rightArrowIcon.destruct();
    }
}

} // namespace bicycle::gui
